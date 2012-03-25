import rease.nodes.inet.DistackOmnetIDS;
import rease.nodes.inet.Classifier;
import rease.nodes.inet.WormHost;
import inet.nodes.inet.Router;
import rease.nodes.inet.InetUserHost;
import rease.nodes.inet.BackupServer;
import rease.nodes.inet.NameServer;
import rease.nodes.inet.InteractiveServer;
import rease.nodes.inet.MailServer;
import rease.nodes.inet.WebServer;
import rease.nodes.inet.StreamingServer;
import rease.nodes.inet.TraceRouter;
import rease.base.ConnectionManager;
import rease.base.TrafficProfileManager;
import rease.networklayer.autorouting.TGMNetworkConfigurator;
import rease.applications.linkmonitor.LinkMonitor;

channel server2edge extends ned.DatarateChannel
{
    parameters:
        delay = 1us;
        datarate = 10Mbps;
}

channel host2edge extends ned.DatarateChannel
{
    parameters:
        delay = 1us;
        datarate = 0.128Mbps;
}
channel edge2host extends ned.DatarateChannel
{
    parameters:
        delay = 1us;
        datarate = 0.768Mbps;
}
channel edge2gateway extends ned.DatarateChannel
{
    parameters:
        delay = 1us;
        datarate = 155Mbps;
}
channel gateway2core extends ned.DatarateChannel
{
    parameters:
        delay = 1us;
        datarate = 1000Mbps;
}
channel core2core extends ned.DatarateChannel
{
    parameters:
        delay = 1us;
        datarate = 2500Mbps;
}
channel stub2stub extends ned.DatarateChannel
{
    parameters:
        delay = 1us;
        datarate = 5000Mbps;
}
channel stub2transit extends ned.DatarateChannel
{
    parameters:
        delay = 1us;
        datarate = 5000Mbps;
}
channel transit2transit extends ned.DatarateChannel
{
    parameters:
        delay = 1us;
        datarate = 10000Mbps;
}

module Internet
{
    parameters:
        @Internet();
    submodules:
        tgmNetworkConfigurator: TGMNetworkConfigurator {
            parameters:
                totalCountOfAS = 20;
                @display("p=20,20;i=abstract/table_s");
        }
        connectionManager: ConnectionManager {
            parameters:
                @display("p=60,20;i=block/classifier_s");
        }
        trafficProfileManager: TrafficProfileManager {
            parameters:
                @display("p=100,20;i=block/cogwheel_s");
        }

        sas0: SAS0 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas1: SAS1 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        tas2: TAS2 {
            parameters:
                @AS();
                @display("i=misc/globe_s");
        }
        tas3: TAS3 {
            parameters:
                @AS();
                @display("i=misc/globe_s");
        }
        tas4: TAS4 {
            parameters:
                @AS();
                @display("i=misc/globe_s");
        }
        sas5: SAS5 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        tas6: TAS6 {
            parameters:
                @AS();
                @display("i=misc/globe_s");
        }
        sas7: SAS7 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas8: SAS8 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        tas9: TAS9 {
            parameters:
                @AS();
                @display("i=misc/globe_s");
        }
        tas10: TAS10 {
            parameters:
                @AS();
                @display("i=misc/globe_s");
        }
        sas11: SAS11 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas12: SAS12 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas13: SAS13 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas14: SAS14 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas15: SAS15 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas16: SAS16 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas17: SAS17 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas18: SAS18 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas19: SAS19 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }

    connections:
        sas0.pppg++ <--> stub2stub <--> sas1.pppg++;
        sas0.pppg++ <--> stub2transit <--> tas2.pppg++;
        sas0.pppg++ <--> stub2stub <--> sas5.pppg++;
        sas0.pppg++ <--> stub2transit <--> tas6.pppg++;
        sas0.pppg++ <--> stub2stub <--> sas16.pppg++;
        sas1.pppg++ <--> stub2transit <--> tas2.pppg++;
        sas1.pppg++ <--> stub2transit <--> tas3.pppg++;
        sas1.pppg++ <--> stub2transit <--> tas10.pppg++;
        sas1.pppg++ <--> stub2transit <--> tas9.pppg++;
        tas2.pppg++ <--> transit2transit <--> tas3.pppg++;
        tas2.pppg++ <--> transit2transit <--> tas4.pppg++;
        tas2.pppg++ <--> transit2transit <--> tas6.pppg++;
        tas2.pppg++ <--> stub2transit <--> sas7.pppg++;
        tas2.pppg++ <--> transit2transit <--> tas9.pppg++;
        tas2.pppg++ <--> stub2transit <--> sas5.pppg++;
        tas2.pppg++ <--> stub2transit <--> sas12.pppg++;
        tas2.pppg++ <--> stub2transit <--> sas15.pppg++;
        tas2.pppg++ <--> transit2transit <--> tas10.pppg++;
        tas2.pppg++ <--> stub2transit <--> sas18.pppg++;
        tas3.pppg++ <--> transit2transit <--> tas4.pppg++;
        tas3.pppg++ <--> transit2transit <--> tas10.pppg++;
        tas3.pppg++ <--> stub2transit <--> sas12.pppg++;
        tas3.pppg++ <--> stub2transit <--> sas13.pppg++;
        tas4.pppg++ <--> stub2transit <--> sas5.pppg++;
        tas4.pppg++ <--> transit2transit <--> tas6.pppg++;
        tas4.pppg++ <--> stub2transit <--> sas11.pppg++;
        tas4.pppg++ <--> stub2transit <--> sas17.pppg++;
        tas4.pppg++ <--> stub2transit <--> sas14.pppg++;
        sas5.pppg++ <--> stub2transit <--> tas10.pppg++;
        tas6.pppg++ <--> stub2transit <--> sas8.pppg++;
        tas6.pppg++ <--> transit2transit <--> tas10.pppg++;
        tas6.pppg++ <--> stub2transit <--> sas14.pppg++;
        sas7.pppg++ <--> stub2transit <--> tas10.pppg++;
        tas9.pppg++ <--> stub2transit <--> sas19.pppg++;
        tas10.pppg++ <--> stub2transit <--> sas11.pppg++;
        tas10.pppg++ <--> stub2transit <--> sas14.pppg++;
        tas10.pppg++ <--> stub2transit <--> sas16.pppg++;
        sas11.pppg++ <--> stub2stub <--> sas13.pppg++;
        sas14.pppg++ <--> stub2stub <--> sas18.pppg++;
        sas18.pppg++ <--> stub2stub <--> sas19.pppg++;

}

network Inet extends Internet
{
    parameters:
}

module SAS0
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        gw2: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge10: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge11: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host12: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host13: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host15: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer16: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: Classifier {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost27: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost28: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost31: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host37: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost38: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer40: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost45: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer47: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host48: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer49: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host50: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost51: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host52: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host54: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host55: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost56: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host57: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host58: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host59: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host60: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host61: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host62: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost63: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer64: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host65: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host66: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host67: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host68: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host69: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host70: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost71: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host72: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost73: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host74: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host75: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        core0.pppg++ <--> gateway2core <--> gw2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge9.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge10.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge11.pppg++;
        host12.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host12.pppg$i++;
        host13.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host13.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host15.pppg$i++;
        host_InteractiveServer16.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_InteractiveServer16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host_WormHost27.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost27.pppg$i++;
        host_WormHost28.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host30.pppg$i++;
        host_WormHost31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host37.pppg$i++;
        host_WormHost38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host39.pppg$i++;
        host_WebServer40.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host_WebServer40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host44.pppg$i++;
        host_WormHost45.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host_WebServer47.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_WebServer47.pppg$i++;
        host48.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host48.pppg$i++;
        host_WebServer49.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_WebServer49.pppg$i++;
        host50.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host50.pppg$i++;
        host_WormHost51.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost51.pppg$i++;
        host52.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host53.pppg$i++;
        host54.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host54.pppg$i++;
        host55.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host55.pppg$i++;
        host_WormHost56.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost56.pppg$i++;
        host57.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host57.pppg$i++;
        host58.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host58.pppg$i++;
        host59.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host59.pppg$i++;
        host60.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host60.pppg$i++;
        host61.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host61.pppg$i++;
        host62.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host62.pppg$i++;
        host_WormHost63.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost63.pppg$i++;
        host_MailServer64.pppg$o++ --> server2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> server2edge --> host_MailServer64.pppg$i++;
        host65.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host65.pppg$i++;
        host66.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host66.pppg$i++;
        host67.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host67.pppg$i++;
        host68.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host68.pppg$i++;
        host69.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host69.pppg$i++;
        host70.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host70.pppg$i++;
        host_WormHost71.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host_WormHost71.pppg$i++;
        host72.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host72.pppg$i++;
        host_WormHost73.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host_WormHost73.pppg$i++;
        host74.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host74.pppg$i++;
        host75.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host75.pppg$i++;
}

