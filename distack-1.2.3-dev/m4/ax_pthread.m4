# SYNOPSIS
#
#   AX_PTHREAD()
#
# DESCRIPTION
#
#   Test for pthread library
#
# LAST MODIFICATION
#
#   2009-02-17

AC_DEFUN([AX_PTHREAD],
[
  AC_CHECK_HEADER([pthread.h],[], 
    AC_MSG_ERROR([pthread library not found. install pthread]))

  AC_CHECK_LIB(pthread, main, [], 
    AC_MSG_ERROR([pthread library not found. install pthread]))
])
