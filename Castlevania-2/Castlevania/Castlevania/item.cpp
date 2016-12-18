#include "item.h"

citem::citem()
{
	CSprite::CSprite();
	type = 0;
}

citem::~citem()
{

}

void citem::load(char* filepath, int columns, int rows, int _type)
{
	CSprite::load(filepath, columns, rows);
	invisibletime = 0;
	status = 0;
	type = _type; 
	if (type == 13)
	{
		animate(15, 0, 1);
		animate(true);
	}
}

void citem::update(int delta)
{
	switch (status)
	{
	case 0:
		invisibletime += delta;
		if (invisibletime > 350)
		{
			status = 1; 
			invisibletime = 0;
		}
		break;
	case 1:
		_Box.at(0).vy -= 0.5;
		break;
	case 2:
		_Box.at(0).vy = 0;
		invisibletime += delta;
		if (type != 13)
		{
			if (invisibletime > 4000)
			{
				status = 3;
			}
		}
		break;
	case 3:

		break;
	}
	_Box.at(0).y += _Box.at(0).vy;
}
void citem::render(int delta)
{
	animate(delta);
	if (status)
		CSprite::render(delta);
}