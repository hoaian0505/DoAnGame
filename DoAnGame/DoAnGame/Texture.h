#pragma once
#include <unordered_map>
#include <d3dx9.h>

using namespace std;


class Texture
{
public:
	LPDIRECT3DTEXTURE9 texture;

	Texture(LPD3DXSPRITE SpriteHandler,LPCSTR FilePath);

	~Texture();

};