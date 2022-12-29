#include <stdint.h>
#include <string.h>

#include "spman.h"

#define SPMAN_PAT_UNUSED    0xff
#define SPMAN_MAX_SPRITES   32
#define SPMAN_MAX_PATTERNS  64
#define SPMAN_SPR_ATTRS     0x1b00

uint8_t sp_last_sprite, sp_last_fixed_sprite, sp_idx;
struct sprite_attr sp_fixed[SPMAN_MAX_SPRITES];
struct sprite_attr sp_buffer[SPMAN_MAX_SPRITES * 2];

uint8_t sp_pat_map[SPMAN_MAX_PATTERNS];
uint8_t sp_last_pat;

void spman_init()
{
    sp_last_pat = 0;
    sp_idx = 0;
    memset(sp_pat_map, SPMAN_PAT_UNUSED, SPMAN_MAX_PATTERNS);
    spman_sprite_flush();
}

uint8_t spman_alloc_pat(uint8_t type, uint8_t *data, uint8_t len, uint8_t flip)
{
    uint8_t i;

    if (sp_pat_map[type] == SPMAN_PAT_UNUSED)
    {
        sp_pat_map[type] = sp_last_pat;
        for (i = 0; i < len; ++i)
        {
            if (flip)
                ubox_set_sprite_pat16_flip(data, sp_last_pat);
            else
                ubox_set_sprite_pat16(data, sp_last_pat);

            data += 32;
            sp_last_pat++;
        }
#ifdef SPMAN_DEBUG
        if (sp_last_pat > 63)
            ubox_set_colors(15, 0, 0);
#endif
    }

    return sp_pat_map[type] * 4;
}

void spman_sprite_flush()
{
    sp_last_fixed_sprite = 0;
    sp_last_sprite = 0;
}

void spman_alloc_fixed_sprite(struct sprite_attr *sp)
{
#ifdef SPMAN_DEBUG
    if (sp_last_fixed_sprite + sp_last_sprite > 30)
    {
        ubox_set_colors(15, 0, 0);
        return;
    }
#endif
    memcpy(&sp_fixed[sp_last_fixed_sprite++], sp, 4);
}

void spman_alloc_sprite(struct sprite_attr *sp)
{
#ifdef SPMAN_DEBUG
    if (sp_last_fixed_sprite + sp_last_sprite > 30)
    {
        ubox_set_colors(15, 0, 0);
        return;
    }
#endif
    memcpy(&sp_buffer[sp_last_sprite++], sp, 4);
}

static const struct sprite_attr hide = { 208, 0, 0, 0 };

static uint8_t *p;

void spman_update()
{
    p = (uint8_t*)SPMAN_SPR_ATTRS;

    if (sp_last_sprite)
    {
        memcpy(&sp_buffer[sp_last_sprite], sp_buffer, sp_last_sprite * 4);

        if (sp_last_sprite > 2)
            sp_idx += 2;

        if (sp_idx >= sp_last_sprite)
            sp_idx -= sp_last_sprite;
    }
    else
        sp_idx = 0;

    memcpy(&sp_buffer[sp_idx + sp_last_sprite], &hide, 4);

    ubox_wait_vsync();
    if (sp_last_fixed_sprite)
    {
        ubox_write_vm(p, sp_last_fixed_sprite * 4, (uint8_t *)sp_fixed);
        p += sp_last_fixed_sprite * 4;
    }
    ubox_write_vm(p, 4 + sp_last_sprite * 4, (uint8_t *)&sp_buffer[sp_idx]);

    spman_sprite_flush();
}

void spman_hide_all_sprites()
{
    ubox_wait_vsync();
    ubox_write_vm((uint8_t *)SPMAN_SPR_ATTRS, 4, (uint8_t *)hide);
}
