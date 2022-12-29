.module mplayer

.globl _mplayer_play_effect

.globl _PLY_AKM_PLAYSOUNDEFFECT

_mplayer_play_effect::
	ld hl, #2
	add hl, sp

	ld a, (hl)
	inc hl
	ld c, (hl)
	inc hl
	ld b, (hl)

        jp _PLY_AKM_PLAYSOUNDEFFECT

