#ifndef _THAMSO_H_
#define _THAMSO_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdlib.h>

// class prototype
class GameObject;	// GameObject.h
class Collider;		// Misc.h
class World;		// World.h
class MainGame;		// MainGame.h
class Sprite;		// Sprite.h

class Player;




#define SCREENWIDTH 512
#define SCREENHEIGHT 448
// ===== --- GAME OBJECT --- =====
#define PLAYER_TYPE 1
#define PROJECTILE_TYPE 2
#define EFFECT_TYPE 3
#define ITEM_TYPE 4
#define ENEMY_TYPE 5
#define DESTRUCTIBLE_TYPE 6
#define GROUND_TYPE 7
#define STAIR_TYPE 8
#define ZONE_TYPE 9
#define ENEMY_TYPE 11
#define DOOR_TYPE 12
#define BRICK_TYPE 13
#define DEADWATER 14
#define ZONE_GATE 15
#define ZONE_DOOR 16
#define EFFECT_TYPE 42
#define WEAPON_TYPE 41

// ===== --- STAIR --- ===== 
#define STAIR_UPRIGHT 17
#define STAIR_UPLEFT 18
#define STAIR_DOWNRIGHT 19
#define STAIR_DOWNLEFT 20

// ==== ---- BOSS --- =====
#define BOSS_TYPE 21

// ===== --- PROJECTILE --- ===== 
#define HEART 24
#define BIGHEART 25
#define WHIPUPGRADE 26
#define GETKNIFE 27
#define GETAXE 28
#define GETHOLYWATER 29
#define GETCLOCK 30
#define GETBOOMERANG 31
#define CROSS 32
#define GENIE 33
#define CHICKEN 34
#define POWER 35

// ===== ---- WEAPON ----- =========
#define AXE 36
#define CLOCK 37
#define KNIFE 38
#define HOLYWATER 39
#define BOOMERANG 40

//---------------////
#define TIMEPAUSE 3.0f
#define TIMEWIN 4.0f

#endif // !_THAMSO_H_
