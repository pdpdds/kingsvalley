.globl _mplayer_init

.globl _PLY_AKM_INIT

_mplayer_init::
	ld ix, #2
	add ix, sp

	ld l, 0 (ix)
	ld h, 1 (ix)
	ld a, 2 (ix)

	di
	call _PLY_AKM_INIT
	ei

	ret
