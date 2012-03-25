##################################################
#           Distack base functionality           #
##################################################

lib_LIBRARIES = libdistackbase.a
AM_CPPFLAGS = -fPIC -DLINUX -D_LINUX -I../ -D_REENTRANT -D_FILE_OFFSET_BITS=64 -pthread -fvisibility=default
libdistackbase_a_SOURCES =
nobase_libdistackbase_a_HEADERS =

if DEBUG
  # compiler flags specific to debug versions
  AM_CPPFLAGS  += -ggdb -DDEBUG
endif

if REMOTE_XML
  AM_CPPFLAGS  += -DREMOTE_XML
endif

if OMNET_SIMULATION
  #omnet specific linker and compiler flags
  AM_CPPFLAGS  += -DOMNET_SIMULATION
endif

AM_LDFLAGS      = -static

libdistackbase_adir = ${pkgincludedir}/base

########### source files start here ###########

#-------------------> common

libdistackbase_a_SOURCES += \
  common/DistackInfo.cpp \
  common/Helper.cpp \
  common/InterruptableSleeper.cpp \
  common/SubnetCounterTree.cpp \
  common/PatriciaTrie.cpp \
  common/Timer.cpp \
  common/FileLogOutputter.cpp \
  common/Log.cpp \
  common/LogLevel.cpp \
  common/LogOutputter.cpp \
  common/StdOutLogOutputter.cpp \
  common/GenericRoutingTable.cpp

nobase_libdistackbase_a_HEADERS += \
  common/DistackInfo.h \
  common/Helper.h \
  common/InterruptableSleeper.h \
  common/SubnetCounterTree.h \
  common/PatriciaTrie.h \
  common/Timer.h \
  common/FileLogOutputter.h \
  common/Log.h \
  common/LogLevel.h \
  common/LogOutputter.h \
  common/StdOutLogOutputter.h \
  common/GenericRoutingTable.h


#-------------------> configuration

libdistackbase_a_SOURCES += \
  configuration/Configuration.cpp \
  configuration/triggerconf.cpp

nobase_libdistackbase_a_HEADERS += \
  configuration/Configuration.h \
  configuration/triggerconf.h

#-------------------> message

libdistackbase_a_SOURCES += \
  message/Message.cpp \
  message/MessagingNode.cpp \
  message/MessagingSystem.cpp \
  message/remote/RemoteMessagingSystem.cpp \
  message/remote/RemoteCommSystem.cpp \
  message/remote/RemoteCommSystemNone.cpp  
if OMNET_SIMULATION
libdistackbase_a_SOURCES += \
  message/remote/RemoteCommSystemOmnetPathbased.cpp \
  message/remote/RemoteCommSystemOmnetRing.cpp \
  message/remote/RemoteCommSystemOmnetTcp.cpp
else
libdistackbase_a_SOURCES += \
  message/remote/RemoteCommSystemTcpSocket.cpp \
  message/remote/RemoteCommSystemGist.cpp
endif

nobase_libdistackbase_a_HEADERS += \
  message/Message.h \
  message/MessagingNode.h \
  message/MessagingSystem.h \
  message/remote/RemoteMessagingSystem.h \
  message/remote/RemoteCommSystem.h \
  message/remote/RemoteCommSystemNone.h
if OMNET_SIMULATION
nobase_libdistackbase_a_HEADERS += \
  message/remote/RemoteCommSystemOmnetPathbased.h \
  message/remote/RemoteCommSystemOmnetRing.h \
  message/remote/RemoteCommSystemOmnetTcp.h
else
nobase_libdistackbase_a_HEADERS += \
  message/remote/RemoteCommSystemTcpSocket.h \
  message/remote/RemoteCommSystemGist.h
endif

#-------------------> modules

libdistackbase_a_SOURCES += \
  module/Channel.cpp \
  module/ChannelManager.cpp \
  module/DynamicLibrary.cpp \
  module/FrameDistribution.cpp \
  module/Module.cpp \
  module/ModuleManager.cpp

nobase_libdistackbase_a_HEADERS += \
  module/Channel.h \
  module/ChannelManager.h \
  module/DistackModuleInterface.h \
  module/DynamicLibrary.h \
  module/FrameDistribution.h \
  module/Module.h \
  module/ModuleManager.h

#-------------------> protocols
libdistackbase_a_SOURCES += \
  protocol/ArpPacket.cpp \
  protocol/EthernetPacket.cpp \
  protocol/Frame.cpp \
  protocol/IcmpPacket.cpp \
  protocol/IpPacket.cpp \
  protocol/Ipv6Packet.cpp \
  protocol/Packet.cpp \
  protocol/PayloadPacket.cpp \
  protocol/TcpPacket.cpp \
  protocol/MplsPacket.cpp \
  protocol/UdpPacket.cpp \
  protocol/PacketFactory.cpp \
  protocol/ProtocolNameResolver.cpp
  
nobase_libdistackbase_a_HEADERS += \
  protocol/ArpPacket.h \
  protocol/EthernetPacket.h \
  protocol/Frame.h \
  protocol/IcmpPacket.h \
  protocol/IpPacket.h \
  protocol/Ipv6Packet.h \
  protocol/Packet.h \
  protocol/PayloadPacket.h \
  protocol/TcpPacket.h \
  protocol/MplsPacket.h \
  protocol/UdpPacket.h \
  protocol/PacketFactory.h \
  protocol/ProtocolNameResolver.h

#-------------------> network

libdistackbase_a_SOURCES += \
  network/FrameBuffer.cpp \
  network/NetworkInterface.cpp \
  network/NetworkManager.cpp
if OMNET_SIMULATION
  libdistackbase_a_SOURCES += network/omnetpp/NetworkInterfaceOmnetpp.cpp
else
  libdistackbase_a_SOURCES += network/libpcap/NetworkInterfacePcap.cpp
endif

nobase_libdistackbase_a_HEADERS += \
  network/FrameBuffer.h \
  network/NetworkInterface.h \
  network/NetworkManager.h
if OMNET_SIMULATION
  nobase_libdistackbase_a_HEADERS += network/omnetpp/NetworkInterfaceOmnetpp.h
else
  nobase_libdistackbase_a_HEADERS += network/libpcap/NetworkInterfacePcap.h
endif
