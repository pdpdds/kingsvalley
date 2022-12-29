########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = gcc
CFLAGS = -Wall -DSDL2 -g -I../../include -I../generated -I../../tools/apultra/src -I../src -I../../tools/apultra/src/libdivsufsort/include
CXXFLAGS = -fpermissive -std=c++11 -Wall -g -I../../include -I../generated -I../../tools/apultra/src/libdivsufsort/include -I../../tools/apultra/src -I../src
LDFLAGS = -lSDL2 -lGL -lGLEW -lSDL2_image -lSDL2_image -lSDL2_mixer

# Makefile settings - Can be customized.
APPNAME = kings
EXT = .c
SRCDIR = ../src
SRC2DIR = ../../src/backend
SRC3DIR = ../../tools/apultra/src
SRC4DIR = ./src
OBJDIR = obj

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
SRC2 = $(wildcard $(SRC2DIR)/*$(EXT))
SRC3 = $(wildcard $(SRC3DIR)/*$(EXT))
SRC4 = $(wildcard $(SRC4DIR)/*$(EXT))

OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
OBJ2 = $(SRC2:$(SRC2DIR)/%$(EXT)=$(OBJDIR)/%.o)

OBJ3 = $(SRC3DIR)/expand.o
OBJ3 += $(SRC3DIR)/matchfinder.o
OBJ3 += $(SRC3DIR)/shrink.o
OBJ3 += $(SRC3DIR)/libdivsufsort/lib/divsufsort.o
OBJ3 += $(SRC3DIR)/libdivsufsort/lib/divsufsort_utils.o
OBJ3 += $(SRC3DIR)/libdivsufsort/lib/sssort.o
OBJ3 += $(SRC3DIR)/libdivsufsort/lib/trsort.o

DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ) $(OBJ2) $(OBJ3)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

$(OBJDIR):
    mkdir -p $(OBJDIR)

# Builds the app
$(APPNAME): $(OBJ) $(OBJ2) $(OBJ3)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

%.d: $(SRC2DIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@	

%.d: $(SRC3DIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@			

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: $(SRC2DIR)/%$(EXT)
	$(CC) $(CFLAGS) -o $@ -c $<	

$(OBJDIR)/%.o: $(SRC3DIR)/%$(EXT)
	$(CC) $(CFLAGS) -o $@ -c $<			

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)
	rm -rf obj

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)