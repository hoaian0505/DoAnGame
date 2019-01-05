#include "Power.h"
#include "Sprite.h"
#include "World.h"
Power::Power() {}

Power::Power(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = POWER;



	isActive = false;
	sizeWidth = 28;
	sizeHeight = 32;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\Items\\13.png");
	sprite = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 2, 2);
	
}

Power :: ~Power()
{

}


void Power::Init(int _X, int _Y)
{
	collider = new Collider();
	collider->setCollider(13, -13, -15, 15);
	isActive = true;
	postY = _Y;
	postX = _X;
	velocityY = -150;

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

void Power::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;

		//cập nhật tọa độ X,Y
		CollisionObject(_DeltaTime);
		postY += velocityY * _DeltaTime;


		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME)
		{
			sprite->Next(0, 1);
			timerSprite = 0;
		}

}



void Power::Render()
{
	if (isActive)
		if (IsInCamera())
			sprite->Render(postX, postY);
}

void Power::Destroy()
{
	manager->Simon->score += 1000;
	this->isActive = false;
	collider = NULL;
	manager->Win = true;
}

void Power::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;

	//-----------------------GROUND-----------------------------

	tempObject = manager->brickGround;
	collisionScale = SweptAABB(tempObject, _DeltaTime);
	if (collisionScale < 1.0f)
	{
		SlideFromGround(tempObject, _DeltaTime, collisionScale);
	}
}
