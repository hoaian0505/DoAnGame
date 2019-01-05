﻿#include "BigHeart.h"
#include "World.h"



BigHeart::BigHeart(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = BIGHEART;
	spriteHandler = _SpriteHandler;
	sizeWidth = 24;
	sizeHeight = 20;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\Items\\1.png");
	sprite = new Sprite(_SpriteHandler,texture->texture, sizeWidth, sizeHeight, 1, 1);
	isActive = false;
	sprite->_Index = 0;


}

BigHeart::~BigHeart()
{
	if (sprite != NULL)
	{
		delete sprite;
	}
}

void BigHeart::Init(int _X, int _Y)
{

	isActive = true;
	postX = _X;
	postY = _Y;
	timeSurvive = 0;
	collider = new Collider();
	// chỉnh collider
	collider->setCollider(14, -14, -14, 14);

	for (int i = 1; i < 30; i++)
	{
		if (manager->vaCham[i]->kickHoat)
			for (int j = 0; j < manager->vaCham[i]->objects.size(); j++)
			{
				if (manager->vaCham[i]->objects[j] == this)
				{
					manager->vaCham[i]->objects.erase(manager->vaCham[i]->objects.begin() + j);
				}
			}
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
			return;
		}
	}
}

void BigHeart::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;

	postY += velocityY * _DeltaTime;

	timeSurvive += _DeltaTime;
	if (timeSurvive >= ITEM_TIME)
		Destroy();
	velocityY = -2000 * _DeltaTime;
	CollisionObject(_DeltaTime);
}



void BigHeart::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void BigHeart::Destroy()
{
	isActive = false;
	collider = NULL;
}


//------Collision


void BigHeart::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;

	//-----------------------GROUND-----------------------------
	for (int i = 1; i < 30; i++)
	{
		if (manager->vaCham[i]->kickHoat)
			for (int j = 0; j < manager->vaCham[i]->objects.size(); j++)
			{
				tempObject = manager->vaCham[i]->objects[j];
				if (tempObject->objectType == BRICK_TYPE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						SlideFromGround(tempObject, _DeltaTime, collisionScale);
					}
				}
			}
	}


	tempObject = manager->brickGround;
	collisionScale = SweptAABB(tempObject, _DeltaTime);
	if (collisionScale < 1.0f)
	{
		SlideFromGround(tempObject, _DeltaTime, collisionScale);
	}
}