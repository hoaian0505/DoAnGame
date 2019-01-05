#pragma once
#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_

#define GAMEMODE_START 0
#define GAMEMODE_INTRO 1
#define GAMEMODE_GAMERUN 2

#include "Game.h"
#include "World.h"
#include "ThamSo.h"
#include "GameObject.h"
#include "startscreen.h"
#include "Intro.h"

class MainGame :public Game
{
public:
	MainGame() {}
	MainGame(HINSTANCE hInstance, LPCSTR Name, int IsFullScreen, int FrameRate);
	~MainGame();

	LPD3DXSPRITE _SpriteHandler;		//Dung truyen vao spritehandler cua class Sprite

	// cinematics
	Startscreen* startscreen;
	Intro* intro;

	vector<int> Object;
	// -----------

	// manage level
	int screenMode;
	float timerIntro;
	void NextLevel();
	void NextIntro();
	// --------
	// ============---------------

	World *world;


	// UI
	bool gateIn;



protected:
	virtual void UpdateBoard();
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddevice);
	// ---------------------------
	virtual void Update(float _DeltaTime);
	virtual void UpdateStartScreen(float _DeltaTime);
	virtual void UpdateIntro(float _DeltaTime);
	virtual void UpdateGame(float _DeltaTime);
	// -----------------------------
	virtual void Render(LPDIRECT3DDEVICE9 d3ddevice);
	virtual void RenderStartScreen();
	virtual void RenderIntro(LPDIRECT3DDEVICE9 d3ddv);
	virtual void RenderGame(LPDIRECT3DDEVICE9 d3ddv);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float _DeltaTime);
	// -------------------------------

	virtual void OnKeyDown(int KeyCode);

};

#endif