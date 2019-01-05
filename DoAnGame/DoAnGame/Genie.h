#ifndef _Genie_H_
#define _Genie_H_

#include "GameObject.h"

class Genie :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	Genie(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Genie();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif 



