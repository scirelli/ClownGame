//Draws falling balls on the desktop
// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <mmsystem.h> //needed to play a sound using windows also need to insert winmm.lib
					  //C:\Program Files\Microsoft Visual Studio\VC98\Lib
//// DEFINES ////////////////////////////////////////////////

//// Structures ////////////////////////////////
struct BALL
{
	float vy;
	float vx;
	float x;
	float y;
};

//// PROTOTYPES /////////////////////////////////////////////
HWND RegisterWindow(HINSTANCE hinstance);
void MainGameAnime(HDC, HWND, HPEN, HBRUSH, HPEN, BALL &);

// GLOBALS ////////////////////////////////////////////////

HWND main_window_handle = NULL; // save the window handle
HINSTANCE main_instance = NULL; // save the instance

/////FUNCTIONS /////////////
float deg2rad(float x)
{
	return (x/180*3.14159265f);
}

//\\\\\\\\\\\\\\\\\\\\\\\\ WINMAIN ////////////////////////////////////////////////

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{

	HWND	 hwnd;		  // generic window handle
	MSG		 msg;		  // generic message
	HDC      hdc;         // generic dc
	BALL     ball;
	HPEN red_pen, black_pen;
	HBRUSH red_brush;
	int force= 25;
	float angle=160;

	//------Initialization---------
	// save the window handle and instance in a global
	main_window_handle = hwnd = RegisterWindow(hinstance);
	main_instance      = hinstance;
	
	ball.vx = (float) sin( deg2rad(angle) ) * force;
	ball.vy = (float) cos( deg2rad(angle) ) * force;
	ball.x = 30;
	ball.y = 399;
	red_pen= CreatePen(PS_SOLID,0, RGB(255,0,0));
	red_brush= CreateSolidBrush(RGB(255,0,0));
	black_pen= CreatePen(PS_SOLID,0, RGB(0,0,0));
	
	//-------End Initial ----------------
	// enter main event loop
	while(1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit message
			if (msg.message == WM_QUIT)
				break;
	
			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
    
    	hdc= GetDC(hwnd);

		MainGameAnime(hdc, hwnd, red_pen, red_brush, black_pen, ball);	
		
		ReleaseDC(hwnd, hdc);
	
	} // end while
	
	DeleteObject(red_pen);
	DeleteObject(red_brush);
	DeleteObject(black_pen);
	
	// return to Windows like this
	return(msg.wParam);

} // end WinMain


