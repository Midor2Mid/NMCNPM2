#ifndef FONT_H
#define FONT_H

#include <d3dx9.h>
#include "global.h"
#include <iostream>
#include "dxgraphics.h"
using namespace std;
class CFont
{
private:
	LPD3DXFONT	_Font;
	RECT		_FontPosition;
public:
	CFont();
	~CFont();
	void initialize();
	void initialize(int size);
	void render(char* text, float x, float y);
	void render(char* text, float x, float y, D3DCOLOR color);
	void onlost();
};
#endif