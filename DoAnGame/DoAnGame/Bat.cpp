#include "Bat.h"
#include "Sprite.h"
#include "World.h"
Bat::Bat() {}

Bat::Bat(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = ENEMY_TYPE;



	isActive = false;
	sizeWidth = 32;
	sizeHeight = 32;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\enemy\\0.png");
	spriteLeft = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 4, 4);
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\enemy\\0-right.png");
	spriteRight = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 4, 4);
	sprite = spriteLeft;
}

Bat :: ~Bat()
{

}

void Bat::Init(int _X, int _Y, bool _isRight)
{
	collider = new Collider();
	collider->setCollider(15, -15, -15, 15);
	isActive = true;
	postY = _Y;
	postX = _X;
	isRight = _isRight;
	if (_isRight)
	{
		sprite = spriteLeft;
		velocityX = -100;
	}
	else
	{
		sprite = spriteRight;
		velocityX = 100;
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


void Bat::Update(const float &_DeltaTime)
{
	if (isRight == false && postX > manager->Simon->postX - 100)
	{
		isActive = false;
		collider = NULL;
	}
	if (isRight == false && postX < manager->Simon->postX - 100)
	{
		isActive = true;
		isRight = true;
		collider = new Collider();
		collider->setCollider(15, -15, -15, 15);
	}

	if (!isActive)
		return;

	if (manager->isPause)
		return;

		//cập nhật tọa độ X,Y
		postX += velocityX * _DeltaTime;
		//postY += velocityY * _DeltaTime;


		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME)
		{
			sprite->Next(1, 3);
			timerSprite = 0;
		}
	

	if (!IsInCamera() && velocityX < 0 && manager->Simon->postX > this->postX)
	{
		this->isActive = false;
		collider = NULL;
	}
	else if (!IsInCamera() && velocityX > 0 && manager->Simon->postX < this->postX)
	{
		this->isActive = false;
		collider = NULL;
	}


}



void Bat::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Bat::Destroy()
{

	manager->Simon->score += 100;
	this->isActive = false;
	manager->effect->Init(postX, postY);
	collider = NULL;
}

void Bat::CollisionObject(float _DeltaTime)
{

}

void Bat::CheckActive()
{

}