#include "FireBall.h"
#include "Sprite.h"
#include "World.h"
FireBall::FireBall() {}

FireBall::FireBall(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = ENEMY_TYPE;



	isActive = false;
	sizeWidth = 14;
	sizeHeight = 12;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\enemy\\fireball.png");
	spriteLeft = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 1, 1);
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\enemy\\fireball-right.png");
	spriteRight = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 1, 1);
	sprite = spriteLeft;
}

FireBall :: ~FireBall()
{

}

void FireBall::Init(int _X, int _Y, bool isRight)
{
	collider = new Collider();
	collider->setCollider(5, -5, -6, 6);
	isActive = true;
	postY = _Y;
	postX = _X;
	if (isRight)
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

void FireBall::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;

	if (manager->isPause)
		return;

		//cập nhật tọa độ X,Y
		postX += velocityX * _DeltaTime;
		//postY += velocityY * _DeltaTime;

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
	//else
	//	this->isActive = true;

}



void FireBall::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void FireBall::Destroy()
{
	this->isActive = false;
	collider = NULL;
}

void FireBall::CollisionObject(float _DeltaTime)
{

}

void FireBall::CheckActive()
{

}