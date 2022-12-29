/*
 * spman lib
 * Copyright (C) 2020-2022 by Juan J. Martinez <jjm@usebox.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _SPMAN_H
#define _SPMAN_H

#include <stdint.h>

#include "ubox.h"

// @Initialization and pattern allocation

/**
 * Initialize **spman**.
 *
 * Sets all the patterns as unused and no allocated sprites.
 *
 * it needs to be called before using any of the functions of the sprite manager.
 */
void spman_init();

/**
 * Allocates a pattern for sprite `type` using `data`.
 *
 * `len` specifies the number of sprite patterns to allocate (16x16 each,
 * exactly 32 bytes).
 *
 * If `flip` is set to a non zero value, the pattern data will be flipped
 * horizontally.
 *
 * The function returns the allocated index in the pattern table, than can be
 * used in [struct sprite_attr](ubox-lib-ref.html#struct-sprite_attr). It
 * can be called multiple times for the same `type` and the allocation happens
 * only once per `type`, returning the previously allocated index.
 *
 * `type` is an abstraction to group patterns. For example, if our game's
 * player character has 3 animation frames per horizontal direction, we could
 * use two different types to group those.
 *
 * Example:
 * ```c
 * enum sprite_types
 * {
 *   SPRITE_PLAYER = 0,
 *   SPRITE_PLAYER_FLIP,
 *   SPRITE_ENEMY,
 * }:
 *
 * spman_alloc_pat(SPRITE_PLAYER, player_sprite, 3, 0);
 * // allocate the same frames flipped horizontally, on the next type
 * spman_alloc_pat(SPRITE_PLAYER_FLIP, player_sprite, 3, 1);
 *
 * // only one frame, keep the allocated pattern
 * uint8_t enemy_pat = spman_alloc_pat(SPRITE_ENEMY, enemy_sprite, 1, 0);
 * ```
 *
 * A `type` can't be reused with a different pattern, [spman_init](#spman_init)
 * has to be called again to free all the patterns.
 */
uint8_t spman_alloc_pat(uint8_t type, uint8_t *data, uint8_t len, uint8_t flip);

// @Sprite allocation

/**
 * Allocates a sprite described by `sp` to be shown on the screen on the next
 * call to [spman_update](#spman_update). This sprite will be excluded from
 * flickering.
 *
 * It is recommended that the number of fixed sprites per line is below 4, or
 * some sprites may never be shown.
 *
 * The limit of sprites to be allocated is 31, including non-fixed sprites.
 *
 * The pattern specified in the struct should be allocated with
 * [spman_alloc_pat](#spman_alloc_pat).
 *
 * Allocated sprites are shown on screen by calling to
 * [spman_update](#spman_update).
 */
void spman_alloc_fixed_sprite(struct sprite_attr *sp);

/**
 * Allocates a sprite described by `sp` to be shown on the screen on the next
 * call to [spman_update](#spman_update).
 *
 * If more than 4 sprites are drawn on the same line, the sprite manager will
 * alternate which ones are drawn, resulting on a "flickering" effect.
 *
 * The limit of sprites to be allocated is 31, including fixed sprites.
 *
 * The pattern specified in the struct should be allocated with
 * [spman_alloc_pat](#spman_alloc_pat).
 *
 * Allocated sprites are shown on screen by calling to
 * [spman_update](#spman_update).
 */
void spman_alloc_sprite(struct sprite_attr *sp);

/**
 * Any allocated sprite will be freed.
 *
 * This doesn't affect sprites currently being shown on the screen.
 */
void spman_sprite_flush();

// @Sprites on screen

/**
 * Allocated sprites are processed, making the changes visible on screen.
 *
 * Once the changes have been applied, all the allocations are freed. This
 * doesn't affect the sprites being shown on screen.
 *
 * Sprites must be allocated with
 * [spman_alloc_fixed_sprite](#spman_alloc_fixed_sprite) and
 * [spman_alloc_sprite](#spman_alloc_sprite).
 *
 */
void spman_update();

/**
 * Hides all the sprites currently shown on screen.
 *
 * This doesn't affect any allocated sprites. To free allocated sprites use
 * [spman_sprite_flush](#spman_sprite_flush).
 */
void spman_hide_all_sprites();

#endif //  _SPMAN_H
