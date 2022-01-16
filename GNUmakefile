# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:40 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for e377 module.  Florin Rotaru, 18/09/2006.
# geant4.10.00.p01              Razvan Lica,   22/07/2014
# --------------------------------------------------------------

name := is530
G4TARGET := $(name)
G4EXLIB := true


CPPFLAGS += $(shell root-config --cflags)
EXTRALIBS += $(shell root-config --glibs) -L/usr/local/lib/


ifndef G4INSTALL
  G4INSTALL = /usr/local/geant4.10.00.p01
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/share/Geant4-10.0.1/geant4make/config/architecture.gmk

include $(G4INSTALL)/share/Geant4-10.0.1/geant4make/config/binmake.gmk

include $(G4INSTALL)/share/Geant4-10.0.1/geant4make/config/common.gmk

include $(G4INSTALL)/share/Geant4-10.0.1/geant4make/config/geomconf.gmk

include $(G4INSTALL)/share/Geant4-10.0.1/geant4make/config/G4UI_USE.gmk

include $(G4INSTALL)/share/Geant4-10.0.1/geant4make/config/G4VIS_USE.gmk

include $(G4INSTALL)/share/Geant4-10.0.1/geant4make/config/interactivity.gmk

include $(G4INSTALL)/share/Geant4-10.0.1/geant4make/config/analysis.gmk

include $(G4INSTALL)/share/Geant4-10.0.1/geant4make/config/common.gmk
