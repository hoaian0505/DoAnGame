#include "Candles.h"
#include "World.h"
#include "Game.h"

Candles::Candles(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = DESTRUCTIBLE_TYPE;
	spriteHandler = _SpriteHandler;
	sizeWidth = 16;
	sizeHeight = 32;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\candles.png");
	sprite = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 2, 2);
	isActive = false;

	collider = new Collider();
	// chỉnh collider
	collider->setCollider(15, -15, -10, 10);
}

Candles::~Candles()
{
	if (sprite != NULL)
	{
		delete sprite;
	}
}

void Candles::Init(int _X, int _Y)
{
	isActive = true;

	postX = _X;
	postY = _Y;

	//random số
	srand(time(NULL));
	a = rand() % 2 + 1;					//	(b-a+1) + a         (random từ a -> b) 

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

void Candles::Update(const float &_DeltaTime)
{

		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME)
		{
			timerSprite -= ANIM_TIME;
			sprite->Next(0, 1);
		}

}


void Candles::Render()
{
	if (isActive)
			sprite->Render(postX, postY);
}

void Candles::Destroy()
{


	if (isActive)
	{
		this->isActive = false;
		manager->effect->Init(postX, postY);

		
		if (manager->whip->whipLevel < 2)
			a = 3;
		if (manager->Simon->health < 9)
			a = 5;
		switch (a)
		{
		case 1:
			manager->countHeart++;
			manager->heart[manager->countHeart]->Init(postX, postY);
			break;
		case 2:
			manager->countBigHeart++;
			manager->bigHeart[manager->countBigHeart]->Init(postX, postY);
			break;
		case 3:
			manager->whipUpgrade->Init(postX, postY);
			break;
		case 4:
			manager->axe->Init(postX, postY);
			break;
		case 5:
			manager->chicken->Init(postX, postY);
			break;
		case 6:
			manager->boomerang->Init(postX, postY);
			break;
		case 7:
			manager->holyWater->Init(postX, postY);
			break;
		case 8:
			manager->knife->Init(postX, postY);
			break;
		case 9:
			manager->cross->Init(postX, postY);
			break;
		case 10:
			manager->clock->Init(postX, postY);
			break;
		case 11:
			manager->genie->Init(postX, postY);
			break;
		default:
			break;
		}
	}
}


//------Collision


void Candles::CollisionObject(float _DeltaTime)
{
}