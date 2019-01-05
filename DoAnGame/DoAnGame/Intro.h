#ifndef _Intro_H_
#define _Intro_H_
#include "ThamSo.h"
#include "Texture.h"
#include "Player.h"

class Intro
{
public:
	// con trỏ đến "phần cứng" sprite
	LPD3DXSPRITE spriteHandler;
	// con trỏ đến "phần cứng" game
	World* manager;

	Sprite *sprite1;
	Sprite *sprite2;
	Sprite *sprite3;
	Sprite *sprite4;
	Texture *texture;
	// simon rieng
	Player *simon_cinematic;


	bool isActive;
	int postX, postY, postX1, postY1, postX2, postY2;
	float timerSprite;

	Intro(LPD3DXSPRITE _SpriteHandler);
	~Intro();

	void Update(Player *simon, float _DeltaTime);
	void UpdateSimon(Player *simon,const float &_DeltaTime);
	void Render();

};
#endif