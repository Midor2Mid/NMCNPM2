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
#include "global.h"
#include "dxinput.h"
#include "camera.h"




int Game_Init(HWND);
void Game_Run(HWND, int);
void Game_End(HWND);


#endif