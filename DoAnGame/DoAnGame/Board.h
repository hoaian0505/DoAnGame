#ifndef _Board_H_
#define _Board_H_

#include "GameObject.h"
#include "Game.h"
#include "Player.h"

class Board :
	public GameObject
{
public:
	Sprite* statusBar;
	Sprite* statusboard;
	
	int _ScreenWidth = SCREENWIDTH;		//base on Game.h
	int _ScreenHeight = SCREENHEIGHT;	//base on Game.h

	Board(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Board();
	bool firstShow;
	virtual void Load(int curHealth, int curEnemy);
	string convertScoreFormat(int score);
	string convertTimeFormat(int timeUI);
	string convertHeartFormat(int digit);

	virtual void CollisionObject(float _DeltaTime);
};

#endif // !_BOARD_H_