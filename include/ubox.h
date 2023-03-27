/*
 * ubox MSX lib
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

#ifndef _UBOX_MSX_H
#define _UBOX_MSX_H

#include <stdint.h>

#if defined(_WIN32)
 // Windows
#if defined(UBOX_API_EXPORTS)
#define UBOX_EXPORT_API __declspec(dllexport)
#else
#define UBOX_EXPORT_API __declspec(dllimport)
#endif
#elif defined(__linux)
 // Linux
#define UBOX_EXPORT_API __attribute__((visibility("default")))
#else
#define UBOX_EXPORT_API
#endif

extern uint8_t* VIDEO_MEMORY_ADDRESS;

#if defined(WIN32) || (__ANDROID__) || defined(SKYOS32) || defined(__linux) || defined(DJGPP) 
#define __z88dk_fastcall
#endif

// @Screen and VDP functions
//
// These functions are not necessarily MSX 1 specific, but only MSX 1
// functionality is documented.
//
// Both the tiles and sprite functions target Screen 2 (256x192 pixels graphics
// mode).
//
// The VRAM layout for Screen 2 is as follows:
//
// | Address range          | Description         |
// | ---                    | ---                 |
// | <tt>0x0000-0x17ff</tt> | Background tiles    |
// | <tt>0x1800-0x1aff</tt> | Background tile map |
// | <tt>0x1b00-0x1b7f</tt> | Sprite attributes   |
// | <tt>0x2000-0x37ff</tt> | Background colors   |
// | <tt>0x3800-0x3fff</tt> | Sprite patterns     |
//

/**
 * Sets the screen mode to `mode`.
 *
 * This is a list of the different MSX 1 modes:
 *
 * | Mode | Name     | Description                          |
 * | ---  | ---      | ---                                  |
 * | 0    | Screen 0 | 40x24 text mode                      |
 * | 1    | Screen 1 | 32x24 colored text mode              |
 * | 2    | Screen 2 | 256x192 graphics mode                |
 * | 3    | Screen 3 | 64*48 block graphics multicolor mode |
 *
 * Example:
 *
 * ```c
 * // sets Screen 2
 * ubox_set_mode(2);
 * ```
 */

UBOX_EXPORT_API void ubox_set_mode(uint8_t mode) __z88dk_fastcall;

/**
 * Enables the screen.
 */
UBOX_EXPORT_API void ubox_enable_screen();

/**
 * Disables the screen.
 *
 * Any content drawn to the screen won't be visible until the screen is enabled
 * with [ubox_enable_screen](#ubox_enable_screen).
 *
 * Note that [ubox_set_mode](#ubox_set_mode) also enables the screen.
 */
UBOX_EXPORT_API void ubox_disable_screen();

/**
 * Changes the screen colors.
 *
 * First it sets `FORCLR` (foreground) to `fg`, `BAKCLR` (background) to `bg`
 * and `BDRCLR` to `border`, and then makes them active.
 *
 * Example:
 *
 * ```c
 * // sets all three colours to black
 * ubox_set_colors(1, 1, 1);
 * ```
 */
UBOX_EXPORT_API void ubox_set_colors(uint8_t fg, uint8_t bg, uint8_t border);

/**
 * Writes a block of `len` bytes from `src` in memory to `dst` in VRAM (video
 * memory).
 *
 * Example:
 * ```c
 * // copy 4 sprites attributes from a buffer to the
 * // sprite attribute table in Screen 2 mode
 * ubox_write_vm((uint8_t*)0x1b00, 4 * 4, buffer);
 * ```
 */
UBOX_EXPORT_API void ubox_write_vm(uint8_t *dst, uint16_t len, uint8_t *src);

/**
 * Reads a block of `len` bytes from `src` in VMEM (video memory) to `dst`
 * in memory.
 */
UBOX_EXPORT_API void ubox_read_vm(uint8_t *dst, uint16_t len, uint8_t *src);

