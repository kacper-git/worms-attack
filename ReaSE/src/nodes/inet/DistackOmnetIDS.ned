package rease.nodes.inet;

//
// Compound module which adds TCP/IP layers to the attack detection
// system Distack (by Mayer|Gamer)
//
// This module uses IP_hack layer to copy incoming packets and analyze them
// in DistackOmnetModule. Original packets are forwarded as usually.


import rease.applications.ids.IDSModule;
import rease.applications.limiter.RateLimiter;
import rease.applications.flow.FlowExporter;
import inet.base.NotificationBoard;
import inet.linklayer.ethernet.EthernetInterface;
import inet.linklayer.ppp.PPPInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.RoutingTable;
import inet.transport.tcp.TCP;
import inet.transport.udp.UDP;
import inet.util.NAMTraceWriter;


//
// \IP router for attack detection
//
module DistackOmnetIDS
{
    parameters:
        @node();
        @display("b=664,475");
        string routingFile;
        bool raoOn;
        string configId;
    gates:
        inout pppg[];
        inout ethg[];
    submodules:
        namTrace: NAMTraceWriter {
            parameters:
                namid = -1; // auto
                @display("p=434,68;i=block/sink");
        }
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=68,68;i=block/control");
        }
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=190,68;i=block/table");
        }
        routingTable: RoutingTable {
            parameters:
                IPForward = true;
                routerId = "auto";
                routingFile = routingFile;
                @display("p=312,68;i=block/table");
        }
        networkLayer: NetworkLayer_hack {
            parameters:
                tracingOn = true;
                copyFlagOn = true;
                raoOn = raoOn;
                spoofingOn = false;
                @display("p=320,253;i=block/fork;q=queue");

            gates:
                ifIn[sizeof(pppg)+sizeof(ethg)];
                ifOut[sizeof(pppg)+sizeof(ethg)];
        }
        distack: DistackOmnetModule {
            parameters:
                @display("p=434,124;i=device/firewall");
                configId = configId;
        }
        tcp: TCP {
            parameters:
                @display("p=190,214;i=block/wheelbarrow");
        }
        udp: UDP {
            parameters:
                @display("p=445,205;i=block/transport");
        }
        ppp[sizeof(pppg)]: PPPInterface {
            parameters:
                @display("p=74,367,row,110;q=l2queue;i=block/ifcard");
        }
        eth[sizeof(ethg)]: EthernetInterface {
            parameters:
                @display("p=74,425,row,110;q=l2queue;i=block/ifcard");
        }
        flowExporter: FlowExporter {
            @display("p=190,125");
        }
        rateLimiter: RateLimiter {
            @display("p=320,367");
            gates:
                ifIn_ppp[sizeof(pppg)+sizeof(ethg)];
                ifOut_ppp[sizeof(pppg)+sizeof(ethg)];
                ifIn_network[sizeof(pppg)+sizeof(ethg)];
                ifOut_network[sizeof(pppg)+sizeof(ethg)];
        }
        idsModule: IDSModule {
            @display("p=312,125");
        }
    connections allowunconnected:
        // connections to network outside
        for i=0..sizeof(pppg)-1 {
            pppg[i] <--> ppp[i].phys;
            ppp[i].netwOut --> rateLimiter.ifIn_ppp[i];
            ppp[i].netwIn <-- rateLimiter.ifOut_ppp[i];
        }
        for i=0..sizeof(ethg)-1 {
            ethg[i] <--> eth[i].phys;
            eth[i].netwOut --> rateLimiter.ifIn_ppp[sizeof(pppg)+i];
            eth[i].netwIn <-- rateLimiter.ifOut_ppp[sizeof(pppg)+i];
        }

        for i=0..sizeof(pppg)+sizeof(ethg)-1 {
            rateLimiter.ifOut_network[i] --> networkLayer.ifIn[i];
            rateLimiter.ifIn_network[i] <-- networkLayer.ifOut[i];
        }

        tcp.ipOut --> networkLayer.tcpIn;
        tcp.ipIn <-- networkLayer.tcpOut;
        udp.ipOut --> networkLayer.udpIn;
        udp.ipIn <-- networkLayer.udpOut;

        tcp.appOut++ --> distack.sigIn++;
        tcp.appIn++ <-- distack.sigOutTCP;
        udp.appOut++ --> distack.sigIn++;
        udp.appIn++ <-- distack.sigOutUDP;

        networkLayer.raoOut --> distack.sigIn++;
        networkLayer.raoIn <-- distack.sigOutRAO;

        networkLayer.distackSigOut --> distack.sigIn++;
        networkLayer.distackSigIn <-- distack.sigOutIP;

        networkLayer.distackOut --> flowExporter.in;
        networkLayer.distackIn <-- distack.out;
        flowExporter.out --> udp.appIn++;
        flowExporter.distack --> idsModule.in;
        idsModule.distack --> distack.in;
        idsModule.out --> udp.appIn++;
        
        idsModule.toRateLimiter --> rateLimiter.fromIDS;
}
