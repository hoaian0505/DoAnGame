#include "HolyWaterW.h"
#include "World.h"
#include "Game.h"

HolyWaterW::HolyWaterW(LPD3DXSPRITE _SpriteHandler, World *_manager)
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
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\weapon\\fire.png");
	spriteGround = new Sprite(_SpriteHandler, texture->texture, 32, 26, 2, 2);

	sprite = spriteRight;
	sprite->_Index = 8;
	spriteRight->_Index = 8;
	spriteLeft->_Index = 8;
	spriteGround->_Index = 0;
	//Damage = 3;
	isActive = false;
	collider = new Collider();
	ColliGround = false;
	timeDamage = 0;
}

HolyWaterW::~HolyWaterW()
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

void HolyWaterW::Init(int _X, int _Y)
{
	collider->setCollider(4, -8, -4, 4);
	timeActive = 0;
	timerSprite = 0;
	///////

	isActive = true;

	postX = _X;
	if (manager->Simon->isCrouch)
		postY = _Y - 14;
	else
		postY = _Y;

	velocityY = 300;

	if (manager->Simon->isRight)
	{
		velocityX = 150;
		sprite = spriteRight;
	}
	else
	{
		velocityX = -150;
		sprite = spriteLeft;
	}

	firstShow = true;
	ColliGround = false;

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

void HolyWaterW::Update(const float &_DeltaTime)
{

		if (!isActive)
			return;

		postX += velocityX * _DeltaTime;
		postY += velocityY * _DeltaTime;

		velocityY -= 1000 * _DeltaTime;

		timeDamage += _DeltaTime;
		//------------
		CollisionObject(_DeltaTime);
		
		if (ColliGround)
		{
			velocityX = 0;
			sprite = spriteGround;
			if (firstShow)
			{
				firstShow = false;
			}

		}
		if (sprite == spriteGround)
		{
			collider->setCollider(10, -8, -12, 12);
			timerSprite += _DeltaTime;
			timeActive += _DeltaTime;
			if (timerSprite >= ANIM_TIME * 1.5f)
			{
				sprite->Next(0, 1);
				timerSprite -= ANIM_TIME * 1.5f;
			}
			if (timeActive > 1.5f)
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


void HolyWaterW::Render()
{
	if (isActive)
	{
		sprite->Render(postX, postY);
	}
}

void HolyWaterW::Destroy()
{
	isActive = false;
}




void HolyWaterW::CollisionObject(float _DeltaTime)
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

				if (tempObject->objectType == BRICK_TYPE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						if (normaly > 0.1f)//chạm từ trên xuống
						{
							this->velocityX += tempObject->velocityX;
						}
						SlideFromGround(tempObject, _DeltaTime, collisionScale);
						ColliGround = true;
					}
				}
			}
	}

	tempObject = manager->brickGround;
	collisionScale = SweptAABB(tempObject, _DeltaTime);
	if (collisionScale < 1.0f)
	{

		if (normaly > 0.1f)//chạm từ trên xuống
		{
			this->velocityX += tempObject->velocityX;
		}
		SlideFromGround(tempObject, _DeltaTime, collisionScale);
		ColliGround = true;
	}
}
