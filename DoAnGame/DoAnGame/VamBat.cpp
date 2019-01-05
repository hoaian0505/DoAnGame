#include "VamBat.h"
#include "Sprite.h"
#include "World.h"
VamBat::VamBat() {}

VamBat::VamBat(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = BOSS_TYPE;



	isActive = false;
	sizeWidth = 96;
	sizeHeight = 46;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\boss\\0.png");
	sprite = new Sprite(_SpriteHandler, texture->texture, sizeWidth, sizeHeight, 3, 3);
	sprite->_Index = 0;
	healthBoss = 16;
	timeActive = 0;
	BossTime = false;
	timePause = 0;
	AttackSimon = false;
	timeAttackSimon = 0;
}

VamBat :: ~VamBat()
{

}

void VamBat::Init(int _X, int _Y)
{
	collider = new Collider();
	collider->setCollider(13, -13, -45, 45);
	isActive = true;
	postY = _Y;
	postX = _X;
	healthBoss = 16;
	timeActive = 0;
	BossTime = false;
	velocityX = -150;
	velocityY = -80;

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

void VamBat::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;

	if (manager->isPause)
		return;

	if (!BossTime)
	{
		timeActive += _DeltaTime;
		if (timeActive > BOSS_TIME)
		{
			BossTime = true;
			manager->Simon->UpdateCamera(Sprite::cameraXRight, Sprite::cameraY, Sprite::cameraXRight, Sprite::cameraXRight);
		}
	}

	if (BossTime && collider!=NULL)
	{
		timePause += _DeltaTime;
		

		if (AttackSimon == false)
		{
			if (velocityY > -30 && velocityY < 0)
				velocityY = -80;
			if (velocityY < 30 && velocityY >= 0 || velocityY>150)
				velocityY = 80;
			if (velocityX > -30 && velocityX < 0)
				velocityX = -150;
			if (velocityX < 30 && velocityX >= 0)
				velocityX = 150;

			timeAttackSimon += _DeltaTime;
		}

		CollisionObject(_DeltaTime);



		if (sqrt(
			pow(manager->Simon->postX - this->postX, 2) +
			pow(manager->Simon->postY - this->postY, 2))
			> 300 && timeAttackSimon > ATTACKSIMONTIME)
		{
			AttackSimon = true;
			timeAttackSimon = 0;
		}

		if (AttackSimon == true)
		{
				velocityX = (manager->Simon->postX - this->postX) * 10 / 3;
				velocityY = (manager->Simon->postY - this->postY) * 10 / 3;
		}



		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME)
		{
			sprite->Next(1, 2);
			timerSprite = 0;
		}

		//cập nhật tọa độ X,Y
		if (timePause < TIMEPAUSEBOSS)
		{
			postX += velocityX * _DeltaTime;
			postY += velocityY * _DeltaTime;
		}

		if (timePause > PAUSINGBOSS)
		{
			timePause = 0;
		}
	}


}



void VamBat::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void VamBat::Destroy()
{
	manager->effect->Init(postX, postY);
	healthBoss -= 2;
	if (healthBoss <= 0)
		Dead();
}

void VamBat::CollisionObject(float _DeltaTime)
{
	if (this->postX + collider->left < Sprite::cameraX)
		velocityX = 150;
	if (this->postX + collider->right > Sprite::cameraXRight + 512)
		velocityX = -150;
	if (this->postY - collider->bottom > Sprite::cameraY-110)
		velocityY = -(velocityY+10);
	if (this->postY + collider->top < 60)
		velocityY = -(velocityY-10);
}

void VamBat::Dead()
{
	manager->Simon->score += 100;
	this->isActive = false;
	manager->effect->Init(postX, postY);
	collider = NULL;
	manager->power->Init(Sprite::cameraX + 512 / 2, 200);
}

void VamBat::CheckActive()
{

}