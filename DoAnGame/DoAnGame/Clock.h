#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "GameObject.h"

class Clock :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	Clock(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Clock();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void RenderCamera();
	virtual void Destroy();


	virtual void CollisionObject(float _DeltaTime);
};

#endif 



