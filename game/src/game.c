#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <ubox.h>
#include <spman.h>
#include <mplayer.h>
#include <ap.h>

#include "main.h"

#define LOCAL
#include "game.h"

#include <map_summary.h>

#include <playermove.h>
#include <playerpickax.h>
#include <playerknife.h>
#include <playerattack.h>
#include <playerdigging.h>
#include <enemy.h>
#include <knife.h>
#include <game_util.h>

#include "item.h"
#include "gate.h"
#include "pushdoor.h"
#include "player.h"
#include "enemy.h"
#include "jewel.h"
#include "trap.h"
#include "character.h"


//enemy animation
const uint8_t enemy_reborn_frames[ENEMY_REBORN_CYCLE] = { 4, 5 };

const uint8_t walk_frames[WALK_CYCLE] = { 0, 1, 0, 2 };
const uint8_t stair_frames[STAIR_CYCLE] = { 0, 1 };
const uint8_t attack_frames[ATTACK_CYCLE] = { 0, 1 };
const uint8_t knife_frames[KNIFE_CYCLE] = { 0, 1, 2, 3 };
const uint8_t digging_frames[DIGGING_CYCLE] = { 0, 1 };

uint8_t cur_map_data[MAX_ROOM_COUNT][MAP_W * MAP_H];


static uint8_t get_entity_count(const uint8_t* mapData)
{
	uint8_t entityCount = 0;

	const uint8_t* m = (const uint8_t*)(mapData);

	//map header is 3 bytes. map size 2byte + 0x00 1 byte
	m += (uint16_t)(m[0] | m[1] << 8) + 3;

	//(map pointer + 3 bytes + map_size) indicates entities. 
	//entity size is 5 bytes. id, type, x, y, type. extra
	//if *m is 0xff it means map data over.
	while (*m != 0xff) {
		entityCount++;

		m += 5;
	}

	return entityCount;
}

uint8_t pattern_knife = 0;
uint8_t pattern_enemy = 0;
uint8_t pattern_attack = 0;
uint8_t pattern_digging = 0;
uint8_t pattern_player = 0;


void allocate_pattern(uint8_t player_move_type) {
	spman_init();

	pattern_knife = spman_alloc_pat(PAT_KNIFE, (uint8_t*)knife_sprite[0], 8, 0);
	spman_alloc_pat(PAT_KNIFE_FLIP, (uint8_t*)knife_sprite[0], 8, 1);

	pattern_enemy = spman_alloc_pat(PAT_ENEMY, (uint8_t*)enemy_sprite[0], 6, 0);
	spman_alloc_pat(PAT_ENEMY_FLIP, (uint8_t*)enemy_sprite[0], 6, 1);

	pattern_attack = spman_alloc_pat(PAT_ATTACK, (uint8_t*)playerattack_sprite[0], 4, 0);
	spman_alloc_pat(PAT_ATTACK_FLIP, (uint8_t*)playerattack_sprite[0], 4, 1);

	pattern_digging = spman_alloc_pat(PAT_DIGGING, (uint8_t*)playerdigging_sprite[0], 4, 0);
	spman_alloc_pat(PAT_DIGGING_FLIP, (uint8_t*)playerdigging_sprite[0], 4, 1);

	switch (player_move_type)
	{
	case MOVE_NORMAL:
		pattern_player = spman_alloc_pat(PAT_PLAYER_MOVE, (uint8_t*)playermove_sprite[0], 6, 0);
		spman_alloc_pat(PAT_PLAYER_MOVE_FLIP, (uint8_t*)playermove_sprite[0], 6, 1);
		break;
	case MOVE_KNIFE:
		pattern_player = spman_alloc_pat(PAT_PLAYER_KNIFE, (uint8_t*)playerknife_sprite[0], 6, 0);
		spman_alloc_pat(PAT_PLAYER_KNIFE_FLIP, (uint8_t*)playerknife_sprite[0], 6, 1);
		break;
	case MOVE_PICKAX:
		pattern_player = spman_alloc_pat(PAT_PLAYER_PICKAX, (uint8_t*)playerpickax_sprite[0], 6, 0);
		spman_alloc_pat(PAT_PLAYER_PICKAX_FLIP, (uint8_t*)playerpickax_sprite[0], 6, 1);
		break;
	}

}

void reset_sprite(uint8_t move_mode)
{
	allocate_pattern(move_mode);

	struct entity* object = entities;
	for (uint8_t i = 0; i < g_maxEntities; i++, object++) {
		switch (object->type) {
		case ET_PLAYER:
			object->pat = pattern_player;
			break;
		case ET_KNIFE:
			object->pat = pattern_knife;
			break;
		case ET_ENEMY:
			object->pat = pattern_enemy;
			break;
		}
	}
}

