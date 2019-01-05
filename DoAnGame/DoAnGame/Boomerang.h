#ifndef _BOOMERANG_H_
#define _BOOMERANG_H_

#include "GameObject.h"

class Boomerang :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	Boomerang(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Boomerang();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void RenderCamera();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif 



