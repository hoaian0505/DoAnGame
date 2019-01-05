#ifndef _Bat_H_
#define _Bat_H_

#include "GameObject.h"

class Bat :
	public GameObject

{
public:
	Sprite *spriteLeft;
	Sprite *spriteRight;
	bool isRight;

	Bat();
	Bat(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Bat();
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);

	virtual void Init(int _X, int _Y, bool isRight);
	virtual void CheckActive();
};
#endif // !_Bat_H_

