#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <mmsystem.h> //needed to play a sound using windows also need to insert winmm.lib
					  //C:\Program Files\Microsoft Visual Studio\VC98\Lib

//// MACROS /////////////////////////////////////////////////

// these read the keyboard asynchronously
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

//// FUNCTIONS //////////////////////////////////////////////

//// Structures ////////////////////////////////
struct BALL
{
	float vy;
	float vx;
	float x;
	float y;
};

void MainGameAnime(HDC hdc, HWND hwnd, HPEN red_pen, HBRUSH red_brush, HPEN black_pen, BALL & ball)
{
	RECT     rect;        //create a rectangle structure
	int      ball_radius= 2;  //radius of the ball
	float    gravity= 1.1f,    //amount of gravity affecting the ball
			 friction= 0.995f; //amount of friction slowing the ball down
		
	//--------- Erase The Ball -----------------------------
	//fill in rect struct for erasing ball
	rect.left = ball.x - ball_radius;
	rect.right = ball.x + ball_radius;
	rect.top = ball.y - ball_radius;
	rect.bottom = ball.y + ball_radius;
		
	//Draw erasing ball
	SelectObject(hdc, black_pen); //black pen
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	Ellipse(hdc,rect.left, rect.top, rect.right, rect.bottom);
	//--------- End Erase The Ball --------------------------
		
	//------ Move the ball--------------
		
	ball.vy += gravity;
	ball.vy *= friction;
	ball.y += ball.vy;
	
	ball.vx += 0;
	ball.vx *= friction;
	ball.x +=  ball.vx;

	if(ball.y >= 400)
	{
		ball.vy = -(ball.vy * 0.995);
		ball.y = 400;
	}
	if(ball.y <= 20)
	{
		ball.vy = -(ball.vy * 0.995);
		ball.y = 20;
	}
	if(ball.x >= 600)
	{
		ball.vx = -ball.vx;
		ball.x = 600;
	}
	if(ball.x <= 20)
	{
		ball.vx = -ball.vx;
		ball.x = 20;
	}
			
	//------ End Move ball -------------

	//---------- Draw The Ball ------------------------------
	//Redraw the ball in its new position
		
	//fill in rect struct for drawing ball
	rect.left = ball.x - ball_radius;
	rect.right = ball.x + ball_radius;
	rect.top = ball.y - ball_radius;
	rect.bottom = ball.y + ball_radius;
	
	//Draw the ball in its new spot
	SelectObject(hdc, red_pen);
	SelectObject(hdc, red_brush);
	Rectangle(hdc,20,400,50,409);
	MoveToEx(hdc,20,20,NULL);
	LineTo(hdc,20,400);
	LineTo(hdc,600,400);
	LineTo(hdc, 600,20);
	LineTo(hdc,20, 20);
	Ellipse(hdc,rect.left, rect.top, rect.right, rect.bottom);
	//---------- End Draw The Ball --------------------------

	//slow things down a bit
	Sleep(25);
		
	return;
}