#ifndef _STARTSCREEN_H_
#define _STARTSCREEN_H_
#include "ThamSo.h";
#include "Texture.h"

class Startscreen
{
public:
	// con trỏ đến "phần cứng" sprite
	LPD3DXSPRITE spriteHandler;
	// con trỏ đến "phần cứng" game
	MainGame* castlevania;

	Sprite *sprite1;
	Sprite *sprite2;
	Sprite *sprite3;
	Texture *texture;

	float timerSprite;
	bool kichHoat;
	Startscreen(LPD3DXSPRITE _SpriteHandler);
	~Startscreen();

	void Update(float _DeltaTime);
	void Render();

};
#endif