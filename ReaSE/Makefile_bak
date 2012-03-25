ifeq "$(OVERSIM)" "true"
	# Build ReaSE for OverSim
	INETDIR = `pwd`/../../INET-OverSim-20101019
	BUILD_OPTIONS = -f --deep -o rease -O out -Xout -I$(INETDIR)/src/base -I$(INETDIR)/src/networklayer/contract -I$(INETDIR)/src/networklayer/ipv4 -I$(INETDIR)/src/networklayer/common -I$(INETDIR)/src/linklayer/contract -I$(INETDIR)/src/networklayer/autorouting -I$(INETDIR)/src/networklayer/arp -I$(INETDIR)/src/transport/udp -I$(INETDIR)/src/transport/contract -I$(INETDIR)/src/transport/tcp -I$(INETDIR)/src/applications/pingapp -linet -L$(INETDIR)/src -KINET_PROJ=$(INETDIR)
	BUILD_OPTIONS += --make-lib
else
	# Build ReaSE as standalone for usage with OMNeT++ and INET only
	INETDIR = ../../INET
	BUILD_OPTIONS = -f --deep -u Cmdenv -o rease -O out -pREASE -I$(INETDIR)/src/networklayer/ipv6 -I$(INETDIR)/src/networklayer/common -I$(INETDIR)/src/util -I$(INETDIR)/src/networklayer/rsvp_te -I$(INETDIR)/src/applications/pingapp -I$(INETDIR)/src/transport/contract -I$(INETDIR)/src/networklayer/ipv4 -I$(INETDIR)/src/base -I$(INETDIR)/src/linklayer/contract -I$(INETDIR)/src/networklayer/arp -I$(INETDIR)/src/networklayer/icmpv6 -I$(INETDIR)/src/transport/udp -I$(INETDIR)/src/networklayer/ted -I$(INETDIR)/src/world -I$(INETDIR)/src/networklayer/contract -I$(INETDIR)/src/transport/tcp -I$(INETDIR)/src/linklayer/mfcore -I$(INETDIR)/src/networklayer/mpls -I$(INETDIR)/src/networklayer/ldp -I$(INETDIR)/src/networklayer/autorouting -L$(INETDIR)/out/gcc-debug/ -lINET -lpcap -KINET_PROJ=$(INETDIR)
endif

all: makefiles
	cd src && $(MAKE)

clean:
	cd src && $(MAKE) clean

cleanall:
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean

makefiles:
ifeq "$(OVERSIM)" "true"
	@echo "\nPlease note that ReaSE is built for usage with OverSim\n"
else
	@echo "\nPlease note that ReaSE is build for usage with OMNeT++ and INET. OverSim is not considered in this setting!\n"
	@echo "In order to compile ReaSE for OverSim ONLY, "
	@echo "verify the INET path in the if clause at the top of the Makefile and type 'make OVERSIM=true'.\n"
endif	
	cd src && opp_makemake $(BUILD_OPTIONS)
