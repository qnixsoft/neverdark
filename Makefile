#!/bin/make -f

srcdir := ${PWD}
subdirs := src/ vss/ game/data/ client/

include scripts/Makefile.common
DESTDIR ?= /
PREFIX ?= ${DESTDIR}usr/local
MKDIR := ${PREFIX}/mk
include ${MKDIR}/hjs.mk

all: index.html main.js vim.css

main.js: client/

inline-js := main.js
index.html: pre-index.html ${inline-js}
	${scripts}/html_tool.sh pre-index.html ${inline-js} > $@

vim.css: vss/

subdirs-install := ${subdirs:%=%-install}
$(subdirs-install):
	${MAKE} -C ${@:%-install=%} install
install: ${subdirs-install}

subdirs-cleaner := ${subdirs:%=%-cleaner}
$(subdirs-cleaner):
	${MAKE} -C ${@:%-cleaner=%} cleaner
cleaner: ${subdirs-cleaner}
	rm config.status config.cache config.log

web: src
	${srcdir}/src/ws-server

game/data/: ${subdirs}

backup-date != date +%s
backup := neverdark-${backup-date}.tar.gz
backup: ${backup}
$(backup):
	tar czf $@ game/geo.db game/data/std-db.db

.PHONY: cleaner ${subdirs-cleaner} web \
	${mt-phony-${mt}} metal-tar backup