module SAS1
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: DistackOmnetIDS {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2;p=328,296;b=86,28");
        }
        gw2: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge10: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge11: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host_WormHost12: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host13: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost15: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost20: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer21: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer24: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer27: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer28: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer31: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost37: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost40: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost41: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost44: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost48: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host50: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host51: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host52: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host54: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost55: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host56: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host57: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host58: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host59: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host60: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost61: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host62: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host63: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host64: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host65: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost66: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host67: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host68: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host69: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host70: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host71: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer72: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host73: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host74: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host75: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host76: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host77: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host78: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host79: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> LinkMonitor <--> gw1.pppg++;
        core0.pppg++ <--> gateway2core <--> gw2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge9.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge10.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge11.pppg++;
        host_WormHost12.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost12.pppg$i++;
        host13.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host13.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host14.pppg$i++;
        host_WormHost15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host_WormHost20.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost20.pppg$i++;
        host_WebServer21.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_WebServer21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host23.pppg$i++;
        host_WebServer24.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_WebServer24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host26.pppg$i++;
        host_InteractiveServer27.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_InteractiveServer27.pppg$i++;
        host_WebServer28.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> LinkMonitor --> host_WebServer28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host30.pppg$i++;
        host_WebServer31.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_WebServer31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host36.pppg$i++;
        host_WormHost37.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host39.pppg$i++;
        host_WormHost40.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost40.pppg$i++;
        host_WormHost41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host43.pppg$i++;
        host_WormHost44.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host47.pppg$i++;
        host_WormHost48.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host49.pppg$i++;
        host50.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host50.pppg$i++;
        host51.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host51.pppg$i++;
        host52.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host53.pppg$i++;
        host54.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host54.pppg$i++;
        host_WormHost55.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost55.pppg$i++;
        host56.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host56.pppg$i++;
        host57.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host57.pppg$i++;
        host58.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host58.pppg$i++;
        host59.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host59.pppg$i++;
        host60.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host60.pppg$i++;
        host_WormHost61.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost61.pppg$i++;
        host62.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host62.pppg$i++;
        host63.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host63.pppg$i++;
        host64.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host64.pppg$i++;
        host65.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host65.pppg$i++;
        host_WormHost66.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost66.pppg$i++;
        host67.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host67.pppg$i++;
        host68.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host68.pppg$i++;
        host69.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host69.pppg$i++;
        host70.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host70.pppg$i++;
        host71.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host71.pppg$i++;
        host_MailServer72.pppg$o++ --> server2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> server2edge --> host_MailServer72.pppg$i++;
        host73.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host73.pppg$i++;
        host74.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host74.pppg$i++;
        host75.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host75.pppg$i++;
        host76.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host76.pppg$i++;
        host77.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host77.pppg$i++;
        host78.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host78.pppg$i++;
        host79.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host79.pppg$i++;
}

module TAS2
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge2: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host8: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host9: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer10: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host11: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host12: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host13: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost14: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost15: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost18: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost25: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer30: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost31: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost33: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer35: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost37: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer40: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer48: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost50: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host51: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host52: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        host8.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host8.pppg$i++;
        host9.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host9.pppg$i++;
        host_WebServer10.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_WebServer10.pppg$i++;
        host11.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host11.pppg$i++;
        host12.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host12.pppg$i++;
        host13.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host13.pppg$i++;
        host_WormHost14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost14.pppg$i++;
        host_WormHost15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host_WormHost18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host_WormHost25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host29.pppg$i++;
        host_WebServer30.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_WebServer30.pppg$i++;
        host_WormHost31.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host_WormHost33.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host34.pppg$i++;
        host_InteractiveServer35.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_InteractiveServer35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host36.pppg$i++;
        host_WormHost37.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host39.pppg$i++;
        host_MailServer40.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_MailServer40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host47.pppg$i++;
        host_WebServer48.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host_WebServer48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host49.pppg$i++;
        host_WormHost50.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost50.pppg$i++;
        host51.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host51.pppg$i++;
        host52.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host52.pppg$i++;
}

module TAS3
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        gw2: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge10: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge11: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge12: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge13: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host15: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost17: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost18: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer21: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer29: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost33: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost35: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost37: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer38: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host40: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost41: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer44: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host48: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host50: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host51: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost52: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer53: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host54: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host55: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host56: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost57: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host58: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host59: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host60: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host61: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost62: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host63: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host64: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host65: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host66: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host67: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host68: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host69: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host70: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host71: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost72: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost73: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host74: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host75: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host76: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host77: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host78: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host79: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host80: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer81: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host82: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host83: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host84: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        core0.pppg++ <--> gateway2core <--> gw2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge9.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge10.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge11.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge12.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge13.pppg++;
        host14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host_WormHost17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost17.pppg$i++;
        host_WormHost18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host20.pppg$i++;
        host_MailServer21.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_MailServer21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host28.pppg$i++;
        host_InteractiveServer29.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_InteractiveServer29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host_WormHost33.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host34.pppg$i++;
        host_WormHost35.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host36.pppg$i++;
        host_WormHost37.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost37.pppg$i++;
        host_WebServer38.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host_WebServer38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host39.pppg$i++;
        host40.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host40.pppg$i++;
        host_WormHost41.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host43.pppg$i++;
        host_WebServer44.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_WebServer44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host47.pppg$i++;
        host48.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host49.pppg$i++;
        host50.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host50.pppg$i++;
        host51.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host51.pppg$i++;
        host_WormHost52.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost52.pppg$i++;
        host_WebServer53.pppg$o++ --> server2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> server2edge --> host_WebServer53.pppg$i++;
        host54.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host54.pppg$i++;
        host55.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host55.pppg$i++;
        host56.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host56.pppg$i++;
        host_WormHost57.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost57.pppg$i++;
        host58.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host58.pppg$i++;
        host59.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host59.pppg$i++;
        host60.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host60.pppg$i++;
        host61.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host61.pppg$i++;
        host_WormHost62.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost62.pppg$i++;
        host63.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host63.pppg$i++;
        host64.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host64.pppg$i++;
        host65.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host65.pppg$i++;
        host66.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host66.pppg$i++;
        host67.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host67.pppg$i++;
        host68.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host68.pppg$i++;
        host69.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host69.pppg$i++;
        host70.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host70.pppg$i++;
        host71.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host71.pppg$i++;
        host_WormHost72.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host_WormHost72.pppg$i++;
        host_WormHost73.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host_WormHost73.pppg$i++;
        host74.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host74.pppg$i++;
        host75.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host75.pppg$i++;
        host76.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host76.pppg$i++;
        host77.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host77.pppg$i++;
        host78.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host78.pppg$i++;
        host79.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host79.pppg$i++;
        host80.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host80.pppg$i++;
        host_WebServer81.pppg$o++ --> server2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> server2edge --> host_WebServer81.pppg$i++;
        host82.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host82.pppg$i++;
        host83.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host83.pppg$i++;
        host84.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host84.pppg$i++;
}