/**
 * Writes `data` to the `reg` VDP register.
 *
 * This function is used to setup the VDP, for example to enable 16x16 sprites.
 *
 * The VDP has 8 registers, from 0 to 7. For example, it is common to use
 * register 1 to enable 16x16 sprites.
 *
 * The control bits in register 1 are:
 *
 * | Bit | Description                           |
 * | --- | ---                                   |
 * | 0   | Enable sprite zoom (x2)               |
 * | 1   | Enable 16x16 sprites (default is 8x8) |
 * | 2   | Not used                              |
 * | 3   | Enable Mode M2, Screen 3 (block)      |
 * | 4   | Enable Mode M1, Screen 0 (text)       |
 * | 5   | Enable v-blank interrupt              |
 * | 6   | Enable screen output control          |
 * | 7   | VRAM size control (0: 4K, 1: 16K)     |
 *
 * Please refer to [Portar
 * Doc](http://problemkaputt.de/portar.htm#vdpregisters00h07hbasicmsx1msx2videoregisters)
 * for further info on VDP registers.
 *
 * Example:
 * ```c
 * // reg 1: activate sprites, v-blank int on, 16x16 sprites
 * ubox_wvdp(1, 0xe2);
 * ```
 */
UBOX_EXPORT_API void ubox_wvdp(uint8_t reg, uint8_t data);

/**
 * Returns the default interrupt frequency according to the BIOS.
 *
 * Possible values are:
 *
 * | Value | Frequency |
 * | ---   | ---       |
 * | 0     | 60Hz      |
 * | 1     | 50Hz      |
 */
UBOX_EXPORT_API uint8_t ubox_get_vsync_freq();

// *INDENT-OFF*
/**
 * This macro waits for the *vsync* interrupt.
 *
 * Interrupts must be enabled or this code will block indefinitely.
 *
 * Example:
 * ```c
 * ubox_wait_vsync();
 * // code to run after the int
 * ```
 */
#if defined(WIN32) || (__ANDROID__) || defined(SKYOS32)  || defined(__linux) || defined(DJGPP)
#define ubox_wait_vsync()
#else
#define ubox_wait_vsync() do { \
    __asm; \
    halt \
    __endasm; \
} while(0)
#endif
// *INDENT-ON*

// @Tile functions
//
// All the functions require **screen 2** (256x192 graphics mode, see
// [ubox_set_mode](#ubox_set_mode)).

/**
 * Sets the current tile set to the tile set pointed by `tiles`.
 *
 * The tile set is expected to have 256 tiles (8x8 pixels, 8 bytes per tile)
 * and it will be loaded into the VDP in all three screen sections.
 *
 * All the tiles functions use an index in this tile set (usually via a `tile`
 * parameter).
 */
UBOX_EXPORT_API void ubox_set_tiles(uint8_t *tiles) __z88dk_fastcall;

/**
 * Sets the current color table for current tile set to the color table pointed
 * by `colors`.
 *
 * The color table is expected to have the 8 color rows for each of the 256 tiles
 * of the tiles table (8 rows, 8 bytes per tile). The colors will be loaded into
 * the VDP in all three screen sections.
 */
UBOX_EXPORT_API void ubox_set_tiles_colors(uint8_t *colors) __z88dk_fastcall;

/**
 * Puts a tile from current tile set on the screen. The tile is identified by
 * index `tile` and placed on position (`x`,`y`).
 *
 * `x` and `y` units are tiles, and both are 0 based.
 *
 * Example:
 * ```c
 * // put the tile with index 1 on the top left corner of the screen
 * ubox_put_tile(0, 0, 1);
 * ```
 *
 * This function is expensive and it performs two calls to the VDP that must
 * keep the state between them. In case the interrupt handler performs
 * operations with the VDP, this function shouldn't be used.
 *
 * To put multiple tiles in a row, use [ubox_write_vm](#ubox_write_vm) instead. The
 * tile map is in the memory address `0x1800`.
 *
 * Example putting multiple tiles:
 * ```c
 * ubox_wait_vsync();
 * // write a complete row of tiles (32) from a buffer
 * ubox_write_vm((uint8_t *)0x1800, 32, buffer);
 * ```
 */
UBOX_EXPORT_API void ubox_put_tile(uint8_t x, uint8_t y, uint8_t tile);

/**
 * Returns the tile index at position (`x`, `y`).
 *
 * `x` and `y` units are tiles, and both are 0 based.
 */
UBOX_EXPORT_API uint8_t ubox_get_tile(uint8_t x, uint8_t y);

/**
 * Fills the screen with the tile from current tile set identified by `tile` index.
 *
 * See [ubox_set_tiles](#ubox_set_tiles) for for information on how to set a
 * tile set.
 */
UBOX_EXPORT_API void ubox_fill_screen(uint8_t tile) __z88dk_fastcall;

