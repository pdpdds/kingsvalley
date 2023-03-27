#ifndef _MAP_SUMMARY_H
#define _MAP_SUMMARY_H
#define MAX_LEVEL 15
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
   map9, 
   map10, 
   map11, 
   map12, 
   map13, 
   map14, 
   map15, 
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
   MAP9_RW_COUNT, 
   MAP10_RW_COUNT, 
   MAP11_RW_COUNT, 
   MAP12_RW_COUNT, 
   MAP13_RW_COUNT, 
   MAP14_RW_COUNT, 
   MAP15_RW_COUNT, 
   0,
};
#else
extern unsigned char** g_map[MAX_LEVEL + 1];
extern unsigned char g_map_room_count[MAX_LEVEL + 1];
#endif // LOCAL
#endif // _MAP_SUMMARY_H
