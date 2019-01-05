#ifndef _BoomerangW_H_
#define _BoomerangW_H_

#include "GameObject.h"

class BoomerangW :
	public GameObject
{
public:
	Sprite *spriteLeft;
	Sprite *spriteRight;
	bool PlayOnRight;
	float timeDamage;

	BoomerangW(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~BoomerangW();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_BoomerangW_H_