// @Interrupt and clock functions

/**
 * Installs and initializes the interrupt handler.
 *
 * `wait_ticks` is the maximum number of interrupts that [ubox_wait](#ubox_wait)
 * will wait. This value divides the frequency at which the machine generates the *vsync*
 * interrupt (50Hz for PAL and 60Hz for NTSC).
 *
 * Some common values are:
 *
 * | wait ticks | PAL      | NTSC   |
 * | ---        | ---      | ---    |
 * | 1          | 50 FPS   | 60 FPS |
 * | 2          | 25 FPS   | 30 FPS |
 * | 3          | 16.6 FPS | 20 FPS |
 *
 * Where FPS is the number of *frames per second* desired to update the game logic.
 *
 * Example:
 * ```c
 * // ubox_wait will wait for 2 ints (25 FPS)
 * ubox_init_isr(2);
 * ```
 *
 * This function must be called once before any of the interrupt and clock
 * functions are used.
 *
 * The installed interrupt handler uses `HTIMI_HOOK` instead of replacing the
 * BIOS handler.
 *
 * The interrupt handler will save all registers. The shadow registers are not
 * preserved or used.
 *
 * For performance reasons the BIOS keyboard buffer and key repeat functionality
 * are disabled, and because of that some BIOS functions, such as `CHGET`,
 * won't work.
 */
UBOX_EXPORT_API void ubox_init_isr(uint8_t wait_ticks) __z88dk_fastcall;

/**
 * Installs a user interrupt handler.
 *
 * The function pointed by `fn` doesn't need to preserve any registers because
 * that is done by the main interrupt handler.
 *
 * It is recommended that the user interrupt handler is short and uses the
 * minimal amount of CPU cycles.
 *
 * Example:
 *
 * ```c
 * uint8_t tick = 0;
 *
 * void my_isr()
 * {
 *      // count interrupts
 *      ++tick;
 * }
 *
 * ubox_set_user_isr(my_isr);
 * ```
 */
UBOX_EXPORT_API void ubox_set_user_isr(void (*fn)()) __z88dk_fastcall;

/**
 * Waits for a maximum `wait_ticks` interrupts (see [ubox_init_isr](#ubox_init_isr)).
 *
 * This function counts the interrupts (ticks) between between current call to
 * `ubox_wait` and the previous one, and if less than `wait_ticks` ticks have
 * passed, it will wait.
 *
 * This is used to ensure that the game loop used time is constant and hence
 * the game plays smooth in case some updates are faster than others.
 *
 * If the time passed between current `ubox_wait` call and the previous is
 * larger than `wait_ticks`, no waiting happens. This may mean that the game
 * loop takes longer than expected and, if that happens frequently, it would be
 * recommended to increase `wait_ticks` value when calling
 * [ubox_init_isr](#ubox_init_isr).
 *
 * Example:
 * ```c
 * // 25 FPS on PAL, 30 FPS on NTSC
 * ubox_init_isr(2);
 *
 * // game loop example
 * while (1)
 * {
 *      update_controls();
 *
 *      update_entities();
 *      draw_entities();
 *
 *      // ensure that one loop takes at least 2 interrupts
 *      ubox_wait();
 * }
 * ```
 */
UBOX_EXPORT_API void ubox_wait();

/**
 * Waits for `frames` frames.
 *
 * This is used to wait a fixed amount of time measured in frames.
 *
 * Because `frames` is 8-bit value, this funcion can only wait for 255 frames
 * in one single call.
 *
 * Example:
 * ```c
 * // assuming PAL and wait_ticks 2
 * // wait for 10 seconds
 * ubox_wait_for(250);
 * ```
 */
UBOX_EXPORT_API void ubox_wait_for(uint8_t frames) __z88dk_fastcall;

extern uint8_t ubox_tick;

/**
 * Sets `ubox_tick` to zero.
 *
 * `ubox_tick` is a 8-bit global variable that is incremented on every interrupt.
 */
UBOX_EXPORT_API void ubox_reset_tick();

// @dummy functions
UBOX_EXPORT_API uint8_t ubox_update();

// @Sprite functions
//
// All the functions require **screen 2** (256x192 graphics mode, see
// [ubox_set_mode](#ubox_set_mode)).

