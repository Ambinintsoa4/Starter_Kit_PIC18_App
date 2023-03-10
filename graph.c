#include "graph.h"
#include "oled.h"
#include "physics.h"
#include "levels.h"


#pragma idata graph_buffer
unsigned char g_graphBuffer[128][8];
#pragma idata

unsigned char * g_graphBufPtr = &g_graphBuffer[0][0];

void FlushGraphics();
//void loadLevel(unsigned char l);


void GeneratePhysWall(struct physWall *w, struct graphWall g)
{
	if (g.orientation == 0)
	{
		w->Ax = g.c2_start-8;
		w->Bx = g.c2_end;

		if (g.c < (signed short int)8)
			w->Ay = 0;
		else
			w->Ay = g.c-8;
		
		w->By = g.c+3;
		if (g.c2_start == 0)
			w->Ax = -30;
		if (g.c2_end == 127)
			w->Bx = 150;
	}
	else
	{
		w->Ax = g.c - 8;
		w->Bx = g.c + 3;

		if (g.c2_start < (signed short int)8)
			w->Ay = 0;
		else
			w->Ay = g.c2_start-8;

		w->By = g.c2_end;

		if (g.c2_end == 63)
			w->By = 80;
	}

	return;
}


void FlushGraphics()
{
	int i, j;

	for (j = 0; j < 8; j++)
	{
		WriteCommand(0xB0+j);
		WriteCommand(0x00+OFFSET);
		WriteCommand(0x10);

		for (i = 0; i < 128; i++)
		{
			WriteData(g_graphBufPtr[i+128*j]);
		}
	}
}

void Fill(unsigned char clr)
{
	int i;
	for (i = 0; i < 1024; i++)
	{
		g_graphBufPtr[i] = clr;
	}
}



void DrawSpaceship(unsigned char x, unsigned char y)
{
						SetPx(x+3,y-1); SetPx(x+4,y-1);
	 					SetPx(x+3,y-2); SetPx(x+4,y-2);
						SetPx(x+3,y-3); SetPx(x+4,y-3); 
	SetPx(x+0,y+2); SetPx(x+0,y+3); SetPx(x+0,y+4); SetPx(x+0,y+5);
	SetPx(x+7,y+2); SetPx(x+7,y+3); SetPx(x+7,y+4); SetPx(x+7,y+5);
	SetPx(x+2,y+0); SetPx(x+3,y+0); SetPx(x+4,y+0); SetPx(x+5,y+0);
	SetPx(x+2,y+7); SetPx(x+3,y+7); SetPx(x+4,y+7); SetPx(x+5,y+7);
	SetPx(x+1,y+1); SetPx(x+6,y+1); SetPx(x+6,y+6); SetPx(x+1,y+6);
						SetPx(x+3,y+8); SetPx(x+4,y+8);
	 					SetPx(x+3,y+9); SetPx(x+4,y+9);
						SetPx(x+3,y+10); SetPx(x+4,y+10); 
	
}
void DrawMeteorite(unsigned char x, unsigned char y)
{ 
						SetPx(x+1,y); SetPx(x+2,y); SetPx(x+3,y); SetPx(x+4,y);
						SetPx(x+1,y+1); SetPx(x+2,y+1); SetPx(x+3,y+1); SetPx(x+4,y+1);

}



void DrawPlane(unsigned char x, unsigned char y)
{
SetPx(x+13,y+5); 
SetPx(x+12,y+4); SetPx(x+12,y+6);
SetPx(x+11,y+3); SetPx(x+11,y+7); 
SetPx(x+10,y+3); SetPx(x+10,y+7); 
SetPx(x+9,y+3); SetPx(x+9,y+7); 
SetPx(x+8,y+3); SetPx(x+8,y+7);
SetPx(x+7,y+3); SetPx(x+7,y+7); 
SetPx(x+6,y+3); SetPx(x+6,y+7);
SetPx(x+5,y+3); SetPx(x+5,y+7);  
SetPx(x+4,y+3); SetPx(x+4,y+7); 
SetPx(x+3,y+2); SetPx(x+3,y+8); 
SetPx(x+2,y+1); SetPx(x+2,y+9); 
SetPx(x+1,y); SetPx(x+1,y+10); 
SetPx(x,y-1);SetPx(x,y+11);
SetPx(x-1,y-1); SetPx(x-1,y); SetPx(x-1,y+4); SetPx(x-1,y+5); SetPx(x-1,y+9); SetPx(x-1,y+10);
SetPx(x-2,y-1); SetPx(x-2,y); SetPx(x-2,y+4); SetPx(x-2,y+5); SetPx(x-2,y+9); SetPx(x-2,y+10);
}



