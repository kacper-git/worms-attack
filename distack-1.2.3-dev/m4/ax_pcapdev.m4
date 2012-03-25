# SYNOPSIS
#
#   AX_PCAPDEV()
#
# DESCRIPTION
#
#   Test for pcap dev library
#
# LAST MODIFICATION
#
#   2009-02-17

AC_DEFUN([AX_PCAPDEV],
[
  AC_CHECK_LIB(pcap, main, [], 
    AC_MSG_ERROR([pcap library not found. install libpcap-dev]))

  AC_CHECK_HEADER([pcap.h],[], 
    AC_MSG_ERROR([pcap dev library not found. install libpcap-dev]))
])
