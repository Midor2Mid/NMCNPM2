#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <map>
#include <utility>
#include "game.h"
#include "dxinput.h"
#include "Camera.h"
#include "gameplay.h"
#include "introscreen.h"
#include "mainmenu.h"

int				GameState = 0;
camera			cmr;
camera			cmr2;
LPD3DXSPRITE	SpriteHandler;
HRESULT			result;
CGamePlay		*gameplay;
cintro			*introscreen;
cmainmenu		*mainmenu;
int isinitgame = false;
int invertcolor = false;
CColor color(0, 0, 0, 0);

int Game_Init(HWND hWnd)
{
	srand(NULL);
	if (!Init_Keyboard(hWnd))
		return 0;
	result = D3DXCreateSprite(d3ddev, &SpriteHandler);
	if (result != D3D_OK)
		return 0;

	//introcreen = new cintro();
	mainmenu = new cmainmenu();
	mainmenu->initialize();
	return 1;
}

int OnKeyDown(int KeyCode)
{
	switch (GameState)
	{
	case 0:
		mainmenu->onKeyDown(KeyCode);
		break;
	case 1:
		break;
	case 2:
		gameplay->OnKeyDown(KeyCode);
		break;
	}

	return 0;
}

int OnKeyUp(int KeyCode)
{
	switch (GameState)
	{
	case 0:
		//mainmenu->onKeyDown(KeyCode);
		break;
	case 1:
		break;
	case 2:
		gameplay->OnKeyUp(KeyCode);
		break;
	}
	return 0;
}

void Game_Run(HWND hWnd, int delta)
{
	Poll_Keyboard();
	switch (GameState)
	{
	case 0:
		mainmenu->update(delta);
		break;
	case 1:
		introscreen->update(delta);
		if (introscreen->isend)
		{
			GameState = 2;
			gameplay = new CGamePlay();
			gameplay->initialize();
		}
		break;
	case 2:
		gameplay->update(delta);
		break;
	case 3:
		break;
	}

	if (d3ddev->BeginScene())
	{

#pragma region
		if (GameState == 2 || GameState == 3)
		{
			if (gameplay != NULL)
				if (gameplay->isActiveHolyCross())
				{
					if (!invertcolor)
					{
						color.setB(color.getB() - 255);
						color.setG(color.getG() - 255);
						color.setR(color.getR() - 255);
					}
					else
					{
						color.setB(color.getB() + 255);
						color.setG(color.getG() + 255);
						color.setR(color.getR() + 255);
					}
					if (color.getB() < 0 || color.getG() < 0 || color.getR() < 0)
					{
						color.setB(0);
						color.setG(0);
						color.setR(0);
						invertcolor = true;
					}
					else
						if (color.getB() > 255 || color.getG() > 255 || color.getR() > 255)
						{
							color.setB(255);
							color.setG(255);
							color.setR(255);
							invertcolor = false;
						}
				}
				else
				{
					invertcolor = false;
					color.setARGB(0, 0, 0, 0);
				}
		}
		else
		{
			color.setARGB(0, 0, 0, 0);
		}
#pragma endregion tao hieu ung set danh

		d3ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(color.getR(), color.getG(), color.getB()), 1.0f, 0);
		SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		switch (GameState)
		{
		case 0:
			if (mainmenu == NULL)
				mainmenu = new cmainmenu();
			mainmenu->render(delta);
			if (mainmenu->isSelected)
			{
				switch (mainmenu->currentSelection)
				{
				case 0:
					GameState = 1;
					introscreen = new cintro();
					introscreen->initialize();
					mainmenu->isSelected = false;
					break;
				case 1:
					GameState = 2;
					gameplay = new CGamePlay();
					gameplay->LoadSaveGame();
					gameplay->initialize();
					mainmenu->isSelected = false;
					break;
				case 2:
					mainmenu->isSelected = false;
					PostMessage(hWnd, WM_DESTROY, 0, 0);
					break;
				}
			}

			if (Key_Down(DIK_ESCAPE))
				PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		case 1:
			introscreen->render(delta);
			break;
		case 2:
			if (gameplay->isExit)
			{
				GameState = 0;
				gameplay->isExit = 0;
			}
			gameplay->render(delta);
			break;
		case 3:
			break;
		}

		SpriteHandler->End();

		switch (GameState)
		{
		case 0:
			mainmenu->renderText(delta);
			break;
		case 1:
			//mainmenu->renderText(delta);
			break;
		case 2:
			gameplay->renderText(delta);
			break;
		case 3:
			break;
		}

		d3ddev->EndScene();

	}
	d3ddev->Present(NULL, NULL, NULL, NULL);



}

void Game_End(HWND hWnd)
{
	if (SpriteHandler != NULL)
		SpriteHandler->Release();
}


