#include "Ghoul.h"
#include "Sprite.h"
#include "World.h"
Ghoul::Ghoul() {}

Ghoul::Ghoul(LPD3DXSPRITE _SpriteHandler, World *_manager) 
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = ENEMY_TYPE;
	


	isActive = false;
	sizeWidth = 34;
	sizeHeight = 64;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\enemy\\1.png");
	spriteLeft = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 2, 2);
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\enemy\\1-right.png");
	spriteRight = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 2, 2);
	sprite = spriteLeft;

	minX = 0;
	maxX = 0;

}

Ghoul :: ~Ghoul()
{

}

void Ghoul::Init(int _X, int _Y, bool _isRight)
{
	collider = new Collider();
	collider->setCollider(32, -32, -15, 15);
	isActive = true;
	postY = _Y;
	postX = _X;
	isRight = _isRight;
	if (_isRight)
	{
		sprite = spriteLeft;
		velocityX = -70;
	}
	else
	{
		sprite = spriteRight;
		velocityX = 70;
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

			minX = manager->vaCham[i]->postX + manager->vaCham[i]->collider->left;
			maxX = manager->vaCham[i]->postX + manager->vaCham[i]->collider->right;

			return;
		}
	}

}

void Ghoul::Update(const float &_DeltaTime)
{
	if (isRight == false && postX > manager->Simon->postX - 200)
	{
		isActive = false;
		collider = NULL;
	}
	if (isRight == false && postX < manager->Simon->postX - 200)
	{
		isActive = true;
		isRight = true;
		collider = new Collider();
		collider->setCollider(32, -32, -15, 15);
	}

	if (!isActive)
		return;
	
	if (manager->isPause)
		return;


	if (velocityX < 0)
	{
		if (postX < minX)
		{
			velocityX = 70;
			sprite = spriteRight;
		}
	}
	else if (velocityX > 0)
	{
		if (postX > maxX)
		{
			velocityX = -70;
			sprite = spriteLeft;
		}
	}

	velocityY -= 600 * _DeltaTime;
	//cập nhật tọa độ X,Y
	CollisionObject(_DeltaTime);
	postX += velocityX * _DeltaTime;
	postY += velocityY * _DeltaTime;

	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(0, 1);
		timerSprite = 0;
	}

}



void Ghoul::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Ghoul::Destroy()
{
	manager->Simon->score += 100;
	this->isActive = false;
	manager->effect->Init(postX, postY);
	collider = NULL;
}

void Ghoul::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;

	//-----------------------GROUND-----------------------------
	for (int i = 1; i < 20; i++)
	{
		tempObject = manager->brick[i];
		collisionScale = SweptAABB(tempObject, _DeltaTime);
		if (collisionScale < 1.0f)
		{
			SlideFromGround(tempObject, _DeltaTime, collisionScale);
			if (sprite == spriteLeft)
			{
				velocityX = -70;
			}
			else
			{
				velocityX = 70;
			}
		}
	}

	tempObject = manager->brickGround;
	collisionScale = SweptAABB(tempObject, _DeltaTime);
	if (collisionScale < 1.0f)
	{
		SlideFromGround(tempObject, _DeltaTime, collisionScale);
	}
}

void Ghoul::CheckActive()
{
	if (postX < Sprite::cameraX || postX > Sprite::cameraX + 512)
		isActive = false;
}