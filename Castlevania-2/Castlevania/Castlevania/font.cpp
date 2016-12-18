#include "font.h"
#include "game.h"
using namespace std;
CFont::CFont()
{
	_Font = NULL;
}
CFont::~CFont()
{
	if (_Font != NULL)
	{
		_Font->Release(); //release font
		_Font = NULL;
	}
}

void CFont::initialize()
{
	initialize(22);
}

void CFont::initialize(int size)
{
	_FontPosition.top = 0;
	_FontPosition.left = 0;
	_FontPosition.right = SCREENWIDTH;
	_FontPosition.bottom = SCREENHEIGHT;
	D3DXFONT_DESC FontDesc = { size,
		0,
		400,
		0,
		false,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_PITCH, "Arial" };

	//create font
	D3DXCreateFontIndirect(d3ddev, &FontDesc, &_Font);
}

void CFont::render(char* text, float x, float y)
{
	render(text, x, y, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CFont::onlost()
{
	_Font->OnLostDevice();
	_Font->OnResetDevice();
}

void CFont::render(char* text, float x, float y, D3DCOLOR color)
{
	_FontPosition.left = x;
	_FontPosition.top = y;
	_Font->DrawText(NULL,
		text,
		-1,
		&_FontPosition,
		NULL,
		color); //draw text
}