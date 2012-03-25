SUBDIRS = src
ACLOCAL_AMFLAGS = -I m4

dist-hook:
	find $(distdir) -name '.[a-zA-Z0-9]*' | xargs rm -rf

EXTRA_DIST = etc/* AUTHORS INSTALL README bootstrap
