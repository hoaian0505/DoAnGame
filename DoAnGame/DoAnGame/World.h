#pragma once
#ifndef _WORLD_H_
#define _WORLD_H_
#include "Player.h"
#include "ThamSo.h"
//--------WEAPON----------
#include "Whip.h"
#include "AxeW.h"
#include "KnifeW.h"
#include "BoomerangW.h"
#include "HolyWaterW.h"

//-------DETRUCTIBLES-----
#include "Pots.h"
#include "Candles.h"

//-------BOARD-------
#include "Board.h"

//------EFFECT-----
#include "Effect.h"
#include "WaterEffect.h"

//-----ITEMS-----
#include "Heart.h"
#include "BigHeart.h"
#include "WhipUpgrade.h"
#include "Knife.h"
#include "Axe.h"
#include "Boomerang.h"
#include "Chicken.h"
#include "Clock.h"
#include "Cross.h"
#include "HolyWater.h"
#include "Genie.h"
#include "Power.h"

//-------ZONE----
#include "Gate.h"
#include "Door.h"

//--------ENEMIES------
#include "Ghoul.h"
#include "Cat.h"
#include "Bat.h"
#include "Fish.h"
#include "FireBall.h"
#include "VamBat.h"

//------GROUND-------
#include "BrickGround.h"
#include "Brick.h"
#include "Stair.h"
#include "DeadWater.h"
#include "VaChamTime.h"

//------MAP--------
#include "TileMap.h"



class World
{
public:
	// con trỏ đến "phần cứng" sprite
	LPD3DXSPRITE spriteHandler;
	// con trỏ đến "phần cứng" game
	MainGame* castlevania;

	Sprite* background;
	Player* Simon;


	//WEAPON
	Whip* whip;
	AxeW* axeW;
	KnifeW* knifeW;
	BoomerangW* boomerangW;
	HolyWaterW* holyWaterW;

	//----SOMETHING ELSE
	TileMap *tilemap;
	Pots* pots[99];
	Board* board;
	Candles* candles[99];
	Brick* brick[99];
	Stair* stair[99];
	BrickGround* brickGround;
	DeadWater* deadWater;
	VaChamTime* vaCham[30];

	std::string status1;
	std::string status2;
	
	//Effect
	Effect *effect;
	WaterEffect *waterEffect[9];

	// ITEMS
	Heart *heart[99];
	BigHeart *bigHeart[99];
	WhipUpgrade *whipUpgrade;
	Axe	*axe;
	Boomerang *boomerang;
	Chicken *chicken;
	Cross *cross;
	Knife *knife;
	HolyWater *holyWater;
	Clock *clock;
	Genie *genie;
	Power *power;

	// ZONE
	Gate* gate;
	Door* door[3];

	// ENEMIES
	Ghoul* ghoul[15];
	Cat* cat[5];
	Bat* bat[5];
	Fish* fish[9];
	FireBall* fireBall[9];
	VamBat* vamBat;


	//-----------
	int countHeart;
	int countBigHeart;

	bool WeaponOnce; //Update Weapon 1 lần thôi

	int Temp;
	bool isPause;
	float timePause;
	float timeWinning;
	bool Win;

	World(LPD3DXSPRITE _SpriteHandler, MainGame *_MainGame);
	~World();

	void Init();
	void Update(float _DeltaTime);
	void Render();
	void UpdateBoard();
	// --------------

	void splitString(const std::string& str, vector<int> &map, char split = ' ')
	{
		std::stringstream ss(str);
		std::string token;
		while (std::getline(ss, token, split)) {
			map.push_back(stoi(token));
		}
	};

	void ReadArrayFromTxt(string FileName, vector<int> &map, char split = ' ')
	{
		ifstream inputFile;
		string strs;
		inputFile.open(FileName);
		if (!inputFile)
			return;
		while (!inputFile.eof())
		{
			inputFile >> strs;
			splitString(strs, map, ',');
		}
		inputFile.close();
	}

};


#endif // !_WORLD_H_
