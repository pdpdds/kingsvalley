all: generated bin build
	make -C data
	cd src && python ../tools/mkdeps.py -b ../build -I ../generated:../../include ./ Makefile.deps
	make -C src

generated:
	mkdir -p ./generated

bin:
	mkdir -p ./bin

build:
	mkdir -p ./build

.PHONY: all clean
clean:
	rm -rf ./generated ./bin ./build
	make -C src clean
	make -C data clean

