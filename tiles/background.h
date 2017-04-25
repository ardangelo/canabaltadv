
//{{BLOCK(background)

//======================================================================
//
//	background, 512x256@4, 
//	Transparent palette entry: 4.
//	+ palette 16 entries, not compressed
//	+ 104 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 64x32 
//	Total size: 32 + 3328 + 4096 = 7456
//
//	Time-stamp: 2017-04-24, 20:04:56
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKGROUND_H
#define GRIT_BACKGROUND_H

#define backgroundTilesLen 3328
extern const unsigned short backgroundTiles[1664];

#define backgroundMapLen 4096
extern const unsigned short backgroundMap[2048];

#define backgroundPalLen 32
extern const unsigned short backgroundPal[16];

#endif // GRIT_BACKGROUND_H

//}}BLOCK(background)