/**
 * Structure to define sprite attributes.
 *
 * | Field     | Description                                                                                                                                          |
 * | ---       | ---                                                                                                                                                  |
 * | `x`       | The horizontal position of the sprite on the screen.                                                                                                 |
 * | `y`       | The vertical position of the sprite on the screen. This coordinate starts in -1 (0xff) instead of 0.                                                 |
 * | `pattern` | The index in the sprite pattern table. When 16x16 sprites are enabled, the lower two bits are ignored (4 regular 8x8 sprites form one 16x16 sprite). |
 * | `attr`    | The sprite attributes. The bits 0-3 are used for color and bit 7 is EC (Early Clock).                                                                |
 *
 * When EC is enabled, the sprite is displaced 32 pixels to the left.
 */
struct sprite_attr {
    uint8_t y;
    uint8_t x;
    uint8_t pattern;
    uint8_t attr;
};

/**
 * Sets the sprite pattern data pointed by `data` into pattern number
 * `pattern`.
 *
 * `pattern` is the index in the sprite pattern table of Screen 2.
 *
 * This function will set a 8x8 pixels pattern.
 *
 * See [ubox_set_sprite_pat16](#ubox_set_sprite_pat16) to set a 16x16 pixels pattern.
 */
UBOX_EXPORT_API void ubox_set_sprite_pat8(uint8_t *data, uint8_t pattern);

/**
 * Sets the sprite pattern data pointed by `data` into pattern number
 * `pattern`, flipping the pattern data horizontally.
 *
 * `pattern` is the index in the sprite pattern table of Screen 2.
 *
 * This function will set a 8x8 pixels pattern.
 *
 * See [ubox_set_sprite_pat16_flip](#ubox_set_sprite_pat16_flip) to set a 16x16
 * pixels pattern.
 */
UBOX_EXPORT_API void ubox_set_sprite_pat8_flip(uint8_t *data, uint8_t pattern);

/**
 * Sets the sprite attributes of sprite number `sprite` using the attributes
 * pointed by `attr`.
 *
 * `sprite` is the index in the sprite table of Screen 2.
 *
 * See [struct sprite_attr](#struct-sprite_attr) description for details on
 * the sprite attributes.
 *
 * Example:
 * ```c
 * ubox_set_sprite_attr(&player_sprite_attr, 0);
 * ```
 *
 * To set the attributes of multiple sprites that are contiguous in the sprite
 * table, it is recommended to use [ubox_write_vm](#ubox_write_vm). The sprite
 * attribute table is in the memory address `0x1b00`.
 */
UBOX_EXPORT_API void ubox_set_sprite_attr(struct sprite_attr *attr, uint8_t sprite);

/**
 * Sets the sprite pattern data pointed by `data` into pattern number
 * `pattern`.
 *
 * `pattern` is the index in the sprite pattern table of Screen 2.
 *
 * This function will set a 16x16 pixels pattern. The pattern is equivalent
 * to setting four 8x8 patterns (upper left, lower left, upper right and lower right).
 *
 * See [ubox_set_sprite_pat8](#ubox_set_sprite_pat8) to set a 8x8 pixels pattern.
 */
UBOX_EXPORT_API void ubox_set_sprite_pat16(uint8_t *data, uint8_t pattern);

/**
 * Sets the sprite pattern data pointed by `data` into pattern number
 * `pattern`, flipping the pattern data horizontally.
 *
 * `pattern` is the index in the sprite pattern table of Screen 2.
 *
 * This function will set a 16x16 pixels pattern. The pattern is equivalent
 * to setting four 8x8 patterns (upper left, lower left, upper right and lower right).
 *
 * See [ubox_set_sprite_pat8_flip](#ubox_set_sprite_pat8_flip) to set a 8x8
 * pixels pattern.
 */
UBOX_EXPORT_API void ubox_set_sprite_pat16_flip(uint8_t *data, uint8_t pattern);

/**
 * Sets the sprite attributes of sprite number `sprite` using the attributes
 * pointed by `attr`.
 *
 * `sprite` is the index in the sprite table of Screen 2.
 *
 * See [struct sprite_attr](#struct-sprite_attr) description for details on
 * the sprite attributes.
 *
 * Example:
 * ```c
 * ubox_set_sprite_attr(&player_sprite_attr, 0);
 * ```
 *
 * To set the attributes of multiple sprites that are contiguous in the sprite
 * table, it is recommended to use [ubox_write_vm](#ubox_write_vm). The sprite
 * attribute table is in the memory address `0x1b00`.
 */
