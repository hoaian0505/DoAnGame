#ifndef _BRICK_H_
#define _BRICK_H_

#include "ThamSo.h"
#include "GameObject.h"

class Brick : public GameObject
{
public:
	LPD3DXSPRITE spriteHandler;

	Brick(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Brick();

	virtual void Init(int _X, int _Y, int _Temp=0);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};

#endif
