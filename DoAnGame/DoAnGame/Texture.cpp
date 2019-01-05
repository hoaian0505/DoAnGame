#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#include "Texture.h"

Texture::Texture(LPD3DXSPRITE SpriteHandler,LPCSTR FilePath)
{
	texture = NULL;

	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		return;
	}

	LPDIRECT3DDEVICE9 d3ddevice;
	SpriteHandler->GetDevice(&d3ddevice);

	result = D3DXCreateTextureFromFileEx(
		d3ddevice,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),				//Mau chi ra trong suot
		&info,
		NULL,
		&texture);

	if (result != D3D_OK)
	{
		return;
	}
}

Texture::~Texture()
{
	texture->Release();
}