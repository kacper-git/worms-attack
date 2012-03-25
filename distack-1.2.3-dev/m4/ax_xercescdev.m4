# SYNOPSIS
#
#   AX_XERCESCDEV()
#
# DESCRIPTION
#
#   Test for xercesc dev library
#
# LAST MODIFICATION
#
#   2009-02-25

AC_DEFUN([AX_XERCESCDEV],
[
  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_CHECK_HEADER([xercesc/dom/DOMDocument.hpp],[], 
    AC_MSG_ERROR([xerces-c headers not found. install libxerces-dev]))
  AC_LANG_RESTORE

  AC_CHECK_LIB(xerces-c, main, [], 
    AC_MSG_ERROR([xerces-c library not found. install libxerces-dev]))
])
