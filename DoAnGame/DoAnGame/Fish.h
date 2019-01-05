#ifndef _Fish_H_
#define _Fish_H_

#include "GameObject.h"

class Fish :
	public GameObject

{
public:
	Sprite *spriteLeft;
	Sprite *spriteRight;
	bool Move;
	float timerFire;
	bool firstTime;

	Fish();
	Fish(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Fish();
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);

	virtual void Init(int _X, int _Y, bool isRight);
	virtual void CheckActive();
};
#endif // !_Fish_H_

