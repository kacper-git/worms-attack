##################################################
#              Distack messages                  #
##################################################

lib_LIBRARIES = libdistackmessage.a
AM_CPPFLAGS   = -fPIC -DLINUX -D_LINUX -I../ -D_REENTRANT -D_FILE_OFFSET_BITS=64 -pthread -fvisibility=default
libdistackmessage_a_SOURCES =
nobase_libdistackmessage_a_HEADERS =

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

libdistackmessage_adir = ${pkgincludedir}/messages

########### source files start here ###########

# attackdetection
libdistackmessage_a_SOURCES += \
  attackdetection/MessageAddressDistribution.cpp \
  attackdetection/MessageAggregateIntervalValues.cpp \
  attackdetection/MessageAggregateWatchValues.cpp \
  attackdetection/MessageLastAnomalyType.cpp \
  attackdetection/MessageLastSuspiciousAggregate.cpp

#utility
libdistackmessage_a_SOURCES += \
  utility/MessageAlert.cpp \
  utility/MessageTimer.cpp

########### header files start here ###########

# attackdetection
nobase_libdistackmessage_a_HEADERS += \
  attackdetection/MessageAddressDistribution.h \
  attackdetection/MessageAggregateIntervalValues.h \
  attackdetection/MessageAggregateWatchValues.h \
  attackdetection/MessageLastAnomalyType.h \
  attackdetection/MessageLastSuspiciousAggregate.h

#utility
nobase_libdistackmessage_a_HEADERS += \
  utility/MessageAlert.h \
  utility/MessageTimer.h

#####################################################
#       ADD YOUR NEW MESSAGE FILES HERE!!!          #
#####################################################

# libmessage_a_SOURCES +=
# nobase_libdistackmessage_a_HEADERS +=