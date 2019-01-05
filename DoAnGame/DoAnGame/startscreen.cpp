#include "startscreen.h"
#include "Sprite.h"
#include "MainGame.h"

Startscreen::Startscreen(LPD3DXSPRITE _SpriteHandler)
{
	// ---  init core  ---
	spriteHandler = _SpriteHandler;

	// init vị trí camera
	Sprite::cameraX = 0;
	Sprite::cameraXLeft = 0;
	Sprite::cameraXRight = 0;
	Sprite::cameraY = 448;

	texture = new Texture(_SpriteHandler, "Resources\\Cinematics\\start_screen.bmp");
	sprite1 = new Sprite(_SpriteHandler, texture->texture, 512, 448, 1, 1);

	texture = new Texture(_SpriteHandler, "Resources\\Cinematics\\startbutton.bmp");
	sprite2 = new Sprite(_SpriteHandler, texture->texture, 230, 22, 10, 1);

	texture = new Texture(_SpriteHandler, "Resources\\Cinematics\\castle_cinematic.bmp");
	sprite3 = new Sprite(_SpriteHandler, texture->texture, 144, 112, 16, 4);

	timerSprite = 0;
	kichHoat = false;
}

Startscreen::~Startscreen()
{

}

void Startscreen::Update(float _DeltaTime)
{
	timerSprite += _DeltaTime;
	if (timerSprite > ANIM_TIME)
	{
		sprite2->Next(0, 9);
		if (!kichHoat)
			sprite3->Next(0, 11);
		else
			sprite3->Next(12, 15);
		if (sprite3->_Index == 11)
			kichHoat = true;
		timerSprite = 0;
	}
}


void Startscreen::Render()
{
	sprite1->Render(256, 224);
	sprite2->Render(256,192);
	sprite3->Render(444, 192);
}