// ------ update K_1.5

#include "Gate.h"
#include "Player.h"
#include "Sprite.h"
#include "World.h"

Gate::Gate(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ZONE_GATE;
	collider = new Collider();
	isActive = true;
	sizeWidth = 64;
	sizeHeight = 64;
}


Gate::~Gate()
{
}

void Gate::Render()
{

}


void Gate::Init(int _X, int _Y)	
{

	isActive = true;

	postX = _X;
	postY = _Y;
	camXLeft = Sprite::cameraXLeft;
	camXRight = 2628;
	camY = Sprite::cameraY;
	collider->setCollider(-4, -5, 0, 5);

	for (int i = 1; i < 30; i++)
	{
		if (IsCollide(manager->vaCham[i]))
		{
			for (int j = 0; j < manager->vaCham[i]->objects.size(); j++)
			{
				if (manager->vaCham[i]->objects[j] == this)
					return;
			}
			manager->vaCham[i]->objects.push_back(this);
		}
	}
}

// player đụng vào => phép màu xảy ra
void Gate::Collision(Player *actor, const float &_DeltaTime)
{
	actor->postX = 90;
	actor->checkpointX = actor->postX;
	actor->postY = 70;
	actor->checkpointY = actor->postY;

	actor->PostXMax = 450;

	Sprite::cameraXLeft = camXLeft;
	Sprite::cameraXRight = camXRight;
	Sprite::cameraY = camY;

	actor->UpdateCamera(32, camY, camXLeft, camXRight);
	actor->savedCamXLeft = camXLeft;
	actor->savedCamXRight = camXRight;
	collider = NULL;
}