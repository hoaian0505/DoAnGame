#ifndef _TileMap_H_
#define _TileMap_H_

#include "ThamSo.h"
#include "GameObject.h"
#include <d3dx9.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <ddraw.h>

class TileMap : public GameObject
{
public:
	LPD3DXSPRITE spriteHandler;
	int maplvl;
	int sizeMap;
	int startCol;
	int endCol;
	int startRow;
	int endRow;
	vector<int> MapFake[3];
	vector<int> MapReal;
	int color;
	bool switchColor;
	int switchTime;

	TileMap(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~TileMap();


	virtual void Init(int _X, int _Y);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	virtual void Update(const float &_DeltaTime);
};

#endif
