#ifndef _XCROSS_H
#define _XCROSS_H
#include "sprite.h"

class cweapon:public CSprite
{
private:
	int _Type;
	int _Status; 
	int _Waitingtime;
public:
	cweapon();
	~cweapon();
	void load(char* filepath, int columns, int rows);
	int getType();
	void setType(int type);
	void setStatus(int stt);
	int getStatus();
	void update(int delta);
};

#endif	_XCROSS_H