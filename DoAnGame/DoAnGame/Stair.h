#ifndef _Stair_H_
#define _Stair_H_

#include "ThamSo.h"
#include "GameObject.h"

class Stair : public GameObject
{
public:
	LPD3DXSPRITE spriteHandler;
	int stairType;
	Stair(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Stair();

	virtual void Init(int _X, int _Y, int _Type);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};

#endif
