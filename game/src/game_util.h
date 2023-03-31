#ifndef _GAME_UTIL_H
#define _GAME_UTIL_H
#include <stdint.h>
#include "game.h"

#define UNUSED_PARAMETER(x) (void)(x)

void my_isr();
int now();

struct rect_
{
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
};
void put_text(uint8_t x, uint8_t y, const uint8_t* text);


uint8_t is_map_blocked(uint8_t x, uint8_t y);
uint8_t is_blocked(uint8_t x, uint8_t y);
uint8_t check_floor(uint8_t x, uint8_t y, uint8_t width);

//object collison
uint8_t is_intersect_by_rect(struct rect_* object1, struct rect_* object2);
uint8_t is_intersect(struct entity* object1, struct entity* object2);


//find object
struct entity* find_object(uint8_t id);
struct entity* find_object_by_type(uint8_t type);
struct entity* find_object_by_tile_index(uint8_t x, uint8_t y);

// tile function
void put_tile(uint8_t pos_x, uint8_t pos_y, uint8_t tile_index);
uint8_t get_tile_index(uint8_t x, uint8_t y);
uint8_t isSolidTile(uint8_t tileIndex);
uint8_t isStairTile(uint8_t tileIndex);
uint8_t isStairTile2(uint8_t tileIndex);

uint8_t is_movable_tile(uint8_t tileIndex);
uint8_t is_static_object(uint8_t tile_index);
void change_object_state(struct entity* object, uint8_t state, uint8_t move_type);

void update_map_data_by_position(uint8_t x, uint8_t y, uint8_t tile_index);
#endif