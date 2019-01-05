#ifndef _WHIPUPGRADE_H_
#define _WHIPUPGRADE_H_

#include "GameObject.h"

class WhipUpgrade :
	public GameObject
{
public:
	Sprite *sprite;
	float timeSurvive;

	WhipUpgrade(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~WhipUpgrade();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_POTS_H_



