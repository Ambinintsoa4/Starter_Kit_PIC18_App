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



float g_foodX, g_foodY;

int planeHeadX,planeHeadY;// plane's head position in X,Y
float g_planeX, g_planeY, g_planeZ;
float g_planeVelX, g_planeVelY, g_planeVelZ;
float g_planeMass;
float g_planeForceX, g_planeForceY, g_planeForceZ;

unsigned char g_planeGth = 0;
unsigned char g_planeGtt = 0;


/*float g_ballX, g_ballY, g_ballZ;
float g_ballVelX, g_ballVelY, g_ballVelZ;
float g_ballForceX, g_ballForceY, g_ballForceZ;
float g_ballMass;
unsigned char g_ballGth = 0;
unsigned char g_ballGtt = 0;
*/
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
	}
}

void InitPhysics()
{
	//food.x = rand() % OLEDX-8;
	//food.y = rand() % OLEDY-8;
	g_planeX = 64, g_planeY = 32;
	g_planeVelX = g_planeVelY= g_planeVelZ = 0;
	g_planeForceX = g_planeForceY = g_planeForceZ = 0;
	g_planeMass = 0.5f;		
}