void DrawCircle(unsigned char x, unsigned char y)
{
	SetPx(x+0,y+2); SetPx(x+0,y+4); //0
	SetPx(x+7,y+3); SetPx(x+7,y+5); //7
	SetPx(x+1,y+1); SetPx(x+1,y+3); SetPx(x+1,y+5); //1
	SetPx(x+6,y+2); SetPx(x+6,y+4); SetPx(x+6,y+6); //6
	SetPx(x+2,y+0); SetPx(x+2,y+2); SetPx(x+2,y+4); SetPx(x+2,y+6); // 2
	SetPx(x+4,y+0); SetPx(x+4,y+2); SetPx(x+4,y+4); SetPx(x+4,y+6); // 4
	SetPx(x+3,y+1); SetPx(x+3,y+3); SetPx(x+3,y+5); SetPx(x+3,y+7); // 3
	SetPx(x+5,y+1); SetPx(x+5,y+3); SetPx(x+5,y+5); SetPx(x+5,y+7); // 5

	SetPx(x+0,y+3); SetPx(x+0,y+5); SetPx(x+1,y+6); SetPx(x+2,y+7);
	SetPx(x+3,y+0); SetPx(x+4,y+7); SetPx(x+5,y+0); SetPx(x+6,y+1);
	SetPx(x+7,y+2); SetPx(x+7,y+4);
}


void DrawHorWall(unsigned char y, unsigned char x_start, unsigned char x_end)
{
	unsigned char i, j;
	for (i = x_start; i <= x_end; i++)
	{
		SetPx(i,y);
		SetPx(i,y+2);
		if (i&0x01 == 1)
			SetPx(i,y+1);
	}

	SetPx(x_start,y+1);
	SetPx(x_end,y+1);
}

void DrawVerWall(unsigned char x, unsigned char y_start, unsigned char y_end)
{
	unsigned char i, j;
	for (i = y_start; i <= y_end; i++)
	{
		SetPx(x,i);
		SetPx(x+2,i);
		if (i&0x01 == 1)
			SetPx(x+1,i);
	}

	SetPx(x+1,y_start);
	SetPx(x+1,y_end);
}

/*void DrawWall(struct graphWall g)
{
	if (g.orientation == 0)
		DrawHorWall(g.c, g.c2_start, g.c2_end);
	else
		DrawVerWall(g.c, g.c2_start, g.c2_end);
}*/

/*void DrawScene()
{
	unsigned char i;
	// Clear the scene
	Fill(0x00);

				//DrawHole(i, i/2);
			//	DrawPlace((unsigned char)(120-i), i/2);
			//	DrawBall(60, (unsigned char)(64-i/2));

	// Draw box around the screen
	DrawHorWall(0, 0, 127);
	DrawHorWall(61, 0, 127);
	DrawVerWall(0, 0, 63);
	DrawVerWall(125, 0, 63);

	if (g_ballGth == 0)
		DrawBall((unsigned char)g_ballX, (unsigned char)g_ballY, 4);
	else
	{
		g_ballGth++;

		if (g_ballGth < 5)
		{
			DrawBall((unsigned char)g_ballX, (unsigned char)g_ballY, 3);
		}
		else if (g_ballGth < 10)
		{
			DrawBall((unsigned char)g_ballX, (unsigned char)g_ballY, 2);
		}
		else if (g_ballGth < 15)
		{
			DrawBall((unsigned char)g_ballX, (unsigned char)g_ballY, 1);
		}
		else
		{
			g_ballGth = 0;
			//loadLevel(g_level);	
			Step(0.0f, 0);
		}
	}

	DrawTrigger(g_levelEndX, g_levelEndY);	
	//DrawPlace((unsigned char)g_ballX+1, (unsigned char)g_ballY);
	//DrawHorWall(20, 0, 70);
	//DrawHorWall(40, 40, 127);

	for (i = 0; i < g_usedWalls; i++)
	{
		DrawWall(g_walls[i]);
	}

	for (i = 0; i < g_usedHoles; i++)
	{
		DrawHole(g_holes[i].x, g_holes[i].y);
	}

	if (g_ballGtt != 0)
	{
		if (g_ballGtt < (unsigned char)16)
		{
			drawRect((g_ballGtt*8)-1);
		}
		else
		{
			drawRect(((32-g_ballGtt)*8)-1);
		}

		g_ballGtt++;

		if (g_ballGtt == (unsigned char)16)
		{
			g_level++;
			//loadLevel(g_level);
		}
		else if (g_ballGtt == (unsigned char)32)
			g_ballGtt = 0;

		
		
	}*/

void DrawScene()
{
	unsigned char i;


if(flag == 0){
// Clear the scene
	Fill(0x00);
//  DrawPlane (55, 20);
	DrawSpaceship(spaceship.x, spaceship.y);
	DrawSpaceship(spaceship.x, spaceship.y + 40);

//	DrawMeteorite(spaceship.x - 5, spaceship.y + 3);
	DrawMeteorite( (meteorite.x), spaceship.y );
	DrawMeteorite( meteorite2.x, spaceship.y + 40);
	DrawPlane ((unsigned char)g_planeX, (unsigned char)g_planeY);
}
else if(flag == 1){
	Fill(0x00);
	WriteGameOver();
}
else if (flag == 2){
	Fill(0x00);
	WriteCongrats();
} 


	// Send all data to screen driver
	FlushGraphics();
}