UBOX_EXPORT_API void ubox_set_sprite_attr(struct sprite_attr *attr, uint8_t sprite);

// @Control functions
//
// The supported controls are: cursor and joystick (port 1 and port 2).
//
// In the case of cursor, space key is used as fire 1 and the "m" key as fire 2.
//
// For one button joysticks, [ubox_read_keys](#ubox_read_keys) can be used to
// provide an alternative fire 2 button using the keyboard.

/**
 * Waits for trigger on cursor (space or "m") or any of the joysticks, and
 * returns the selected control.
 *
 * See [ubox_read_ctl](#ubox_read_ctl) for possible control values.
 */
UBOX_EXPORT_API uint8_t ubox_select_ctl();

/**
 * Read the control identified by `control` and return the status of it.
 *
 * Possible control values are:
 *
 * | Control             | Description                                                                               |
 * | ---                 | ---                                                                                       |
 * | UBOX_MSX_CTL_CURSOR | Cursor for move, space for fire 1 and "m" for fire 2                                      |
 * | UBOX_MSX_CTL_PORT1  | Joystick on port 1                                                                        |
 * | UBOX_MSX_CTL_PORT2  | Joystick on port 2                                                                        |
 * | UBOX_MSX_CTL_NONE   | No control is selected. This is the default output of [ubox_select_ctl](#ubox_select_ctl) |
 *
 * The control status is a bit map with the following values:
 *
 * | Mask               | Bit |
 * | ---                | --- |
 * | UBOX_MSX_CTL_UP    | 0   |
 * | UBOX_MSX_CTL_DOWN  | 1   |
 * | UBOX_MSX_CTL_LEFT  | 2   |
 * | UBOX_MSX_CTL_RIGHT | 3   |
 * | UBOX_MSX_CTL_FIRE1 | 4   |
 * | UBOX_MSX_CTL_FIRE2 | 5   |
 *
 * Example:
 * ```c
 * if (ubox_read_ctl(UBOX_MSX_CTL_CURSOR) & UBOX_MSX_CTL_UP)
 * {
 *      // in the cursor, UP is on
 * }
 * ```
 */
UBOX_EXPORT_API uint8_t ubox_read_ctl(uint8_t control) __z88dk_fastcall;

#define UBOX_MSX_CTL_CURSOR  0
#define UBOX_MSX_CTL_PORT1   1
#define UBOX_MSX_CTL_PORT2   2
#if defined(__ANDROID__) || defined(WIN32) || defined(__linux) || defined(DJGPP)
#define UBOX_MSX_CTL_EXIT    0x64
#endif
#define UBOX_MSX_CTL_NONE    0xff

#define UBOX_MSX_CTL_UP      1
#define UBOX_MSX_CTL_DOWN    2
#define UBOX_MSX_CTL_LEFT    4
#define UBOX_MSX_CTL_RIGHT   8
#define UBOX_MSX_CTL_FIRE1   16
#define UBOX_MSX_CTL_FIRE2   32

/**
 * Reads a row of the keyboard matrix and returns a bit map with the state of
 * the keys in that row.
 *
 * It is important to remember that there are different keyboard layouts and
 * that there is no reliable way of detecting 100% of them.
 *
 * Constants for the QWERTY layout are provided as `UBOX_MSX_KEY_*`, and that covers
 * the most common models.
 *
 * Example:
 * ```c
 * // read row 7 that includes RET, SEL, BS, STOP, TAB, ESC, F5 and F4
 * uint8_t keys = ubox_read_keys(7);
 *
 * if (keys & UBOX_MSX_KEY_ESC)
 * {
 *      // ESC key is pressed
 * }
 * ```
 */
UBOX_EXPORT_API uint8_t ubox_read_keys(uint8_t row) __z88dk_fastcall;

// row 0
#define UBOX_MSX_KEY_7           0x80
#define UBOX_MSX_KEY_6           0x40
#define UBOX_MSX_KEY_5           0x20
#define UBOX_MSX_KEY_4           0x10
#define UBOX_MSX_KEY_3           0x08
#define UBOX_MSX_KEY_2           0x04
#define UBOX_MSX_KEY_1           0x02
#define UBOX_MSX_KEY_0           0x01

