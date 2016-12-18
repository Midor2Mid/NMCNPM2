#ifndef _MAINMENU_H
#define _MAINMENU_H

#include "sprite.h"
#include "font.h"

class cmainmenu
{
private:
	CSprite mainmenu;
	CFont arialsmaller;
	CFont arialbigger;
	char *menuitem[3];
	CSound *select;
	CSound *backgroundmusic;
public:
	cmainmenu();
	~cmainmenu();
	bool isSelected;
	int currentSelection;
	void initialize();
	void update(int delta);
	void render(int delta);
	void renderText(int delta);
	void onKeyDown(int keycode);
};

#endif _MAINMENU_H