#ifndef _Power_H_
#define _Power_H_

#include "GameObject.h"

class Power :
	public GameObject

{
public:
	Power();
	Power(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Power();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);


};
#endif // !_Power_H_