module TAS4
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge2: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host9: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer10: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host11: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host12: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host13: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host15: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost19: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer27: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost29: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer31: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost33: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer34: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host37: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host40: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost44: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer46: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost47: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost48: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host50: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host51: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost52: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost54: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host55: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        host9.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host9.pppg$i++;
        host_MailServer10.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_MailServer10.pppg$i++;
        host11.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host11.pppg$i++;
        host12.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host12.pppg$i++;
        host13.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host13.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host_WormHost19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host_WebServer27.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_WebServer27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host28.pppg$i++;
        host_WormHost29.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host30.pppg$i++;
        host_WebServer31.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_WebServer31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host_WormHost33.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost33.pppg$i++;
        host_InteractiveServer34.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_InteractiveServer34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host39.pppg$i++;
        host40.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host43.pppg$i++;
        host_WormHost44.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host45.pppg$i++;
        host_WebServer46.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host_WebServer46.pppg$i++;
        host_WormHost47.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost47.pppg$i++;
        host_WormHost48.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host49.pppg$i++;
        host50.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host50.pppg$i++;
        host51.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host51.pppg$i++;
        host_WormHost52.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host53.pppg$i++;
        host_WormHost54.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost54.pppg$i++;
        host55.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host55.pppg$i++;
}

module SAS5
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        gw2: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        gw3: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge10: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge11: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge12: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge13: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge14: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge15: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge16: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge17: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge18: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge19: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge20: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge21: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host_WormHost22: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer23: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer24: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost28: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost29: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer30: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost35: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost36: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer37: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer38: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost40: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost43: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer47: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost48: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer50: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host51: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost52: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost53: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host54: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host55: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost56: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost57: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_StreamingServer58: StreamingServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost59: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host60: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host61: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host62: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host63: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host64: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host65: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host66: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host67: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost68: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host69: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer70: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host71: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host72: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host73: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host74: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost75: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host76: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host77: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host78: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host79: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host80: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host81: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host82: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host83: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host84: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host85: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host86: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host87: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host88: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost89: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host90: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host91: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host92: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host93: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost94: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host95: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost96: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host97: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost98: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host99: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host100: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host101: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host102: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host103: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost104: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host105: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host106: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host107: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host108: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host109: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost110: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host111: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host112: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host113: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host114: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host115: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer116: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost117: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host118: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer119: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host120: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host121: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost122: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host123: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host124: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer125: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost126: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host127: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host128: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host129: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host130: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost131: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host132: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost133: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host134: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host135: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer136: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host137: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host138: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host139: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host140: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host141: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer142: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost143: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost144: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host145: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host146: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host147: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host148: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host149: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host150: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost151: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host152: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        core0.pppg++ <--> gateway2core <--> gw2.pppg++;
        core0.pppg++ <--> gateway2core <--> gw3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge9.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge10.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge11.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge12.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge13.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge14.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge15.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge16.pppg++;
        gw3.pppg++ <--> edge2gateway <--> edge17.pppg++;
        gw3.pppg++ <--> edge2gateway <--> edge18.pppg++;
        gw3.pppg++ <--> edge2gateway <--> edge19.pppg++;
        gw3.pppg++ <--> edge2gateway <--> edge20.pppg++;
        gw3.pppg++ <--> edge2gateway <--> edge21.pppg++;
        host_WormHost22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost22.pppg$i++;
        host_WebServer23.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_WebServer23.pppg$i++;
        host_InteractiveServer24.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_InteractiveServer24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host27.pppg$i++;
        host_WormHost28.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost28.pppg$i++;
        host_WormHost29.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost29.pppg$i++;
        host_WebServer30.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_WebServer30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host34.pppg$i++;
        host_WormHost35.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost35.pppg$i++;
        host_WormHost36.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost36.pppg$i++;
        host_InteractiveServer37.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_InteractiveServer37.pppg$i++;
        host_MailServer38.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_MailServer38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host39.pppg$i++;
        host_WormHost40.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host42.pppg$i++;
        host_WormHost43.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host_InteractiveServer47.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host_InteractiveServer47.pppg$i++;
        host_WormHost48.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host49.pppg$i++;
        host_MailServer50.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host_MailServer50.pppg$i++;
        host51.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host51.pppg$i++;
        host_WormHost52.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost52.pppg$i++;
        host_WormHost53.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost53.pppg$i++;
        host54.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host54.pppg$i++;
        host55.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host55.pppg$i++;
        host_WormHost56.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost56.pppg$i++;
        host_WormHost57.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost57.pppg$i++;
        host_StreamingServer58.pppg$o++ --> server2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> server2edge --> host_StreamingServer58.pppg$i++;
        host_WormHost59.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost59.pppg$i++;
        host60.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host60.pppg$i++;
        host61.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host61.pppg$i++;
        host62.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host62.pppg$i++;
        host63.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host63.pppg$i++;
        host64.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host64.pppg$i++;
        host65.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host65.pppg$i++;
        host66.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host66.pppg$i++;
        host67.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host67.pppg$i++;
        host_WormHost68.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost68.pppg$i++;
        host69.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host69.pppg$i++;
        host_WebServer70.pppg$o++ --> server2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> server2edge --> host_WebServer70.pppg$i++;
        host71.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host71.pppg$i++;
        host72.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host72.pppg$i++;
        host73.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host73.pppg$i++;
        host74.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host74.pppg$i++;
        host_WormHost75.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host_WormHost75.pppg$i++;
        host76.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host76.pppg$i++;
        host77.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host77.pppg$i++;
        host78.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host78.pppg$i++;
        host79.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host79.pppg$i++;
        host80.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host80.pppg$i++;
        host81.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host81.pppg$i++;
        host82.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host82.pppg$i++;
        host83.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host83.pppg$i++;
        host84.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host84.pppg$i++;
        host85.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host85.pppg$i++;
        host86.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host86.pppg$i++;
        host87.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host87.pppg$i++;
        host88.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host88.pppg$i++;
        host_WormHost89.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host_WormHost89.pppg$i++;
        host90.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host90.pppg$i++;
        host91.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host91.pppg$i++;
        host92.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host92.pppg$i++;
        host93.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host93.pppg$i++;
        host_WormHost94.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host_WormHost94.pppg$i++;
        host95.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host95.pppg$i++;
        host_WormHost96.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host_WormHost96.pppg$i++;
        host97.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host97.pppg$i++;
        host_WormHost98.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host_WormHost98.pppg$i++;
        host99.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host99.pppg$i++;
        host100.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host100.pppg$i++;
        host101.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host101.pppg$i++;
        host102.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host102.pppg$i++;
        host103.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host103.pppg$i++;
        host_WormHost104.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host_WormHost104.pppg$i++;
        host105.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host105.pppg$i++;
        host106.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host106.pppg$i++;
        host107.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host107.pppg$i++;
        host108.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host108.pppg$i++;
        host109.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host109.pppg$i++;
        host_WormHost110.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host_WormHost110.pppg$i++;
        host111.pppg$o++ --> host2edge --> edge16.pppg$i++;
        edge16.pppg$o++ --> edge2host --> host111.pppg$i++;
        host112.pppg$o++ --> host2edge --> edge16.pppg$i++;
        edge16.pppg$o++ --> edge2host --> host112.pppg$i++;
        host113.pppg$o++ --> host2edge --> edge16.pppg$i++;
        edge16.pppg$o++ --> edge2host --> host113.pppg$i++;
        host114.pppg$o++ --> host2edge --> edge16.pppg$i++;
        edge16.pppg$o++ --> edge2host --> host114.pppg$i++;
        host115.pppg$o++ --> host2edge --> edge16.pppg$i++;
        edge16.pppg$o++ --> edge2host --> host115.pppg$i++;
        host_WebServer116.pppg$o++ --> server2edge --> edge16.pppg$i++;
        edge16.pppg$o++ --> server2edge --> host_WebServer116.pppg$i++;
        host_WormHost117.pppg$o++ --> host2edge --> edge16.pppg$i++;
        edge16.pppg$o++ --> edge2host --> host_WormHost117.pppg$i++;
        host118.pppg$o++ --> host2edge --> edge16.pppg$i++;
        edge16.pppg$o++ --> edge2host --> host118.pppg$i++;
        host_WebServer119.pppg$o++ --> server2edge --> edge16.pppg$i++;
        edge16.pppg$o++ --> server2edge --> host_WebServer119.pppg$i++;
        host120.pppg$o++ --> host2edge --> edge17.pppg$i++;
        edge17.pppg$o++ --> edge2host --> host120.pppg$i++;
        host121.pppg$o++ --> host2edge --> edge17.pppg$i++;
        edge17.pppg$o++ --> edge2host --> host121.pppg$i++;
        host_WormHost122.pppg$o++ --> host2edge --> edge17.pppg$i++;
        edge17.pppg$o++ --> edge2host --> host_WormHost122.pppg$i++;
        host123.pppg$o++ --> host2edge --> edge17.pppg$i++;
        edge17.pppg$o++ --> edge2host --> host123.pppg$i++;
        host124.pppg$o++ --> host2edge --> edge17.pppg$i++;
        edge17.pppg$o++ --> edge2host --> host124.pppg$i++;
        host_MailServer125.pppg$o++ --> server2edge --> edge17.pppg$i++;
        edge17.pppg$o++ --> server2edge --> host_MailServer125.pppg$i++;
        host_WormHost126.pppg$o++ --> host2edge --> edge17.pppg$i++;
        edge17.pppg$o++ --> edge2host --> host_WormHost126.pppg$i++;
        host127.pppg$o++ --> host2edge --> edge18.pppg$i++;
        edge18.pppg$o++ --> edge2host --> host127.pppg$i++;
        host128.pppg$o++ --> host2edge --> edge18.pppg$i++;
        edge18.pppg$o++ --> edge2host --> host128.pppg$i++;
        host129.pppg$o++ --> host2edge --> edge18.pppg$i++;
        edge18.pppg$o++ --> edge2host --> host129.pppg$i++;
        host130.pppg$o++ --> host2edge --> edge18.pppg$i++;
        edge18.pppg$o++ --> edge2host --> host130.pppg$i++;
        host_WormHost131.pppg$o++ --> host2edge --> edge18.pppg$i++;
        edge18.pppg$o++ --> edge2host --> host_WormHost131.pppg$i++;
        host132.pppg$o++ --> host2edge --> edge19.pppg$i++;
        edge19.pppg$o++ --> edge2host --> host132.pppg$i++;
        host_WormHost133.pppg$o++ --> host2edge --> edge19.pppg$i++;
        edge19.pppg$o++ --> edge2host --> host_WormHost133.pppg$i++;
        host134.pppg$o++ --> host2edge --> edge19.pppg$i++;
        edge19.pppg$o++ --> edge2host --> host134.pppg$i++;
        host135.pppg$o++ --> host2edge --> edge19.pppg$i++;
        edge19.pppg$o++ --> edge2host --> host135.pppg$i++;
        host_WebServer136.pppg$o++ --> server2edge --> edge19.pppg$i++;
        edge19.pppg$o++ --> server2edge --> host_WebServer136.pppg$i++;
        host137.pppg$o++ --> host2edge --> edge19.pppg$i++;
        edge19.pppg$o++ --> edge2host --> host137.pppg$i++;
        host138.pppg$o++ --> host2edge --> edge19.pppg$i++;
        edge19.pppg$o++ --> edge2host --> host138.pppg$i++;
        host139.pppg$o++ --> host2edge --> edge20.pppg$i++;
        edge20.pppg$o++ --> edge2host --> host139.pppg$i++;
        host140.pppg$o++ --> host2edge --> edge20.pppg$i++;
        edge20.pppg$o++ --> edge2host --> host140.pppg$i++;
        host141.pppg$o++ --> host2edge --> edge20.pppg$i++;
        edge20.pppg$o++ --> edge2host --> host141.pppg$i++;
        host_WebServer142.pppg$o++ --> server2edge --> edge20.pppg$i++;
        edge20.pppg$o++ --> server2edge --> host_WebServer142.pppg$i++;
        host_WormHost143.pppg$o++ --> host2edge --> edge20.pppg$i++;
        edge20.pppg$o++ --> edge2host --> host_WormHost143.pppg$i++;
        host_WormHost144.pppg$o++ --> host2edge --> edge20.pppg$i++;
        edge20.pppg$o++ --> edge2host --> host_WormHost144.pppg$i++;
        host145.pppg$o++ --> host2edge --> edge20.pppg$i++;
        edge20.pppg$o++ --> edge2host --> host145.pppg$i++;
        host146.pppg$o++ --> host2edge --> edge21.pppg$i++;
        edge21.pppg$o++ --> edge2host --> host146.pppg$i++;
        host147.pppg$o++ --> host2edge --> edge21.pppg$i++;
        edge21.pppg$o++ --> edge2host --> host147.pppg$i++;
        host148.pppg$o++ --> host2edge --> edge21.pppg$i++;
        edge21.pppg$o++ --> edge2host --> host148.pppg$i++;
        host149.pppg$o++ --> host2edge --> edge21.pppg$i++;
        edge21.pppg$o++ --> edge2host --> host149.pppg$i++;
        host150.pppg$o++ --> host2edge --> edge21.pppg$i++;
        edge21.pppg$o++ --> edge2host --> host150.pppg$i++;
        host_WormHost151.pppg$o++ --> host2edge --> edge21.pppg$i++;
        edge21.pppg$o++ --> edge2host --> host_WormHost151.pppg$i++;
        host152.pppg$o++ --> host2edge --> edge21.pppg$i++;
        edge21.pppg$o++ --> edge2host --> host152.pppg$i++;
}

