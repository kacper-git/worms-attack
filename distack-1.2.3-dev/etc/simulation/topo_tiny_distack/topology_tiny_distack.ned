import rease.nodes.inet.DDoSZombie;
import rease.nodes.inet.DistackOmnetIDS;
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

channel host2edge extends ned.DatarateChannel
{
    parameters:
        delay = 1 us;
        datarate = 0.128Mbps;
}
channel edge2host extends ned.DatarateChannel
{
    parameters:
        delay = 1 us;
        datarate = 0.768Mbps;
}
channel server2edge extends ned.DatarateChannel
{
    parameters:
        delay = 1 us;
        datarate = 10Mbps;
}
channel edge2gateway extends ned.DatarateChannel
{
    parameters:
        delay = 1 us;
        datarate = 155Mbps;
}
channel gateway2core extends ned.DatarateChannel
{
    parameters:
        delay = 1 us;
        datarate = 1000Mbps;
}
channel core2core extends ned.DatarateChannel
{
    parameters:
        delay = 1 us;
        datarate = 2500Mbps;
}
channel stub2transit extends ned.DatarateChannel
{
    parameters:
        delay = 1 us;
        datarate = 5000Mbps;
}
channel stub2stub extends ned.DatarateChannel
{
    parameters:
        delay = 1 us;
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
                totalCountOfAS = 3;
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
        tas0: TAS0 {
            parameters:
                @AS();
                @display("i=misc/globe_s");
        }
        sas1: SAS1 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");
        }
        sas2: SAS2 {
            parameters:
                @AS();
                @display("i=misc/cloud_s");

        }
    connections:
        tas0.out++ --> stub2transit --> sas1.in++;
        tas0.out++ --> stub2transit --> sas2.in++;
        sas1.out++ --> stub2transit --> tas0.in++;
        sas2.out++ --> stub2transit --> tas0.in++;

}

network Inet extends Internet
{
    parameters:
}

