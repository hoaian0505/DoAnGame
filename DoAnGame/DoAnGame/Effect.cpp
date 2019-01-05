#include "Effect.h"
#include "World.h"

Effect::Effect(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = EFFECT_TYPE;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\Effects\\star.png");
	sprite1 = new Sprite(_SpriteHandler, texture->texture, 16, 20, 1, 1);
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\Effects\\fire.png");
	sprite2 = new Sprite(_SpriteHandler, texture->texture, 43, 44, 3, 3);
	isActive = false;

	collider = new Collider();
	// chỉnh collider
	collider->setCollider(0, -0, -0, 0);
}

Effect::~Effect()
{
	if (sprite1 != NULL)
	{
		delete sprite1;
	}
	if (sprite2 != NULL)
	{
		delete sprite2;
	}
}

void Effect::Init(int _X, int _Y)
{
	isActive = true;
	postX = _X;
	postY = _Y;
	sprite2->_Index = 0;

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

void Effect::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;

	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		timerSprite -= ANIM_TIME;
		sprite2->Next(1, 3);
	}
	if (sprite2->_Index == 3)
	{
		sprite2->_Index = 0;
		isActive = false;
	}
}



void Effect::Render()
{
	if (isActive)
	{
		sprite1->Render(postX - 5, postY + 5);
		sprite2->Render(postX + 5, postY - 5);
	}
}

void Effect::Destroy()
{

}


//------Collision


void Effect::CollisionObject(float _DeltaTime)
{
}