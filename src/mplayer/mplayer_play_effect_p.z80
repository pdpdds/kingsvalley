.module mplayer

.globl _mplayer_play_effect_p
.globl _mplayer_is_sound_effect_on
.globl mplayer_current_efx

.globl _PLY_AKM_PLAYSOUNDEFFECT

_mplayer_play_effect_p::
	ld hl, #2
	add hl, sp

	ld e, (hl)
	inc hl
	ld c, (hl)
        inc hl
        ld b, (hl)

        ; e effect no
        ; bc: channel and volume
        push bc
        push de
        ld l, c
        call _mplayer_is_sound_effect_on

	ld a, l
	or a
        pop de
        pop bc
	jr z, play_efx

	ld a, (mplayer_current_efx)
        ; comment out following line if you don't want to
        ; replace current sound if is the same effect type
        dec a
	cp e
	ret nc

play_efx:
	; all good, play the effect
	ld a, e
	ld (mplayer_current_efx), a

        jp _PLY_AKM_PLAYSOUNDEFFECT

