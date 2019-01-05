#include "BoomerangW.h"
#include "World.h"
#include "Game.h"

BoomerangW::BoomerangW(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	sizeWidth = 64;
	sizeHeight = 64;
	objectType = WEAPON_TYPE;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\weapon\\subweapon_left.bmp");
	spriteLeft = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 9, 6);
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\weapon\\subweapon_right.bmp");
	spriteRight = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 9, 6);

	sprite = spriteRight;
	sprite->_Index = 5;
	spriteRight->_Index = 5;
	spriteLeft->_Index = 5;
	//Damage = 3;
	isActive = false;
	PlayOnRight = false;
	collider = new Collider();
	collider->setCollider(10, -10, -10, 10);
	timeDamage = 0;
}

BoomerangW::~BoomerangW()
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

void BoomerangW::Init(int _X, int _Y)
{
	timerSprite = 0;
	///////

	isActive = true;

	if (manager->Simon->isCrouch)
		postY = _Y - 14;
	else
		postY = _Y;

	velocityY = 0;

	if (manager->Simon->isRight)
	{
		postX = _X + 5;
		velocityX = 300;
		sprite = spriteRight;
		PlayOnRight = true;
	}
	else
	{
		postX = _X - 5;
		velocityX = -300;
		sprite = spriteLeft;
		PlayOnRight = false;
	}

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

void BoomerangW::Update(const float &_DeltaTime)
{
		if (!isActive)
			return;

		timerSprite += _DeltaTime;

		postX += velocityX * _DeltaTime;
		postY += velocityY * _DeltaTime;

		if (PlayOnRight)
			velocityX -= 250 * _DeltaTime;
		else
			velocityX += 250 * _DeltaTime;

		if (timerSprite >= ANIM_TIME / 1.5f)
		{
			sprite->Next(5, 7);
			timerSprite -= ANIM_TIME / 1.5f;
		}

		timeDamage += _DeltaTime;
		//------------
		CollisionObject(_DeltaTime);

		if (PlayOnRight)
		{
			if (velocityX < 0 && IsCollide(manager->Simon))
			{
				isActive = false;
				return;
			}
		}
		else
		{
			if (velocityX > 0 && IsCollide(manager->Simon))
			{
				isActive = false;
				return;
			}
		}

		if (!IsInCamera())
		{
			isActive = false;
			return;
		}

}


void BoomerangW::Render()
{
	if (isActive)
	{
		sprite->Render(postX, postY);
	}
}

void BoomerangW::Destroy()
{
	isActive = false;
}




void BoomerangW::CollisionObject(float _DeltaTime)
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

				if (tempObject->objectType == ENEMY_TYPE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
					}
				}

				if (tempObject->objectType == BOSS_TYPE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						if (timeDamage > ANIM_TIME * 3)
						{
							tempObject->Destroy();
							timeDamage = 0;
						}
					}
				}
			}
	}
}
