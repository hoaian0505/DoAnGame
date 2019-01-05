

#include "World.h"
#include "MainGame.h"
#include <time.h>



World::World(LPD3DXSPRITE _SpriteHandler, MainGame *_MainGame)
{
	// ---  init core  ---
	spriteHandler = _SpriteHandler;
	castlevania = _MainGame;

	// ---  init static object  ---
	Simon = new Player(spriteHandler, this);
	tilemap = new TileMap(spriteHandler, this);


	/////--WEAPON
	whip = new Whip(spriteHandler, this);
	axeW = new AxeW(spriteHandler, this);
	knifeW = new KnifeW(spriteHandler, this);
	boomerangW = new BoomerangW(spriteHandler, this);
	holyWaterW = new HolyWaterW(spriteHandler, this);


	//////--------Destructible
	for (int i=1;i<=5;i++)
		pots[i] = new Pots(spriteHandler, this);
	for (int i = 1; i < 21; i++)
		candles[i] = new Candles(spriteHandler, this);

	/////----BOARD
	board = new Board(spriteHandler, this);


	
	// ---------ITEMS-------
	for (int i = 1; i < 20; i++)
	{
		heart[i] = new Heart(spriteHandler, this);
		bigHeart[i] = new BigHeart(spriteHandler, this);
	}

	whipUpgrade=new WhipUpgrade(spriteHandler, this);
	// -------7 others ------
	axe = new Axe(spriteHandler, this);
	cross = new Cross(spriteHandler, this);
	boomerang = new Boomerang(spriteHandler, this);
	clock = new Clock(spriteHandler, this);
	holyWater = new HolyWater(spriteHandler, this);
	knife = new Knife(spriteHandler, this);
	chicken = new Chicken(spriteHandler, this);
	genie = new Genie(spriteHandler, this);
	power = new Power(spriteHandler, this);

	// ----- ZONE
	gate = new Gate(spriteHandler, this);
	for (int i = 1; i < 3; i++)
		door[i] = new Door(spriteHandler, this);

	// ----- ENEMIES
	for (int i = 1; i < 15; i++)
		ghoul[i] = new Ghoul(spriteHandler, this);
	for (int i = 1; i < 5; i++)
		cat[i] = new Cat(spriteHandler, this);
	for (int i = 1; i < 5; i++)
		bat[i] = new Bat(spriteHandler, this);
	for (int i = 1; i < 9; i++)
		fish[i] = new Fish(spriteHandler, this);
	for (int i = 1; i < 9; i++)
		fireBall[i] = new FireBall(spriteHandler, this);
	vamBat = new VamBat(spriteHandler, this);

	//-------GROUND
	for (int i = 1; i < 20; i++)
		brick[i] = new Brick(spriteHandler, this);
	for (int i = 1; i < 25; i++)
		stair[i] = new Stair(spriteHandler, this);
	brickGround = new BrickGround(spriteHandler, this);
	deadWater = new DeadWater(spriteHandler, this);
	for (int i = 1; i < 30; i++)
		vaCham[i] = new VaChamTime(spriteHandler, this);

	//---------EFFECT
	effect = new Effect(spriteHandler, this);
	for (int i = 1; i < 9; i++)
		waterEffect[i] = new WaterEffect(spriteHandler, this);

	Temp = 0;
	countHeart = 0;
	countBigHeart = 0;
	isPause = false;
	timePause = 0;
	timeWinning = 0;
	Win = false;
}


World::~World()
{
	delete Simon;
	delete whip;

}

// 
void World::Init()
{
	

}

// gọi ở đầu game_run
void World::Update(float _DeltaTime)
{
	WeaponOnce = false;

	if (Win)
	{
		timeWinning += _DeltaTime;
		if (timeWinning >= TIMEWIN)
			return;
	}



	tilemap->Update(_DeltaTime);

	for (int i = 1; i < 30; i++)
		vaCham[i]->Update(_DeltaTime);
	//------ cập nhật 


	for (int i = 1; i < 30; i++)
	{
		if (vaCham[i]->kickHoat)
			for (int j = 0; j < vaCham[i]->objects.size(); j++)
			{
				if (vaCham[i]->objects[j]->objectType != ZONE_DOOR)
					vaCham[i]->objects[j]->Update(_DeltaTime);
			}
	}

	Simon->Update(_DeltaTime);

	if (isPause)
	{
		timePause += _DeltaTime;
		if (timePause > TIMEPAUSE)
		{
			timePause = 0;
			isPause = false;
		}
	}
}

// gọi bên trong BeginScene() và EndScene();
void World::Render()
{
	board->Load(Simon->health,vamBat->healthBoss);

	tilemap->Render();

	for (int i = 1; i < 30; i++)
	{
		if (vaCham[i]->kickHoat)
			for (int j = 0; j < vaCham[i]->objects.size(); j++)
			{
				vaCham[i]->objects[j]->Render();
			}
	}

	Simon->Render();


	//WEAPON ON CAMERA
	/*axe->RenderCamera();
	boomerang->RenderCamera();
	clock->RenderCamera();
	holyWater->RenderCamera();
	knife->RenderCamera();*/
}

void World::UpdateBoard()
{
	status1 = "SCORE - " + board->convertScoreFormat(Simon->score) +
		"            TIME "
		+ board->convertTimeFormat(Simon->timeUI) +
		"            STAGE " + board->convertHeartFormat(1) +
		
		"\nPLAYER" +
		"\nENEMY";
	status2 = board->convertHeartFormat(Simon->heart) + "\n"
		+ board->convertHeartFormat(Simon->P);
}

