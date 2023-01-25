#include <ubox.h>
#include <mplayer.h>
#include "game.h"
#include "game_util.h"
#include <map_summary.h>
#include <title.h>
#include <tiles.h>
#include <map.h>

#define LOCAL
#include "main.h"
#include <ap.h>

void draw_menu() {
    uint8_t i = 0;

    ubox_disable_screen();

    ubox_wait_vsync();
    
    cur_map = (const uint8_t**)map0;
    ap_uncompress(cur_map_data[0], cur_map[0] + 3);

#if defined(__SDCC)
    uint8_t* video_memory = (uint8_t*)0x1800;
#else
    uint8_t* video_memory = 0;
#endif

    ubox_write_vm(video_memory, MAP_W * 24, (uint8_t*)cur_map_data);

    ubox_enable_screen();
    
;    uint8_t delay = 0;
    while (ubox_update())
    {
        ctl = ubox_select_ctl();

        if (ctl != UBOX_MSX_CTL_NONE)
        {
#if !defined(__SDCC) 
            if (ctl == UBOX_MSX_CTL_EXIT) {
                g_gamestate = STATE_EXIT;
                break;
            }

            if (ctl != UBOX_MSX_CTL_FIRE1) {
                continue;
            }
#endif
            mplayer_play_effect_p(EFX_START, EFX_CHAN_NO, 0);
            //mplayer_init(SONG, SONG_GAME_START);

#ifdef _DEBUG

            while (delay < 60)
            {

                if((delay % 4 == 0) || (delay % 4 == 1))
                    put_text(9, 17, (uint8_t*)"               ");
                else
                    put_text(9, 17, (uint8_t*)"   PLAY START");

                delay++;
                ubox_wait();
            }

            ubox_wait_for(16);
#endif

            g_gamestate = STATE_GAME_RESET;
            lives = MAX_LIVES;
            g_stage = 1;
            break;
        }

        ubox_wait();
    }    
}

void draw_end_game()
{
    ubox_disable_screen();

    ubox_fill_screen(WHITESPACE_TILE);

    put_text(3, 9, (uint8_t*)"CONGRATUATION");
    put_text(3, 12, (uint8_t*)"(PRESS ESC)");
     
    ubox_enable_screen();

    while (1) {
        if (ubox_read_keys(7) == UBOX_MSX_KEY_ESC)
            break;

        ubox_wait();
    }

    g_gamestate = STATE_TITLE;
}

void draw_game_over() {
    ubox_disable_screen();

    ubox_fill_screen(WHITESPACE_TILE);
    put_text(11, 10, (uint8_t*)"GAME  OVER");

    ubox_enable_screen();

    mplayer_init(SONG, SONG_GAME_OVER);

    ubox_wait_for(255);

    g_gamestate = STATE_TITLE;
}

void draw_stage_clear()
{
    ubox_disable_screen();

    put_text(11, 10, (uint8_t*)"STAGE CLEAR");

    ubox_enable_screen();

    ubox_wait_for(200);

    g_gamestate = STATE_GAME_RESET;
    g_stage++;
}

void draw_stage_reset() {
    if(g_stage > MAX_LEVEL || g_map[g_stage - 1] == 0) {
        g_gamestate = STATE_NO_MAP;
        return;
    }

    ubox_disable_screen();
    ubox_fill_screen(WHITESPACE_TILE);
    
    put_text(12, 10, (uint8_t*)"STAGE ");

    if (g_stage > 10)
    {
        ubox_put_tile(18, 10, (g_stage / 10) + 16);
        ubox_put_tile(19, 10, (g_stage % 10) + 16);
    }
    else
        ubox_put_tile(18, 10, g_stage + 16);

    ubox_enable_screen();

    ubox_wait_for(96);

    g_gamestate = STATE_IN_GAME;
    
}

#if !defined(__SDCC)
extern void ubox_init_game_system(const char* szTitle, int screen_width, int screen_height, uint8_t map_width, uint8_t map_height);
extern void ubox_load_music(uint8_t music_index, char* filename, uint8_t loop);
extern void ubox_add_sprite(uint8_t music_index, char* filename, uint8_t loop);

uint8_t game_main() {
#if defined(DJGPP)
    int game_width = 320;
    int game_height = 200;
#else
    int game_width = 640;
    int game_height = 480;
#endif
    
    ubox_init_game_system("King's Valley", game_width, game_height, 32, 24);

    ubox_load_music(SONG_SILENCE, "", 0);
    ubox_load_music(SONG_IN_GAME, "audio/bgm.wav",1);
    ubox_load_music(SONG_GAME_OVER, "audio/gameover.wav", 0);
    ubox_load_music(SONG_GAME_START, "audio/start.wav", 0);
 
    ubox_add_sprite(PAT_PLAYER_MOVE, "./p_move.png", 1);
    ubox_add_sprite(PAT_PLAYER_KNIFE, "./p_knife.png", 1);
    ubox_add_sprite(PAT_PLAYER_PICKAX, "./p_pickax.png", 1);
    ubox_add_sprite(PAT_DIGGING, "./p_dig.png", 1);
    ubox_add_sprite(PAT_ATTACK, "./p_attack.png", 1);
    ubox_add_sprite(PAT_ENEMY, "./enemy.png", 1);
    ubox_add_sprite(PAT_KNIFE, "./knife.png", 1);
   
#else
uint8_t main()
{
#endif
    ubox_init_isr(2);

    ubox_set_mode(2);
    ubox_set_colors(1, 1, 1);

    ubox_disable_screen();

    ubox_set_tiles_colors((uint8_t*)tiles_colors);
    ubox_set_tiles((uint8_t*)tiles);  

    ubox_fill_screen(WHITESPACE_TILE);

    ubox_enable_screen();
    ubox_wvdp(1, 0xe2);    

    mplayer_init(SONG, SONG_SILENCE);
    mplayer_init_effects(EFFECTS);

    ubox_set_user_isr(my_isr);

    g_gamestate = STATE_TITLE;
    g_player_info.score = 0;


    while (STATE_EXIT != g_gamestate) {
        switch (g_gamestate) {
        case STATE_TITLE:
            draw_menu();
            break;
        case STATE_IN_GAME:
            run_game(g_stage);

            if(g_gamestate == STATE_IN_GAME)
                g_gamestate = STATE_TITLE;            
            break;
        case STATE_GAME_RESET:
            draw_stage_reset();
            break;
        case STATE_GAME_CLEAR:
            draw_stage_clear();
            break;
        case STATE_GAME_OVER:
            draw_game_over();
            break;
        case STATE_NO_MAP:
            draw_end_game();
            break;    
        }

         ubox_wait();
    }

    return 0;
   
}
