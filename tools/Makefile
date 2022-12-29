BIN := ../bin/hex2bin ../bin/rasm ../bin/apultra

all: $(BIN)

../bin/hex2bin:
	mkdir -p hex2bin-2.0/bin
	make -C hex2bin-2.0
	make -C hex2bin-2.0 cleanall

../bin/rasm:
	make -C rasm

../bin/apultra:
	make -C apultra

.PHONY: all clean
clean:
	make -C hex2bin-2.0 cleanall
	make -C rasm clean
