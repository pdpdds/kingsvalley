
; these are common
PLY_AKM_HARDWARE_MSX = 1
PLY_AKM_MANAGE_SOUND_EFFECTS = 1
PLY_AKM_Rom = 1
PLY_AKM_ROM_Buffer = #c000

include "PlayerAkm.asm"

; IN: L = channel
; OUT: L = 0 if is not on
PLY_AKM_IsSoundEffectOnDisarkGenerateExternalLabel:
PLY_AKM_IsSoundEffectOn:
	ld a,l
	add a,a
	add a,a
	add a,a
	ld c,a
	ld b,0
        ld hl,PLY_AKM_Channel1_SoundEffectData
	add hl,bc
	ld a,(hl)
	inc hl
	or (hl)
	ld l,a
	ret

