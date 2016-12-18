#include "candle.h"

void CCandle::load(char* filename)
{
	CSprite::load(filename, 2, 1);
	animate(true);
	animate(30, 0, 1);
}