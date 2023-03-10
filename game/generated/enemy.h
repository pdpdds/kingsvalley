#ifndef _ENEMY_SPRITE_H
#define _ENEMY_SPRITE_H

#define ENEMY_SPRITE_LEN 192

#define ENEMY_SPRITE_FRAMES 6

#ifdef LOCAL
const unsigned char enemy_sprite[6][32] = {
{
0x00, 0x03, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03,
0x07, 0x04, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03,
0x00, 0xc0, 0xe0, 0x40, 0xe0, 0xe0, 0xc0, 0x80,
0xe0, 0x80, 0x60, 0x80, 0x80, 0x00, 0x00, 0x80,
},
{
0x00, 0x03, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03,
0x07, 0x04, 0x07, 0x07, 0x1f, 0x1e, 0x11, 0x01,
0x00, 0xc0, 0xe0, 0x40, 0xe0, 0xe0, 0xe0, 0xc0,
0x80, 0xe0, 0xb0, 0xc0, 0xc0, 0x80, 0x80, 0xc0,
},
{
0x00, 0x03, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03,
0x07, 0x06, 0x05, 0x01, 0x03, 0x07, 0x0e, 0x08,
0x00, 0xc0, 0xe0, 0x40, 0xe0, 0x00, 0xe0, 0xc0,
0xe0, 0x78, 0x48, 0xc0, 0xe8, 0xf8, 0x18, 0x00,
},
{
0x00, 0x00, 0x20, 0x00, 0x08, 0x04, 0x00, 0x00,
0xb0, 0x00, 0x00, 0x04, 0x08, 0x00, 0x20, 0x00,
0x00, 0x00, 0x82, 0x00, 0x88, 0x90, 0x00, 0x00,
0x0d, 0x00, 0x00, 0x90, 0x88, 0x00, 0x82, 0x00,
},
{
0x00, 0x00, 0x01, 0x0a, 0x1f, 0x1f, 0x0f, 0x17,
0x3f, 0x1f, 0x07, 0x0f, 0x0b, 0x06, 0x00, 0x00,
0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf0, 0xe0, 0xf0,
0xe8, 0xf8, 0xf8, 0xd0, 0xf0, 0xc0, 0x00, 0x00,
},
{
0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x03, 0x05,
0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xc0, 0xa0, 0xf0, 0xd0,
0xe0, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
}
};

#else

extern const unsigned char enemy_sprite[6][32];
#endif // LOCAL

#endif // _ENEMY_SPRITE_H

