#include "Sprite.h"
#include "Player.h"
#include <math.h>
#include "GameObject.h"
#include "World.h"

// --------- init static ------------------
int Sprite::cameraXLeft = 64;
int Sprite::cameraXRight = 992;
int Sprite::cameraX = 64;
int Sprite::cameraY = 0;
// ----------------------------------------

void Sprite::CameraFollow(GameObject* object, float deltaTime)
{
	float distance = ((object->postX - 256) - cameraX);
	cameraX += (distance / 0.1f)*deltaTime;

	if (cameraX < cameraXLeft)
	{
		cameraX = cameraXLeft;
		return;
	}
	if (cameraX > cameraXRight)
	{
		cameraX = cameraXRight;
		return;
	}
}

// --------------------------

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPDIRECT3DTEXTURE9 tex, int Width, int Height, int Count, int SpritePerRow)
{
	_SpriteHandler = SpriteHandler;
	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;
	_Image = tex;
}


void Sprite::Render(int X, int Y)
{
	RECT srect;

	srect.left = (_Index % _SpritePerRow)*(_Width);
	srect.top = (_Index / _SpritePerRow)*(_Height);
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;

	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);


	// từ giờ viewpointX và viewpointY sẽ do các biến static quyết định, 
		//								vpx & vpy bỏ.
	D3DXVECTOR3 position(X, Y, 0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -Sprite::cameraX;
	mt._42 = Sprite::cameraY;

	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);

	_SpriteHandler->Draw(_Image, &srect, &center, &p, D3DCOLOR_XRGB(255, 255, 255));
}



void Sprite::Next(int start, int end)
{
	if (_Index < end && _Index >= start)
		_Index++;
	else
		_Index = start;
}

void Sprite::Reset()
{
	_Index = 0;
}

Sprite::~Sprite()
{
	_Image->Release();
}


/*
	Utility function to wrap LPD3DXSPRITE::Draw
*/

//===================BORING THINGS====================================

void Sprite::Render2(float X, float Y,int color)
{

	RECT srect;

	srect.left = (_Index % _SpritePerRow)*(_Width);
	srect.top = (_Index / _SpritePerRow)*(_Height);
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;


	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	D3DXVECTOR3 position(X, Y, 0);

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -Sprite::cameraX + 50;
	mt._42 = Sprite::cameraY;

	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, Y + 17, 0);
	
	_SpriteHandler->Draw(_Image, &srect, &center, &p, D3DCOLOR_XRGB(255,255,color));
}



