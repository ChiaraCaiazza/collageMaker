collageMaker:	collageMaker.c ioUtils.c layout.c imageUtils.c
	gcc -lconfig -Wall collageMaker.c ioUtils.c layout.c imageUtils.c `pkg-config vips --cflags --libs` -o collageMaker