#ifndef _AxeW_H_
#define _AxeW_H_

#include "GameObject.h"

class AxeW :
	public GameObject
{
public:
	Sprite *spriteLeft;
	Sprite *spriteRight;
	float timeDamage;

	AxeW(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~AxeW();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_AxeW_H_



