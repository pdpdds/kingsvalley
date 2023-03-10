#ifndef _PLAYERPICKAX_SPRITE_H
#define _PLAYERPICKAX_SPRITE_H

#define PLAYERPICKAX_SPRITE_LEN 192

#define PLAYERPICKAX_SPRITE_FRAMES 6

#ifdef LOCAL
const unsigned char playerpickax_sprite[6][32] = {
{
0x00, 0x01, 0x03, 0x00, 0x67, 0x04, 0x18, 0x0c,
0x06, 0x01, 0x03, 0x03, 0x01, 0x00, 0x00, 0x01,
0x00, 0xc0, 0xe0, 0x00, 0xf0, 0x08, 0x00, 0x00,
0x00, 0xc0, 0xc0, 0x80, 0xc0, 0x00, 0x00, 0xc0,
},
{
0x00, 0x08, 0x10, 0x03, 0x10, 0x33, 0x27, 0x23,
0x21, 0x02, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00,
0x00, 0x00, 0x00, 0xe0, 0x00, 0xf0, 0xf0, 0xe0,
0xc0, 0x20, 0x10, 0x78, 0x00, 0x80, 0x80, 0x00,
},
{
0x00, 0x01, 0x03, 0x00, 0x07, 0x60, 0x20, 0x08,
0x04, 0x03, 0x03, 0x03, 0x09, 0x09, 0x00, 0x00,
0x00, 0xc0, 0xe0, 0x00, 0xf0, 0x08, 0x00, 0x00,
0x00, 0xc0, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0xe0,
},
{
0x00, 0x00, 0x08, 0x1b, 0x10, 0x13, 0x17, 0x63,
0x41, 0x40, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00,
0x00, 0x00, 0x00, 0xe0, 0x00, 0xf0, 0xf0, 0xe0,
0xc0, 0x00, 0xe0, 0x00, 0x00, 0xc0, 0xc0, 0x00,
},
{
0x00, 0x01, 0x03, 0x00, 0x07, 0x48, 0x80, 0x18,
0x0e, 0x03, 0x01, 0x01, 0x01, 0x00, 0x0c, 0x08,
0x00, 0xc0, 0xe0, 0x00, 0xf0, 0x08, 0x00, 0x00,
0x00, 0x60, 0xe8, 0xc0, 0xc8, 0x88, 0x18, 0x00,
},
{
0x00, 0x00, 0x10, 0x33, 0x20, 0x23, 0x67, 0xe3,
0x81, 0x84, 0x8c, 0x08, 0x02, 0x07, 0x02, 0x00,
0x00, 0x00, 0x00, 0xe0, 0x00, 0xf0, 0xf0, 0xe0,
0xc0, 0x90, 0x10, 0x00, 0x00, 0x70, 0x00, 0x00,
}
};

#else

extern const unsigned char playerpickax_sprite[6][32];
#endif // LOCAL

#endif // _PLAYERPICKAX_SPRITE_H