module TAS6
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        gw2: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge10: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge11: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge12: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge13: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge14: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host15: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer21: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost22: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost27: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost30: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost32: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host37: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer39: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer40: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost47: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost48: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost50: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost51: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host52: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host54: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host55: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost56: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer57: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host58: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host59: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host60: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host61: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host62: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host63: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer64: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host65: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host66: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host67: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host68: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host69: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost70: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer71: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host72: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host73: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host74: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host75: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host76: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host77: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost78: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host79: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer80: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host81: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost82: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost83: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host84: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost85: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host86: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host87: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host88: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost89: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host90: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host91: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host92: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host93: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host94: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host95: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host96: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host97: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost98: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host99: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host100: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host101: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host102: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer103: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer104: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host105: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost106: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        core0.pppg++ <--> gateway2core <--> gw2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge9.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge10.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge11.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge12.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge13.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge14.pppg++;
        host15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host20.pppg$i++;
        host_WebServer21.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_WebServer21.pppg$i++;
        host_WormHost22.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host_WormHost27.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host29.pppg$i++;
        host_WormHost30.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host31.pppg$i++;
        host_WormHost32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host38.pppg$i++;
        host_WebServer39.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_WebServer39.pppg$i++;
        host_InteractiveServer40.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_InteractiveServer40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host_WormHost47.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost47.pppg$i++;
        host_WormHost48.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host49.pppg$i++;
        host_WormHost50.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost50.pppg$i++;
        host_WormHost51.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost51.pppg$i++;
        host52.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host53.pppg$i++;
        host54.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host54.pppg$i++;
        host55.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host55.pppg$i++;
        host_WormHost56.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost56.pppg$i++;
        host_InteractiveServer57.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_InteractiveServer57.pppg$i++;
        host58.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host58.pppg$i++;
        host59.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host59.pppg$i++;
        host60.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host60.pppg$i++;
        host61.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host61.pppg$i++;
        host62.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host62.pppg$i++;
        host63.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host63.pppg$i++;
        host_WebServer64.pppg$o++ --> server2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> server2edge --> host_WebServer64.pppg$i++;
        host65.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host65.pppg$i++;
        host66.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host66.pppg$i++;
        host67.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host67.pppg$i++;
        host68.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host68.pppg$i++;
        host69.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host69.pppg$i++;
        host_WormHost70.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost70.pppg$i++;
        host_WebServer71.pppg$o++ --> server2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> server2edge --> host_WebServer71.pppg$i++;
        host72.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host72.pppg$i++;
        host73.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host73.pppg$i++;
        host74.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host74.pppg$i++;
        host75.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host75.pppg$i++;
        host76.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host76.pppg$i++;
        host77.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host77.pppg$i++;
        host_WormHost78.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host_WormHost78.pppg$i++;
        host79.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host79.pppg$i++;
        host_MailServer80.pppg$o++ --> server2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> server2edge --> host_MailServer80.pppg$i++;
        host81.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host81.pppg$i++;
        host_WormHost82.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost82.pppg$i++;
        host_WormHost83.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost83.pppg$i++;
        host84.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host84.pppg$i++;
        host_WormHost85.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost85.pppg$i++;
        host86.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host86.pppg$i++;
        host87.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host87.pppg$i++;
        host88.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host88.pppg$i++;
        host_WormHost89.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host_WormHost89.pppg$i++;
        host90.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host90.pppg$i++;
        host91.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host91.pppg$i++;
        host92.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host92.pppg$i++;
        host93.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host93.pppg$i++;
        host94.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host94.pppg$i++;
        host95.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host95.pppg$i++;
        host96.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host96.pppg$i++;
        host97.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host97.pppg$i++;
        host_WormHost98.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host_WormHost98.pppg$i++;
        host99.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host99.pppg$i++;
        host100.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host100.pppg$i++;
        host101.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host101.pppg$i++;
        host102.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host102.pppg$i++;
        host_MailServer103.pppg$o++ --> server2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> server2edge --> host_MailServer103.pppg$i++;
        host_WebServer104.pppg$o++ --> server2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> server2edge --> host_WebServer104.pppg$i++;
        host105.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host105.pppg$i++;
        host_WormHost106.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host_WormHost106.pppg$i++;
}

