#
# OMNeT++/OMNEST Makefile for rease
#
# This file was generated with the command:
#  opp_makemake -f --deep -o rease -O out -pREASE -I../../inet/src/networklayer/common -I../../inet/src/networklayer/rsvp_te -I../../inet/src/networklayer/icmpv6 -I../../inet/src/transport/tcp -I../../inet/src/networklayer/mpls -I../../inet/src/networklayer/ted -I../../inet/src/networklayer/contract -I../../inet/src/util -I../../inet/src/transport/contract -I../../inet/src/linklayer/mfcore -I../../inet/src/networklayer/ldp -I../../inet/src/networklayer/ipv4 -I../../inet/src/base -I../../inet/src/util/headerserializers -I../../inet/src/networklayer/ipv6 -I../../inet/src/transport/sctp -I../../inet/src/world -I../../inet/src/applications/pingapp -I../../inet/src/linklayer/contract -I../../inet/src/networklayer/arp -I../../inet/src/transport/udp -I../../inet/src/networklayer/autorouting -L../../inet/out/$(CONFIGNAME)/src -ldistack -lxmlrpc_server_abyss++ -lxmlrpc_server++ -lxmlrpc_server_abyss -lxmlrpc_server -lxmlrpc_abyss -lpthread -lxmlrpc++ -lxmlrpc -lxmlrpc_util -lxmlrpc_xmlparse -lxmlrpc_xmltok -linet -KINET_PROJ=../../inet
#

