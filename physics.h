#ifndef _PHYSICS_H
#define _PHYSICS_H

extern signed short int g_devAccelerationX;
extern signed short int g_devAccelerationY;
extern signed short int g_devAccelerationZ;

extern signed short int g_devAccOffsetX;
extern signed short int g_devAccOffsetY;
extern signed short int g_devAccOffsetZ;

/*extern float g_ballX, g_ballY, g_ballZ;
extern float g_ballVelX, g_ballVelY, g_ballVelZ;
extern float g_ballForceX, g_ballForceY, g_ballForceZ;
extern unsigned char g_ballGth;
extern unsigned char g_ballGtt;*/

extern int planeX,planeY;
extern float g_planeX, g_planeY, g_planeZ;
extern int planeHeadX,planeHeadY;
extern float g_planeVelX, g_planeVelY, g_planeVelZ;
extern float g_planeForceX, g_planeForceY, g_planeForceZ;
extern unsigned char g_planeGth;
extern unsigned char g_planeGtt;


struct physWall{
	signed short int Ax,Bx,Ay, By;
} ;

struct physWallMover
{
	unsigned char wallId;
	unsigned char amp;
	unsigned char speedCoef;
	unsigned char orientation;
	unsigned char x, y;
} ;

void ReadAccState();
void Step(float dtime, unsigned char animBall);
void InitPhysics();

#endif