// row 1
#define UBOX_MSX_KEY_SEMI        0x80  // ";"
#define UBOX_MSX_KEY_CSBRACKET   0x40  // "]"
#define UBOX_MSX_KEY_OSBRACKET   0x20  // "["
#define UBOX_MSX_KEY_BSLASH      0x10  // "\"
#define UBOX_MSX_KEY_EQUAL       0x08  // "="
#define UBOX_MSX_KEY_MINUS       0x04  // "-"
#define UBOX_MSX_KEY_9           0x02
#define UBOX_MSX_KEY_8           0x01

// row 2
#define UBOX_MSX_KEY_B           0x80  // "B"
#define UBOX_MSX_KEY_A           0x40  // "A"
#define UBOX_MSX_KEY_FSLASH      0x10  // "/"
#define UBOX_MSX_KEY_DOT         0x08  // "."
#define UBOX_MSX_KEY_COMMA       0x04  // ","
#define UBOX_MSX_KEY_QUOTE       0x02  // "'"
#define UBOX_MSX_KEY_TICK        0x01  // "`"

// row 3
#define UBOX_MSX_KEY_J           0x80  // "J"
#define UBOX_MSX_KEY_I           0x40  // "I"
#define UBOX_MSX_KEY_H           0x20  // "H"
#define UBOX_MSX_KEY_G           0x10  // "G"
#define UBOX_MSX_KEY_F           0x08  // "F"
#define UBOX_MSX_KEY_E           0x04  // "E"
#define UBOX_MSX_KEY_D           0x02  // "D"
#define UBOX_MSX_KEY_C           0x01  // "C"

// row 4
#define UBOX_MSX_KEY_R           0x80  // "R"
#define UBOX_MSX_KEY_Q           0x40  // "Q"
#define UBOX_MSX_KEY_P           0x20  // "P"
#define UBOX_MSX_KEY_O           0x10  // "O"
#define UBOX_MSX_KEY_N           0x08  // "N"
#define UBOX_MSX_KEY_M           0x04  // "M"
#define UBOX_MSX_KEY_L           0x02  // "L"
#define UBOX_MSX_KEY_K           0x01  // "K"

// row 5
#define UBOX_MSX_KEY_Z           0x80  // "Z"
#define UBOX_MSX_KEY_Y           0x40  // "Y"
#define UBOX_MSX_KEY_X           0x20  // "X"
#define UBOX_MSX_KEY_W           0x10  // "W"
#define UBOX_MSX_KEY_V           0x08  // "V"
#define UBOX_MSX_KEY_U           0x04  // "U"
#define UBOX_MSX_KEY_T           0x02  // "T"
#define UBOX_MSX_KEY_S           0x01  // "S"

// row 6
#define UBOX_MSX_KEY_F3          0x80  // F3
#define UBOX_MSX_KEY_F2          0x40  // F2
#define UBOX_MSX_KEY_F1          0x20  // F1
#define UBOX_MSX_KEY_CODE        0x10  // CODE
#define UBOX_MSX_KEY_CAP         0x08  // CAP
#define UBOX_MSX_KEY_GRAPH       0x04  // GRAPH
#define UBOX_MSX_KEY_CTRL        0x02  // CTRL
#define UBOX_MSX_KEY_SHIFT       0x01  // SHIFT

// row 7
#define UBOX_MSX_KEY_RET         0x80  // RET
#define UBOX_MSX_KEY_SEL         0x40  // SEL
#define UBOX_MSX_KEY_BS          0x20  // BS
#define UBOX_MSX_KEY_STOP        0x10  // STOP
#define UBOX_MSX_KEY_TAB         0x08  // TAB
#define UBOX_MSX_KEY_ESC         0x04  // ESC
#define UBOX_MSX_KEY_F5          0x02  // F5
#define UBOX_MSX_KEY_F4          0x01  // F4

// row 8
#define UBOX_MSX_KEY_RIGHT       0x80  // RIGHT
#define UBOX_MSX_KEY_DOWN        0x40  // DOWN
#define UBOX_MSX_KEY_UP          0x20  // UP
#define UBOX_MSX_KEY_LEFT        0x10  // LEFT
#define UBOX_MSX_KEY_DEL         0x08  // DEL
#define UBOX_MSX_KEY_INS         0x04  // INS
#define UBOX_MSX_KEY_HOME        0x02  // HOME
#define UBOX_MSX_KEY_SPACE       0x01  // SPACE

#endif // _UBOX_MSX_H
