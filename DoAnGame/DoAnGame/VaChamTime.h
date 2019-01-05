#ifndef _VaChamTime_H_
#define _VaChamTime_H_

#include "ThamSo.h"
#include "GameObject.h"
#include <iostream>
#include <vector>

class VaChamTime : public GameObject
{
public:
	LPD3DXSPRITE spriteHandler;
	std::vector<GameObject*> objects;
	bool kickHoat;

	VaChamTime(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~VaChamTime();

	virtual void Update(const float &_DeltaTime);
	virtual void Init(int _X, int _Y);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};

#endif
