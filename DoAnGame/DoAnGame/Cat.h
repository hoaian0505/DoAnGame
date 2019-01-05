#ifndef _Cat_H_
#define _Cat_H_

#include "GameObject.h"

class Cat :
	public GameObject

{
public:
	bool isSleeping;
	bool hasJumped;
	bool isRight;
	float timeRun;
	bool ColliGround;

	Sprite *spriteLeft;
	Sprite *spriteRight;

	Cat();
	Cat(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Cat();
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);

	virtual void Init(int _X, int _Y, bool _isRight, float _timeRun);
	virtual void CheckActive();
};
#endif // !_Cat_H_

