#include "physics.h"
#include "graph.h"
#include "GenericTypeDefs.h"
#include "BMA150.h"
#include "levels.h"
#include "math.h"
#include "oled.h"
#include <stdlib.h> // for rand() function

signed short int g_devAccelerationX;
signed short int g_devAccelerationY;
signed short int g_devAccelerationZ;

signed short int g_devAccOffsetX = 0;
signed short int g_devAccOffsetY = 0;
signed short int g_devAccOffsetZ = 0;



float g_spaceshipX, g_spaceshipY;

//Meteorite
signed short int CoefMeteoriteVelX;
signed short int CoefMeteorite2VelX;

int MeteoriteBaseX, Meteorite2BaseX, MeteoriteBaseY, Meteorite2BaseY; // Position of the base of the meteorite in X,Y
signed short float MeteoriteVelX;// Velocity of the velocity in X
float MeteoriteAccX=9.81f;// Acceleration of the meteorite in X (gravity)
float MeteoriteMass=0.5f;// Mass of the meteorite (500g)

int Meteorite2BaseX, Meteorite2BaseY; // Position of the base of the meteorite in X,Y
signed short float Meteorite2VelX;// Velocity of the velocity in X
float Meteorite2AccX=9.81f;// Acceleration of the meteorite in X (gravity)
float Meteorite2Mass=0.5f;// Mass of the meteorite (500g)

signed short int deltaX;// Displacement in X of the meteorite during a time interval dt
signed short int deltaY;// Displacement in Y of the meteorite during a time interval dt

signed short int deltaX2;// Displacement in X of the meteorite during a time interval dt
signed short int deltaY2;// Displacement in Y of the meteorite during a time interval dt

int DX,DX2,DY,DY2;// Relative distance between plane and meteorite in X,Y
int DX2WIN,DY2WIN;// Relative distance between plane and meteorite in X,Y to win

//Spaceship
signed short int CoefSpaceshipVelX;
signed short int CoefSpaceship2VelX;

int SpaceshipBaseX, Spaceship2BaseX, SpaceshipBaseY, Spaceship2BaseY; // Position of the base of the Spaceship in X,Y
signed short float SpaceshipVelX;// Velocity of the Spaceship in X
float SpaceshipAccX=9.81f;// Acceleration of the Spaceship in X (gravity)
float SpaceshipMass=0.5f;// Mass of the Spaceship (500g)

signed short int deltaSCX;// Displacement in X of the Spaceship during a time interval dt
signed short int deltaSCY;// Displacement in Y of the Spaceship during a time interval dt

signed short int deltaSCX2;// Displacement in X of the Spaceship during a time interval dt
signed short int deltaSCY2;// Displacement in Y of the Spaceship during a time interval dt

int DSCX,DSCX2,DSCY,DSCY2;// Relative distance between plane and Spaceship in X,Y
int DSCX2WIN,DSCY2WIN;// Relative distance between plane and meteorite in X,Y to win



int planeHeadX,planeHeadY;// plane's head position in X,Y
float g_planeX, g_planeY, g_planeZ;
float g_planeVelX, g_planeVelY, g_planeVelZ;
float g_planeMass;
float g_planeForceX, g_planeForceY, g_planeForceZ;

unsigned char g_planeGth = 0;
unsigned char g_planeGtt = 0;
unsigned char flag = 0;

unsigned char g_colDirs = 0; //0000.x1 x2 y1 y2;

//rom unsigned char sin100_tab[32] = {0, 9, 19, 29, 38, 47, 56, 64, 71, 78, 84, 89, 93, 96, 98, 99, 99, 99, 97, 94, 90, 86, 80, 74, 67, 59, 51, 42, 33, 23, 14, 4};


float wallLineUp(unsigned char x, struct physWall w)
{
	return ((((float)x-(float)w.Ax)/((float)w.Bx-(float)w.Ax))*((float)w.Ay-(float)w.By) + (float)w.By);
}

float wallLineDown(unsigned char x, struct physWall w)
{
	return ((((float)x-(float)w.Ax)/((float)w.Bx-(float)w.Ax))*((float)w.By-(float)w.Ay) + (float)w.Ay);
}

void checkWall(struct physWall w)
{
	if (g_planeX >= w.Ax && g_planeX <= w.Bx && g_planeY >= w.Ay && g_planeY <= w.By)
	{
		if (g_planeY>=wallLineDown(g_planeX, w) && g_planeY<=wallLineUp(g_planeX, w))
		{
			g_planeX = w.Ax;
			g_planeVelX = -g_planeVelX*0.6f;
			g_colDirs |= 0x01;
		}
		else if (g_planeY<=wallLineDown(g_planeX, w) && g_planeY>=wallLineUp(g_planeX, w))
		{
			g_planeX = w.Bx;
			g_planeVelX = -g_planeVelX*0.6f;
			g_colDirs |= 0x02;
		}
		else if (g_planeY>wallLineDown(g_planeX, w) && g_planeY>wallLineUp(g_planeX, w))
		{
			g_planeY = w.By;
			g_planeVelY = -g_planeVelY*0.6f;
			g_colDirs |= 0x04;
		}
		else if (g_planeY<wallLineDown(g_planeX, w) && g_planeY<wallLineUp(g_planeX, w))
		{
			g_planeY = w.Ay;
			g_planeVelY = -g_planeVelY*0.6f;
			g_colDirs |= 0x08;
		}
	}
}

