#ifndef _DeadWater_H_
#define _DeadWater_H_

#include "ThamSo.h"
#include "GameObject.h"

class DeadWater : public GameObject
{
public:
	LPD3DXSPRITE spriteHandler;

	DeadWater(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~DeadWater();

	virtual void Init(int _X, int _Y);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};

#endif
