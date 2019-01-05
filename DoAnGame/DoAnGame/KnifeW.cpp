#include "KnifeW.h"
#include "World.h"
#include "Game.h"

KnifeW::KnifeW(LPD3DXSPRITE _SpriteHandler, World *_manager)
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
	sprite->_Index = 0;
	spriteRight->_Index = 0;
	spriteLeft->_Index = 0;
	//Damage = 3;
	isActive = false;
	collider = new Collider();
	collider->setCollider(10, -10, -18, 18);
	timeDamage = 0;
}

KnifeW::~KnifeW()
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

void KnifeW::Init(int _X, int _Y)
{
	///////

	isActive = true;

	if (manager->Simon->isCrouch)
		postY = _Y - 14;
	else
		postY = _Y;


	if (manager->Simon->isRight)
	{
		postX = _X + 10;
		velocityX = 250;
		sprite = spriteRight;
	}
	else
	{
		postX = _X - 10;
		velocityX = -250;
		sprite = spriteLeft;
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

void KnifeW::Update(const float &_DeltaTime)
{

		if (!isActive)
			return;

		postX += velocityX * _DeltaTime;

		timeDamage += _DeltaTime;
		//------------
		CollisionObject(_DeltaTime);
	

	if (!IsInCamera())
	{
		isActive = false;
		return;
	}

}


void KnifeW::Render()
{
	if (isActive)
	{
		sprite->Render(postX, postY);
	}
}

void KnifeW::Destroy()
{
	isActive = false;
}




void KnifeW::CollisionObject(float _DeltaTime)
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
