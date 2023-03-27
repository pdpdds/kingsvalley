OPTIMIZED_CFLAGS = -O3 -ffast-math
CFLAGS = $(OPTIMIZED_CFLAGS) -std=c99 -Wall  \
	-I. -I..\..\allegro\include -I.\include -I../../include	-I../generated -I../djgpp/allegro/include -I../src
CFLAGS+= -I../../tools/apultra/src -I../../tools/apultra/src/libdivsufsort/include -I../../src/backend
CFLAGS += -DUSE_DATAFILE
CFLAGS += -DALLEGRO4 -DDJGPP
CPPFLAGS = $(OPTIMIZED_CFLAGS) -Wall  \
	-I. -I..\..\allegro\include -I.\include
CC = gcc.exe
CPP = gpp.exe

LDFLAGS = -L../djgpp/allegro/lib

.c.o: 
	$(CC) $(CFLAGS) -c $< 2>&1 | tee -a compile.log

src/%.o: ../src/%.c 
	$(CC) $(CFLAGS) -c -o $@ $< 

msvc.src/%.o: ../../src/backend/%.c 
	$(CC) $(CFLAGS) -c -o $@ $< 

apultra.src/%.o: ../../tools/apultra/src/%.c 
	$(CC) $(CFLAGS) -c -o $@ $< 	



OBJS += ../../tools/apultra/src/expand.o
OBJS += ../../tools/apultra/src/matchfinder.o
OBJS += ../../tools/apultra/src/shrink.o
OBJS += ../../tools/apultra/src/libdivsufsort/lib/divsufsort.o
OBJS += ../../tools/apultra/src/libdivsufsort/lib/divsufsort_utils.o
OBJS += ../../tools/apultra/src/libdivsufsort/lib/sssort.o
OBJS += ../../tools/apultra/src/libdivsufsort/lib/trsort.o

all: main.exe

main.exe : $(OBJS) $(patsubst %.c,%.o,$(wildcard ../src/*.c)) $(patsubst %.c,%.o,$(wildcard ../../src/backend/*.c))
	gcc -o main.exe ./*.o\
		$(LDFLAGS) -L../../allegro/lib -lalpng -lalleg -lstdc++
	strip main.exe

clean:
	rm -f *.o
	rm -f src/*.o	
	rm -f compile.log
	rm -f main.exe