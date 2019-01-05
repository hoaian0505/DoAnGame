#include "DeadWater.h"
#include "Misc.h"
#include "World.h"
#include "Game.h"

DeadWater::DeadWater(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = DEADWATER;


	// sẵn sàng render
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\ground\\2-2.png");
	sprite = new Sprite(_SpriteHandler, texture->texture, 32, 32, 1, 1);

	isActive = false;

	// set giá trị collider
	collider = new Collider();
	collider->setCollider(15, -16, -544, 16);

}

DeadWater::~DeadWater() {};

void DeadWater::Init(int _X, int _Y)
{


	isActive = true;
	postX = _X;
	postY = _Y;

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

void DeadWater::Render()
{

}

// gọi đến hàm này khi whip đánh trúng
void DeadWater::Collision()
{

}

void DeadWater::Destroy()
{
	// làm cho đối tượng này biến mất
	this->isActive = false;

}