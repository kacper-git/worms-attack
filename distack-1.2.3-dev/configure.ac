AC_INIT([distack], [1.2.2-dev], [])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/Distack.cpp])
AC_CONFIG_MACRO_DIR([m4])


AC_ARG_ENABLE(debug,
[  --enable-debug    Turn on debugging],
[case "${enableval}" in
  yes) debug=true ;;
  no)  debug=false ;;
  *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
esac],[debug=false])
AM_CONDITIONAL(DEBUG, test x$debug = xtrue)

AC_ARG_ENABLE(simulation,
[  --enable-simulation    Turn on simulation support],
[case "${enableval}" in
  yes) simulation=true ;;
  no)  simulation=false ;;
  *) AC_MSG_ERROR(bad value ${enableval} for --enable-simulation) ;;
esac],[simulation=false])
AM_CONDITIONAL(OMNET_SIMULATION, test x$simulation = xtrue)

AC_ARG_ENABLE(remotexml,
[  --enable-remotexml    Turn on remote XML support],
[case "${enableval}" in
  yes) remotexml=true ;;
  no)  remotexml=false ;;
  *) AC_MSG_ERROR(bad value ${enableval} for --enable-remotexml) ;;
esac],[remotexml=false])
AM_CONDITIONAL(REMOTE_XML, test x$remotexml = xtrue)

AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_LANG(C++)

if test "$enable_simulation" = yes; then
  AX_OMNETINET            dnl Check for OMNeT++/INET headers and ReaSE INET Patch
else
  AX_PCAPDEV              dnl Check for pcap dev library if not building for real-world
fi

AX_XERCESCDEV             dnl Check for xercesc dev library
AX_PTHREAD                dnl Check for pthread library
AX_LIBTOOLDEV             dnl Check for libtool dev library
BOOST_REQUIRE([1.38])     dnl Check for boost library version
BOOST_THREADS             dnl Check for Boost.Thread
BOOST_SERIALIZATION       dnl Check for Boost.Serialization
BOOST_SIGNALS             dnl Check for Boost.Signals
BOOST_ASIO                dnl Check for Boost.Asio
BOOST_SYSTEM              dnl Check for Boost.System

AC_CONFIG_FILES([
Makefile 
src/Makefile 
src/base/Makefile 
src/messages/Makefile 
src/modules/Makefile
])
AC_OUTPUT
