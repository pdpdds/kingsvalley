.module mplayer

.globl _mplayer_init_effects
.globl mplayer_current_efx

.globl _PLY_AKM_INITSOUNDEFFECTS

_mplayer_init_effects::
        xor a
        ld (mplayer_current_efx), a
        jp _PLY_AKM_INITSOUNDEFFECTS

.area _DATA

mplayer_current_efx: .ds 1

