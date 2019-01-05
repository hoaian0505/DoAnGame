#include "Whip.h"
#include "World.h"
#include "Game.h"

Whip::Whip(LPD3DXSPRITE _SpriteHandler, World *_manager) 
{
	manager = _manager;
	
	sizeWidth = 200;
	sizeHeight = 70;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\morningstar.png");
	spriteLeft = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 9, 3);

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\morningstar_right.png");
	spriteRight = new Sprite(_SpriteHandler, texture->texture, sizeWidth, 71, 9, 3);
	
	sprite = spriteRight;
	whipLevel = 0;
	isActive = false;
	collider = new Collider();
}

Whip::~Whip()
{
	if (spriteLeft != NULL)
	{
		delete spriteLeft;
	}
	if (spriteRight != NULL)
	{
		delete spriteRight;
	}
}

void Whip::Init(int _X, int _Y)
{
	isActive = true;

	postX = _X;

	if (manager->Simon->isCrouch)
		postY = _Y - 14;
	else
		postY = _Y;

	if (manager->Simon->isRight)
	{
		sprite = spriteRight;
		collider->setCollider(0, 0, 0, 0);
		if (whipLevel < 2)
			collider->setCollider(16, -5, 27, 65);
		else
			collider->setCollider(18, -20, 27, 110);
	}
	else
	{
		sprite = spriteLeft;
		if (whipLevel < 2)
			collider->setCollider(16, -5, -65, -27);
		else
			collider->setCollider(18, -20, -110, -27);
	}
	firstShow = true;
	if (whipLevel == 0)
		sprite->_Index = 0;
	if (whipLevel == 1)
		sprite->_Index = 3;
	if (whipLevel == 2)
		sprite->_Index = 6;


}

void Whip::Update(const float &_DeltaTime)
{
	timerSprite += _DeltaTime;
	if (!manager->Simon->isAttack)
		isActive = false;
	if (!isActive)
		return;

	postX = manager->Simon->postX;

	if (manager->Simon->isCrouch)
		postY = manager->Simon->postY - 14;
	else
		postY = manager->Simon->postY;

	if (manager->Simon->isChangeFrame)
	{
		if (whipLevel == 0)
			sprite->Next(1, 3);
		if (whipLevel == 1)
			sprite->Next(4, 6);
		if (whipLevel == 2)
			sprite->Next(7, 9);
	}

	//------------
	if (whipLevel == 0)
		if (manager->Simon->isAttack &&	sprite->_Index==2)
		{
			CollisionObject(_DeltaTime);
		}
	if (whipLevel == 1)
		if (manager->Simon->isAttack &&	sprite->_Index == 5)
		{
			CollisionObject(_DeltaTime);
		}
	if (whipLevel == 2)
		if (manager->Simon->isAttack &&	sprite->_Index == 8)
		{
			CollisionObject(_DeltaTime);;
		}
}

void Whip::Disappear()
{
	if (whipLevel == 0)
	{
		if (sprite->_Index == 3)
			sprite->_Index = 9;
	}
	else if (whipLevel == 1)
	{
		if (sprite->_Index == 6)
			sprite->_Index = 9;
	}
	else if (whipLevel == 2)
	{
		if (sprite->_Index == 9)
			sprite->_Index = 9;
	}
}
void Whip::Render(int _X,int _Y)
{
	if (isActive)
	{
		if (_X != 0 && _Y != 0)
			sprite->Render(_X, _Y);
		else
			sprite->Render(postX, postY);
	}
}

void Whip::Destroy()
{
	isActive = false;
}




void Whip::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;


	//-----------------------DESTRUCTIBLES----------------------------------
	for (int i = 1; i < 30; i++)
	{
		if (manager->vaCham[i]->kickHoat)
			for (int j = 0; j < manager->vaCham[i]->objects.size(); j++)
			{
				tempObject = manager->vaCham[i]->objects[j];
				if (tempObject->objectType == DESTRUCTIBLE_TYPE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
					}
				}

				if (tempObject->objectType == ENEMY_TYPE || tempObject->objectType == BOSS_TYPE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
					}
				}
			}
	}

}
