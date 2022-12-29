#ifndef _MAP_SUMMARY_H
#define _MAP_SUMMARY_H
#define MAX_LEVEL 8
#ifdef LOCAL
#include "map.h"
unsigned char** g_map[MAX_LEVEL + 1] =  {
   map1, 
   map2, 
   map3, 
   map4, 
   map5, 
   map6, 
   map7, 
   map8, 
   0,
};
unsigned char g_map_room_count[MAX_LEVEL + 1] =  {
   MAP1_RW_COUNT, 
   MAP2_RW_COUNT, 
   MAP3_RW_COUNT, 
   MAP4_RW_COUNT, 
   MAP5_RW_COUNT, 
   MAP6_RW_COUNT, 
   MAP7_RW_COUNT, 
   MAP8_RW_COUNT, 
   0,
};
#else
extern unsigned char** g_map[MAX_LEVEL + 1];
extern unsigned char g_map_room_count[MAX_LEVEL + 1];
#endif // LOCAL
#endif // _MAP_SUMMARY_H