# Name of target to be created (-o option)
TARGET = rease$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../inet/src/networklayer/common \
    -I../../inet/src/networklayer/rsvp_te \
    -I../../inet/src/networklayer/icmpv6 \
    -I../../inet/src/transport/tcp \
    -I../../inet/src/networklayer/mpls \
    -I../../inet/src/networklayer/ted \
    -I../../inet/src/networklayer/contract \
    -I../../inet/src/util \
    -I../../inet/src/transport/contract \
    -I../../inet/src/linklayer/mfcore \
    -I../../inet/src/networklayer/ldp \
    -I../../inet/src/networklayer/ipv4 \
    -I../../inet/src/base \
    -I../../inet/src/util/headerserializers \
    -I../../inet/src/networklayer/ipv6 \
    -I../../inet/src/transport/sctp \
    -I../../inet/src/world \
    -I../../inet/src/applications/pingapp \
    -I../../inet/src/linklayer/contract \
    -I../../inet/src/networklayer/arp \
    -I../../inet/src/transport/udp \
    -I../../inet/src/networklayer/autorouting \
    -I. \
    -Iapplications \
    -Iapplications/classifier \
    -Iapplications/ddos \
    -Iapplications/flow \
    -Iapplications/generic \
    -Iapplications/ids \
    -Iapplications/limiter \
    -Iapplications/linkmonitor \
    -Iapplications/pingApp \
    -Iapplications/ponder \
    -Iapplications/tcpApp \
    -Iapplications/udpApp \
    -Iapplications/util \
    -Iapplications/worm \
    -Ibase \
    -Inetworklayer \
    -Inetworklayer/autorouting \
    -Inetworklayer/contract \
    -Inetworklayer/ipv4 \
    -Inetworklayer/queue \
    -Inodes \
    -Inodes/inet \
    -Itransport \
    -Itransport/contract \
    -Itransport/tcp \
    -Itransport/udp

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../inet/out/$(CONFIGNAME)/src  -ldistack -lxmlrpc_server_abyss++ -lxmlrpc_server++ -lxmlrpc_server_abyss -lxmlrpc_server -lxmlrpc_abyss -lpthread -lxmlrpc++ -lxmlrpc -lxmlrpc_util -lxmlrpc_xmlparse -lxmlrpc_xmltok -linet
LIBS += -Wl,-rpath,`abspath ../../inet/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/applications/classifier/Classifier.o \
    $O/applications/ddos/TribeFloodNetwork.o \
    $O/applications/flow/FlowExporter.o \
    $O/applications/generic/GenericApplication.o \
    $O/applications/generic/InetUser.o \
    $O/applications/ids/IDSModule.o \
    $O/applications/limiter/RateLimiter.o \
    $O/applications/linkmonitor/LinkMonitor.o \
    $O/applications/pingApp/GenericICMPPingApplication.o \
    $O/applications/ponder/EventPublisher.o \
    $O/applications/ponder/RateLimiterControlIP.o \
    $O/applications/ponder/RateLimiterControlLink.o \
    $O/applications/ponder/MechanismExporter.o \
    $O/applications/ponder/FlowExporterControl.o \
    $O/applications/ponder/RateLimiterControlFlow.o \
    $O/applications/ponder/IDSControl.o \
    $O/applications/tcpApp/GenericTCPApplicationClientThread.o \
    $O/applications/tcpApp/GenericTCPApplicationServerThread.o \
    $O/applications/tcpApp/GenericTCPApplication.o \
    $O/applications/udpApp/GenericUDPApplicationServerThread.o \
    $O/applications/udpApp/GenericUDPApplicationClientThread.o \
    $O/applications/udpApp/GenericUDPApplicationTimeout.o \
    $O/applications/udpApp/GenericUDPApplication.o \
    $O/applications/worm/UDPWormVictim.o \
    $O/applications/worm/WormStatisticCollector.o \
    $O/base/TrafficProfileManager.o \
    $O/base/ConnectionManager.o \
    $O/networklayer/autorouting/TGMNetworkConfigurator.o \
    $O/networklayer/ipv4/IP_hack.o \
    $O/networklayer/queue/DropTailTraceQueue.o \
    $O/transport/contract/UDPSocketVector.o \
    $O/transport/contract/DistackTCPSocketMap.o \
    $O/transport/tcp/TCP_hack.o \
    $O/transport/tcp/TCPConnection_hack.o \
    $O/transport/udp/UDP_hack.o \
    $O/applications/flow/flow_message_m.o \
    $O/applications/generic/GenericApplicationMessage_m.o \
    $O/applications/ids/IPBlock_m.o \
    $O/applications/util/DistackRAOData_m.o \
    $O/applications/util/DistackRemoteTCPPayload_m.o \
    $O/applications/worm/UDPWormQueryMessage_m.o \
    $O/networklayer/contract/IPv6ControlInfo_hacked_m.o \
    $O/networklayer/contract/IPControlInfo_hacked_m.o \
    $O/networklayer/ipv4/IPDatagram_hacked_m.o

# Message files
MSGFILES = \
    applications/flow/flow_message.msg \
    applications/generic/GenericApplicationMessage.msg \
    applications/ids/IPBlock.msg \
    applications/util/DistackRAOData.msg \
    applications/util/DistackRemoteTCPPayload.msg \
    applications/worm/UDPWormQueryMessage.msg \
    networklayer/contract/IPv6ControlInfo_hacked.msg \
    networklayer/contract/IPControlInfo_hacked.msg \
    networklayer/ipv4/IPDatagram_hacked.msg

# Other makefile variables (-K)
INET_PROJ=../../inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH) -PREASE_API

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f rease rease.exe librease.so librease.a librease.dll librease.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f applications/*_m.cc applications/*_m.h
	-rm -f applications/classifier/*_m.cc applications/classifier/*_m.h
	-rm -f applications/ddos/*_m.cc applications/ddos/*_m.h
	-rm -f applications/flow/*_m.cc applications/flow/*_m.h
	-rm -f applications/generic/*_m.cc applications/generic/*_m.h
	-rm -f applications/ids/*_m.cc applications/ids/*_m.h
	-rm -f applications/limiter/*_m.cc applications/limiter/*_m.h
	-rm -f applications/linkmonitor/*_m.cc applications/linkmonitor/*_m.h
	-rm -f applications/pingApp/*_m.cc applications/pingApp/*_m.h
	-rm -f applications/ponder/*_m.cc applications/ponder/*_m.h
	-rm -f applications/tcpApp/*_m.cc applications/tcpApp/*_m.h
	-rm -f applications/udpApp/*_m.cc applications/udpApp/*_m.h
	-rm -f applications/util/*_m.cc applications/util/*_m.h
	-rm -f applications/worm/*_m.cc applications/worm/*_m.h
	-rm -f base/*_m.cc base/*_m.h
	-rm -f networklayer/*_m.cc networklayer/*_m.h
	-rm -f networklayer/autorouting/*_m.cc networklayer/autorouting/*_m.h
	-rm -f networklayer/contract/*_m.cc networklayer/contract/*_m.h
	-rm -f networklayer/ipv4/*_m.cc networklayer/ipv4/*_m.h
	-rm -f networklayer/queue/*_m.cc networklayer/queue/*_m.h
	-rm -f nodes/*_m.cc nodes/*_m.h
	-rm -f nodes/inet/*_m.cc nodes/inet/*_m.h
	-rm -f transport/*_m.cc transport/*_m.h
	-rm -f transport/contract/*_m.cc transport/contract/*_m.h
	-rm -f transport/tcp/*_m.cc transport/tcp/*_m.h
	-rm -f transport/udp/*_m.cc transport/udp/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc applications/*.cc applications/classifier/*.cc applications/ddos/*.cc applications/flow/*.cc applications/generic/*.cc applications/ids/*.cc applications/limiter/*.cc applications/linkmonitor/*.cc applications/pingApp/*.cc applications/ponder/*.cc applications/tcpApp/*.cc applications/udpApp/*.cc applications/util/*.cc applications/worm/*.cc base/*.cc networklayer/*.cc networklayer/autorouting/*.cc networklayer/contract/*.cc networklayer/ipv4/*.cc networklayer/queue/*.cc nodes/*.cc nodes/inet/*.cc transport/*.cc transport/contract/*.cc transport/tcp/*.cc transport/udp/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/applications/classifier/Classifier.o: applications/classifier/Classifier.cc \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/classifier/Classifier.h \
	applications/flow/flow_message_m.h \
	applications/ids/IDSModule.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	applications/flow/FlowExporter.h \
	applications/limiter/RateLimiter.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	applications/ponder/MechanismExporter.h \
	applications/ponder/EventPublisher.h
$O/applications/ddos/TribeFloodNetwork.o: applications/ddos/TribeFloodNetwork.cc \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMPMessage.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	$(INET_PROJ)/src/networklayer/arp/ARP.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INET_PROJ)/src/networklayer/ipv4/RoutingTableAccess.h \
	applications/ddos/TribeFloodNetwork.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket_m.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddressResolver.h \
	$(INET_PROJ)/src/applications/pingapp/PingPayload_m.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMP.h \
	networklayer/contract/IPv6ControlInfo_hacked_m.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket.h \
	networklayer/contract/IPControlInfo_hacked_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMPMessage_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/IRoutingTable.h
$O/applications/flow/flow_message_m.o: applications/flow/flow_message_m.cc \
	applications/flow/FlowExporter.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/flow/flow_message_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h
$O/applications/flow/FlowExporter.o: applications/flow/FlowExporter.cc \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/classifier/Classifier.h \
	applications/flow/flow_message_m.h \
	applications/ids/IDSModule.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment.h \
	$(INET_PROJ)/src/transport/sctp/SCTPMessage_m.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddressResolver.h \
	applications/limiter/RateLimiter.h \
	applications/flow/FlowExporter.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	applications/ponder/MechanismExporter.h
$O/applications/generic/InetUser.o: applications/generic/InetUser.cc \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	applications/generic/InetUser.h \
	applications/generic/TransmissionConfig.h \
	applications/generic/GenericApplication.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	applications/pingApp/GenericICMPPingApplication.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	base/ConnectionManager.h \
	base/TrafficProfileManager.h \
	applications/udpApp/GenericUDPApplication.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	applications/tcpApp/GenericTCPApplication.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPSocketMap.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	transport/contract/UDPSocketVector.h
$O/applications/generic/GenericApplication.o: applications/generic/GenericApplication.cc \
	base/ReaSEDefs.h \
	base/TrafficProfileManager.h \
	base/ConnectionManager.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddressResolver.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/generic/InetUser.h \
	applications/generic/TransmissionConfig.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	applications/generic/GenericApplication.h
$O/applications/generic/GenericApplicationMessage_m.o: applications/generic/GenericApplicationMessage_m.cc \
	applications/generic/GenericApplicationMessage_m.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/base/INETDefs.h
$O/applications/ids/IDSModule.o: applications/ids/IDSModule.cc \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	applications/ids/IPBlock_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/classifier/Classifier.h \
	applications/ids/IDSModule.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment.h \
	$(INET_PROJ)/src/transport/sctp/SCTPMessage_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddressResolver.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo_m.h \
	applications/flow/FlowExporter.h \
	applications/limiter/RateLimiter.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMPMessage_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	applications/ponder/MechanismExporter.h \
	applications/ponder/EventPublisher.h
$O/applications/ids/IPBlock_m.o: applications/ids/IPBlock_m.cc \
	applications/ids/IPBlock_m.h
$O/applications/limiter/RateLimiter.o: applications/limiter/RateLimiter.cc \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	applications/ids/IPBlock_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/classifier/Classifier.h \
	applications/flow/flow_message_m.h \
	applications/ids/IDSModule.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment.h \
	$(INET_PROJ)/src/transport/sctp/SCTPMessage_m.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket_m.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddressResolver.h \
	applications/flow/FlowExporter.h \
	applications/limiter/RateLimiter.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	applications/ponder/MechanismExporter.h
$O/applications/linkmonitor/LinkMonitor.o: applications/linkmonitor/LinkMonitor.cc \
	applications/linkmonitor/LinkMonitor.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	applications/flow/FlowExporter.h \
	applications/limiter/RateLimiter.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/classifier/Classifier.h \
	applications/ids/IDSModule.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	applications/ponder/MechanismExporter.h \
	applications/ponder/EventPublisher.h
$O/applications/pingApp/GenericICMPPingApplication.o: applications/pingApp/GenericICMPPingApplication.cc \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/generic/InetUser.h \
	applications/generic/TransmissionConfig.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo.h \
	applications/generic/GenericApplication.h \
	applications/pingApp/GenericICMPPingApplication.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo.h \
	base/TrafficProfileManager.h \
	base/ConnectionManager.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo_m.h \
	$(INET_PROJ)/src/applications/pingapp/PingPayload_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddressResolver.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h
$O/applications/ponder/EventPublisher.o: applications/ponder/EventPublisher.cc \
	applications/ponder/EventPublisher.h
$O/applications/ponder/FlowExporterControl.o: applications/ponder/FlowExporterControl.cc \
	applications/limiter/RateLimiter.h \
	applications/flow/FlowExporter.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/classifier/Classifier.h \
	applications/ids/IDSModule.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	applications/ponder/MechanismExporter.h \
	applications/ponder/FlowExporterControl.h
$O/applications/ponder/MechanismExporter.o: applications/ponder/MechanismExporter.cc \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/classifier/Classifier.h \
	applications/ids/IDSModule.h \
	applications/ponder/RateLimiterControlLink.h \
	applications/flow/FlowExporter.h \
	applications/limiter/RateLimiter.h \
	applications/ponder/RateLimiterControlIP.h \
	applications/ponder/RateLimiterControlFlow.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	applications/ponder/IDSControl.h \
	applications/ponder/MechanismExporter.h \
	applications/ponder/FlowExporterControl.h \
	applications/ponder/EventPublisher.h
$O/applications/ponder/IDSControl.o: applications/ponder/IDSControl.cc \
	applications/flow/FlowExporter.h \
	applications/limiter/RateLimiter.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/classifier/Classifier.h \
	applications/ids/IDSModule.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	applications/ponder/IDSControl.h \
	applications/ponder/MechanismExporter.h
$O/applications/ponder/RateLimiterControlFlow.o: applications/ponder/RateLimiterControlFlow.cc \
	applications/flow/FlowExporter.h \
	applications/limiter/RateLimiter.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/ponder/RateLimiterControlFlow.h \
	applications/classifier/Classifier.h \
	applications/ids/IDSModule.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	applications/ponder/MechanismExporter.h
$O/applications/ponder/RateLimiterControlLink.o: applications/ponder/RateLimiterControlLink.cc \
	applications/flow/FlowExporter.h \
	applications/limiter/RateLimiter.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/classifier/Classifier.h \
	applications/ids/IDSModule.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	applications/ponder/RateLimiterControlLink.h \
	applications/ponder/MechanismExporter.h
$O/applications/ponder/RateLimiterControlIP.o: applications/ponder/RateLimiterControlIP.cc \
	applications/flow/FlowExporter.h \
	applications/limiter/RateLimiter.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/ponder/RateLimiterControlIP.h \
	applications/classifier/Classifier.h \
	applications/ids/IDSModule.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	applications/ponder/MechanismExporter.h
$O/applications/tcpApp/GenericTCPApplicationClientThread.o: applications/tcpApp/GenericTCPApplicationClientThread.cc \
	applications/generic/GenericApplicationMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	applications/generic/TransmissionConfig.h \
	applications/generic/InetUser.h \
	applications/generic/GenericApplication.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	base/ConnectionManager.h \
	base/TrafficProfileManager.h \
	base/ReaSEDefs.h \
	applications/tcpApp/GenericTCPApplicationClientThread.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	applications/tcpApp/GenericTCPApplication.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/transport/contract/TCPSocketMap.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h
$O/applications/tcpApp/GenericTCPApplicationServerThread.o: applications/tcpApp/GenericTCPApplicationServerThread.cc \
	applications/generic/GenericApplicationMessage_m.h \
	applications/tcpApp/GenericTCPApplicationServerThread.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	applications/generic/InetUser.h \
	applications/generic/TransmissionConfig.h \
	applications/generic/GenericApplication.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	base/ConnectionManager.h \
	base/TrafficProfileManager.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	applications/tcpApp/GenericTCPApplication.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/transport/contract/TCPSocketMap.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h
$O/applications/tcpApp/GenericTCPApplication.o: applications/tcpApp/GenericTCPApplication.cc \
	applications/tcpApp/GenericTCPApplicationServerThread.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	applications/generic/TransmissionConfig.h \
	applications/generic/InetUser.h \
	applications/generic/GenericApplication.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	base/ReaSEDefs.h \
	base/TrafficProfileManager.h \
	base/ConnectionManager.h \
	applications/tcpApp/GenericTCPApplicationClientThread.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	applications/tcpApp/GenericTCPApplication.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/transport/contract/TCPSocketMap.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h
$O/applications/udpApp/GenericUDPApplicationServerThread.o: applications/udpApp/GenericUDPApplicationServerThread.cc \
	applications/generic/GenericApplicationMessage_m.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/udpApp/GenericUDPApplicationServerThread.h \
	applications/generic/TransmissionConfig.h \
	applications/generic/InetUser.h \
	applications/generic/GenericApplication.h \
	base/ConnectionManager.h \
	base/TrafficProfileManager.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	applications/udpApp/GenericUDPApplication.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	transport/contract/UDPSocketVector.h
$O/applications/udpApp/GenericUDPApplicationTimeout.o: applications/udpApp/GenericUDPApplicationTimeout.cc \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/generic/TransmissionConfig.h \
	applications/generic/InetUser.h \
	applications/generic/GenericApplication.h \
	applications/udpApp/GenericUDPApplicationTimeout.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	base/ReaSEDefs.h \
	base/TrafficProfileManager.h \
	base/ConnectionManager.h \
	applications/udpApp/GenericUDPApplication.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	transport/contract/UDPSocketVector.h
$O/applications/udpApp/GenericUDPApplication.o: applications/udpApp/GenericUDPApplication.cc \
	applications/generic/GenericApplicationMessage_m.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/udpApp/GenericUDPApplicationServerThread.h \
	applications/generic/TransmissionConfig.h \
	applications/generic/InetUser.h \
	applications/generic/GenericApplication.h \
	base/ConnectionManager.h \
	base/TrafficProfileManager.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	applications/udpApp/GenericUDPApplication.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	applications/udpApp/GenericUDPApplicationClientThread.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	transport/contract/UDPSocketVector.h
$O/applications/udpApp/GenericUDPApplicationClientThread.o: applications/udpApp/GenericUDPApplicationClientThread.cc \
	applications/generic/GenericApplicationMessage_m.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/generic/TransmissionConfig.h \
	applications/generic/InetUser.h \
	applications/generic/GenericApplication.h \
	base/ConnectionManager.h \
	base/TrafficProfileManager.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	applications/udpApp/GenericUDPApplication.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	applications/udpApp/GenericUDPApplicationClientThread.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	transport/contract/UDPSocketVector.h
$O/applications/util/DistackRemoteTCPPayload_m.o: applications/util/DistackRemoteTCPPayload_m.cc \
	base/ReaSEDefs.h \
	applications/util/DistackRemoteTCPPayload_m.h
$O/applications/util/DistackRAOData_m.o: applications/util/DistackRAOData_m.cc \
	base/ReaSEDefs.h \
	applications/util/DistackRAOData_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h
$O/applications/worm/UDPWormVictim.o: applications/worm/UDPWormVictim.cc \
	applications/worm/UDPWormQueryMessage_m.h \
	applications/worm/UDPWormVictim.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	applications/worm/WormStatisticCollector.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket_m.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo_m.h \
	networklayer/contract/IPv6ControlInfo_hacked_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket.h \
	networklayer/contract/IPControlInfo_hacked_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h
$O/applications/worm/WormStatisticCollector.o: applications/worm/WormStatisticCollector.cc \
	applications/worm/WormStatisticCollector.h
$O/applications/worm/UDPWormQueryMessage_m.o: applications/worm/UDPWormQueryMessage_m.cc \
	applications/worm/UDPWormQueryMessage_m.h \
	base/ReaSEDefs.h
$O/base/TrafficProfileManager.o: base/TrafficProfileManager.cc \
	base/ReaSEDefs.h \
	base/TrafficProfileManager.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/generic/TransmissionConfig.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/base/ModuleAccess.h
$O/base/ConnectionManager.o: base/ConnectionManager.cc \
	base/ReaSEDefs.h \
	base/TrafficProfileManager.h \
	base/ConnectionManager.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/generic/TransmissionConfig.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/base/ModuleAccess.h
$O/networklayer/autorouting/TGMNetworkConfigurator.o: networklayer/autorouting/TGMNetworkConfigurator.cc \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/networklayer/autorouting/NetworkConfigurator.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTable.h \
	$(INET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddressResolver.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	networklayer/autorouting/TGMNetworkConfigurator.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h
$O/networklayer/contract/IPv6ControlInfo_hacked_m.o: networklayer/contract/IPv6ControlInfo_hacked_m.cc \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo_m.h \
	networklayer/contract/IPv6ControlInfo_hacked_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h
$O/networklayer/contract/IPControlInfo_hacked_m.o: networklayer/contract/IPControlInfo_hacked_m.cc \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	networklayer/contract/IPControlInfo_hacked_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h
$O/networklayer/ipv4/IPDatagram_hacked_m.o: networklayer/ipv4/IPDatagram_hacked_m.cc \
	networklayer/ipv4/IPDatagram_hacked_m.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h
$O/networklayer/ipv4/IP_hack.o: networklayer/ipv4/IP_hack.cc \
	$(INET_PROJ)/src/networklayer/ipv4/IPFragBuf.h \
	networklayer/ipv4/IPDatagram_hacked_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/base/QueueBase.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo.h \
	$(INET_PROJ)/src/networklayer/ipv4/IP.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMPMessage.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	$(INET_PROJ)/src/base/ProtocolMap.h \
	$(INET_PROJ)/src/base/AbstractQueue.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INET_PROJ)/src/networklayer/ipv4/RoutingTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	networklayer/ipv4/IP_hack.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMP.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket.h \
	networklayer/contract/IPControlInfo_hacked_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMPAccess.h \
	$(INET_PROJ)/src/networklayer/ipv4/ICMPMessage_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INET_PROJ)/src/base/ReassemblyBuffer.h
$O/networklayer/queue/DropTailTraceQueue.o: networklayer/queue/DropTailTraceQueue.cc \
	$(INET_PROJ)/src/base/IPassiveQueue.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	networklayer/queue/DropTailTraceQueue.h \
	$(INET_PROJ)/src/base/PassiveQueueBase.h
$O/transport/contract/UDPSocketVector.o: transport/contract/UDPSocketVector.cc \
	$(INET_PROJ)/src/transport/contract/UDPSocket.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/generic/TransmissionConfig.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	transport/contract/UDPSocketVector.h
$O/transport/contract/DistackTCPSocketMap.o: transport/contract/DistackTCPSocketMap.cc \
	transport/contract/DistackTCPSocketMap.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h
$O/transport/tcp/TCP_hack.o: transport/tcp/TCP_hack.cc \
	$(INET_PROJ)/src/transport/tcp/TCPConnection.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo.h \
	$(INET_PROJ)/src/transport/tcp/TCP.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPControlInfo_m.h \
	transport/tcp/TCPConnection_hack.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	transport/tcp/TCP_hack.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h
$O/transport/tcp/TCPConnection_hack.o: transport/tcp/TCPConnection_hack.cc \
	$(INET_PROJ)/src/transport/tcp/TCPConnection.h \
	$(INET_PROJ)/src/transport/tcp/TCPSACKRexmitQueue.h \
	$(INET_PROJ)/src/transport/tcp/TCPSendQueue.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment.h \
	$(INET_PROJ)/src/transport/tcp/TCP.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/transport/tcp/TCPSegment_m.h \
	transport/tcp/TCPConnection_hack.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/tcp/TCPAlgorithm.h \
	transport/tcp/TCP_hack.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INET_PROJ)/src/transport/tcp/TCPReceiveQueue.h
$O/transport/udp/UDP_hack.o: transport/udp/UDP_hack.cc \
	applications/generic/GenericApplicationMessage_m.h \
	$(INET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket_m.h \
	base/ReaSEDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/transport/udp/UDPPacket.h \
	transport/udp/UDP_hack.h \
	$(INET_PROJ)/src/transport/udp/UDP.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPAddress.h

