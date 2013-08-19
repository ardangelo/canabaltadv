
//{{BLOCK(bg1)

//======================================================================
//
//	bg1, 512x256@4, 
//	Transparent color : FF,00,FF
//	+ 169 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 64x32 
//	Total size: 5408 + 4096 = 9504
//
//	Time-stamp: 2013-08-18, 22:05:06
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BG1_H
#define GRIT_BG1_H

#define bg1TilesLen 5408
extern const unsigned int bg1Tiles[1352];

#define bg1MapLen 4096
extern const unsigned short bg1Map[2048];

#endif // GRIT_BG1_H

//}}BLOCK(bg1)

//{{BLOCK(Shared)

//======================================================================
//
//	Shared, 16x16@4, 
//	Transparent color : FF,00,FF
//	+ palette 256 entries, not compressed
//	Total size: 512 = 512
//
//	Time-stamp: 2013-08-18, 22:05:06
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SHARED_H
#define GRIT_SHARED_H

#define SharedPalLen 512
extern const unsigned short SharedPal[256];

#endif // GRIT_SHARED_H

//}}BLOCK(Shared)
