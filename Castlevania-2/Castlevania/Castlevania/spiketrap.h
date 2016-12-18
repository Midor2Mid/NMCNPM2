#ifndef _SPIKE_TRAP
#define _SPIKE_TRAP
#include "sprite.h"

class cspiketrap:public CSprite
{
private:
	vector<int> _Status;
	int _Speed;
	void _draw(int tile, float x, float y, float height);
public:
	void load(char* filepath);
	int	 isActive(int id);
	void setStatus(int id, int status);
	void addNewObject(int id, float x, float y, float width, float height, int flip);
	void update(int delta, int id);
	int render(int delta, int id);
};

#endif // !_SPIKE_TRAP
