#ifndef GRAPH_H
#define GRAPH_H

#include "physics.h"

#pragma idata graph_buffer
extern unsigned char g_graphBuffer[128][8];
#pragma idata

extern unsigned char * g_graphBufPtr;// = &g_graphBuffer[0];

#define SetPx(x,y) g_graphBufPtr[x+(y >> 3)*128] |= (0x01 << (y&0x07))
/*#define SetPx(x, y, r, g, b) \
do { \
    unsigned int index = (x) + ((y) >> 3) * 128; \
    unsigned char bitPos = (y) & 0x07; \
    unsigned char bitMask = 1 << bitPos; \
    g_graphBufPtr[index] &= ~bitMask; \
    g_graphBufPtr[index] |= ((r & 0x01) << 2) | ((g & 0x01) << 1) | (b & 0x01); \
} while(0)*/

struct Spaceship {
	unsigned char x,y;
};

struct Meteorite {
	unsigned char x,y;
};

struct graphWall {
	unsigned char c;
	unsigned char c2_start, c2_end;
	unsigned char orientation; // 0 - horizontal, 1 - vertical
};

struct Hole {
	unsigned char x,y;
};

void DrawBall(unsigned char x, unsigned char y, unsigned char p1);
void DrawScene();
void Fill(unsigned char clr);

void GeneratePhysWall(struct physWall *w, struct graphWall g);

#endif
