#include "BrickGround.h"
#include "Misc.h"
#include "World.h"
#include "Game.h"

BrickGround::BrickGround(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;



	// sẵn sàng render
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\ground\\2.png");
	sprite1 = new Sprite(_SpriteHandler, texture->texture, 32, 32, 1, 1);
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\ground\\2-2.png");
	sprite2 = new Sprite(_SpriteHandler, texture->texture, 32, 32, 1, 1);
	sprite = sprite1;

	isActive = false;

	// set giá trị collider
	collider = new Collider();
	collider->setCollider(15, -16, -16, 16);

}

BrickGround::~BrickGround() {};

void BrickGround::Init(int _X, int _Y, int _Temp)
{

	if (manager->Temp == 0)
		sprite = sprite1;
	else if (manager->Temp == 1)
		sprite = sprite2;

	isActive = true;
	postX = _X;
	postY = _Y;
	
	if (_Temp > 1)
	{
		collider->setCollider(15, -16, -16, 16 * _Temp);
	}
}

void BrickGround::Update(float _DeltaTime)
{

}

void BrickGround::Render()
{
	if (IsInCamera())
		sprite->Render(postX, postY);
}

// gọi đến hàm này khi whip đánh trúng
void BrickGround::Collision()
{

}

void BrickGround::Destroy()
{
	// làm cho đối tượng này biến mất
	this->isActive = false;

}