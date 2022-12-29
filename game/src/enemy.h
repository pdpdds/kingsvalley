#ifndef _ENEMY_H
#define _ENEMY_H
#include <stdint.h>
#include "game.h"


void update_enemy();

extern void player_die();
extern void change_object_state(struct entity* object, uint8_t state, uint8_t move_Type);
extern void update_character();

#endif