#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_



#include "GameObject.h"

class Player :
	public GameObject
{
public:
	float timeUI;



	//cac bien kiem soat trang thai
	bool isRight;	//trang thai quay sang phai
	bool isAttack;  //trang thai danh
	bool isJump;	//trang thai nhay 
	bool isCrouch;  //trang thai ngoi
	bool isHitted;	//trang thai bị thương
	bool isChangeFrame;		//trang thai bat tu
	int ChangingScene; // bien thu tu cac hanh dong khi chuyen scene
	bool isUsingWeapon;
	bool isImmortal;	// bất tử
	bool isImmortal2;

	bool isMoveToX;		//biến xác định trạng thái simon bị chuyển đến vị trí X
	float DestinationX;		// đích đến của Simon khi bị chuyển đến 1 vị trí xác định
	float timeImmortal;		//thoi gian bat tu
	float thoiGianBatTu;   //Thoi gian bat tu tối đa

	// stair direction key
	int onStair; //< -1 nếu không ở gần cầu thang >; < 0 nếu ở đầu cầu thang > < 1 nếu đang trong cầu thang >
	int stairType; // loại cầu thang mà Player đang đứng
	int stairMoveKey; // Lệnh điều khiển chuyển động trên cầu thang < -1 đi xuống>; < 0 đứng yên >; < 1 đi lên >
	bool isClimbingUp; // xác đinh Player có phải đang đi lên hay không?
	float timeStairAnim; // biến tính thời gian để chuyển sprite
	bool isClimTime; // xác định Player đang thực hiện  1 động tác đi cầu thang
	int TempPostX; //vị trí cầu thang chuẩn xác

	int PostXMax; //Vị trí tối đa của Simon trong SCreen
	int TempDoor; //va chạm với door thứ mấy
	//ZONE
	int typeZone;

	Sprite *spriteLeft;
	Sprite *spriteRight;
	Sprite *potionLeft;
	Sprite *potionRight;
	Sprite *usualLeft;
	Sprite *usualRight;
	bool atePotion;


	int P;				// Số mạng 
	int heart;			// số trái tim (số lượng đạn)
	int score;
	int health;			// chừng nào mất 1 mạng (P)
	int subWeapon;


	// dùng cho việc hồi sinh
	int checkpointX;
	int checkpointY;
	int savedCamXLeft;
	int savedCamXRight;
	int savedCamY;

	// constructor & destructor
	Player(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Player();


	// virtual function
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();

	//hàm update vị trí camera
	void UpdateCamera(float cameraX, float cameraY, float cameraXLeft, float cameraXRight);

	// input function
	// Khi có input từ bàn phím => gọi các hàm này
	// nhấn giữ
	void Move(int moveKey, const float &_DeltaTime);// -1 <-    0      1 ->
	void Down(int downkey);


	// nhấn 1 lần
	void Jump();
	void Attack();
	void ActivateWeapon();
	void Injured();
	void MovingOnStair(int keyMove);

	// các hàm update các trạng thái của simon
	void UpdateWhenJumping(float _DeltaTime);
	void UpdateWhenMoveToPossionX(float _DeltaTime);
	void UpdateWhenAttack(float _DeltaTime);
	void UpdateWhenChangingScene(float _DeltaTime);
	void UpdateWhenAttackOnStair(float _DeltaTime);
	void UpdateWhenOnStair(float _DeltaTime);

	//Collider
	virtual void CollisionObject(float _DeltaTime);


};

#endif
