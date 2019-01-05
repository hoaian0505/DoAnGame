#ifndef _POTS_H_
#define _POTS_H_

#include "GameObject.h"

class Pots :
	public GameObject
{
public:
	Sprite *sprite;


	Pots(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Pots();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_POTS_H_



