#include "introscreen.h"


void cintro::initialize()
{
	introscreen.load("resource/image/intro.png", 1, 1);
	introscreen.setPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);
	introscreen.setCamera(1);
	simon.load("resource/image/simon.png",8,3);
	simon.setPosition(SCREENWIDTH, 80);
	simon.animate(true);
	simon.animate(25, 0, 3);
	simon.setCamera(1);
	helicopter.load("resource/image/helicopter.png",1,1);
	helicopter.setPosition(SCREENWIDTH, SCREENHEIGHT -150);
	helicopter.setCamera(1);
	bat.load("resource/image/bat.png",2,1);
	bat.setPosition(50, 300);
	bat.animate(true);
	bat.animate(15,0, 1);
	bat.setCamera(1);
	isend = false;
	_WaitingCount = 0;
	intro = LoadSound("resource/music/Game_Start_Prologue.wav");
	PlaySound(intro);
}

void cintro::update(int delta)
{
	helicopter._Box.at(0).vx = -0.3;
	helicopter._Box.at(0).vy = 0.03;
	bat._Box.at(0).vx = 0.5;
	bat._Box.at(0).vy = 0.07;
	simon._Box.at(0).vx = -1;
	if (simon.getX() < SCREENWIDTH / 2)
	{
		simon._Box.at(0).vx = 0;
		simon.animate(false);
		simon.setCurrentFrame(9);
		_WaitingCount += delta;
		if (_WaitingCount>3000)
			isend = true;
	}

	simon._Box.at(0).x += simon._Box.at(0).vx;
	helicopter._Box.at(0).x += helicopter._Box.at(0).vx;
	helicopter._Box.at(0).y += helicopter._Box.at(0).vy;
	bat._Box.at(0).x += bat._Box.at(0).vx;
	bat._Box.at(0).y += bat._Box.at(0).vy;
}

void cintro::render(int delta)
{
	introscreen.render(delta);
	simon.animate(delta);
	simon.render(delta);
	helicopter.render(delta);
	bat.animate(delta);
	bat.render(delta);
}

void cintro::renderText(int delta)
{
}