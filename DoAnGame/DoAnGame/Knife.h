#ifndef _KNIFE_H_
#define _KNIFE_H_

#include "GameObject.h"

class Knife :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	Knife(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Knife();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void RenderCamera();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif 



