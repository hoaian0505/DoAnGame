#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <unordered_map>
#include <d3d9.h>
#include <d3dx9.h>
#include "ThamSo.h"

using namespace std;



class Sprite
{

protected:

	
	LPDIRECT3DTEXTURE9 _Image;
	LPD3DXSPRITE _SpriteHandler;

	int _Width;								// Sprite width
	int _Height;							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row
public:
	// bien index, da bi di doi sang public
	int _Index;								// Current sprite index, [0,n-1]

	// ==== CÁC BIẾN STATIC ======
	static int cameraXLeft;
	static int cameraXRight;
	static int cameraX;
	static int cameraY;

	// update Camera
	static void CameraFollow(GameObject* object, float deltaTime);
	//================================
	

	//==================================

	Sprite(LPD3DXSPRITE SpriteHandler, LPDIRECT3DTEXTURE9 tex, int Width, int Height, int Count, int SpritePerRow);
	void Next(int start, int end);
	void Reset();

	// Render current sprite at location (X,Y) at the target surface
	void Render(int X, int Y);
	~Sprite();



	//Boring Things -----------------------------------------------------------------------
	void Render2(float x, float y,int color);

};

	
#endif