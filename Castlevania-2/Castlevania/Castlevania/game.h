#ifndef _GAME_H
#define _GAME_H

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <dsound.h>
#include <dinput.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "dxgraphics.h"
#include "dxaudio.h"
#include "dxinput.h"
#include "camera.h"

#define SCREENWIDTH		515
#define SCREENHEIGHT	450
#define FULLSCREEN		0
#define APPTITLE		"Castlevania"
extern LPD3DXSPRITE	SpriteHandler;

int Game_Init(HWND);
void Game_Run(HWND, int);
void Game_End(HWND);

extern camera	cmr;
extern camera	cmr2;
#endif