# SYNOPSIS
#
#   AX_LIBTOOLDEV()
#
# DESCRIPTION
#
#   Test for the Dev version of Libtool
#
# LAST MODIFICATION
#
#   2009-02-17

AC_DEFUN([AX_LIBTOOLDEV],
[
  AC_CHECK_HEADER([ltdl.h],[], 
    AC_MSG_ERROR([libltdl library not found. install libltdl-dev]))

  AC_CHECK_LIB(ltdl, main, [], 
    AC_MSG_ERROR([libltdl library not found. install libltdl-dev])) 
])
