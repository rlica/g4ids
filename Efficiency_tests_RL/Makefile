BINDIR = $(ROOTSYS)/usr/bin
MANDIR = $(ROOTSYS)/usr/share/man/man1


ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
ROOTINC      := -I$(shell root-config --incdir)

CC           = gcc
CPP          = g++

CFLAGS       += -Wall
CFLAGS       += -g
CFLAGS       += -std=c++0x

CFLAGS       += $(ROOTCFLAGS) -w
LDFLAGS      += -Wl,-no-as-needed $(ROOTLIBS) -Lusr/lib64
#LDFLAGS      += -Wl, $(ROOTLIBS) 


EXE1 = ./clover_g4_eff
OBJ1 = Clover_G4_eff.o
SRC1 = Clover_G4_eff.C
MAN1 = Clover_G4_eff.1
DICT = Terminator.Dict.cc
DICTOBJ = Terminator.Dict.o

all: $(DICT) $(LIB1) $(EXE1)

$(DICT): Terminator.hh
	 rootcint -f Terminator.Dict.cc -c Terminator.hh

$(DICTOBJ): $(DICT)
	 $(CPP) $(ROOTCFLAGS) -I. -c -o Terminator.Dict.o Terminator.Dict.cc

$(LIB1): $(LIB1OBJS)
	 $(CPP) -shared -WI,-soname,$(LIB1) -o $@ $(LIB1OBJS)

$(EXE1): $(OBJ1) $(LIB1) $(DICTOBJ)
	$(CPP) $(LDFLAGS)  -o $(EXE1) $(OBJ1) $(DICTOBJ)
	
$(OBJ1) : $(SRC1)
	$(CPP) $(CFLAGS) -I. -c -o $(OBJ1) $(SRC1)

%.o: %.cc
	$(CPP) $(CFLAGS) -c $< -o $@

clean:
	rm -f *~ *.o $(OBJ1) $(EXE1) $(DICT) $(DICTOBJ) Terminator.Dict.h

install: $(EXE1)
	install -m 755 -d $(BINDIR)
	install -m 755 $(EXE1) $(BINDIR)
	install -m 755 -d $(MANDIR)
	install -m 644 $(MAN1) $(MANDIR)

deinstall:
	rm -f $(EXEDIR)/$(EXE1)

