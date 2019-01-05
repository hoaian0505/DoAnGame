#ifndef _WHIP_H_
#define _WHIP_H_

#include "GameObject.h"

class Whip:
	public GameObject
{
public:
	Sprite *spriteLeft;
	Sprite *spriteRight;
	int whipLevel;

	Whip(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Whip();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render(int _X=0,int _Y=0);
	virtual void Destroy();
	virtual void Disappear();
	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_WHIP_H_



