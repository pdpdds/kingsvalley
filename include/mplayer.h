/*
 * mplayer lib
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
 *
 * Arkos 2 AKM
 * Copyright (c) 2016-2020 Julien Névo (contact@julien-nevo.com)
 * (check mplayer/akm/LICENSE.txt; MIT License)
 */

#ifndef _MPLAYER_H
#define _MPLAYER_H

#include <stdint.h>

#if defined(WIN32) || defined(__ANDROID__) || defined(SKYOS32)  || defined(__linux)   || defined(DJGPP)
#define __z88dk_fastcall
#endif

// @Initialization

/**
 * Sets the player to play `sub_song` from `song`.
 *
 * `sub_song` starts from 0.
 *
 * This function can be called as many times as needed, for example, to change
 * the playback to a different sub-song.
 *
 * It is required to call it at least once before using
 * [mplayer_play](#mplayer_play).
 *
 * Example:
 *
 * ```c
 * // tell the compiler we will use this
 * // global symbol
 * extern uint8_t SONG[];
 *
 * mplayer_init(SONG, 0);
 * ```
 *
 * See [exporting songs and effects](#exporting-songs-and-effects) for details
 * on how to add songs to your project.
 */
void mplayer_init(uint8_t *song, uint8_t sub_song);

/**
 * Inits the effects table.
 *
 * It is required to call it least once before using
 * [mplayer_play](#mplayer_play) or any of the play effect functions.
 *
 * Example:
 *
 * ```c
 * // tell the compiler we will use this
 * // global symbol
 * extern uint8_t EFFECTS[];
 *
 * mplayer_init_effects(EFFECTS);
 * ```
 *
 * See [exporting songs and effects](#exporting-songs-and-effects) for details
 * on how to add effects to your project.
 */
void mplayer_init_effects(uint8_t *effects) __z88dk_fastcall;

// @Playback

/**
 * Plays a frame using the PSG.
 *
 * This must be called from the interrupt handler. See
 * [set_user_isr](ubox-lib-ref.html#ubox_set_user_isr).
 *
 * [mplayer_init](#mplayer_init) must be called before using it.
 *
 * If the player is stopped, [mplayer_stop](#mplayer_stop) must be called to
 * silence the PSG.
 */
void mplayer_play();

/**
 * Silences the PSG, stopping any sound.
 *
 * This doesn't stop the player if [mplayer_play](#mplayer_play) is called.
 */
void mplayer_stop();

// @Sound effects

/**
 * Plays `effect_no` on `chan` channel at `inv_vol` volume.
 *
 * `effect_no` starts on 1 and refers to the index in the effects table set by
 * [mplayer_init_effects](#mplayer_init_effects).
 *
 * `chan` can be 0, 1 or 2. It is recommended to use one channel for effects
 * and the other two for the music.
 *
 * `inv_vol` is the inverted volume, with 0 for max volume and 16 for no sound.
 *
 * If an effects is already playing on the channel, it will be interrupted and
 * replaced by this effect.
 *
 * The effects table must be set with
 * [mplayer_init_effects](#mplayer_init_effects) before using this function.
 *
 * See [mplayer_play_effect_p](#mplayer_play_effect_p) for playing effects with
 * priority.
 *
 * Example:
 *
 * ```c
 * // plays effect 1 on channel 2 at highest volume
 * mplayer_play_effect(1, 2, 0);
 * ```
 */
void mplayer_play_effect(uint8_t effect_no, uint8_t chan, uint8_t inv_vol);

/**
 * Plays `effect_no` on `chan` channel at `inv_vol` volume using priority.
 *
 * `effect_no` starts on 1 and refers to the index in the effects table set by
 * [mplayer_init_effects](#mplayer_init_effects).
 *
 * `effect_no` is used as priority, being effect number 1 the one with
 * lowest priority.
 *
 * `chan` can be 0, 1 or 2. It is recommended to use one channel for effects
 * and the other two for the music.
 *
 * `inv_vol` is the inverted volume, with 0 for max volume and 16 for no sound.
 *
 * The effect is played if no effect is already being played or if the effect
 * being played has less priority. In that case, the effect currently being
 * played will be interrupted and replaced by this effect.
 *
 * The effects table must be set with
 * [mplayer_init_effects](#mplayer_init_effects) before using this function.
 *
 * See [mplayer_play_effect](#mplayer_play_effect) for playing effects without
 * priority.
 *
 * Example:
 *
 * ```c
 * // plays effect 2 on channel 2 at highest volume
 * mplayer_play_effect_p(2, 2, 0);
 * // won't interrupt effect 2 because it is higher priority than 1
 * mplayer_play_effect_p(1, 2, 0);
 * ```
 */
void mplayer_play_effect_p(uint8_t effect_no, uint8_t chan, uint8_t inv_vol);

/**
 * Stops the effect being played on `chan` channel.
 */
void mplayer_stop_effect_channel(uint8_t chan) __z88dk_fastcall;

/**
 * Returns 0 if there's no sound effect being played on `chan` channel, or
 * a value different than 0 otherwise.
 */
uint8_t mplayer_is_sound_effect_on(uint8_t chan) __z88dk_fastcall;

#endif // _MPLAYER_H
