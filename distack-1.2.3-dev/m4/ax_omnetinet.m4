# SYNOPSIS
#
#   AX_OMNETINET()
#
# DESCRIPTION
#
#   Test for omnet/inet headers and ReaSE INET Patch
#
# LAST MODIFICATION
#
#   2009-02-18

AC_DEFUN([AX_OMNETINET],
[
  AC_CHECK_HEADER([omnetpp.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([IPDatagram.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([ICMPMessage.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([TCPSocket.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([TCPSegment.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([UDPSocket.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([UDPPacket.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([RoutingTableAccess.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([RoutingTable.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([IPAddress.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([ModuleAccess.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([ARP.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([DistackRAOData_m.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([DistackRemoteTCPPayload_m.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))

  AC_CHECK_HEADER([DistackTCPSocketMap.h],[], 
    AC_MSG_ERROR([header not found. install OMNeT++/INET and ReaSE INET Patch]))
])
