# DIR_FUNCIONES = funcArchivoTXT funcDirectorio funcFirebird funcSocket funcString
#
#.PHONY: func
#
# func:
#	$(MAKE) -C $(DIR_FUNCIONES)

SUBDIRS := $(wildcard func*/)

SHELL=/bin/bash

all:
	@for a in $(SUBDIRS); do \
		if [ -d $$a ]; then \
			echo "Compilando: $$a"; \
			$(MAKE) -C $$a; \
		fi; \
	done;

clean:
	@for a in $(SUBDIRS); do \
		if [ -d $$a ]; then \
			echo "Compilando: $$a"; \
			$(MAKE) -C $$a clean;\
		fi; \
	done;