module SAS7
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge2: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host_WebServer7: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host8: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer9: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host10: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host11: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host12: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host13: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host15: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost16: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost17: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer19: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer20: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost23: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost25: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost28: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost29: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host37: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost39: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        host_WebServer7.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_WebServer7.pppg$i++;
        host8.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host8.pppg$i++;
        host_WebServer9.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_WebServer9.pppg$i++;
        host10.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host10.pppg$i++;
        host11.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host11.pppg$i++;
        host12.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host12.pppg$i++;
        host13.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host13.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host15.pppg$i++;
        host_WormHost16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost16.pppg$i++;
        host_WormHost17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host_MailServer19.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_MailServer19.pppg$i++;
        host_InteractiveServer20.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_InteractiveServer20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host_WormHost23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host_WormHost25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host27.pppg$i++;
        host_WormHost28.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost28.pppg$i++;
        host_WormHost29.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host38.pppg$i++;
        host_WormHost39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost39.pppg$i++;
}

module SAS8
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge2: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host9: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost10: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host11: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost12: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host13: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost14: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost15: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost19: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost24: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer27: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost28: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer32: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer33: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost35: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost36: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer37: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost38: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost39: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost40: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer44: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost48: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host50: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host51: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host52: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        host9.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host9.pppg$i++;
        host_WormHost10.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost10.pppg$i++;
        host11.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host11.pppg$i++;
        host_WormHost12.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost12.pppg$i++;
        host13.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host13.pppg$i++;
        host_WormHost14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost14.pppg$i++;
        host_WormHost15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host_WormHost19.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host23.pppg$i++;
        host_WormHost24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host_MailServer27.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_MailServer27.pppg$i++;
        host_WormHost28.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
        host_WebServer32.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_WebServer32.pppg$i++;
        host_InteractiveServer33.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_InteractiveServer33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host34.pppg$i++;
        host_WormHost35.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost35.pppg$i++;
        host_WormHost36.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost36.pppg$i++;
        host_WebServer37.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_WebServer37.pppg$i++;
        host_WormHost38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost38.pppg$i++;
        host_WormHost39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost39.pppg$i++;
        host_WormHost40.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host43.pppg$i++;
        host_WebServer44.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host_WebServer44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host47.pppg$i++;
        host_WormHost48.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host49.pppg$i++;
        host50.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host50.pppg$i++;
        host51.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host51.pppg$i++;
        host52.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host53.pppg$i++;
}

module TAS9
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        gw2: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge10: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge11: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge12: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge13: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host15: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer16: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost31: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost33: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer34: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host37: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer38: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host40: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer45: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host48: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer49: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost50: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost51: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host52: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host54: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host55: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host56: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host57: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host58: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer59: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host60: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host61: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost62: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost63: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host64: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost65: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host66: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost67: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host68: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host69: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost70: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host71: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost72: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer73: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host74: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost75: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host76: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host77: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host78: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost79: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host80: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost81: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host82: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host83: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host84: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer85: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host86: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host87: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host88: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host89: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host90: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host91: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost92: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host93: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        core0.pppg++ <--> gateway2core <--> gw2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge9.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge10.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge11.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge12.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge13.pppg++;
        host14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host15.pppg$i++;
        host_WebServer16.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_WebServer16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host30.pppg$i++;
        host_WormHost31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host_WormHost33.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost33.pppg$i++;
        host_WebServer34.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_WebServer34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host37.pppg$i++;
        host_MailServer38.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_MailServer38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host39.pppg$i++;
        host40.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host44.pppg$i++;
        host_MailServer45.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host_MailServer45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host47.pppg$i++;
        host48.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host48.pppg$i++;
        host_WebServer49.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host_WebServer49.pppg$i++;
        host_WormHost50.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost50.pppg$i++;
        host_WormHost51.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost51.pppg$i++;
        host52.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host53.pppg$i++;
        host54.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host54.pppg$i++;
        host55.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host55.pppg$i++;
        host56.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host56.pppg$i++;
        host57.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host57.pppg$i++;
        host58.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host58.pppg$i++;
        host_WebServer59.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_WebServer59.pppg$i++;
        host60.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host60.pppg$i++;
        host61.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host61.pppg$i++;
        host_WormHost62.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost62.pppg$i++;
        host_WormHost63.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost63.pppg$i++;
        host64.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host64.pppg$i++;
        host_WormHost65.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost65.pppg$i++;
        host66.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host66.pppg$i++;
        host_WormHost67.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost67.pppg$i++;
        host68.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host68.pppg$i++;
        host69.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host69.pppg$i++;
        host_WormHost70.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost70.pppg$i++;
        host71.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host71.pppg$i++;
        host_WormHost72.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost72.pppg$i++;
        host_InteractiveServer73.pppg$o++ --> server2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> server2edge --> host_InteractiveServer73.pppg$i++;
        host74.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host74.pppg$i++;
        host_WormHost75.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host_WormHost75.pppg$i++;
        host76.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host76.pppg$i++;
        host77.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host77.pppg$i++;
        host78.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host78.pppg$i++;
        host_WormHost79.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost79.pppg$i++;
        host80.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host80.pppg$i++;
        host_WormHost81.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost81.pppg$i++;
        host82.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host82.pppg$i++;
        host83.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host83.pppg$i++;
        host84.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host84.pppg$i++;
        host_InteractiveServer85.pppg$o++ --> server2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> server2edge --> host_InteractiveServer85.pppg$i++;
        host86.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host86.pppg$i++;
        host87.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host87.pppg$i++;
        host88.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host88.pppg$i++;
        host89.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host89.pppg$i++;
        host90.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host90.pppg$i++;
        host91.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host91.pppg$i++;
        host_WormHost92.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host_WormHost92.pppg$i++;
        host93.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host93.pppg$i++;
}

