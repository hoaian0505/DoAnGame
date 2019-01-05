#ifndef _WaterEffect_H_
#define _WaterEffect_H_

#include "GameObject.h"

class WaterEffect :
	public GameObject
{
public:

	WaterEffect(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~WaterEffect();
	bool firstShow;
	virtual void Init(int _X, int _Y,bool isRight);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_WaterEffect_H_



