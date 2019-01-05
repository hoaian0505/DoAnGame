#include "VaChamTime.h"
#include "Misc.h"
#include "World.h"
#include "Game.h"

VaChamTime::VaChamTime(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;


	// sẵn sàng render
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\BrickColli.bmp");
	sprite = new Sprite(_SpriteHandler, texture->texture, 256, 448, 1, 1);

	isActive = false;

	// set giá trị collider
	collider = new Collider();
	collider->setCollider(224, -224, -128, 128);
	kickHoat = false;
}

VaChamTime::~VaChamTime() {};

void VaChamTime::Init(int _X, int _Y)
{
	isActive = true;
	postX = _X;
	postY = _Y;

}

void VaChamTime::Update(const float &_DeltaTime)
{
	if (IsInCamera())
		kickHoat = true;
	else
		kickHoat = false;
}

void VaChamTime::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}


void VaChamTime::Collision()
{

}

void VaChamTime::Destroy()
{
	// làm cho đối tượng này biến mất
	this->isActive = false;

}