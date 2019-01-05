#include "Cat.h"
#include "Sprite.h"
#include "World.h"
Cat::Cat() {}

Cat::Cat(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = ENEMY_TYPE;

	isActive = false;
	sizeWidth = 64;
	sizeHeight = 32;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\enemy\\2.png");
	spriteLeft = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 29, 6);
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\enemy\\2-right.png");
	spriteRight = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 29, 6);

	sprite = spriteLeft;
	ColliGround = false;
}

Cat :: ~Cat()
{

}

void Cat::Init(int _X, int _Y, bool _isRight,float _timeRun)
{
	collider = new Collider();
	collider->setCollider(6, -16, -14, 14);
	isActive = true;
	timeRun = _timeRun;

	isSleeping = true;
	hasJumped = false;

	postY = _Y;
	postX = _X;
	isRight = _isRight;
	if (isRight)
	{
		sprite = spriteLeft;
		velocityX = -200;
	}
	else
	{
		sprite = spriteRight;
		velocityX = 200;
	}

	sprite->_Index = 0;
	velocityY = 0;
	ColliGround = false;

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


void Cat::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;

	if (manager->isPause)
		return;

	//Thức dậy - Không ngủ nữa
	if (sqrt(
		pow(manager->Simon->postX - this->postX, 2) +
		pow(manager->Simon->postY - this->postY, 2))
		< 200)
		isSleeping = false;
	//Kiểm tra có đang ngủ hay không?
	if (isSleeping)
		return;



	if (isSleeping == false)
		timeRun -= _DeltaTime;




	if (timeRun < 0)
	{
		if (!ColliGround)
		{
			if (!hasJumped)
			{
				hasJumped = true;
				sprite->_Index = 3;
				velocityY = 300;
			}
			velocityY -= 1000 * _DeltaTime;
		}
	}

	if (hasJumped)
		if (ColliGround)
		{
			//velocityY = 0;
			//postY = 60;
			hasJumped = false;
			if (isRight)
			{
				sprite = spriteRight;
				velocityX = 200;
			}
			else
			{
				sprite = spriteLeft;
				velocityX = -200;
			}
			sprite->_Index = 0;
		}

	if (!hasJumped)
	{
		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME)
		{
			sprite->Next(1, 3);
			timerSprite = 0;
		}
	}

	CollisionObject(_DeltaTime);
	
	//cập nhật tọa độ X,Y
	postX += velocityX * _DeltaTime;
	postY += velocityY * _DeltaTime;

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



void Cat::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Cat::Destroy()
{
	manager->Simon->score += 100;
	this->isActive = false;
	manager->effect->Init(postX, postY);
	collider = NULL;
}

void Cat::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;

	//-----------------------GROUND-----------------------------


		tempObject = manager->brickGround;
		collisionScale = SweptAABB(tempObject, _DeltaTime);
		if (collisionScale < 1.0f)
		{

			if (normaly > 0.1f)//chạm từ trên xuống
			{
				this->postY = (manager->brickGround->postY + manager->brickGround->collider->top - this->collider->bottom) + 0.1f;
				velocityY = 0.0f;
			}
			ColliGround = true;
		}

}

void Cat::CheckActive()
{
}