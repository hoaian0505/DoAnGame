#ifndef _BrickGround_H_
#define _BrickGround_H_

#include "ThamSo.h"
#include "GameObject.h"

class BrickGround : public GameObject
{
public:
	LPD3DXSPRITE spriteHandler;
	Sprite* sprite1;
	Sprite* sprite2;

	BrickGround(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~BrickGround();

	virtual void Init(int _X, int _Y, int _Temp = 0);
	virtual void Update(float _DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};

#endif
