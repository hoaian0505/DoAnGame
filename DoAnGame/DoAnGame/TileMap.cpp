#include "TileMap.h"
#include "Misc.h"
#include "World.h"
#include "Game.h"

/*void splitString(const std::string& str, vector<int> &map, char split = ' ')
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
}*/


TileMap::TileMap(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;



	// sẵn sàng render
	texture = new Texture(_SpriteHandler, "Resources\\Map\\map1_tiled.png");
	sprite = new Sprite(_SpriteHandler,texture->texture, 32, 32, 448, 28);

	maplvl = 0;

	manager->ReadArrayFromTxt("Resources\\Map\\map1.txt", MapFake[1], ',');
	manager->ReadArrayFromTxt("Resources\\Map\\map2.txt", MapFake[2], ',');

	MapReal = MapFake[1];
	sizeMap = 0;
	startCol = 0;
	endCol = 0;
	startRow = 0;
	endRow = 0;
	color = 255;
	switchColor = false;
	timerSprite = 0;
	switchTime = 0;
}

TileMap::~TileMap() {};

void TileMap::Init(int _X, int _Y)
{

}

void TileMap::Update(const float &_DeltaTime)
{
	if (maplvl == 1)
	{
		startCol = int(Sprite::cameraX / 32) - 1;					
		endCol = startCol + int(SCREENWIDTH / 32);
		startRow = 0;
		endRow = 12;
		sizeMap = 47;
	}
	else if (maplvl == 2)
	{

		startCol = int(Sprite::cameraX / 32) - 1;					
		endCol = startCol + int(SCREENWIDTH / 32);
		if (manager->Simon->postY < 20)
		{
			startRow = 14;
			endRow = 24;
		}
		else
		{
			startRow = 3;
			endRow = 13;
		}
		sizeMap=200;

		MapReal = MapFake[2];
	}

	if (switchColor)
	{
		timerSprite += _DeltaTime;
		if (timerSprite >= ANIM_TIME/2.0f)
		{
			timerSprite = 0;
			if (color == 255)
				color = 0;
			else
				color = 255;
			switchTime++;
		}
		if (switchTime == 10)
		{
			switchColor = false;
			switchTime = 0;
		}
	}
}

void TileMap::Render()
{
	if (sizeMap != 0)
	{
		if (maplvl==1)
			if (endCol > 46)
				return;
		for (int c = startCol; c <= endCol; c++)
		{
			for (int r = startRow; r <= endRow; r++)
			{
				int i = sizeMap * r + c;
				int id = MapReal[i] - 1;
				sprite->_Index = id;
				float x = (c) * 32;
				float y;
				if (manager->Simon->postY < 20)
					y = (r - 11) * 32;
				else
					y = (r) * 32;

				sprite->Render2(x, y,color);
			}
		}
	}

}

// gọi đến hàm này khi whip đánh trúng
void TileMap::Collision()
{

}

void TileMap::Destroy()
{
	// làm cho đối tượng này biến mất
	this->isActive = false;

}


