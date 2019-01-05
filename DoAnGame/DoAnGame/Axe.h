#ifndef _AXE_H_
#define _AXE_H_

#include "GameObject.h"

class Axe :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	Axe(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Axe();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void RenderCamera();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif 