void ReadAccState()
{
	//do sprawdzenia i ew poprawy
	unsigned char lsb, msb;
	lsb = BMA150_ReadByte(BMA150_ACC_X_LSB);
	msb = BMA150_ReadByte(BMA150_ACC_X_MSB);
	
	g_devAccelerationX = (signed short int)(((unsigned short int)msb << 8) | (lsb));
	g_devAccelerationX /= 32;

	lsb = BMA150_ReadByte(BMA150_ACC_Y_LSB);
	msb = BMA150_ReadByte(BMA150_ACC_Y_MSB);
	
	g_devAccelerationY = (signed short int)(((unsigned short int)msb << 8) | (lsb));
	g_devAccelerationY /= 32;

	lsb = BMA150_ReadByte(BMA150_ACC_Z_LSB);
	msb = BMA150_ReadByte(BMA150_ACC_Z_MSB);
	
	/*g_devAccelerationZ = (signed short int)(((unsigned short int)msb << 8) | (lsb));
	g_devAccelerationZ /= 32;*/
}

void Step(float dtime, unsigned char animPlane)
{
	float posChange, d;
	unsigned char i, j;
	static float time = 0.0f;

	time = time+dtime;

	ReadAccState();

	
	SpaceshipBaseX = spaceship.x;
	Spaceship2BaseX = spaceship.x;
	SpaceshipBaseY = spaceship.y;
	Spaceship2BaseY = spaceship.y + 40;

	DSCX = distance(SpaceshipBaseX, g_planeX);
	DSCX2 = distance(Spaceship2BaseX, g_planeX);
	DSCY =  distance(SpaceshipBaseY, g_planeY);
	DSCY2 = distance(Spaceship2BaseY, g_planeY);

	if (animPlane)
	{
		g_planeForceX = (float)(g_devAccelerationY-g_devAccOffsetY)/2.0f;
		g_planeForceY = (float)(g_devAccelerationX-g_devAccOffsetX)/2.0f;
		
		posChange = g_planeX + ((float)g_planeVelX* dtime) + (((g_planeForceX) / g_planeMass) * dtime * dtime) / 2.0f;
	    g_planeVelX = (posChange - g_planeX) / dtime;
	    g_planeX = posChange;
	
		posChange = g_planeY + ((float)g_planeVelY * dtime) + (((g_planeForceY) / g_planeMass) * dtime * dtime) / 2.0f;
	    g_planeVelY = (posChange - g_planeY) / dtime;
	    g_planeY = posChange;
		
		if (g_planeY <= 3)
		{
			g_planeY = 3;
			g_planeVelY= -g_planeVelY*0.6f;

			if ((g_colDirs & 0x08) == 0x08)
				g_planeGth = 1;
		}
	
		if (g_planeY >= 53)
		{
			g_planeY = 53;
			g_planeVelY = -g_planeVelY*0.6f;

			if ((g_colDirs & 0x04) == 0x04)
				g_planeGth = 1;
		}
	
		if (g_planeX <= 3)
		{
			g_planeX = 3;
			g_planeVelX = -g_planeVelX*0.6f;

			if ((g_colDirs & 0x02) == 0x02)
				g_planeGth = 1;
		}
	
		if (g_planeX >= 118)
		{
			g_planeX = 118;
			g_planeVelX = -g_planeVelX*0.6f;

			if ((g_colDirs & 0x01) == 0x01)
				g_planeGth = 1;
		}

if (g_planeX == 118)
		{
			flag = 2;
			}
	}
}

void InitPhysics()
{
	g_planeX = 64, g_planeY = 32;
	g_planeVelX = g_planeVelY= g_planeVelZ = 0;
	g_planeForceX = g_planeForceY = g_planeForceZ = 0;
	g_planeMass = 0.5f;	

	//Food = Vaisseau spatiale
	spaceship.x = 120;
	spaceship.y = 12;
	
	// Meteorite 1
	MeteoriteVelX=1.0f;
	MeteoriteAccX=9.81f;
	MeteoriteMass=0.5f;

	// Meteorite 2
	Meteorite2VelX=0.5f;
	Meteorite2AccX=9.81f;
	Meteorite2Mass=0.5f;
	g_planeGth = 0;
	g_planeGtt = 0;
	deltaY=0;	

}
int abs(int x)
{
	int absx=x;
	if (x<0)
	{
		absx=-x;
	}
	return (absx);
}

void Meteorite_Rain(float dtime, unsigned char animBall)
{
	CoefMeteoriteVelX=0;
	CoefMeteorite2VelX=1;

	MeteoriteVelX*=(float)CoefMeteoriteVelX;	
	Meteorite2VelX*=(float)CoefMeteorite2VelX;

	if (animBall)

	{	// Free fall theory meteorite 1 
	deltaX=(int)((MeteoriteVelX*dtime)+((MeteoriteAccX*dtime*dtime)/2.0f));
	meteorite.x-= deltaX ;
	MeteoriteVelX=1.0f;

		// Free fall theory meteorite 2 
	deltaX2=(int)((Meteorite2VelX*dtime)+(Meteorite2AccX*dtime*dtime) / 2.0f);
	meteorite2.x-= deltaX;
	Meteorite2VelX=0.5f;
	

	MeteoriteBaseX=meteorite.x;
	Meteorite2BaseX=meteorite2.x;

	MeteoriteBaseY=spaceship.y;
	Meteorite2BaseY=spaceship.y + 40;

	DX = distance( MeteoriteBaseX, g_planeX);
	DX2 = distance( Meteorite2BaseX, g_planeX);
	DY = distance( MeteoriteBaseY, g_planeY);
	DY2 = distance( Meteorite2BaseY, g_planeY);



if (IsCollid(DX, DY) == TRUE || IsCollid(DX2, DY2)== TRUE)
		{
		 	flag = 1;
		} 
	return;
	}
}
BOOL IsCollid(int x, int y){
	DX2WIN=1;
	DY2WIN=3;

	if(x<=DX2WIN && y<=DY2WIN)
	{
		return TRUE;
	} 
		return FALSE;
}

int distance(int a, int b) {
	return abs(a - b);
}





