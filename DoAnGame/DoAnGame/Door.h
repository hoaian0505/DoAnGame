#ifndef _Door_H_
#define _Door_H_

#include "GameObject.h"

class Door :
	public GameObject
{
	// will mo to this coordinate
	int triggerX;
	int triggerY;

	//	change camera to this, no need to change camX because it follows the player
	int camXLeft;
	int camXRight;
	int camY;

	//bool CloseDoor;
public:
	virtual void Render();
	bool OpenDoor;

	//virtual void Init(int _top, int _bottom, int _left, int _right,int _triggerX, int _triggerY, int _camXLeft, int _camXRight, int _camY);

	virtual void Init(int _X, int _Y);
	virtual void Collision(Player *actor, const float &_DeltaTime);
	virtual void Update(const float &_DeltaTime);
	//virtual void Update2(const float &_DeltaTime);

	Door(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Door();
};

#endif
