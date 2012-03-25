if OMNET_SIMULATION
lib_LTLIBRARIES = libdistack.la
else
bin_PROGRAMS    = distack
endif

# compiler flags ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AM_CPPFLAGS     = -rdynamic -fPIC -DLINUX -D_LINUX -I../src 
AM_CPPFLAGS    += -D_REENTRANT -D_FILE_OFFSET_BITS=64 -pthread -fvisibility=default
AM_CPPFLAGS    += $(BOOST_CPPFLAGS)

if DEBUG
  AM_CPPFLAGS  += -ggdb -DDEBUG
endif

if REMOTE_XML
  AM_CPPFLAGS  += -DREMOTE_XML
endif

if OMNET_SIMULATION
  AM_CPPFLAGS  += -DOMNET_SIMULATION
endif

# linker flags ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AM_LDFLAGS     = -lpthread -lxerces-c -lltdl -rdynamic

AM_LDFLAGS    += $(BOOST_THREAD_LDFLAGS) $(BOOST_POOL_LDFLAGS) \
                 $(BOOST_SERIALIZATION_LDFLAGS) $(BOOST_SIGNALS_LDFLAGS) \
                 $(BOOST_SYSTEM_LDFLAGS)

LIBS          += $(BOOST_THREAD_LIBS) $(BOOST_POOL_LIBS) \
                 $(BOOST_SERIALIZATION_LIBS) $(BOOST_SIGNALS_LIBS) \
                 $(BOOST_SYSTEM_LIBS)

if OMNET_SIMULATION
  AM_LDFLAGS  += -shared
else
  AM_LDFLAGS  += -lpcap
endif

# sources and subdirs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SUBDIRS         = base messages modules

if OMNET_SIMULATION
  libdistack_ladir             = ${pkgincludedir}
  libdistack_la_SOURCES        = Distack.cpp
  nobase_libdistack_la_HEADERS = Distack.h
  libdistack_la_LIBADD         = base/libdistackbase.a messages/libdistackmessage.a
  libdistack_la_LIBADD        += base/*.o messages/*.o
else
  # workaround from http://www.gnu.org/software/libtool/manual/automake/Libtool-Issues.html
  distack_CPPFLAGS             = $(AM_CPPFLAGS)
  distack_SOURCES              = Distack.cpp Distack.h
  distack_LDADD                = base/libdistackbase.a messages/libdistackmessage.a
  distack_LDADD               += base/*.o messages/*.o
endif
