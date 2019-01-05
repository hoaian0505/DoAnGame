#include "Brick.h"
#include "Misc.h"
#include "World.h"
#include "Game.h"

Brick::Brick(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = BRICK_TYPE;


	// sẵn sàng render
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\ground\\2-2.png");
	sprite = new Sprite(_SpriteHandler, texture->texture,32, 32, 1, 1);

	isActive = false;

	// set giá trị collider
	collider = new Collider();
	collider->setCollider(15, -16, -16, 16);

}

Brick::~Brick() {};

void Brick::Init(int _X, int _Y,int _Temp)
{


	isActive = true;
	postX = _X;
	postY = _Y;

	if (_Temp == 1)
	{
		collider->setCollider(80, -80, -64, 64);
	}
	if (_Temp > 1)
	{
		collider->setCollider(15, -16, -16, 16 * _Temp);
	}

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

void Brick::Render()
{

}

// gọi đến hàm này khi whip đánh trúng
void Brick::Collision()
{

}

void Brick::Destroy()
{
	// làm cho đối tượng này biến mất
	this->isActive = false;

}