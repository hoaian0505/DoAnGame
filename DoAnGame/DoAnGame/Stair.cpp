#include "Stair.h"
#include "Misc.h"
#include "World.h"
#include "Game.h"

Stair::Stair(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;


	// sẵn sàng render
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\ground\\2-2.png");
	sprite = new Sprite(_SpriteHandler, texture->texture, 32, 32, 1, 1);

	isActive = false;

	// set giá trị collider
	collider = new Collider();
	collider->setCollider(5,4, -10, 1);


}

Stair::~Stair() {};

void Stair::Init(int _X, int _Y, int _Type)
{
	objectType = _Type;

	isActive = true;
	postX = _X;
	postY = _Y;

	if (_Type == STAIR_DOWNRIGHT || _Type == STAIR_UPLEFT)
		collider->setCollider(5, 4, -1, 10);

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

void Stair::Render()
{

}

// gọi đến hàm này khi whip đánh trúng
void Stair::Collision()
{

}

void Stair::Destroy()
{
	// làm cho đối tượng này biến mất
	this->isActive = false;

}