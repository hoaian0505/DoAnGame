#ifndef _HEART_H_
#define _HEART_H_

#include "GameObject.h"

class Heart :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	Heart(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Heart();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_POTS_H_



