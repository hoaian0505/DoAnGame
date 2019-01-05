#ifndef _CROSS_H_
#define _CROSS_H_

#include "GameObject.h"

class Cross :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	Cross(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Cross();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif 



