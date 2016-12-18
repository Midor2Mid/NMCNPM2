#ifndef _BOSS_BAT_H
#define _BOSS_BAT_H
#include <time.h>
#include "sprite.h"
class CBossbat :public CSprite{
private:
	float _Vx, _Vy;
	float _Dx, _Dy;
	float _DestinationX, _DestinationY;
	float _CurrentDestinationX, _CurrentDestinationY;
	float a;
	float _ReturnPositionX, _ReturnPositionY;
	float _WaitingTime;
	float _CurrentWaitingTime;
	float _MovingSpeed;
	float virtualx;
	int _Status;
	int invulnerablecounttime, invulnerablecount, invulnerableCountInvert;
	int _StopUpdate;
public:
	void setStopUpdate(int stop);
	int invulnerable;
	int health;
	int isActive(int);
	int getStatus();
	void setStatus(int stt, int id);
	int  bossstate;
	void moveX(int);
	void moveY(int);
	void move(int, int, int);
	void load(char * );
	void update(int, Box, int);
	void getObject(Box);
	int getHealth();
	int render(int delta, int id);
};

#endif // !_BOSS_BAT_H
