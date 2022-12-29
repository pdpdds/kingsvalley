#ifndef _MAIN_H
#define _MAIN_H

#include <stdint.h>

#ifndef LOCAL
#define LOCAL extern
#endif

#define WHITESPACE_TILE 0

// sub-songs matching our Arkos song
// configure the song to use MSX AY
#if defined(_WIN32) || defined(DJGPP) || defined(__linux)
enum songs
{
    SONG_SILENCE = 0,
    SONG_IN_GAME = 1,
    SONG_GAME_OVER = 2,
    SONG_GAME_START = 3,
};
#else
enum songs
{
    SONG_SILENCE = 1,
    SONG_IN_GAME = 0,
    SONG_GAME_OVER = 1,
    SONG_GAME_START = 1,
};
#endif

// we will use 0 and 1 for the music
#define EFX_CHAN_NO 2

// sound effects matching our Arkos efx song
// configure the song to use MSX AY

#if defined(__SDCC)
enum effects
{
    EFX_NONE = 0,
    EFX_START,
    EFX_DOOR,
    EFX_DIG,
    EFX_HIT,
    EFX_DEAD,
};
#else
enum effects
{
    EFX_NONE = 0,
    EFX_START = 0,
    EFX_DOOR = 0,
    EFX_DIG = 0,
    EFX_HIT = 0,
    EFX_DEAD = 0,
};
#endif

void draw_end_game();
void draw_menu();

// store the selected control
LOCAL uint8_t ctl;

// Arkos data
extern uint8_t SONG[];
extern uint8_t EFFECTS[];

#ifdef LOCAL
#undef LOCAL
#endif

#endif // _MAIN_H
