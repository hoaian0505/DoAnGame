#include "Intro.h"
#include "Sprite.h"

Intro::Intro(LPD3DXSPRITE _SpriteHandler)
{
	// ---  init core  ---
	spriteHandler = _SpriteHandler;

	// init vị trí camera
	Sprite::cameraX = 0;
	Sprite::cameraXLeft = 0;
	Sprite::cameraXRight = 0;
	Sprite::cameraY = 448;

	texture = new Texture(_SpriteHandler, "Resources\\Cinematics\\intro.png");
	sprite1 = new Sprite(_SpriteHandler, texture->texture, 512, 448, 1, 1);

	texture = new Texture(_SpriteHandler, "Resources\\Cinematics\\helicopter.png");
	sprite2 = new Sprite(_SpriteHandler, texture->texture, 64, 28, 1, 1);

	texture = new Texture(_SpriteHandler, "Resources\\Cinematics\\bat.png");
	sprite3 = new Sprite(_SpriteHandler, texture->texture, 16, 16, 2, 2);
	sprite4 = new Sprite(_SpriteHandler, texture->texture, 16, 16, 2, 2);
	
	timerSprite = 0;
	postX = 400;
	postY = 300;

	postX1 = 100;
	postY1 = 150;

	postX2 = 350;
	postY2 = 250;
	
	isActive = false;
}

Intro::~Intro()
{

}

void Intro::Update(Player *simon,float _DeltaTime)
{
	if (isActive)
	{


		timerSprite += _DeltaTime;
		if (timerSprite > ANIM_TIME)
		{
			postX -= 80 *_DeltaTime;

			postX1 += 100 * _DeltaTime;
			postY1 += 200 * _DeltaTime;

			postX2 -= 120 * _DeltaTime;
			postY2 += 100 * _DeltaTime;

			sprite3->Next(0, 1);
			sprite4->Next(0, 1);
			timerSprite = 0;
		}

		UpdateSimon(simon,_DeltaTime/1.5f);
	}
}


void Intro::Render()
{
	if (isActive)
	{
		sprite1->Render(256, 224);
		sprite2->Render(postX, postY);
		sprite3->Render(postX1, postY1);
		sprite4->Render(postX2, postY2);
	}
}

void Intro::UpdateSimon(Player *simon,const float &_DeltaTime)
{
	if (simon->postX <= 256)
	{
		simon->sprite->_Index = 27;
	}
	else
	{
		simon->Move(-1, _DeltaTime);
		simon->postX += (simon->velocityX * _DeltaTime/2);
	}
}