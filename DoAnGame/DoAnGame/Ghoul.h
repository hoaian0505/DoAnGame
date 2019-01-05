#ifndef _GHOUL_H_
#define _GHOUL_H_

#include "GameObject.h"

class Ghoul :
	public GameObject

{
public:
	Sprite *spriteLeft;
	Sprite *spriteRight;
	float minX;	//vị trí X tối thiểu
	float maxX;	//vị trí X tối đa
	bool isRight;

	Ghoul();
	Ghoul(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Ghoul();
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);


	virtual void Init(int _X, int _Y, bool isRight);
	virtual void CheckActive();
};
#endif // !_GHOUL_H_

