#include "Board.h"
#include "Player.h"

#include <d3dx9.h>
#include <stdio.h>
#include <stdlib.h> 

Board::Board(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\bar_health.bmp");
	statusBar = new Sprite(_SpriteHandler,texture->texture, 8, 16, 4, 4);
	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\blackboard.png");
	statusboard = new Sprite(_SpriteHandler, texture->texture, 520, 80, 1, 1);
}

Board::~Board()
{

}

void Board::Load(int curHealth, int curEnemy)
{
	statusboard->Render(180 + Sprite::cameraX, 400 + Sprite::cameraY - _ScreenHeight);
	for (int i = 0; i < curHealth; i++)
	{
		statusBar->Next(0, 0);
		statusBar->Render(85 + i * 8 + Sprite::cameraX, 408 + Sprite::cameraY - _ScreenHeight);
	}
	for (int i = curHealth; i < 16; i++)
	{
		statusBar->Next(1, 1);
		statusBar->Render(85 + i * 8 + Sprite::cameraX, 408 + Sprite::cameraY - _ScreenHeight);
	}
	for (int i = 0; i < curEnemy; i++)
	{
		statusBar->Next(2, 2);
		statusBar->Render(85 + i * 8 + Sprite::cameraX, 388 + Sprite::cameraY - _ScreenHeight);
	}
	for (int i = curEnemy; i < 16; i++)
	{
		statusBar->Next(3, 3);
		statusBar->Render(85 + i * 8 + Sprite::cameraX, 388 + Sprite::cameraY - _ScreenHeight);
	}

}

string Board::convertScoreFormat(int score)
{
	if (score < 10)
		return "00000" + std::to_string(score);
	else if (score < 100)
		return "0000" + std::to_string(score);
	else if (score < 1000)
		return "000" + std::to_string(score);
	else if (score < 10000)
		return "00" + std::to_string(score);
	else if (score < 100000)
		return "0" + std::to_string(score);
	else
		return std::to_string(score);
}
string Board::convertTimeFormat(int timeUI)
{
	if (timeUI < 10)
		return "000" + std::to_string(timeUI);
	else if (timeUI < 100)
		return "00" + std::to_string(timeUI);
	else if (timeUI < 1000)
		return "0" + std::to_string(timeUI);
	else
		return std::to_string(timeUI);
}
string Board::convertHeartFormat(int digit)
{
		return "0" + std::to_string(digit);
}


//---------Collision


void Board::CollisionObject(float _DeltaTime)
{
}