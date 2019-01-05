#ifndef _BIGHEART_H_
#define _BIGHEART_H_

#include "GameObject.h"

class BigHeart :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	BigHeart(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~BigHeart();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_POTS_H_



