#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
#include "dxgraphics.h"
#include "dxaudio.h"
#include "dxinput.h"
#include "game.h"

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		if (d3ddev != NULL)
			d3ddev->Release();
		if (d3d != NULL)
			d3d->Release();
		if (dinput != NULL)
			dinput->Release();
		Kill_Keyboard();
		Kill_Mouse();
		Game_End(hWnd);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	//fill the struct with info
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm = NULL;

	//set up the window with the class info
	return RegisterClassEx(&wc);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	MyRegisterClass(hInstance);
	DWORD style;
	if (FULLSCREEN)
		style = WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	hWnd = CreateWindow(APPTITLE,
		APPTITLE,
		style,
		200,
		80,
		SCREENWIDTH,
		SCREENHEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, "Khong Khoi Tao Windows", "Loi CreateWindows", MB_OK);
		return 0;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (!Init_Direct3D(hWnd, SCREENWIDTH, SCREENHEIGHT, FULLSCREEN))
	{
		MessageBox(NULL, "Khong Khoi Tao Direct 3D", "Loi Init_Driect3D", MB_OK);
		return 0;
	}
	if (!Init_DirectInput(hWnd))
	{
		MessageBox(hWnd, "Error initializing DirectInput", "Error", MB_OK);
		return 0;
	}
	if (!Init_DirectSound(hWnd))
	{
		MessageBox(hWnd, "Error initializing DirectSound", "Error", MB_OK);
		return 0;
	}
	if (!Game_Init(hWnd))
	{
		MessageBox(NULL, "Khong khoi tao game", "Loi Game_Init", MB_OK);
		return 0;
	}

	int done = 0;
	DWORD frame_start = timeGetTime();;
	int _FrameRate = 60;
	DWORD tick_per_frame = 1000 / _FrameRate;
	DWORD _DeltaTime = 0;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD now = timeGetTime();
			_DeltaTime = now - frame_start;
			if (_DeltaTime >= tick_per_frame)
			{
				frame_start = now;
				Game_Run(hWnd, _DeltaTime);
			}
		}
	}

	return msg.wParam;
}