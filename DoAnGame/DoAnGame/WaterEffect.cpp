#include "WaterEffect.h"
#include "World.h"

WaterEffect::WaterEffect(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = EFFECT_TYPE;

	sizeWidth = 14;
	sizeHeight = 28;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\Effects\\2.png");
	sprite = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 1, 1);
	isActive = false;

	collider = new Collider();
	collider->setCollider(0, -0, -0, 0);
}

WaterEffect::~WaterEffect()
{
	if (sprite != NULL)
	{
		delete sprite;
	}

}

void WaterEffect::Init(int _X, int _Y,bool isRight)
{
	isActive = true;
	postX = _X;
	postY = _Y;

	if (isRight)
		velocityX = 30;
	else
		velocityX = -30;
	velocityY = 200;

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

void WaterEffect::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;

		postX += velocityX * _DeltaTime;
		postY += velocityY * _DeltaTime;
		velocityY -= 700 * _DeltaTime;
}



void WaterEffect::Render()
{
	if (isActive)
		{
			sprite->Render(postX, postY);
		}
}

void WaterEffect::Destroy()
{

}


//------Collision


void WaterEffect::CollisionObject(float _DeltaTime)
{
}