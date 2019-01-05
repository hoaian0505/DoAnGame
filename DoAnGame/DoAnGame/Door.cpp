
#include "Door.h"
#include "Player.h"
#include "Sprite.h"
#include "World.h"

Door::Door(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ZONE_DOOR;
	collider = new Collider();
	spriteHandler = _SpriteHandler;
	isActive = true;
	sizeWidth = 48;
	sizeHeight = 96;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\ground\\Gate1.png");
	sprite = new Sprite(spriteHandler, texture->texture, sizeWidth, sizeHeight, 4, 4);
	sprite->_Index = 0;

}


Door::~Door()
{
}


void Door::Init(int _X, int _Y)	
{

	isActive = true;
	OpenDoor = false;

	postX = _X;
	postY = _Y;

	collider->setCollider(5, -5, -20, -10);

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
		}
	}
}


void Door::Render()
{
	sprite->Render(postX, postY);
}

void Door::Update(const float &_DeltaTime)
{
	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME * 3)
	{
		timerSprite -= ANIM_TIME * 3;
		sprite->Next(0, 3);
		if (sprite->_Index == 2 && !OpenDoor)
		{
			manager->Simon->ChangingScene++;
			OpenDoor = true;
		}
		else if (sprite->_Index == 0 && OpenDoor)
		{
			manager->Simon->ChangingScene++;
			isActive = false;
		}
	}
}


void Door::Collision(Player *actor, const float &_DeltaTime)
{

}