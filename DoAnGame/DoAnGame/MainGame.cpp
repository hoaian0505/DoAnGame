#include "MainGame.h"
#include <d3d9.h>
#include <d3dx9.h>



#define SIMON_SPEED 0.2f
#define VIEW_PORT_Y 448

MainGame::MainGame(HINSTANCE hInstance, LPCSTR Name, int IsFullScreen, int FrameRate) :Game(hInstance, Name, IsFullScreen, FrameRate)
{

}

void MainGame::LoadResources(LPDIRECT3DDEVICE9 _d3ddevice)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(_d3ddevice, &_SpriteHandler);

	world = new World(_SpriteHandler, this);
	world->Init();
	

	gateIn = false;

	// ------------- cinematics --------------
	startscreen = new Startscreen(_SpriteHandler);
	intro = new Intro(_SpriteHandler);

	// ---------------
	screenMode = GAMEMODE_START;
}

// ==========================================================================
// --------------------------MAIN UPDATE FUNCTION ---------------------------
// ==========================================================================

// --------------------------------------
void MainGame::Update(float _DeltaTime)
{
	switch (screenMode)
	{
		// start screen
	case GAMEMODE_START:
		UpdateStartScreen(_DeltaTime);
		break;
		// intro
	case GAMEMODE_INTRO:
		UpdateIntro(_DeltaTime);
		break;
		// game running
	case GAMEMODE_GAMERUN:
		UpdateGame(_DeltaTime);
		break;
	default:
		break;
	}
}

// ------------------------------
void MainGame::UpdateStartScreen(float _DeltaTime)
{
	startscreen->Update(_DeltaTime);
}

// ------------------------------
void MainGame::UpdateIntro(float _DeltaTime)
{
	intro->Update(world->Simon,_DeltaTime);
	// chỉ xuất hiện 1 lúc
	timerIntro -= _DeltaTime;
	if (timerIntro <= 0.0f)
	{
		NextLevel();
	}
}

// ------------------------------
void MainGame::UpdateGame(float _DeltaTime)
{

	world->Update(_DeltaTime);
	
}

// -----------------------------------------------------------
// -----------------------------------------------------------