module TAS10
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge2: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host7: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host8: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost9: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host10: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host11: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host12: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host13: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost15: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost25: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer26: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer33: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host37: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host40: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer43: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer44: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        host7.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host7.pppg$i++;
        host8.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host8.pppg$i++;
        host_WormHost9.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost9.pppg$i++;
        host10.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host10.pppg$i++;
        host11.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host11.pppg$i++;
        host12.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host12.pppg$i++;
        host13.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host13.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host14.pppg$i++;
        host_WormHost15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host_WormHost25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost25.pppg$i++;
        host_WebServer26.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_WebServer26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host_WebServer33.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_WebServer33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host39.pppg$i++;
        host40.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host42.pppg$i++;
        host_InteractiveServer43.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_InteractiveServer43.pppg$i++;
        host_MailServer44.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_MailServer44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host46.pppg$i++;
}

module SAS11
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge2: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host8: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer9: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host10: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host11: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer12: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost13: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer14: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost15: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost17: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer18: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost23: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost30: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host37: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost40: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost43: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost44: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer45: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host48: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host50: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost51: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost52: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host54: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host55: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host56: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host57: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host58: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host59: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        host8.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host8.pppg$i++;
        host_MailServer9.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_MailServer9.pppg$i++;
        host10.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host10.pppg$i++;
        host11.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host11.pppg$i++;
        host_WebServer12.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_WebServer12.pppg$i++;
        host_WormHost13.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost13.pppg$i++;
        host_InteractiveServer14.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_InteractiveServer14.pppg$i++;
        host_WormHost15.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host16.pppg$i++;
        host_WormHost17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost17.pppg$i++;
        host_WebServer18.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_WebServer18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host22.pppg$i++;
        host_WormHost23.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host29.pppg$i++;
        host_WormHost30.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host39.pppg$i++;
        host_WormHost40.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host42.pppg$i++;
        host_WormHost43.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost43.pppg$i++;
        host_WormHost44.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost44.pppg$i++;
        host_WebServer45.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_WebServer45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host47.pppg$i++;
        host48.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host49.pppg$i++;
        host50.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host50.pppg$i++;
        host_WormHost51.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost51.pppg$i++;
        host_WormHost52.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host53.pppg$i++;
        host54.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host54.pppg$i++;
        host55.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host55.pppg$i++;
        host56.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host56.pppg$i++;
        host57.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host57.pppg$i++;
        host58.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host58.pppg$i++;
        host59.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host59.pppg$i++;
}

module SAS12
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge2: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host_InteractiveServer6: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost7: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host8: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host9: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost10: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost11: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host12: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host13: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost14: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host15: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer19: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer20: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer22: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost26: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost30: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        host_InteractiveServer6.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_InteractiveServer6.pppg$i++;
        host_WormHost7.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost7.pppg$i++;
        host8.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host8.pppg$i++;
        host9.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host9.pppg$i++;
        host_WormHost10.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost10.pppg$i++;
        host_WormHost11.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost11.pppg$i++;
        host12.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host12.pppg$i++;
        host13.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host13.pppg$i++;
        host_WormHost14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host18.pppg$i++;
        host_WebServer19.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_WebServer19.pppg$i++;
        host_MailServer20.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_MailServer20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host21.pppg$i++;
        host_WebServer22.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_WebServer22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host25.pppg$i++;
        host_WormHost26.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host29.pppg$i++;
        host_WormHost30.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
}

module SAS13
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge2: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host7: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost8: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host9: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host10: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host11: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host12: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost13: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host15: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost16: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer23: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost30: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost34: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost36: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host37: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost40: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer43: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer45: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer46: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        host7.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host7.pppg$i++;
        host_WormHost8.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost8.pppg$i++;
        host9.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host9.pppg$i++;
        host10.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host10.pppg$i++;
        host11.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host11.pppg$i++;
        host12.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host12.pppg$i++;
        host_WormHost13.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost13.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host15.pppg$i++;
        host_WormHost16.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host22.pppg$i++;
        host_WebServer23.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_WebServer23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host29.pppg$i++;
        host_WormHost30.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host33.pppg$i++;
        host_WormHost34.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host35.pppg$i++;
        host_WormHost36.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host39.pppg$i++;
        host_WormHost40.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host42.pppg$i++;
        host_WebServer43.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_WebServer43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host44.pppg$i++;
        host_MailServer45.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_MailServer45.pppg$i++;
        host_InteractiveServer46.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_InteractiveServer46.pppg$i++;
}

module SAS14
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge2: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host10: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost11: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host12: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost13: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host15: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost16: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer17: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost20: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer26: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer30: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost34: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer37: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host40: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost41: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host48: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host50: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost51: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host52: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost54: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost55: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer56: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host57: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost58: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost59: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost60: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host61: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host62: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host63: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host64: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge9.pppg++;
        host10.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host10.pppg$i++;
        host_WormHost11.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost11.pppg$i++;
        host12.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host12.pppg$i++;
        host_WormHost13.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost13.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host15.pppg$i++;
        host_WormHost16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost16.pppg$i++;
        host_InteractiveServer17.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_InteractiveServer17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host_WormHost20.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host25.pppg$i++;
        host_WebServer26.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_WebServer26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host29.pppg$i++;
        host_MailServer30.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_MailServer30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host33.pppg$i++;
        host_WormHost34.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host36.pppg$i++;
        host_WebServer37.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_WebServer37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host39.pppg$i++;
        host40.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host40.pppg$i++;
        host_WormHost41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host47.pppg$i++;
        host48.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host49.pppg$i++;
        host50.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host50.pppg$i++;
        host_WormHost51.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost51.pppg$i++;
        host52.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host53.pppg$i++;
        host_WormHost54.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost54.pppg$i++;
        host_WormHost55.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost55.pppg$i++;
        host_WebServer56.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_WebServer56.pppg$i++;
        host57.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host57.pppg$i++;
        host_WormHost58.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost58.pppg$i++;
        host_WormHost59.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost59.pppg$i++;
        host_WormHost60.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost60.pppg$i++;
        host61.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host61.pppg$i++;
        host62.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host62.pppg$i++;
        host63.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host63.pppg$i++;
        host64.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host64.pppg$i++;
}

module SAS15
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        gw2: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge10: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge11: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge12: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host_WormHost13: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer14: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host15: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer16: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost17: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer19: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer27: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer30: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost33: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost34: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost35: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host37: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host40: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer44: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host48: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost50: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost51: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost52: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host54: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host55: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host56: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host57: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host58: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host59: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer60: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host61: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host62: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost63: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host64: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host65: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer66: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost67: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost68: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost69: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host70: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host71: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host72: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host73: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host74: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host75: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host76: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost77: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host78: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host79: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host80: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host81: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host82: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host83: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host84: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost85: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host86: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost87: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host88: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host89: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host90: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost91: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost92: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        core0.pppg++ <--> gateway2core <--> gw2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge9.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge10.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge11.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge12.pppg++;
        host_WormHost13.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost13.pppg$i++;
        host_WebServer14.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_WebServer14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host15.pppg$i++;
        host_InteractiveServer16.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_InteractiveServer16.pppg$i++;
        host_WormHost17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host_MailServer19.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_MailServer19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host_WebServer27.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_WebServer27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host29.pppg$i++;
        host_WebServer30.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_WebServer30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host_WormHost33.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost33.pppg$i++;
        host_WormHost34.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost34.pppg$i++;
        host_WormHost35.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host39.pppg$i++;
        host40.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host43.pppg$i++;
        host_WebServer44.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_WebServer44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host47.pppg$i++;
        host48.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host49.pppg$i++;
        host_WormHost50.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost50.pppg$i++;
        host_WormHost51.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost51.pppg$i++;
        host_WormHost52.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host53.pppg$i++;
        host54.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host54.pppg$i++;
        host55.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host55.pppg$i++;
        host56.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host56.pppg$i++;
        host57.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host57.pppg$i++;
        host58.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host58.pppg$i++;
        host59.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host59.pppg$i++;
        host_MailServer60.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_MailServer60.pppg$i++;
        host61.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host61.pppg$i++;
        host62.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host62.pppg$i++;
        host_WormHost63.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost63.pppg$i++;
        host64.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host64.pppg$i++;
        host65.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host65.pppg$i++;
        host_InteractiveServer66.pppg$o++ --> server2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> server2edge --> host_InteractiveServer66.pppg$i++;
        host_WormHost67.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost67.pppg$i++;
        host_WormHost68.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost68.pppg$i++;
        host_WormHost69.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost69.pppg$i++;
        host70.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host70.pppg$i++;
        host71.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host71.pppg$i++;
        host72.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host72.pppg$i++;
        host73.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host73.pppg$i++;
        host74.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host74.pppg$i++;
        host75.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host75.pppg$i++;
        host76.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host76.pppg$i++;
        host_WormHost77.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost77.pppg$i++;
        host78.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host78.pppg$i++;
        host79.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host79.pppg$i++;
        host80.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host80.pppg$i++;
        host81.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host81.pppg$i++;
        host82.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host82.pppg$i++;
        host83.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host83.pppg$i++;
        host84.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host84.pppg$i++;
        host_WormHost85.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost85.pppg$i++;
        host86.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host86.pppg$i++;
        host_WormHost87.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost87.pppg$i++;
        host88.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host88.pppg$i++;
        host89.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host89.pppg$i++;
        host90.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host90.pppg$i++;
        host_WormHost91.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost91.pppg$i++;
        host_WormHost92.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost92.pppg$i++;
}

