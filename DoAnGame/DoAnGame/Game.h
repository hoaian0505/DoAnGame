
#pragma once
#pragma warning
////////////////////////////////////////////////////////
// -Class này cài đặt các xử lý khi game chạy, gồm:
//		+ Khai báo, cài đặt DirectX 
//		+ Cài đặt DInput
//		+ Đăng kí lớp cửa sổ, tạo Hwnd, các thuộc 
//		tính màn hình,...
//		+ Game Time
////////////////////////////////////////////////////////

#ifndef _GAME_H_
#define _GAME_H_

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dxerr.h>
#include <dsound.h>
#include <string>
#include "ThamSo.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#define KEYBOARD_BUFFER_SIZE 1024




#define KEY_DOWN(code) ( IsKeyDown(code) )
class Game
{




public:
	LPD3DXSPRITE spriteHandler = NULL;
	LPDIRECT3DDEVICE9 d3ddevice;

	//Doi tuong direct3d de load hinh anh
	LPDIRECT3D9 d3d;

	LPDIRECT3DSURFACE9 backbuffer;
	LPDIRECT3DSURFACE9 surface;


	//Doi tuong direct input de nhap input
	LPDIRECTINPUT8 directinput;
	LPDIRECTINPUTDEVICE8 keyboard;

	BYTE keystate[256];							// Trang thai phim
	DIDEVICEOBJECTDATA _KeyEvents[1024];		//Du lieu su kien phim



	//Bien dung cho Game time
	DWORD _DeltaTime;							//Thoi gian tu frame truoc den frame nay
	//DWORD _SleepTime;			// failed on using GetTickCount()
	int _FrameRate;								//Thuong la 30 hinh/giay

	//Cac thuoc tinh man hinh
	int _IsFullScreen;
	int _ScreenWidth;
	int _ScreenHeight;

	//Dùng đăng kí cửa sổ
	HINSTANCE _hInstance;
	HWND _hWnd;
	LPCSTR _Name;

	//Tạo font, dùng hiện chữ
	ID3DXFont *smallFont;
	ID3DXFont *largeFont;
	RECT recZone1;
	RECT recZone2;

	std::string statusZone1;
	std::string statusZone2;


	Game() {}
	Game(HINSTANCE hInstance, LPCSTR Name, int IsFullscreen, int FrameRate);
	~Game();

	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



	//---------Hàm cài đặt------------
	void Init();					//Cai dat toan bo game (gom window, directx,...)
	void _InitWindow();
	void _InitDirectX();
	void _InitKeyboard();
	void _InitFont();



	//-----Chay game
	void Run();						//Chạy game
	void _ProcessKeyBoard();		//Xử lý bàn phím
	int IsKeyDown(int KeyCode);		//Phím có đang nhấn không 

	//--------Hàm ảo, cài đặt cụ thể trong lớp của từng đối tượng
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void Update(float _DeltaTime);
	virtual void UpdateFrame(float _DeltaTime);
	virtual void Render(LPDIRECT3DDEVICE9 d3ddv);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv);//, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float _DeltaTime);



	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

};
#endif
