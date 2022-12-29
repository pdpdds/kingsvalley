akm_sdcc.z80: main.asm
	rasm main.asm -o akm -s -sl -sq
	Disark --sourceProfile sdcc --symbolFile akm.sym --src16bitsValuesInHex --src8bitsValuesInHex --undocumentedOpcodesToBytes akm.bin akm_sdcc.z80

