#ifndef _CANDLES_H_
#define _CANDLES_H_

#include "GameObject.h"

class Candles :
	public GameObject
{
public:
	Sprite *sprite;
	int a = 0;

	Candles(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Candles();
	bool firstShow;
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_CANDLES_H_



