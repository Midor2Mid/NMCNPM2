#ifndef MOUSE_H
#define MOUSE_H

#include "Sprite.h"
class Mouse:public CSprite {
private:
	bool _PreviousState;
	bool _CurrentState;
public:

	Mouse();
	~Mouse();

	void		load();
	camera		getCurrentCamera();
	float getX();
	float getY();
	void setCurrentState(bool);
	void setPreviousState(bool);
	bool getCurrentState();
	bool getPreviousState();
};

#endif // !MOUSE_H
