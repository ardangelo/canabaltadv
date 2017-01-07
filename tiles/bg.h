
//{{BLOCK(bg)

//======================================================================
//
//	bg, 16x8@4, 
//	+ palette 16 entries, not compressed
//	+ 2 tiles not compressed
//	Total size: 32 + 64 = 96
//
//	Time-stamp: 2017-01-07, 14:48:36
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BG_H
#define GRIT_BG_H

#define TILE_SKY_S0 0
#define TILE_BUILD_S0 1

#define bgTilesLen 64
extern const unsigned short bgTiles[32];

#define bgPalLen 32
extern const unsigned short bgPal[16];

#endif // GRIT_BG_H

//}}BLOCK(bg)
