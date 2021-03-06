#ifndef _CHICKEN_H_
#define _CHICKEN_H_

#include "GameObject.h"

class Chicken :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	Chicken(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Chicken();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif 