void setup_movable_door(struct entity* door)
{
	uint8_t height = 0;
	while(1) {

		uint8_t tile_index = cur_map_data[door->roomId][(door->x >> 3) + ((door->y - height) >> 3) * MAP_W];

		if (tile_index != BLANK_TILE)
			break;

		if (door->extra == 1)
		{
			cur_map_data[door->roomId][(door->x >> 3) + ((door->y - height) >> 3) * MAP_W] = MOVABLE_DOOR_TILE1;
			cur_map_data[door->roomId][((door->x + 8) >> 3) + ((door->y - height) >> 3) * MAP_W] = MOVABLE_DOOR_TILE2;
		}
		else
		{
			cur_map_data[door->roomId][(door->x >> 3) + ((door->y - height) >> 3) * MAP_W] = MOVABLE_DOOR_TILE4;
			cur_map_data[door->roomId][((door->x + 8) >> 3) + ((door->y - height) >> 3) * MAP_W] = MOVABLE_DOOR_TILE3;
		}
		
		height += 8;
	}

	door->height = height;
}

static void init_map_entities(uint8_t stage) {
	uint8_t roomCount = 1;
	uint8_t entity_type, last = 0;

	allocate_pattern(MOVE_NORMAL);

	cur_map = (const uint8_t**)g_map[stage - 1];

	roomCount = g_map_room_count[stage - 1];

	for (uint8_t i = 0; i < roomCount; i++) {
		g_maxEntities += get_entity_count(cur_map[i]);
	}

	memset(entities, 0, sizeof(struct entity) * MAX_ENTITIES);

	for (uint8_t i = 0; i < roomCount; i++) {
		const uint8_t* m = (const uint8_t*)(cur_map[i]);
		ap_uncompress(cur_map_data[i], cur_map[i] + 3);

		m += (uint16_t)(m[0] | m[1] << 8) + 3;

		while (*m != 0xff) {

			entity_type = m[0] & (~DIR_FLAG);

			entities[last].type = entity_type;
			entities[last].roomId = i;
			entities[last].x = m[1];
			entities[last].y = m[2];
			entities[last].identifier = m[3];
			entities[last].extra = m[4];
			entities[last].state = PS_IDLE;
			entities[last].control = 0;
			entities[last].flags = 0;

			entities[last].dir = m[0] & DIR_FLAG ? DIR_LEFT : DIR_RIGHT;

			switch (entity_type) {
			case ET_JEWEL:
				entities[last].update = update_jewel;
				entities[last].width = 8;
				entities[last].height = 8;
				g_jewels_count++;
				break;
			case ET_LOCK:
				entities[last].update = update_item;
				break;
			case ET_KNIFE:
				entities[last].update = update_knife;
				entities[last].width = 8;
				entities[last].height = 8;
				entities[last].pat = pattern_knife;
				break;
			case ET_PICKAX:
				entities[last].update = update_item;
				break;

			case ET_EXIT:
				entities[last].update = update_exit;
				entities[last].width = 16;
				entities[last].height = 24;
				break;

			case ET_PLAYER:

				entities[last].pat = pattern_player;
				g_cur_room_id = i;
				entities[last].update = update_player;
				entities[last].pivot_x = 4;
				entities[last].pivot_y = 0;
				entities[last].x += entities[last].pivot_x;
				entities[last].y += entities[last].pivot_y;
				entities[last].width = 8;
				entities[last].height = 16;

				player = &entities[last];
				break;

			case ET_ENEMY:
				entities[last].pat = pattern_enemy;
				entities[last].update = update_enemy;
				entities[last].width = 8;
				entities[last].height = 16;
				entities[last].pivot_x = 4;
				entities[last].pivot_y = 0;
				entities[last].regentime = ENEMY_REBORN_CYCLE * 2;
				
				entities[last].state = PS_NONE;
				entities[last].subtype = entities[last].extra & (0x0f);
				entities[last].strategy = 0;

				entities[last].flags = entities[last].extra & (~0x0f);

				break;
			case ET_TRAP:
				entities[last].width = 8;
				entities[last].height = 8;
				entities[last].regentime = ENEMY_REBORN_CYCLE * 2;
				entities[last].extra = entities[last].extra;
				entities[last].state = PS_IDLE;
				entities[last].update = update_trap;

				break;
			case ET_PUSHDOOR:
				entities[last].state = PS_IDLE;
				entities[last].update = update_pushdoor;
				entities[last].width = 8;
				entities[last].height = 0;
				setup_movable_door(&entities[last]);
				entities[last].dir = entities[last].extra;
				if (entities[last].height == 0)
					entities[last].type = ET_UNUSED;

				break;

			}

			last++;

			// entity is 5 bytes
			m += 5;
		}
	}
}

static void draw_static_object() {
	struct entity* object = entities;
	for (uint8_t i = 0; i < g_maxEntities; i++, object++)
	{
		if (g_cur_room_id != object->roomId || !object->type)
			continue;

		if (object->type == ET_JEWEL)
		{
			put_tile(object->x, object->y, JEWEL_TILE + object->extra);
		}
		if (object->type == ET_KNIFE && object->state == PS_IDLE)
		{
			put_tile(object->x, object->y, KNIFE_TILE);
		}

		if (object->type == ET_LOCK)
			put_tile(object->x, object->y, LOCK_TILE);
	}
}

