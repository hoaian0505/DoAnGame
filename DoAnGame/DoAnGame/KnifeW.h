#ifndef _KnifeW_H_
#define _KnifeW_H_

#include "GameObject.h"

class KnifeW :
	public GameObject
{
public:
	Sprite *spriteLeft;
	Sprite *spriteRight;
	float timeDamage;

	KnifeW(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~KnifeW();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_KnifeW_H_