module TAS0
{
    gates:
        input in[];
        output out[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");

        }
        core0: DistackOmnetIDS {
            parameters:
                configId = "settings.xml";
                raoOn = true;
                @CoreRouter();
                @RL();
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
        host5: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host6: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host7: DDoSZombie {
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
        host10: DDoSZombie {
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
        host13: DDoSZombie {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");

        }
    connections:
        in++ --> core0.pppg$i++;
        out++ <-- core0.pppg$o++;
        in++ --> core0.pppg$i++;
        out++ <-- core0.pppg$o++;

        core0.pppg$o++ --> core2core --> core0.pppg$i++;
        core0.pppg$o++ --> core2core --> core0.pppg$i++;
        core0.pppg$o++ --> gateway2core --> gw1.pppg$i++;
        gw1.pppg$o++ --> gateway2core --> core0.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge2.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge3.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge4.pppg$i++;
        edge2.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge3.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge4.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        host5.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host5.pppg$i++;
        host6.pppg$o++ --> server2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> server2edge --> host6.pppg$i++;
        host7.pppg$o++ --> host2edge --> edge2.pppg$i++;
        edge2.pppg$o++ --> edge2host --> host7.pppg$i++;
        host8.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host8.pppg$i++;
        host9.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host9.pppg$i++;
        host10.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host10.pppg$i++;
        host11.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host11.pppg$i++;
        host12.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host12.pppg$i++;
        host13.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host13.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host14.pppg$i++;
}

module SAS1
{
    gates:
        input in[];
        output out[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");

        }
        core0: Router {
            parameters:
                @CoreRouter();
                @RL();
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
        host14: DDoSZombie {
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
        host17: DDoSZombie {
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
        host21: DDoSZombie {
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
        host25: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host26: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host27: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host28: InteractiveServer {
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
        host32: DDoSZombie {
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
        host35: DDoSZombie {
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
        host41: DDoSZombie {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host42: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host43: DDoSZombie {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host44: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host45: MailServer {
            parameters:
                @RL();
                @display("i=device/laptop");

        }
    connections:
        in++ --> core0.pppg$i++;
        out++ <-- core0.pppg$o++;

        core0.pppg$o++ --> core2core --> core0.pppg$i++;
        core0.pppg$o++ --> core2core --> core0.pppg$i++;
        core0.pppg$o++ --> gateway2core --> gw1.pppg$i++;
        core0.pppg$o++ --> gateway2core --> gw2.pppg$i++;
        gw1.pppg$o++ --> gateway2core --> core0.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge3.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge4.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge5.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge6.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge7.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge8.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge9.pppg$i++;
        gw2.pppg$o++ --> gateway2core --> core0.pppg$i++;
        gw2.pppg$o++ --> edge2gateway --> edge10.pppg$i++;
        gw2.pppg$o++ --> edge2gateway --> edge11.pppg$i++;
        gw2.pppg$o++ --> edge2gateway --> edge12.pppg$i++;
        gw2.pppg$o++ --> edge2gateway --> edge13.pppg$i++;
        edge3.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge4.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge5.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge6.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge7.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge8.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge9.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge10.pppg$o++ --> edge2gateway --> gw2.pppg$i++;
        edge11.pppg$o++ --> edge2gateway --> gw2.pppg$i++;
        edge12.pppg$o++ --> edge2gateway --> gw2.pppg$i++;
        edge13.pppg$o++ --> edge2gateway --> gw2.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> server2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> server2edge --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host27.pppg$i++;
        host28.pppg$o++ --> server2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> server2edge --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host34.pppg$i++;
        host35.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host35.pppg$i++;
        host36.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host36.pppg$i++;
        host37.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host37.pppg$i++;
        host38.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host38.pppg$i++;
        host39.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host39.pppg$i++;
        host40.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host40.pppg$i++;
        host41.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host41.pppg$i++;
        host42.pppg$o++ --> host2edge --> edge12.pppg$i++;
        edge12.pppg$o++ --> edge2host --> host42.pppg$i++;
        host43.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host43.pppg$i++;
        host44.pppg$o++ --> host2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> edge2host --> host44.pppg$i++;
        host45.pppg$o++ --> server2edge --> edge13.pppg$i++;
        edge13.pppg$o++ --> server2edge --> host45.pppg$i++;
}

module SAS2
{
    gates:
        input in[];
        output out[];
    submodules:
        connectionManager: ConnectionManager {
            parameters:
                @display("p=20,20;i=block/classifier_s");

        }
        core0: Router {
            parameters:
                @CoreRouter();
                @RL();
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
        host13: WebServer {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host14: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host15: DDoSZombie {
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
        host18: DDoSZombie {
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
        host21: DDoSZombie {
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
        host33: DDoSZombie {
            parameters:
                @RL();
                @display("i=device/laptop");
        }
        host34: InetUserHost {
            parameters:
                @RL();
                @display("i=device/laptop");

        }
    connections:
        in++ --> core0.pppg$i++;
        out++ <-- core0.pppg$o++;

        core0.pppg$o++ --> core2core --> core0.pppg$i++;
        core0.pppg$o++ --> core2core --> core0.pppg$i++;
        core0.pppg$o++ --> gateway2core --> gw1.pppg$i++;
        core0.pppg$o++ --> gateway2core --> gw2.pppg$i++;
        gw1.pppg$o++ --> gateway2core --> core0.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge3.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge4.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge5.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge6.pppg$i++;
        gw1.pppg$o++ --> edge2gateway --> edge7.pppg$i++;
        gw2.pppg$o++ --> gateway2core --> core0.pppg$i++;
        gw2.pppg$o++ --> edge2gateway --> edge8.pppg$i++;
        gw2.pppg$o++ --> edge2gateway --> edge9.pppg$i++;
        gw2.pppg$o++ --> edge2gateway --> edge10.pppg$i++;
        gw2.pppg$o++ --> edge2gateway --> edge11.pppg$i++;
        edge3.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge4.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge5.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge6.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge7.pppg$o++ --> edge2gateway --> gw1.pppg$i++;
        edge8.pppg$o++ --> edge2gateway --> gw2.pppg$i++;
        edge9.pppg$o++ --> edge2gateway --> gw2.pppg$i++;
        edge10.pppg$o++ --> edge2gateway --> gw2.pppg$i++;
        edge11.pppg$o++ --> edge2gateway --> gw2.pppg$i++;
        host12.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host12.pppg$i++;
        host13.pppg$o++ --> server2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> server2edge --> host13.pppg$i++;
        host14.pppg$o++ --> host2edge --> edge3.pppg$i++;
        edge3.pppg$o++ --> edge2host --> host14.pppg$i++;
        host15.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host15.pppg$i++;
        host16.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host16.pppg$i++;
        host17.pppg$o++ --> host2edge --> edge4.pppg$i++;
        edge4.pppg$o++ --> edge2host --> host17.pppg$i++;
        host18.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host18.pppg$i++;
        host19.pppg$o++ --> host2edge --> edge5.pppg$i++;
        edge5.pppg$o++ --> edge2host --> host19.pppg$i++;
        host20.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host20.pppg$i++;
        host21.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host21.pppg$i++;
        host22.pppg$o++ --> host2edge --> edge6.pppg$i++;
        edge6.pppg$o++ --> edge2host --> host22.pppg$i++;
        host23.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host23.pppg$i++;
        host24.pppg$o++ --> host2edge --> edge7.pppg$i++;
        edge7.pppg$o++ --> edge2host --> host24.pppg$i++;
        host25.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host25.pppg$i++;
        host26.pppg$o++ --> host2edge --> edge8.pppg$i++;
        edge8.pppg$o++ --> edge2host --> host26.pppg$i++;
        host27.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host27.pppg$i++;
        host28.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host28.pppg$i++;
        host29.pppg$o++ --> host2edge --> edge9.pppg$i++;
        edge9.pppg$o++ --> edge2host --> host29.pppg$i++;
        host30.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host30.pppg$i++;
        host31.pppg$o++ --> host2edge --> edge10.pppg$i++;
        edge10.pppg$o++ --> edge2host --> host31.pppg$i++;
        host32.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host32.pppg$i++;
        host33.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host33.pppg$i++;
        host34.pppg$o++ --> host2edge --> edge11.pppg$i++;
        edge11.pppg$o++ --> edge2host --> host34.pppg$i++;
}

