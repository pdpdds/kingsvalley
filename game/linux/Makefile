########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = gcc
CFLAGS = -Wall -fcommon -DSDL2 -g -I../../include -I../generated -I../../tools/apultra/src -I../src -I../../tools/apultra/src/libdivsufsort/include -I../../src/backend
CXXFLAGS = -fpermissive -std=c++11 -Wall -g -I../../include -I../generated -I../../tools/apultra/src/libdivsufsort/include -I../../tools/apultra/src -I../src
LDFLAGS = -lSDL2 -lGL -lGLEW -lSDL2_image -lSDL2_image -lSDL2_mixer  -lSDL2_gfx -lSDL2_ttf

# Makefile settings - Can be customized.
APPNAME = kings
EXT = .c
SRCDIR = ../src
SRC2DIR = ../../src/backend
SRC3DIR = ../../tools/apultra/src
SRC4DIR = ../../src/backend/sdl_common
SRC5DIR = ../../src/backend/sdl2
OBJDIR = obj

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
SRC2 = $(wildcard $(SRC2DIR)/*$(EXT))
SRC3 = $(wildcard $(SRC3DIR)/*$(EXT))
SRC4 = $(wildcard $(SRC4DIR)/*$(EXT))
SRC5 = $(wildcard $(SRC5DIR)/*$(EXT))

OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
OBJ2 = $(SRC2:$(SRC2DIR)/%$(EXT)=$(OBJDIR)/%.o)

OBJ3 = $(SRC3DIR)/expand.o
OBJ3 += $(SRC3DIR)/matchfinder.o
OBJ3 += $(SRC3DIR)/shrink.o
OBJ3 += $(SRC3DIR)/libdivsufsort/lib/divsufsort.o
OBJ3 += $(SRC3DIR)/libdivsufsort/lib/divsufsort_utils.o
OBJ3 += $(SRC3DIR)/libdivsufsort/lib/sssort.o
OBJ3 += $(SRC3DIR)/libdivsufsort/lib/trsort.o


OBJ4 = $(SRC4:$(SRC4DIR)/%$(EXT)=$(OBJDIR)/%.o)
OBJ5 = $(SRC5:$(SRC5DIR)/%$(EXT)=$(OBJDIR)/%.o)

DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)
TEMP_DIR = obj
########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(TEMP_DIR) $(APPNAME)
	
$(TEMP_DIR):
	mkdir -p $(OBJDIR)

# Builds the app
$(APPNAME):  $(OBJ) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

%.d: $(SRC2DIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@	

%.d: $(SRC3DIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@			
	
%.d: $(SRC4DIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@			
	
%.d: $(SRC5DIR)/%$(EXT)
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
	
$(OBJDIR)/%.o: $(SRC4DIR)/%$(EXT)
	$(CC) $(CFLAGS) -o $@ -c $<		
	
$(OBJDIR)/%.o: $(SRC5DIR)/%$(EXT)
	$(CC) $(CFLAGS) -o $@ -c $<		

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) -rf $(DELOBJ) $(DEP) $(APPNAME)
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