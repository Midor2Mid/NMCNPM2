#ifndef DRAGON_CANNON_H
#define DRAGON_CANNON_H

#include "fireball.h"

class CDragonCannon:public CSprite
{
private:
	vector<int> _WaitingFiring; // thoi gian gioi han giua moi lan ban
	vector<int> _WaitingFire;	//thoi gian cho mot dot ban
	int _LimitFireBall;
	cfireball _fire;
	Box _simonbox;
	vector<vector<cfireball>>	fire;
public:
	vector<Box> getListFire(int id);
	vector<int> _Status;
	vector<int> health;
	vector<int> invulnerabletime;
	vector<int> invulnerable;
	void	getSimonbox(Box simonbox);
	void	addNewObject(int id, float x, float y, float width, float height, int flip);
	void	setStatus(int stt, int id);
	int		isActive(int id);
	void	ClearAll();
	void	load(char* filepath);
	void	update(int delta, int id);
	int		render(int delta, int id);
};

#endif