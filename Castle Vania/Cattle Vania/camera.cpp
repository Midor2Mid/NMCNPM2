#include	"camera.h"

camera::camera(void)
{
	pos.x = 1;
	pos.y = SCREENHEIGHT;
	D3DXMatrixIdentity(&MatrixTransform);
	MatrixTransform._22 = -1;
	_MaxMovingX = 0;
}
camera::~camera(void)
{

}

float camera::getMaxMovingX()
{
	return _MaxMovingX;
}

void camera::UpdateMapEditor(float x, float y)
{
	pos.x -= x;
	pos.y += y;
}

void camera::setMaxMovingX(float maxX)
{
	_MaxMovingX = maxX;
}

void camera::setMaxMovingY(float maxY)
{
	_MaxMovingY = maxY;
}

void camera::setMinMovingX(float minX)
{
	_MinMovingX = minX;
}

void camera::setMinMovingY(float minY)
{
	_MinMovingY = minY;
}

void camera::UpdateWorldMap(float x, float y)
{
	pos.x -= x;
	pos.y += y;
	if (pos.x < 1)
		pos.x = 1;
	if (pos.y < SCREENHEIGHT)
		pos.y = SCREENHEIGHT;
}

void camera::Update(float x)
{
	if (x > pos.x + SCREENWIDTH || x < pos.x)
	{
		pos.x = x - SCREENWIDTH / 2;
	}

	if (x  < _MaxMovingX - SCREENWIDTH / 2)
		pos.x = x - SCREENWIDTH / 2;
	if (pos.x < _MinMovingX)
		pos.x = _MinMovingX;
	if (pos.x + SCREENWIDTH > _MaxMovingX)
		pos.x = _MaxMovingX - SCREENWIDTH;


}
D3DXVECTOR2 camera::GetPointTransform(float x, float y)
{
	MatrixTransform._41 = -pos.x;
	MatrixTransform._42 = pos.y;

	D3DXVECTOR3 pos(x, y, 0);
	D3DXVECTOR4 result;
	D3DXVec3Transform(&result, &pos, &MatrixTransform);
	return D3DXVECTOR2(result.x, result.y);
}