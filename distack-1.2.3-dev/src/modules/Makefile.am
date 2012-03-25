lib_LTLIBRARIES =

# libraries ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# attackdetection libraries
lib_LTLIBRARIES += \
  libModuleAnalyzerAddressSpace.la \
  libModuleAnalyzerAggregateWatch.la \
  libModuleAnalyzerProtocolAnomaly.la \
  libModuleCollectorAddressSpace.la \
  libModuleCollectorAggregateThreshold.la

# sampling libraries
lib_LTLIBRARIES += \
  libModuleFilterProtocol.la \
  libModuleFilterSubnet.la \
  libModuleSamplingNoutOfN.la \
  libModuleSamplingSystematicCountBased.la \
  libModuleSamplingSystematicTimeBased.la \
  libModuleSamplingUniformProbabilistic.la

# utility libraries
lib_LTLIBRARIES += \
  libModuleOutputterPlotter.la \
  libModuleUtilityIpLister.la \
  libModuleUtilityTimer.la

# install path ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

libModuleAnalyzerAddressSpace_ladir               = ${pkgincludedir}/modules
libModuleAnalyzerAggregateWatch_ladir             = ${pkgincludedir}/modules
libModuleAnalyzerProtocolAnomaly_ladir            = ${pkgincludedir}/modules
libModuleCollectorAddressSpace_ladir              = ${pkgincludedir}/modules
libModuleCollectorAggregateThreshold_ladir        = ${pkgincludedir}/modules

libModuleFilterProtocol_ladir                     = ${pkgincludedir}/modules
libModuleFilterSubnet_ladir                       = ${pkgincludedir}/modules
libModuleSamplingNoutOfN_ladir                    = ${pkgincludedir}/modules
libModuleSamplingSystematicCountBased_ladir       = ${pkgincludedir}/modules
libModuleSamplingSystematicTimeBased_ladir        = ${pkgincludedir}/modules
libModuleSamplingUniformProbabilistic_ladir       = ${pkgincludedir}/modules

libModuleOutputterPlotter_ladir                   = ${pkgincludedir}/modules
libModuleUtilityIpLister_ladir                    = ${pkgincludedir}/modules
libModuleUtilityTimer_ladir                       = ${pkgincludedir}/modules

# sources and subdirs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

libModuleAnalyzerAddressSpace_la_SOURCES         = attackdetection/ModuleAnalyzerAddressSpace.cpp
libModuleAnalyzerAggregateWatch_la_SOURCES       = attackdetection/ModuleAnalyzerAggregateWatch.cpp
libModuleAnalyzerProtocolAnomaly_la_SOURCES      = attackdetection/ModuleAnalyzerProtocolAnomaly.cpp
libModuleCollectorAddressSpace_la_SOURCES        = attackdetection/ModuleCollectorAddressSpace.cpp
libModuleCollectorAggregateThreshold_la_SOURCES  = attackdetection/ModuleCollectorAggregateThreshold.cpp

libModuleFilterProtocol_la_SOURCES               = sampling/ModuleFilterProtocol.cpp
libModuleFilterSubnet_la_SOURCES                 = sampling/ModuleFilterSubnet.cpp
libModuleSamplingNoutOfN_la_SOURCES              = sampling/ModuleSamplingNoutOfN.cpp
libModuleSamplingSystematicCountBased_la_SOURCES = sampling/ModuleSamplingSystematicCountBased.cpp
libModuleSamplingSystematicTimeBased_la_SOURCES  = sampling/ModuleSamplingSystematicTimeBased.cpp
libModuleSamplingUniformProbabilistic_la_SOURCES = sampling/ModuleSamplingUniformProbabilistic.cpp

libModuleOutputterPlotter_la_SOURCES             = utility/ModuleOutputterPlotter.cpp
libModuleUtilityIpLister_la_SOURCES              = utility/ModuleUtilityIpLister.cpp
libModuleUtilityTimer_la_SOURCES                 = utility/ModuleUtilityTimer.cpp

# headers and subdirs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

nobase_libModuleAnalyzerAddressSpace_la_HEADERS         = attackdetection/ModuleAnalyzerAddressSpace.h
nobase_libModuleAnalyzerAggregateWatch_la_HEADERS       = attackdetection/ModuleAnalyzerAggregateWatch.h
nobase_libModuleAnalyzerProtocolAnomaly_la_HEADERS      = attackdetection/ModuleAnalyzerProtocolAnomaly.h
nobase_libModuleCollectorAddressSpace_la_HEADERS        = attackdetection/ModuleCollectorAddressSpace.h
nobase_libModuleCollectorAggregateThreshold_la_HEADERS  = attackdetection/ModuleCollectorAggregateThreshold.h

nobase_libModuleFilterProtocol_la_HEADERS               = sampling/ModuleFilterProtocol.h
nobase_libModuleFilterSubnet_la_HEADERS                 = sampling/ModuleFilterSubnet.h
nobase_libModuleSamplingNoutOfN_la_HEADERS              = sampling/ModuleSamplingNoutOfN.h
nobase_libModuleSamplingSystematicCountBased_la_HEADERS = sampling/ModuleSamplingSystematicCountBased.h
nobase_libModuleSamplingSystematicTimeBased_la_HEADERS  = sampling/ModuleSamplingSystematicTimeBased.h
nobase_libModuleSamplingUniformProbabilistic_la_HEADERS = sampling/ModuleSamplingUniformProbabilistic.h

nobase_libModuleOutputterPlotter_la_HEADERS             = utility/ModuleOutputterPlotter.h
nobase_libModuleUtilityIpLister_la_HEADERS              = utility/ModuleUtilityIpLister.h
nobase_libModuleUtilityTimer_la_HEADERS                 = utility/ModuleUtilityTimer.h


# compiler flags ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AM_CPPFLAGS     = -fPIC -DLINUX -D_LINUX -I../ -D_REENTRANT \
                  -D_FILE_OFFSET_BITS=64 -pthread -fvisibility=default

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

AM_LDFLAGS      = -rdynamic

if OMNET_SIMULATION
  AM_LDFLAGS   += -shared
endif