module SAS16
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        gw2: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge10: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge11: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge12: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge13: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge14: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host_WebServer15: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost18: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost21: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost22: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost29: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer30: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost35: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer37: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost40: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer42: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost47: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host48: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost49: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host50: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host51: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host52: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost54: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer55: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host56: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host57: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost58: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost59: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host60: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host61: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host62: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer63: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host64: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host65: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host66: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host67: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost68: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host69: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host70: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host71: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host72: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer73: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost74: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host75: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host76: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host77: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host78: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host79: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host80: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host81: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host82: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host83: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host84: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host85: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host86: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host87: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host88: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host89: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer90: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host91: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer92: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host93: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host94: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host95: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost96: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host97: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host98: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host99: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        core0.pppg++ <--> gateway2core <--> gw2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge9.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge10.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge11.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge12.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge13.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge14.pppg++;
        host_WebServer15.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_WebServer15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host_WormHost18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host20.pppg$i++;
        host_WormHost21.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost21.pppg$i++;
        host_WormHost22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host28.pppg$i++;
        host_WormHost29.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost29.pppg$i++;
        host_InteractiveServer30.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_InteractiveServer30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host34.pppg$i++;
        host_WormHost35.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host36.pppg$i++;
        host_WebServer37.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_WebServer37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host39.pppg$i++;
        host_WormHost40.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host41.pppg$i++;
        host_WebServer42.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host_WebServer42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host46.pppg$i++;
        host_WormHost47.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost47.pppg$i++;
        host48.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host48.pppg$i++;
        host_WormHost49.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost49.pppg$i++;
        host50.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host50.pppg$i++;
        host51.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host51.pppg$i++;
        host52.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host53.pppg$i++;
        host_WormHost54.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost54.pppg$i++;
        host_MailServer55.pppg$o++ --> server2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> server2edge --> host_MailServer55.pppg$i++;
        host56.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host56.pppg$i++;
        host57.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host57.pppg$i++;
        host_WormHost58.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost58.pppg$i++;
        host_WormHost59.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost59.pppg$i++;
        host60.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host60.pppg$i++;
        host61.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host61.pppg$i++;
        host62.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host62.pppg$i++;
        host_InteractiveServer63.pppg$o++ --> server2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> server2edge --> host_InteractiveServer63.pppg$i++;
        host64.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host64.pppg$i++;
        host65.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host65.pppg$i++;
        host66.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host66.pppg$i++;
        host67.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host67.pppg$i++;
        host_WormHost68.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host_WormHost68.pppg$i++;
        host69.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host69.pppg$i++;
        host70.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host70.pppg$i++;
        host71.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host71.pppg$i++;
        host72.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host72.pppg$i++;
        host_MailServer73.pppg$o++ --> server2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> server2edge --> host_MailServer73.pppg$i++;
        host_WormHost74.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost74.pppg$i++;
        host75.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host75.pppg$i++;
        host76.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host76.pppg$i++;
        host77.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host77.pppg$i++;
        host78.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host78.pppg$i++;
        host79.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host79.pppg$i++;
        host80.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host80.pppg$i++;
        host81.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host81.pppg$i++;
        host82.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host82.pppg$i++;
        host83.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host83.pppg$i++;
        host84.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host84.pppg$i++;
        host85.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host85.pppg$i++;
        host86.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host86.pppg$i++;
        host87.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host87.pppg$i++;
        host88.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host88.pppg$i++;
        host89.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host89.pppg$i++;
        host_WebServer90.pppg$o++ --> server2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> server2edge --> host_WebServer90.pppg$i++;
        host91.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host91.pppg$i++;
        host_WebServer92.pppg$o++ --> server2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> server2edge --> host_WebServer92.pppg$i++;
        host93.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host93.pppg$i++;
        host94.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host94.pppg$i++;
        host95.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host95.pppg$i++;
        host_WormHost96.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host_WormHost96.pppg$i++;
        host97.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host97.pppg$i++;
        host98.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host98.pppg$i++;
        host99.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host99.pppg$i++;
}

module SAS17
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        gw2: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge10: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge11: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge12: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host13: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost15: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost23: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer24: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost27: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost33: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost37: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host40: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host48: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer49: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer50: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer51: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host52: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost53: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host54: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost55: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host56: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host57: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host58: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost59: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host60: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost61: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer62: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host63: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost64: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host65: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer66: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host67: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host68: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host69: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host70: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host71: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host72: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host73: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host74: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host75: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost76: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host77: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost78: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host79: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host80: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host81: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        core0.pppg++ <--> gateway2core <--> gw2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge9.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge10.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge11.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge12.pppg++;
        host13.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host13.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host14.pppg$i++;
        host_WormHost15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host_WormHost23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost23.pppg$i++;
        host_WebServer24.pppg$o++ --> server2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> server2edge --> host_WebServer24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host_WormHost27.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host_WormHost33.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host36.pppg$i++;
        host_WormHost37.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host39.pppg$i++;
        host40.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host47.pppg$i++;
        host48.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host48.pppg$i++;
        host_WebServer49.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_WebServer49.pppg$i++;
        host_InteractiveServer50.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_InteractiveServer50.pppg$i++;
        host_WebServer51.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_WebServer51.pppg$i++;
        host52.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host52.pppg$i++;
        host_WormHost53.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost53.pppg$i++;
        host54.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host54.pppg$i++;
        host_WormHost55.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost55.pppg$i++;
        host56.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host56.pppg$i++;
        host57.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host57.pppg$i++;
        host58.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host58.pppg$i++;
        host_WormHost59.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost59.pppg$i++;
        host60.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host60.pppg$i++;
        host_WormHost61.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost61.pppg$i++;
        host_WebServer62.pppg$o++ --> server2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> server2edge --> host_WebServer62.pppg$i++;
        host63.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host63.pppg$i++;
        host_WormHost64.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost64.pppg$i++;
        host65.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host65.pppg$i++;
        host_MailServer66.pppg$o++ --> server2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> server2edge --> host_MailServer66.pppg$i++;
        host67.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host67.pppg$i++;
        host68.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host68.pppg$i++;
        host69.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host69.pppg$i++;
        host70.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host70.pppg$i++;
        host71.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host71.pppg$i++;
        host72.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host72.pppg$i++;
        host73.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host73.pppg$i++;
        host74.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host74.pppg$i++;
        host75.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host75.pppg$i++;
        host_WormHost76.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host_WormHost76.pppg$i++;
        host77.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host77.pppg$i++;
        host_WormHost78.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host_WormHost78.pppg$i++;
        host79.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host79.pppg$i++;
        host80.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host80.pppg$i++;
        host81.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host81.pppg$i++;
}