void MainGame::NextLevel()
{
	
	int Temp = 250;
	int BrickDistance = 32;
	this->screenMode = GAMEMODE_GAMERUN;
	int j = 1;

	UpdateGame(0.0f);
	switch (world->Temp)
	{
	case 0:

		//------------GRID----------------------
		world->ReadArrayFromTxt("Resources\\Objects\\Grid.txt", Object, ' ');
		for (int i = 0; i < Object.size()-1; i += 2)
		{
			world->vaCham[j]->Init(Object[i], Object[i+1]);
			j++;
		}


		world->tilemap->maplvl = 1;
		world->Simon->postX = 64;
		world->Simon->postY = 95;
		world->Simon->isRight = true;
		Sprite::cameraX = 32;
		Sprite::cameraXLeft = 32;
		Sprite::cameraXRight = 992;
		Sprite::cameraY = 448;

		//-------------------POTS----------------------
		Object.clear();
		world->ReadArrayFromTxt("Resources\\Objects\\Pot.txt", Object, ' ');

		j = 1;
		for (int i = 0; i < Object.size() - 1; i += 2)
		{
			world->pots[j]->Init(Object[i], Object[i + 1]);
			j++;
		}

		Object.clear();
		world->ReadArrayFromTxt("Resources\\Objects\\Gate.txt", Object, ' ');
		world->gate->Init(Object[0], Object[1]);
		

		//--------GROUND-------
		world->brickGround->Init(32, 46,94);

		break;

	case 1:
		//-----------DISABLE ITEMS----------
		for (int i = 1; i <= 5; i++)
		{
			world->pots[i]->isActive = false;
		}
		//----------CANDLES-------------
		Object.clear();
		world->ReadArrayFromTxt("Resources\\Objects\\Candle.txt", Object, ' ');

		j = 1;
		for (int i = 0; i < Object.size() - 1; i += 2)
		{
			world->candles[j]->Init(Object[i], Object[i + 1]);
			j++;
		}
		world->candles[3]->a = 10;
		world->candles[11]->a = 9;
		world->candles[17]->a = 11;

		//---------GHOULS----------
		Object.clear();
		world->ReadArrayFromTxt("Resources\\Objects\\Ghoul.txt", Object, ' ');

		j = 1;
		for (int i = 0; i < Object.size() - 1; i += 2)
		{
			if (j == 4)
				world->ghoul[j]->Init(Object[i], Object[i + 1],false);
			else
				world->ghoul[j]->Init(Object[i], Object[i + 1], true);
			j++;
		}

		//--------CATS--------------
		Object.clear();
		world->ReadArrayFromTxt("Resources\\Objects\\Cat.txt", Object, ' ');

		j = 1;
		for (int i = 0; i < Object.size() - 1; i += 3)
		{
			world->cat[j]->Init(Object[i], Object[i + 1], true, float(Object[i+2])/10);
			j++;
		}


		//--------BATS-----------
			Object.clear();
			world->ReadArrayFromTxt("Resources\\Objects\\Bat.txt", Object, ' ');

			j = 1;
			for (int i = 0; i < Object.size() - 1; i += 2)
			{
				if (j == 4)
					world->bat[j]->Init(Object[i], Object[i + 1], false);
				else
					world->bat[j]->Init(Object[i], Object[i + 1], true);
				j++;
			}

		//-------FISHES---------
			Object.clear();
			world->ReadArrayFromTxt("Resources\\Objects\\Fish.txt", Object, ' ');

			j = 1;
			for (int i = 0; i < Object.size() - 1; i += 2)
			{
				if (j < 3)
					world->fish[j]->Init(Object[i], Object[i + 1], false);
				else
					world->fish[j]->Init(Object[i], Object[i + 1], true);
				j++;
			}


		//--------GROUND-------
		world->brickGround->Init(32, 12,357);
		

				//-----------STAIR------------

		Object.clear();
		world->ReadArrayFromTxt("Resources\\Objects\\Stair.txt", Object, ' ');

		j = 1;
		for (int i = 0; i < Object.size() - 1; i += 3)
		{
			world->stair[j]->Init(Object[i], Object[i + 1], Object[i + 2]);
			j++;
		}

				//-------------BRICK----------

		Object.clear();
		world->ReadArrayFromTxt("Resources\\Objects\\Brick.txt", Object, ' ');

		j = 1;
		for (int i = 0; i < Object.size() - 1; i += 3)
		{
			world->brick[j]->Init(Object[i], Object[i + 1],Object[i+2]);
			j++;
		}
		
		//----------------DEAD WATER----------------
		Object.clear();
		world->ReadArrayFromTxt("Resources\\Objects\\deadWater.txt", Object, ' ');
		world->deadWater->Init(Object[0], Object[1]);
		//------------BOSS-----------------------

		Object.clear();
		world->ReadArrayFromTxt("Resources\\Objects\\Boss.txt", Object, ' ');
		world->vamBat->Init(Object[0], Object[1]);

				//------------DOOR------------
		Object.clear();
		world->ReadArrayFromTxt("Resources\\Objects\\Door.txt", Object, ' ');

		j = 1;
		for (int i = 0; i < Object.size() - 1; i += 2)
		{
			world->door[j]->Init(Object[i], Object[i + 1]);
			j++;
		}

		gateIn = true;
		break;
	default:
		break;
	}
}

// ==========================================================================
// --------------------------MAIN RENDER FUNCTION ---------------------------
// ==========================================================================
// ---  between BeginScene & EndScene ---
void MainGame::Render(LPDIRECT3DDEVICE9 d3ddv)
{
	switch (screenMode)
	{
		// start screen
	case GAMEMODE_START:
		RenderStartScreen();
		break;
		// intro
	case GAMEMODE_INTRO:
		RenderIntro(d3ddv);
		break;
		// game running
	case GAMEMODE_GAMERUN:
		RenderGame(d3ddv);
		break;
	default:
		break;
	}
}

// -----------------------
void MainGame::RenderStartScreen()
{
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	startscreen->Render();
	_SpriteHandler->End();
}

// ------------------------
void MainGame::RenderIntro(LPDIRECT3DDEVICE9 d3ddv)
{
	//d3ddv->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	intro->Render();
	world->Simon->Render();
	_SpriteHandler->End();
}

