#ifndef _HolyWater_H_
#define _HolyWater_H_

#include "GameObject.h"

class HolyWater :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	HolyWater(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~HolyWater();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void RenderCamera();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif 



