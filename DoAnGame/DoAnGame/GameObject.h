//======= GAMEOBJECT ========
// cho kế thừa muôn nơi
// --------- update K_1.3

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <d3dx9.h>
#include "Sprite.h"
#include "Misc.h"
#include "Texture.h"

#include <cstdlib>
#include <ctime>


using namespace std;

//#include <math.h>

#define PLAYER_TYPE 1

#define ANIM_TIME 0.15f
#define ITEM_TIME 2.5f
#define BOSS_TIME 6.0f

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

#define PI 3.141592f
#define val PI/180



class GameObject
{
public:
	// các biến
	World *manager;
	LPD3DXSPRITE spriteHandler;
	bool isActive;
	int objectType;

	int sizeWidth;
	int sizeHeight;

	Texture *texture;
	Sprite *sprite;
	float timerSprite;

	Collider *collider;

	float postX;
	float postY;
	float velocityX;
	float velocityY;



	// ------ bo sung K_1.3 --- xét va chạm
	float normalx;	// "vector pháp tuyến" said thầy Dũng
	float normaly;

	Collider *BroadPhaseBox;
	float collisionTimeScale;
	// ----- đây là game đơn luồng => các hàm chạy tuần tự
	// ----------------------- => xài chung 1 biến là được rồi.


	// constructor và destructor
	GameObject();
	virtual ~GameObject();

	// ====== CÁC HÀM CHÍNH ======
	// ------ bo sung K_1.3

	// xét coi có va chạm ko
	bool IsCollide(GameObject* target);
	bool IsInside(GameObject* target);
	//ham kiem tra doi tuong co nam trong camera hay khong
	bool IsInCamera();

	float SweptAABB(GameObject *target, const float &_DeltaTime);


	// ====== các phương thức ảo =====
	virtual void Init(int _X, int _Y);		// reset object
	virtual void Update(const float &_DeltaTime);	// update per frame
	virtual void Render();							// render per frame
	virtual void Destroy();					// clear sub object, without delete this




	//Collider


	virtual void CollisionObject(GameObject *target, const float &_DeltaTime);	// xét có va chạm không, nếu có thì xử lý

	//---------Va chạm với tường
	void ResponseFrom(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale);
	void DeflectFrom(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale);
	void SlideFromGround(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale);
};



#endif