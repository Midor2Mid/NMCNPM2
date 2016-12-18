#include "mainmenu.h"

cmainmenu::cmainmenu()
{
	isSelected = false;
}

cmainmenu::~cmainmenu()
{
}

void cmainmenu::initialize()
{
	arialbigger.initialize(32);
	arialsmaller.initialize(22);
	mainmenu.load("resource/image//mainmenu.png", 1, 1);
	mainmenu.setPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);
	mainmenu.setCamera(1);
	currentSelection = 0;
	menuitem[0] = "New Game";
	menuitem[1] = "Continue";
	menuitem[2] = "Exit";
	isSelected = false;
	select = LoadSound("resource/sound/select.wav");
	backgroundmusic = LoadSound("resource/music/Title_Theme_Prelude.wav");
	LoopSound(backgroundmusic);
}

void cmainmenu::render(int delta)
{
	mainmenu.render(delta);
}

void cmainmenu::update(int delta)
{
	
}

void cmainmenu::renderText(int delta)
{
	arialsmaller.onlost();
	arialbigger.onlost();
	switch (currentSelection)
	{
	case 0:
		arialbigger.render(menuitem[0], 200, 290);
		arialsmaller.render(menuitem[1], 228, 330);
		arialsmaller.render(menuitem[2], 245, 360);
		break;
	case 1:
		arialsmaller.render(menuitem[0], 220, 300);
		arialbigger.render(menuitem[1], 210, 325);
		arialsmaller.render(menuitem[2], 245, 360);
		break;
	case 2:
		arialsmaller.render(menuitem[0], 220, 300);
		arialsmaller.render(menuitem[1], 228, 330);
		arialbigger.render(menuitem[2], 242, 355);
		break;
	}
}

void cmainmenu::onKeyDown(int keycode)
{
	switch (keycode)
	{
	case DIK_W:
		PlaySound(select);
		currentSelection--;
		if (currentSelection < 0)
			currentSelection = 2;
		break;
	case DIK_S:
		PlaySound(select);
		currentSelection++;
		if (currentSelection > 2)
			currentSelection = 0;
		break;
	case DIK_ESCAPE:
		break;
	case DIK_RETURN:
		StopSound(backgroundmusic);
		isSelected = true;
		break;
	}
}