module SAS18
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        gw2: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge9: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge10: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge11: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge12: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge13: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge14: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge15: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host_WormHost16: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host18: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host20: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host24: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host25: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host29: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer35: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host37: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host38: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host39: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host40: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost41: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost45: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost48: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host50: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host51: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host52: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host54: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost55: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host56: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host57: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost58: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host59: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost60: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost61: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer62: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost63: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost64: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host65: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host66: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host67: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host68: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host69: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host70: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host71: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost72: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host73: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host74: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host75: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host76: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host77: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost78: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost79: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host80: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host81: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host82: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host83: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host84: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host85: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host86: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer87: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host88: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host89: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost90: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host91: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer92: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host93: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host94: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost95: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost96: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host97: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer98: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host99: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer100: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host101: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host102: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host103: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer104: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer105: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer106: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost107: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost108: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        core0.pppg++ <--> gateway2core <--> gw2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge9.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge10.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge11.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge12.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge13.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge14.pppg++;
        gw2.pppg++ <--> edge2gateway <--> edge15.pppg++;
        host_WormHost16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host34.pppg$i++;
        host_InteractiveServer35.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host_InteractiveServer35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host39.pppg$i++;
        host40.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host40.pppg$i++;
        host_WormHost41.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host_WormHost41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host44.pppg$i++;
        host_WormHost45.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host47.pppg$i++;
        host_WormHost48.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host49.pppg$i++;
        host50.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host50.pppg$i++;
        host51.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host51.pppg$i++;
        host52.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host53.pppg$i++;
        host54.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host54.pppg$i++;
        host_WormHost55.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost55.pppg$i++;
        host56.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host56.pppg$i++;
        host57.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host57.pppg$i++;
        host_WormHost58.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost58.pppg$i++;
        host59.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host59.pppg$i++;
        host_WormHost60.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost60.pppg$i++;
        host_WormHost61.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host_WormHost61.pppg$i++;
        host_WebServer62.pppg$o++ --> server2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> server2edge --> host_WebServer62.pppg$i++;
        host_WormHost63.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost63.pppg$i++;
        host_WormHost64.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost64.pppg$i++;
        host65.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host65.pppg$i++;
        host66.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host66.pppg$i++;
        host67.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host67.pppg$i++;
        host68.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host68.pppg$i++;
        host69.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host69.pppg$i++;
        host70.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host70.pppg$i++;
        host71.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host71.pppg$i++;
        host_WormHost72.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host_WormHost72.pppg$i++;
        host73.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host73.pppg$i++;
        host74.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host74.pppg$i++;
        host75.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host75.pppg$i++;
        host76.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host76.pppg$i++;
        host77.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host77.pppg$i++;
        host_WormHost78.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host_WormHost78.pppg$i++;
        host_WormHost79.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host_WormHost79.pppg$i++;
        host80.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host80.pppg$i++;
        host81.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host81.pppg$i++;
        host82.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host82.pppg$i++;
        host83.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host83.pppg$i++;
        host84.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host84.pppg$i++;
        host85.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host85.pppg$i++;
        host86.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host86.pppg$i++;
        host_WebServer87.pppg$o++ --> server2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> server2edge --> host_WebServer87.pppg$i++;
        host88.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host88.pppg$i++;
        host89.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host89.pppg$i++;
        host_WormHost90.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host_WormHost90.pppg$i++;
        host91.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host91.pppg$i++;
        host_WebServer92.pppg$o++ --> server2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> server2edge --> host_WebServer92.pppg$i++;
        host93.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host93.pppg$i++;
        host94.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host94.pppg$i++;
        host_WormHost95.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host_WormHost95.pppg$i++;
        host_WormHost96.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host_WormHost96.pppg$i++;
        host97.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host97.pppg$i++;
        host_WebServer98.pppg$o++ --> server2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> server2edge --> host_WebServer98.pppg$i++;
        host99.pppg$o++ --> host2edge --> edge14.pppg$i++;
        edge14.pppg$o++ --> edge2host --> host99.pppg$i++;
        host_MailServer100.pppg$o++ --> server2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> server2edge --> host_MailServer100.pppg$i++;
        host101.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host101.pppg$i++;
        host102.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host102.pppg$i++;
        host103.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host103.pppg$i++;
        host_InteractiveServer104.pppg$o++ --> server2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> server2edge --> host_InteractiveServer104.pppg$i++;
        host_MailServer105.pppg$o++ --> server2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> server2edge --> host_MailServer105.pppg$i++;
        host_WebServer106.pppg$o++ --> server2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> server2edge --> host_WebServer106.pppg$i++;
        host_WormHost107.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host_WormHost107.pppg$i++;
        host_WormHost108.pppg$o++ --> host2edge --> edge15.pppg$i++;
        edge15.pppg$o++ --> edge2host --> host_WormHost108.pppg$i++;
}

module SAS19
{
    gates:
        inout pppg[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");
        }

        core0: Router {
            parameters:
                @RL();
                @CoreRouter();
                @display("i=abstract/switch");
        }
        gw1: Router {
            parameters:
                @RL();
                @display("i=abstract/router2");
        }
        edge2: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge3: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge4: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge5: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge6: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge7: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        edge8: Router {
            parameters:
                @RL();
                @display("i=abstract/router");
        }
        host9: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost10: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host11: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer12: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host13: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_InteractiveServer14: InteractiveServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer15: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host16: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host17: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost18: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host19: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_MailServer20: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host21: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host22: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host23: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost24: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost25: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost26: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost29: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host30: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host31: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host32: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host33: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host35: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host36: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WebServer37: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost38: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost39: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host40: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host41: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost42: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host46: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host47: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host48: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host49: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host50: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host51: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost52: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host53: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host_WormHost54: WormHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host55: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host56: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host57: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host58: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host59: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host60: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host61: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host62: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host63: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }

    connections:
        pppg++ <--> core0.pppg++;
        pppg++ <--> core0.pppg++;

        core0.pppg++ <--> gateway2core <--> gw1.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge2.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge3.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge4.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge5.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge6.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge7.pppg++;
        gw1.pppg++ <--> edge2gateway <--> edge8.pppg++;
        host9.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host9.pppg$i++;
        host_WormHost10.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost10.pppg$i++;
        host11.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host11.pppg$i++;
        host_WebServer12.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_WebServer12.pppg$i++;
        host13.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host13.pppg$i++;
        host_InteractiveServer14.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_InteractiveServer14.pppg$i++;
        host_WebServer15.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host_WebServer15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host17.pppg$i++;
        host_WormHost18.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host_WormHost18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host19.pppg$i++;
        host_MailServer20.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host_MailServer20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host23.pppg$i++;
        host_WormHost24.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost24.pppg$i++;
        host_WormHost25.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost25.pppg$i++;
        host_WormHost26.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host_WormHost26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host28.pppg$i++;
        host_WormHost29.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host_WormHost29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host36.pppg$i++;
        host_WebServer37.pppg$o++ --> server2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> server2edge --> host_WebServer37.pppg$i++;
        host_WormHost38.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost38.pppg$i++;
        host_WormHost39.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost39.pppg$i++;
        host40.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host41.pppg$i++;
        host_WormHost42.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host_WormHost42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host44.pppg$i++;
        host45.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host45.pppg$i++;
        host46.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host46.pppg$i++;
        host47.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host47.pppg$i++;
        host48.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host48.pppg$i++;
        host49.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host49.pppg$i++;
        host50.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host50.pppg$i++;
        host51.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host51.pppg$i++;
        host_WormHost52.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost52.pppg$i++;
        host53.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host53.pppg$i++;
        host_WormHost54.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host_WormHost54.pppg$i++;
        host55.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host55.pppg$i++;
        host56.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host56.pppg$i++;
        host57.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host57.pppg$i++;
        host58.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host58.pppg$i++;
        host59.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host59.pppg$i++;
        host60.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host60.pppg$i++;
        host61.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host61.pppg$i++;
        host62.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host62.pppg$i++;
        host63.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host63.pppg$i++;
}

