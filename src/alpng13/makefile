# AllegroPNG
# MS Visual C++ without dependencies

CFLAGS = -IC:\github\allegro4_dos\msvc15\include

SOURCES = src\alpng_save.c src\alpng_interlacing.c src\alpng_filereader.c src\alpng_drawer.c src\alpng_common.c src\alpng_filters.c src\quantization\octree.c src\inflate\huffman.c src\inflate\inflate.c src\inflate\input.c

OBJECTS = objects\alpng_save.obj objects\alpng_interlacing.obj objects\alpng_filereader.obj objects\alpng_drawer.obj objects\alpng_common.obj objects\alpng_filters.obj objects\octree.obj objects\huffman.obj objects\inflate.obj objects\input.obj

all: alpng.lib ex01.exe

alpng.lib: $(OBJECTS)
	lib /nologo /out:alpng.lib $**

{}.c{objects/}.obj:
	cl $(CFLAGS) /nologo /MD /O2 /Isrc /c  /Fo$@ $<

{src\}.c{objects/}.obj:
	cl $(CFLAGS) /nologo /MD /O2 /Isrc /c  /Fo$@ $<

{src\inflate\}.c{objects/}.obj:
	cl $(CFLAGS) /nologo /MD /O2 /Isrc /c  /Fo$@ $<

{src\quantization\}.c{objects/}.obj:
	cl $(CFLAGS) /nologo /MD /O2 /Isrc /c  /Fo$@ $<

ex01.exe: objects\ex01.obj alpng.lib
	link /nologo /libpath:. /out:$@ $** alleg.lib 

clean: 
	del alpng.lib 2> nul
	del ex01.exe 2> nul
	del objects\*.obj 2> nul
	del ex01.exe.manifest 2> nul
