#include "GenericTypeDefs.h"
#ifndef _PHYSICS_H
#define _PHYSICS_H

extern signed short int g_devAccelerationX;
extern signed short int g_devAccelerationY;
extern signed short int g_devAccelerationZ;

extern signed short int g_devAccOffsetX;
extern signed short int g_devAccOffsetY;
extern signed short int g_devAccOffsetZ;

extern signed short int CoefMeteoriteVelX;
extern int MeteoriteBaseX, Meteorite2BaseX, MeteoriteBaseY, Meteorite2BaseY;
extern signed short float MeteoriteVelX; // Velocity of the Meteorite in X
extern float MeteoriteAccX;// Acceleration of the Meteorite in X (gravity) float MeteoriteAccX=9.81f;// Acceleration of the Meteorite in X (gravity)
extern float MeteoriteMass;// Mass of the Meteorite (500g)
extern signed short int deltaX;// Displacement in X of the Meteorite during a time interval dt
extern signed short int deltaY;// Displacement in Y of the Meteorite during a time interval dt

extern int DX,DX2,DY,DY2;

extern signed short int CoefMeteorite2VelX;
extern int Meteorite2BaseX, Meteorite2BaseY;
extern signed short float Meteorite2VelX;
extern float Meteorite2AccX;
extern float Meteorite2Mass;
extern signed short int deltaX2;
extern signed short int deltaY2;

extern signed short int CoefSpaceshipVelX;
extern signed short int CoefSpaceship2VelX;

extern int SpaceshipBaseX, Spaceship2BaseX, SpaceshipBaseY, Spaceship2BaseY;
extern signed short float SpaceshipVelX;
extern float SpaceshipAccX;
extern float SpaceshipMass;

extern signed short int deltaSCX;
extern signed short int deltaSCY;

extern signed short int deltaSCX2;
extern signed short int deltaSCY2;

extern int DSCX,DSCX2,DSCY,DSCY2;

extern int planeX,planeY;
extern float g_planeX, g_planeY, g_planeZ;
extern int planeHeadX,planeHeadY;
extern float g_planeVelX, g_planeVelY, g_planeVelZ;
extern float g_planeForceX, g_planeForceY, g_planeForceZ;
extern unsigned char g_planeGth;
extern unsigned char g_planeGtt;
extern unsigned char flag;

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
void Meteorite_Rain(float dtime, unsigned char animBall);
void InitPhysics();
BOOL IsCollid(int x, int y);
int distance(int a, int b);
void WriteGameOver(void);
void WriteCongrats(void);
#endif
