#include "Fish.h"
#include "Sprite.h"
#include "World.h"
Fish::Fish() {}

Fish::Fish(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = ENEMY_TYPE;



	isActive = false;
	sizeWidth = 32;
	sizeHeight = 64;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\enemy\\3.png");
	spriteLeft = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 3, 3);
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\enemy\\3-right.png");
	spriteRight = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 3, 3);
	sprite = spriteLeft;
	firstTime = false;
}

Fish :: ~Fish()
{

}

void Fish::Init(int _X, int _Y, bool isRight)
{
	collider = new Collider();
	collider->setCollider(31, -32, -15, 15);
	isActive = true;
	postY = _Y;
	postX = _X;
	if (isRight)
	{
		sprite = spriteLeft;
		velocityX = -30;
	}
	else
	{
		sprite = spriteRight;
		velocityX = 30;
	}
	sprite->_Index = 2;
	velocityY = 570;
	for (int i = 1; i < 8; i++)
	{
		if (!manager->waterEffect[i]->isActive)
		{
			manager->waterEffect[i]->Init(_X - 5, _Y, true);
			manager->waterEffect[i + 1]->Init(_X + 5, _Y, false);

			break;
		}
	}
	Move = false;
	timerFire = 0;
	firstTime = true;

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


void Fish::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;

	if (manager->isPause)
		return;

		if (firstTime)
		{
			firstTime = false;
		}
		velocityY -= 700 * _DeltaTime;

		if (velocityY < 0)
			CollisionObject(_DeltaTime);

		//cập nhật tọa độ X,Y
		if (velocityY == 0)
		{
			Move = true;
		}

		if (velocityY < 0)
			Move = false;


		if (Move)
		{
			if (sprite->_Index!=0)
				postX += velocityX * _DeltaTime;
			timerSprite += _DeltaTime;
			if (timerSprite >= ANIM_TIME*4)
			{
				sprite->Next(1, 2);
				timerSprite = 0;
			}
			timerFire += _DeltaTime;
			if (timerFire > ANIM_TIME * 16.5)
			{
				sprite->_Index = 0;
				for (int i = 1; i < 9; i++)
				{
					if (!manager->fireBall[i]->isActive)
					{
						if (sprite == spriteLeft)
							manager->fireBall[i]->Init(postX, postY + 8, true);
						else
							manager->fireBall[i]->Init(postX, postY + 8, false);
						break;
					}
				}
				timerFire = 0;
				
			}
		}
		postY += velocityY * _DeltaTime;


		

}



void Fish::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Fish::Destroy()
{
	manager->Simon->score += 100;
	this->isActive = false;
	manager->effect->Init(postX, postY);
	collider = NULL;
}

void Fish::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;

	//-----------------------GROUND-----------------------------
	for (int i = 10; i < 16; i++)
	{
		tempObject = manager->brick[i];
		collisionScale = SweptAABB(tempObject, _DeltaTime);
		if (collisionScale < 1.0f)
		{

			if (normaly > 0.1f)//chạm từ trên xuống
			{
				this->postY = (tempObject->postY + tempObject->collider->top - this->collider->bottom) + 0.1f;
				velocityY = 0.0f;
			}
			
		}
	}
}

void Fish::CheckActive()
{

}