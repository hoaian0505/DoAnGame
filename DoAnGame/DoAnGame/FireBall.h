#ifndef _FireBall_H_
#define _FireBall_H_

#include "GameObject.h"

class FireBall :
	public GameObject

{
public:
	Sprite *spriteLeft;
	Sprite *spriteRight;

	FireBall();
	FireBall(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~FireBall();
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);

	virtual void Init(int _X, int _Y, bool isRight);
	virtual void CheckActive();
};
#endif // !_FireBall_H_

