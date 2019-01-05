#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "GameObject.h"

class Effect :
	public GameObject
{
public:
	Sprite *sprite1;
	Sprite *sprite2;


	Effect(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Effect();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_EFFECT_H_



