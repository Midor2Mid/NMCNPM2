#ifndef _BOSS_MEDUSA_H
#define _BOSS_MEDUSA_H

#include "sprite.h"

class CBossmedusa :public CSprite
{
private:
	void moveLikeJagger(int delta, int id);
	int _Status;
	int _Waitingtime;
	int _ActionType;
	float _DestinationXPosition;
	float _BalanceY;
	float _MovingAngle;
	bool invertmove;
	int maximumWaitingTime;
	float _DestinationX, _DestinationY;
	float _CurrentDestinationX, _CurrentDestinationY;
	float a;
	float _ReturnPositionX, _ReturnPositionY;
	float _WaitingTime;
	float _CurrentWaitingTime;
	float _MovingSpeed;

	float virtualx;
	int invulnerablecounttime, invulnerablecount, invulnerableCountInvert;
	int _StopUpdate;
public:
	void setStopUpdate(int stop);
	int		invulnerable;
	int		health;
	int		getHealth();
	void	load(char* filepath);
	void	setStatus(int stt, int id);
	int		isActive(int id);
	void	update(int delta, Box bx, int id);
	int		render(int delta, int id); 
	int		getStatus();
};

#endif