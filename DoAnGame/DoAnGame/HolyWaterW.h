#ifndef _HolyWaterW_H_
#define _HolyWaterW_H_

#include "GameObject.h"

class HolyWaterW :
	public GameObject
{
public:
	Sprite *spriteLeft;
	Sprite *spriteRight;
	Sprite *spriteGround;
	float timeActive;
	bool ColliGround;
	float timeDamage;

	HolyWaterW(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~HolyWaterW();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_HolyWaterW_H_



