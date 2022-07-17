.POSIX:
# scripts path
SCRIPTDIR=$(shell pwd)/scripts
CPU=$(SCRIPTDIR)/cpu
INTERNET=$(SCRIPTDIR)/internet
MEMORY=$(SCRIPTDIR)/memory
VOLUME=$(SCRIPTDIR)/volume
CLOCK=$(SCRIPTDIR)/clock
# preprocessor defined for scripts
CDEF = -DCPU=\"$(CPU)\" -DINTERNET=\"$(INTERNET)\" -DMEMORY=\"$(MEMORY)\" -DVOLUME=\"$(VOLUME)\" -DCLOCK=\"$(CLOCK)\" -DSCRIPTDIR=\"$(SCRIPTDIR)\"
CFLAGS= -lX11
PREFIX = /usr/local
CC = gcc

dwmblocks: dwmblocks.o
	$(CC) -o $@ $< $(CFLAGS) $(CDEF)
dwmblocks.o: dwmblocks.c blocks.h
	$(CC) -c $< $(CFLAGS) $(CDEF)
clean:
	rm -f *.o *.gch dwmblocks
install: dwmblocks
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 0755 dwmblocks $(DESTDIR)$(PREFIX)/bin/dwmblocks
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dwmblocks

.PHONY: clean install uninstall