void MainGame::RenderGame(LPDIRECT3DDEVICE9 d3ddv)
{
	
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	if (world->Temp == 0)
	{ }
	else
	{
		if (gateIn == false)
		{
			NextLevel();
		}
	}


	world->Render();
	_SpriteHandler->End();

	//Viết lên Board
	UpdateBoard();
}
// ----------------------------------------------------
//------------------------------------------------------
// ----------------------------------------------------


void MainGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float _DeltaTime)		//Chạy khi nhấn giữ
{

	switch (screenMode)
	{
		// start screen --------------------------------------------------------
	case GAMEMODE_START:
		break;
	case GAMEMODE_INTRO:
		break;
		// game running ---------------------------------------------------------
	case GAMEMODE_GAMERUN:
		//cheat
		if (IsKeyDown(DIK_Q))
		{
			world->Simon->postX += 500;
		}
		if (world->Simon->onStair <= 0) // truong hop chua leo cau thang
		{
			if (IsKeyDown(DIK_DOWN))
			{
				if (world->Simon->onStair == 0)
				{
					world->Simon->Down(-1);
					return;
				}

				//-- trang thai khong lien quan den cau thang
				if (IsKeyDown(DIK_LEFT))
				{
					world->Simon->isRight = false;
				}
				else if (IsKeyDown(DIK_RIGHT))
				{
					world->Simon->isRight = true;
				}
				world->Simon->Move(0, _DeltaTime);
				world->Simon->Down(1);
			}
			else // khong nhan phim DOWN
			{
				//truong hop nhan phim UP
				if (IsKeyDown(DIK_UP))
				{
					if (world->Simon->onStair == 0)
					{
						if (world->Simon->stairType == STAIR_UPLEFT || world->Simon->stairType == STAIR_UPRIGHT)
						{
							world->Simon->onStair = 1;
							world->Simon->MovingOnStair(1);

							return;
						}
					}

				}

				//cac trang thai ngoai cau thang
				world->Simon->Down(0);
				if (IsKeyDown(DIK_LEFT))
				{
					if (world->Simon->ChangingScene > 0)
						return;
					world->Simon->Move(-1, _DeltaTime);
				}
				else if (IsKeyDown(DIK_RIGHT))
				{
					if (world->Simon->ChangingScene > 0)
						return;
					world->Simon->Move(1, _DeltaTime);
				}
				else
				{
					if (world->Simon->ChangingScene == 0)
						world->Simon->Move(0, _DeltaTime);
				}

			}
		}
		else // truong hop dang leo cau thang
		{
			if (IsKeyDown(DIK_UP))
			{
				world->Simon->MovingOnStair(1);
			}
			if (IsKeyDown(DIK_DOWN))
			{
				world->Simon->MovingOnStair(-1);
			}
			world->Simon->MovingOnStair(0);
		}


		break;
	default:
		break;
	}
}


void MainGame::OnKeyDown(int KeyCode)
{

	switch (screenMode)
	{
		// start screen
	case GAMEMODE_START://------------------------------------------------
	{
		if (KeyCode == DIK_RETURN)
		{
			NextIntro();
		}
	}
	break;
	// intro
	case GAMEMODE_INTRO:
		break;
		// game running
	case GAMEMODE_GAMERUN:// -------------------------------------------------
	{
		switch (KeyCode)
		{
		case DIK_S:  //Chỉ nhảy khi vừa nhấn, nhấn giữ không có tác dụng
			world->Simon->Jump();
			break;
		case DIK_A:
		{

			if (IsKeyDown(DIK_UP))
			{
				world->Simon->ActivateWeapon();
			}
			else
				world->Simon->Attack();
			break;
		}
		case DIK_UP:
		{
				break;
		}
		case DIK_TAB:
			srand(time(NULL));
			int randomTemp = rand() % 5 + 36;					//	(b-a+1) + a         (random từ a -> b) 
			world->Simon->subWeapon = randomTemp;
			break;
		}
	}
	break;
	// ------------------------------------------------------

	default:
		break;
	}
}


MainGame::~MainGame()
{

}



void MainGame::NextIntro()
{
	timerIntro = 9.0f;

	statusZone1 = "";
	statusZone2 = "";

	intro->isActive = true;

	world->Simon->Init(530, 78);

	this->screenMode = GAMEMODE_INTRO;
	UpdateIntro(0.0f);


}

void MainGame::UpdateBoard()
{
	world->UpdateBoard();
	statusZone1 = world->status1;
	statusZone2 = world->status2;
}