static void draw_map(uint8_t roomId)
{
	ubox_wait_vsync();

#if defined(__ANDROID__) || defined(WIN32) || defined(DJGPP)
	uint8_t* video_memory = 0;
#else
	uint8_t* video_memory = (uint8_t*)0x1800;
#endif

	ubox_write_vm(video_memory, MAP_W * MAP_H, cur_map_data[roomId]);
}

void draw_hud()
{
	put_text(1, 0, (uint8_t*)"SCORE");
	ubox_put_tile(6, 0, 32);

	uint32_t score = g_player_info.score;
	
	for (uint8_t i = 0; i < 6; i++) {
		ubox_put_tile(7 + 5 - i, 0, (score % 10) + 16);
		score = score / 10;
	}


	put_text(24, 0, (uint8_t*)"REST");
	ubox_put_tile(28, 0, 32);
	if (lives > 10)
	{
		ubox_put_tile(29, 0, (lives / 10) + 16);
		ubox_put_tile(30, 0, (lives % 10) + 16);
	}
	else
	{
		ubox_put_tile(29, 0, 0 + 16);
		ubox_put_tile(30, 0, lives + 16);
	}

	ubox_put_tile(1, MAP_H, 26);
	put_text(2, MAP_H, (uint8_t*)"KONAMI");
	put_text(12, MAP_H, (uint8_t*)"PYRAMID");
	ubox_put_tile(19, MAP_H, 32);


	//sprintf(buffer, "%d", g_stage);
	//put_text(20, MAP_H, (uint8_t*)buffer);

	if (g_stage > 10)
	{
		ubox_put_tile(20, MAP_H, (g_stage / 10) + 16);
		ubox_put_tile(21, MAP_H, (g_stage % 10) + 16);
	}
	else
		ubox_put_tile(20, MAP_H, g_stage + 16);
}

void update_screen()
{
	spman_sprite_flush();
	spman_update();
	ubox_disable_screen();

	ubox_fill_screen(WHITESPACE_TILE);

	draw_map(g_cur_room_id);
	draw_static_object();

	draw_hud();

	ubox_enable_screen();
}

uint8_t process_game() {
	uint8_t i = 0;

	if (gameover_delay) {
		if (--gameover_delay == 0) {
			if (g_gamestate != STATE_IN_GAME)
				return 1;
		}
	}

	control = ubox_read_ctl(ctl);

	/*for (i = 0, self = entities; i < g_maxEntities; i++, self++) {
		if (self->type != ET_UNUSED)
			self->update();
	}*/

	return 0;
}

void process_door_animation(uint8_t start)
{
	uint8_t tile_x = player->x >> 3;
	uint8_t tile_y = player->y >> 3;

	if (start) {
		player->x += 8;
		player->y -= 8;
		player->dir = 1;
		player->delay = 0;
	}
	else {
		player->dir = 0;
		player->delay = 0;
	}
	
	uint8_t end = 0;
	while (!end) {

		while (ubox_update() && end == 0)
		{
			if (start) {
				if (process_start_gate_animation(tile_x, tile_y)) {

					g_gamestate = STATE_IN_GAME;
					end = 1;
					mplayer_init(SONG, SONG_IN_GAME);

					break;
				}
			}
			else {
				if (process_end_gate_animation(tile_x, tile_y)) {

					g_gamestate = STATE_GAME_CLEAR;
					end = 1;
					break;
				}
			}


			ubox_wait();
			spman_update();

#if defined(_WIN32) || defined(__ANDROID__)
			//draw_map(g_cur_room_id);
			//draw_static_object();
			//draw_hud();
#endif
		}
	}
}

void run_game(int stage) {
	invuln = 0;
	gameover_delay = 0;
	g_cur_room_id = 0;
	g_maxEntities = 0;
	g_jewels_count = 0;

	g_gamestate = STATE_IN_GAME_ENTER;
	g_player_info.jewels = 0;

	ubox_disable_screen();
	ubox_fill_screen(WHITESPACE_TILE);

	init_map_entities(stage);

	draw_map(g_cur_room_id);
	draw_static_object();
	draw_hud();

	ubox_enable_screen();

	uint8_t end = 0;

	while (!end) {

		while (ubox_update() > 0 && end == 0) {		
			
			if (ubox_read_keys(7) == UBOX_MSX_KEY_ESC) {
				end = 1;
				break;
			}			

			switch (g_gamestate)
			{
			case STATE_GAME_CLEAR:
				end = 1;
				break;
			case STATE_IN_GAME_ENTER:
				mplayer_play_effect_p(EFX_DOOR, EFX_CHAN_NO, 0);
				process_door_animation(1);
				break;
			case STATE_IN_GAME_EXIT:
				process_door_animation(0);
				break;

			case STATE_IN_GAME:
			case STATE_GAME_RESET:
			case STATE_GAME_OVER:
#if defined(_WIN32) || defined(__ANDROID__) || defined(DJGPP) 
				//draw_map(g_cur_room_id);
				//draw_static_object();
				//draw_hud();
#endif

				end = process_game();
				break;
			}

			if (end)
				break;

			ubox_wait();
			spman_update();
		}
	}

	mplayer_init(SONG, SONG_SILENCE);
	spman_hide_all_sprites();
}