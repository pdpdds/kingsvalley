all: libs

export PATH := $(PWD)/bin:$(PATH)

libs: lib ubox spman mplayer ap

game: bin libs
	make -C tools
	make -C game
	
openmsx: game
	openmsx.exe -carta ./bin/kings.rom -machine C-BIOS_MSX2
	
gulkave: bin libs
	make -C gulkave clean
	make -C tools
	make -C gulkave	
	openmsx.exe -carta ./bin/gulkave.rom -machine C-BIOS_MSX2

docs:
	make -C docs

ubox:
	make -C src/ubox

spman:
	make -C src/spman

mplayer:
	make -C src/mplayer

ap:
	make -C src/ap

bin/apultra: bin
	make -C tools ../bin/apultra

.PHONY: clean cleanall docs libs game
clean:
	make -C src/ubox clean
	make -C src/spman clean
	make -C src/mplayer clean
	make -C src/ap clean
	make -C game clean

lib:
	mkdir -p ./lib

bin:
	mkdir -p ./bin

cleanall: clean
	rm -rf ./bin ./lib
	make -C docs clean

