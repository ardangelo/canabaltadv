
@{{BLOCK(bg1)

@=======================================================================
@
@	bg1, 512x256@4, 
@	Transparent color : FF,00,FF
@	+ 169 tiles (t|f|p reduced) not compressed
@	+ regular map (flat), not compressed, 64x32 
@	Total size: 5408 + 4096 = 9504
@
@	Time-stamp: 2013-08-18, 22:05:06
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global bg1Tiles		@ 5408 unsigned chars
bg1Tiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111100,0x11111100,0x11110000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111111,0x00011111,0x00111111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000010
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00100000,0x00100000,0x00100000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00001000,0x00001000,0x00001000
	.word 0x11111000,0x11111000,0x11100000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000

	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x01111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x10000001,0x01111111,0x00011111,0x00111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00000001,0x00000000,0x00000000,0x00000000,0x00000001,0x00000001,0x00000011,0x00111111
	.word 0x00100000,0x00100000,0x00100000,0x00100000,0x01110000,0x11111100,0x11111100,0x10001100
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x11000011
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x11100001
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x11100000,0x11111111,0x11111111,0x11110000

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00111111,0x11111111,0x11111111,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x11111111,0x11111111,0x01110000
	.word 0x00000000,0x00000000,0x00000000,0x00000001,0x11111001,0x11111111,0x11111111,0x00111000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x00011100
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x00001110
	.word 0x00001000,0x00001000,0x00001000,0x00001000,0x00011100,0x00111111,0x00111111,0x00111000
	.word 0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000
	.word 0x00000011,0x00000111,0x00000111,0x00000111,0x00000111,0x00001111,0x11111111,0x11111111

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000001,0x00000001
	.word 0x11001100,0x11111100,0x11111100,0x11111100,0x11111000,0x11110000,0x11100000,0x11000000
	.word 0x01100110,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x10110011,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11111001,0x11101111,0x11100111,0x11101111,0x11111011,0x11110011,0x11111111,0x11111111
	.word 0x10111111,0x00011111,0x00001111,0x00011111,0x10111111,0x11111111,0x11111111,0x11111111
	.word 0x11011001,0x10001111,0x00000110,0x10001111,0x11011001,0x01110000,0x11111111,0x11111111
	.word 0x01101100,0x11000111,0x10000011,0x11000111,0x01101100,0x00111000,0x11111111,0x11111111

	.word 0x11001101,0x01111000,0x00110000,0x01111000,0x11001101,0x10000111,0x11111111,0x11111111
	.word 0x01100110,0x00111100,0x00011000,0x00111100,0x01100110,0x11000011,0x11111111,0x11111111
	.word 0x10110011,0x00011110,0x00001100,0x00011110,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11011001,0x10001111,0x00000110,0x10001111,0x11111111,0x01111111,0x11111111,0x11111111
	.word 0x00111100,0x00110111,0x00110011,0x00110111,0x00111100,0x00011000,0x00001111,0x00000111
	.word 0x00000001,0x00000111,0x00011111,0x00001111,0x00001111,0x00001111,0x00001111,0x00001111
	.word 0x00000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000
	.word 0x00000000,0x00001111,0x00001111,0x00001111,0x00001111,0x00001111,0x00001111,0x00001111

	.word 0x00000000,0x11111100,0x11111100,0x11111100,0x11111100,0x11111100,0x11111100,0x11111100
	.word 0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x10000000,0x10000000
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x01110011,0x01110011
	.word 0x11100011,0x11100011,0x00000011,0x10000011,0x10000011,0x10000011,0x00000001,0x00000001
	.word 0x11111111,0x11111111,0x11111110,0x11111111,0x11111111,0x11111111,0x00000111,0x10001111
	.word 0x00111111,0x00111111,0x00000011,0x00001111,0x00001111,0x00001111,0x00000111,0x00000111
	.word 0x11111100,0x11111100,0x11100000,0x01000000,0x01000000,0x01000000,0x01000000,0x01000000
	.word 0x01111111,0x01111111,0x00001110,0x00000100,0x00000100,0x00000100,0x00000100,0x00000100

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00010000
	.word 0x11000000,0x11000000,0x11000000,0x10100000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x01011111,0x00001111,0x00000011,0x00000001,0x00000000,0x00000000,0x11000000,0x11000000
	.word 0x11111100,0x11111100,0x11100000,0x01100000,0x01100000,0x01100001,0x01100011,0x01100011
	.word 0x11111111,0x11111111,0x11111111,0x11111100,0x11111000,0x11111000,0x11111000,0x11111000
	.word 0x00001111,0x00001111,0x00001111,0x00001111,0x00001111,0x00001111,0x00001111,0x00001111
	.word 0x11000000,0x11000000,0x11000000,0x11100000,0x11100000,0x11100000,0x11100000,0x11100000
	.word 0x00001111,0x00001111,0x00001111,0x00011111,0x00011111,0x00011111,0x00011111,0x00011111

	.word 0x11111100,0x11111100,0x11111100,0x11111110,0x11111110,0x11111110,0x11111110,0x11111110
	.word 0x00000000,0x00000000,0x00000000,0x00000001,0x00000001,0x00000001,0x00000001,0x00000001
	.word 0x00000000,0x00000000,0x00000000,0x00100000,0x11100000,0x11100000,0x11100000,0x11100000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000001,0x00000001,0x00000111
	.word 0x11011011,0x01110011,0x01110011,0x11011011,0x10001111,0x00000111,0x10001111,0x11011011
	.word 0x00000110,0x00000110,0x00000110,0x00000110,0x00000111,0x00000111,0x00000111,0x00000110
	.word 0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,0x11000000
	.word 0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,0x00000111

	.word 0x00000000,0x11110000,0x11111000,0x11111100,0x11111110,0x11111110,0x11111111,0x11111111
	.word 0x00010000,0x00001000,0x00000111,0x00001111,0x00111111,0x01111111,0x11111111,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00001000,0x00000100,0x00000011,0x00000111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01111100
	.word 0x01000000,0x01000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000
	.word 0x11000000,0x10000000,0x00000000,0x00001001,0x00000111,0x11111111,0x11111111,0x11111111
	.word 0x01100011,0x01100001,0x01100001,0x01100001,0x01100001,0x01101111,0x11111111,0x11111111
	.word 0x11111000,0x11111100,0x11111000,0x11111100,0x11111100,0x11111110,0x11111111,0x11111111

	.word 0x11100000,0x11100000,0x11100000,0x11100000,0x11100000,0x11110000,0x11110000,0x11110000
	.word 0x00011111,0x00011111,0x00011111,0x00011111,0x00011111,0x00111111,0x00111111,0x00111111
	.word 0x11111110,0x11111110,0x11111110,0x11111110,0x11111110,0x11111111,0x11111111,0x11111111
	.word 0x00000001,0x00000001,0x00000001,0x00000001,0x00000001,0x00000011,0x00000011,0x00000011
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00110000
	.word 0x01110011,0x01110011,0x11011011,0x10001111,0x00000111,0x10001111,0x11011011,0x01110011
	.word 0x00000110,0x00000110,0x00000110,0x00000111,0x00000111,0x00000111,0x00000110,0x00000110
	.word 0x11000000,0x11000000,0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.word 0x10000111,0x10000111,0x10000011,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111110,0x11111000,0x11100000,0x10000000
	.word 0x00001111,0x00011111,0x00011111,0x11111111,0x01111111,0x11111111,0x11111111,0x11111111
	.word 0x00000000,0x00000010,0x00000001,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x11000000,0x10000000,0x10000000,0x10000000,0x10000000,0x10000000,0x11111111
	.word 0x01111100,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00000000,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00000000,0x00111111,0x00011111,0x00011111,0x00011111,0x00011111,0x00011111,0x11111111

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000011
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00100000,0x11000000
	.word 0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11111111
	.word 0x00001111,0x00001111,0x00001111,0x00001111,0x00001111,0x00001111,0x00001111,0x11111111
	.word 0x11000000,0x11000000,0x11100000,0x11110000,0x11111000,0x11111110,0x11111111,0x11111111
	.word 0x00000000,0x00000011,0x00000111,0x00000111,0x10000111,0x10000111,0x10000111,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000001,0x00000011,0x00001111,0x11111111

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x11000000,0x11000000,0x11000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11110000,0x11110000,0x11110000,0x11110000,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00111111,0x00111111,0x00111111,0x00111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00000011,0x00000011,0x00000011,0x00000011,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00111000,0x00111000,0x00111100,0x00111111,0x00111111,0x00111111,0x11111111,0x11111111
	.word 0x00000000,0x00000000,0x11111100,0x11111100,0x11111100,0x11111100,0x11111111,0x11111111

	.word 0x00000000,0x00000000,0x00000111,0x00000111,0x00000111,0x00000111,0x11111111,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000011,0x00000011
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111000,0x11111000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x11111111
	.word 0x11111111,0x11111111,0x11111110,0x11111110,0x11111110,0x11111110,0x11111111,0x11111111
	.word 0x11111111,0x11110011,0x11000011,0x00000011,0x00000011,0x00000011,0x11111111,0x11111111
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111100,0x11110000,0x11111111,0x11111111
	.word 0x00000001,0x00000001,0x00000001,0x00000001,0x00000001,0x00000000,0x11111111,0x11111111

	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x00011111,0x00011111
	.word 0x00000000,0x00000000,0x10000000,0x10000000,0x10000000,0x10000000,0x10000000,0x10000000
	.word 0x00001000,0x01111111,0x01111111,0x01111111,0x01111111,0x01111111,0x00111111,0x00111111
	.word 0x11000000,0x11111000,0x11000000,0x11000000,0x11000000,0x11100000,0x11110000,0x11110000
	.word 0x00000111,0x00000011,0x00000011,0x00000011,0x00000011,0x00000011,0x00000011,0x00000011
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01000000,0x01000000
	.word 0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000011,0x00000011,0x00000011,0x00000000,0x00000011,0x00000011,0x00000011,0x00000000

	.word 0x11111000,0x11110000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x00111111,0x11111111,0x11111111,0x01111111
	.word 0x00010111,0x00010001,0x00000000,0x00000000,0x00000000,0x00000000,0x00010000,0x00010001
	.word 0x00001111,0x00001011,0x00111000,0x11110000,0x11110000,0x11000000,0x11110000,0x11111000
	.word 0x00000000,0x00000000,0x00000000,0x01000000,0x10000000,0x00000000,0x00000000,0x00000000
	.word 0x01000000,0x10000000,0x10000000,0x11000000,0x11000000,0x11111001,0x11111110,0x11111111
	.word 0x11111000,0x11111100,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00000000,0x00000001,0x00000011,0x00000011,0x00000011,0x00000011,0x00000011,0x00000001

	.word 0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x11111110,0x11111110,0x11111110
	.word 0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x10001111,0x00000111,0x10001111,0x11011011,0x01110011,0x01110011,0x11011011,0x10001111
	.word 0x00000111,0x00000111,0x00000111,0x00000110,0x00000110,0x00000110,0x00000110,0x00000111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x11111110,0x11111110
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000011,0x00000011,0x00000001,0x00000001
	.word 0x11110011,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11111100,0x11111100,0x11111100,0x11111100,0x11111100,0x11111100,0x11111100,0x11111100

	.word 0x00000011,0x00000011,0x00000011,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11000000,0x11000000,0x11110000,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00000001,0x00000001,0x00000000,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11111110,0x11111110,0x11111110,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11111111,0x11111111,0x10001111,0x00000111,0x00000111,0x00000111,0x00000111,0x01111111
	.word 0x00000111,0x10001111,0x11011011,0x01110011,0x01110011,0x11011011,0x10001111,0x00000111
	.word 0x00000111,0x00000111,0x00000110,0x00000110,0x00000110,0x00000110,0x00000111,0x00000111
	.word 0x00000000,0x00000000,0x10000000,0x10000000,0x00000000,0x10000000,0x00000000,0x00000000

	.word 0x00000000,0x00000000,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11111110,0x11111110,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00000001,0x00000001,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11000000,0x11000000,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x01100000,0x01100000,0x11111111,0x11111111,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111111,0x11111111,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111000,0x11111000,0x11111100
	.word 0x00000000,0x00000000,0x00000000,0x00011100,0x00011110,0x11111111,0x11111111,0x11111111

	.word 0x11111100,0x11111100,0x11111100,0x11111100,0x11111100,0x11111111,0x11111111,0x11111111
	.word 0x10000011,0x00000011,0x00000011,0x00000111,0x00000011,0x00000000,0x00000100,0x00000110
	.word 0x10001111,0x11011011,0x01110011,0x01110011,0x11011011,0x10001111,0x00001111,0x10001111
	.word 0x11111111,0x11111111,0x11111111,0x01111111,0x10011111,0x10001111,0x11101111,0x11111001
	.word 0x00000000,0x00000000,0x11000000,0x11000001,0x11000111,0x11000111,0x11110111,0x11110111
	.word 0x00000000,0x00000001,0x10000000,0x10111000,0x11111110,0x11001110,0x01111111,0x11111111
	.word 0x11111100,0x11111100,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111000
	.word 0x10011111,0x11000111,0x11111011,0x11111101,0x11111101,0x11111111,0x11111111,0x11111111

	.word 0x01111111,0x10111111,0x10011111,0x11101111,0x11101111,0x11101111,0x11111111,0x11111111
	.word 0x11000010,0x10110010,0x01111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11111111,0x11111111,0x11111110,0x11111111,0x11111011,0x11111111,0x11111111,0x11111111
	.word 0x11011111,0x01111111,0x01111111,0x11011111,0x10001111,0x00001111,0x11111111,0x11111111
	.word 0x11000110,0x11000110,0x11000110,0x11000110,0x11000111,0x01000111,0x11111111,0x11111111
	.word 0x00011111,0x00011111,0x00011111,0x00011111,0x00011111,0x00010000,0x11111111,0x11111111
	.word 0x00111111,0x11011111,0x11101111,0x11111001,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11110111,0x11110111,0x11110111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111

	.word 0x11110011,0x11101111,0x11101111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111

	.section .rodata
	.align	2
	.global bg1Map		@ 4096 unsigned chars
bg1Map:
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0001,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0003,0x0000,0x0004,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0005,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0006,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0007,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0009,0x000A,0x000B,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x000C,0x000D,0x000E
	.hword 0x000F,0x0010,0x0002,0x0011,0x0012,0x0013,0x0014,0x040E
	.hword 0x000D,0x000E,0x0414,0x0015,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0016,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0017,0x0018,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0019,0x001A,0x001B
	.hword 0x001C,0x0008,0x001D,0x001E,0x001F,0x041F,0x041E,0x0020
	.hword 0x0021,0x0022,0x0023,0x0024,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0016,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0025,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0026,0x0027,0x0000
	.hword 0x0028,0x0000,0x0000,0x0000,0x0000,0x0029,0x002A,0x042A
	.hword 0x002B,0x002C,0x002D,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x002E,0x002F,0x0000,0x0030,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0031,0x0032,0x0033
	.hword 0x0034,0x0008,0x0008,0x0008,0x0008,0x0008,0x0035,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0036,0x0037,0x0000
	.hword 0x0038,0x0039,0x003A,0x003B,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x003C,0x003D,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x003E,0x003F,0x0040,0x0041,0x0042,0x0000,0x0000

	.hword 0x0000,0x0043,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0044,0x0045,0x0046
	.hword 0x0047,0x0008,0x0008,0x0008,0x0008,0x0008,0x0035,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0048,0x0049,0x0000
	.hword 0x004A,0x004B,0x0048,0x0049,0x004C,0x0000,0x0000,0x0000
	.hword 0x0000,0x004D,0x004E,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x004F,0x0050,0x0051,0x0008,0x0052,0x0053,0x0000

	.hword 0x0054,0x0055,0x0056,0x0057,0x0058,0x0059,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0430,0x005A,0x005B,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x005C,0x005D
	.hword 0x005E,0x005F,0x0060,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0061,0x0062,0x0062,0x0063,0x0064,0x0062
	.hword 0x0008,0x0065,0x0063,0x0064,0x0066,0x0067,0x0068,0x0069
	.hword 0x0000,0x084D,0x084E,0x0000,0x0000,0x0000,0x0000,0x006A
	.hword 0x006B,0x006C,0x0008,0x0008,0x006D,0x006E,0x006F,0x006B

	.hword 0x0008,0x0008,0x0008,0x0008,0x0070,0x0859,0x0000,0x0000
	.hword 0x0000,0x0000,0x0071,0x0072,0x0073,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0074,0x0000,0x0075,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0076,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0077
	.hword 0x0000,0x083C,0x083D,0x0000,0x0000,0x0000,0x0000,0x0078
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0079,0x007A,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0C18,0x007B,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0416,0x007C,0x007D,0x007E,0x007F,0x0000
	.hword 0x0080,0x0081,0x0081,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0000
	.hword 0x0000,0x0082,0x0083,0x0000,0x0000,0x0084,0x0085,0x0016
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0086,0x0818,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0087,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0088,0x0089,0x0008,0x0008,0x008A,0x0081
	.hword 0x008B,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x008C,0x0000
	.hword 0x0000,0x008D,0x008E,0x008F,0x0090,0x0091,0x0092,0x0093
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0094,0x0095,0x0000
	.hword 0x0000,0x0096,0x0097,0x0098,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0C91,0x0099,0x0418
	.hword 0x006B,0x009A,0x0883,0x0000,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x009B,0x009C
	.hword 0x009D,0x009E,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x009F,0x00A0,0x00A1
	.hword 0x00A2,0x00A3,0x00A4,0x00A5,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x00A6,0x0409,0x00A7
	.hword 0x0008,0x00A8,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008
	.hword 0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008

@}}BLOCK(bg1)

@{{BLOCK(Shared)

@=======================================================================
@
@	Shared, 16x16@4, 
@	Transparent color : FF,00,FF
@	+ palette 256 entries, not compressed
@	Total size: 512 = 512
@
@	Time-stamp: 2013-08-18, 22:05:06
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global SharedPal		@ 512 unsigned chars
SharedPal:
	.hword 0x7C1F,0x3DAC,0x4A10,0x6B5A,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(Shared)
