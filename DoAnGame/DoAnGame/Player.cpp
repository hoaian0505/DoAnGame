#include "Player.h"
#include "World.h"
#include "Game.h"

// === CONSTRUCTOR === DESTRUCTOR ===
Player::Player(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = PLAYER_TYPE;
	
	sizeWidth = 64;
	sizeHeight = 64;

	isRight = true;
	isJump = false;
	isAttack = false;
	isChangeFrame = false;
	isMoveToX = false;
	isUsingWeapon = false;
	atePotion = false;

	onStair = -1;
	stairMoveKey = 0;
	isClimTime = false;
	atePotion = false;
	TempPostX = 0;
	typeZone = 0;

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\simon_left.bmp");
	usualLeft = new Sprite(_SpriteHandler,texture->texture, 64, 64, 27, 6);

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\simon_right.bmp");
	usualRight = new Sprite(_SpriteHandler, texture->texture, 64,64, 27, 6);

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\simon_potion_left.bmp");
	potionLeft = new Sprite(_SpriteHandler, texture->texture, 64, 64, 27, 6);

	texture = new Texture(_SpriteHandler, "Resources\\Sprites\\simon_potion_right.bmp");
	potionRight = new Sprite(_SpriteHandler, texture->texture, 64, 64, 27, 6);

	spriteLeft = usualLeft;
	spriteRight = usualRight;
	sprite = spriteRight;

	heart = 30;
	health = 16;
	score = 0;
	P = 3;
	timeUI = 500;
	ChangingScene = 0;
	subWeapon = 0;

	//Collider
	collider = new Collider();
	collider->setCollider(24, -32, -14, 14);

	PostXMax = 500;

	TempDoor = 1;

	thoiGianBatTu = 0;
}


Player::~Player()
{
	if (spriteLeft != NULL)
	{
		delete spriteLeft;
	}
	if (spriteRight != NULL)
	{
		delete spriteRight;
	}
}

// ===== VIRTUAL =====
void Player::Init(int _X, int _Y)
{
	subWeapon = 0;

	// main init
	isActive = true;
	isRight = true;
	isJump = false;
	isAttack = false;
	isUsingWeapon = false;
	isChangeFrame = false;
	isHitted = false;
	isImmortal = false;
	isImmortal2 = false;
	isMoveToX = false;
	onStair = -1;
	stairMoveKey = 0;
	isClimTime = false;
	isClimbingUp = true;
	typeZone = 0;

	postX = _X;
	postY = _Y;


}


void Player::Render()
{

		sprite->Render(postX, postY);
		
		if (isAttack)
			{
				if (velocityY != 0)
					manager->whip->Render(postX, postY);
				else
					manager->whip->Render();
			}
				
		switch (subWeapon)
		{
		case AXE:
			manager->axe->RenderCamera();
			break;
		case KNIFE:
			manager->knife->RenderCamera();
			break;
		case BOOMERANG:
			manager->boomerang->RenderCamera();
			break;
		case HOLYWATER:
			manager->holyWater->RenderCamera();
			break;
		case CLOCK:
			manager->clock->RenderCamera();
			break;
		}
}



void Player::Destroy()
{
	//weaponLevel = 0;
	manager->whip->whipLevel = 0;
	subWeapon = 0;

	// init lại các giá trị ban đầu
	heart = 30;
	health = 16;
	P--;
	if (P < 0)
		P = 0;
	//score = 0;
	
	// trở lại trạng thái tại checkpoint
	postX = checkpointX;
	postY = checkpointY;
	velocityX = 0;
	velocityY = 0;


}


// ---=== UPDATE ===---

void Player::Update(const float &_DeltaTime)
{
	if (postY < 20)
	{
		Sprite::cameraY = 96;
		Sprite::cameraXRight = savedCamXRight+32;
	}
	else
	{
		Sprite::cameraY = 448;
		if (Sprite::cameraXRight > 3000)
			Sprite::cameraXRight = savedCamXRight;
	}

	if (ChangingScene > 0)
	{
		UpdateWhenChangingScene(_DeltaTime);
		return;
	}

	timeUI -= _DeltaTime;
	if (timeUI <= 0)
	{
		timeUI = 0;
		Destroy();
		timeUI = 500;
	}



		if (isJump)
		{
			UpdateWhenJumping(_DeltaTime);
		}



	if (onStair <= 0)
	{

		if (isAttack)
		{
			UpdateWhenAttack(_DeltaTime);
		}
		else
		{
			isChangeFrame = false;
		}
	}
	else
	{
		velocityX = 0;
		velocityY = 0;

		//dang tan cong
		if (isAttack || isUsingWeapon)
		{
			UpdateWhenAttackOnStair(_DeltaTime);
		}
		else
		{
			isChangeFrame = false;
		}
	}

	if (isHitted)
	{
		timeImmortal = 0;
	}

	if (isImmortal)
	{
			timeImmortal += _DeltaTime;
			if (timeImmortal > thoiGianBatTu)
			{
				isImmortal = false;
				isHitted = false;
			}
	}


	if (!isImmortal)
	{
		spriteLeft = usualLeft;
		spriteRight = usualRight;
		if (isRight)
			sprite = usualRight;
		else
			sprite = usualLeft;
	}

	Sprite::CameraFollow(this, _DeltaTime);
	if (postX < (Sprite::cameraXLeft + 15))
		postX = Sprite::cameraXLeft + 15;
	if (postX > (Sprite::cameraXRight + PostXMax))
		postX = Sprite::cameraXRight + PostXMax;

	if (isMoveToX)
	{
		UpdateWhenMoveToPossionX(_DeltaTime);
		return;
	}
	if (onStair <= 0)
			velocityY -= 600 * _DeltaTime;
	else
		UpdateWhenOnStair(_DeltaTime);

	CollisionObject(_DeltaTime);

	if (isAttack && !isJump)
	{
	}
	else
		postX += (velocityX * _DeltaTime);
	postY += velocityY * _DeltaTime;


}

void Player::Move(int moveKey, const float &_DeltaTime)

{
	if (isHitted)
		return;
	if (isJump)
		return;
	if (isAttack)
		return;

	{
		switch (moveKey)
		{
		case -1:
			velocityX = -150;
			isRight = false;
			sprite = spriteLeft;

			break;
		case 1:
			velocityX = 150;
			isRight = true;
			sprite = spriteRight;

			break;
		default:
			velocityX = 0;
			sprite->Next(0, 0);
			break;
		}

		if (velocityX != 0)
		{
			timerSprite += _DeltaTime;
			if (timerSprite > ANIM_TIME)
			{
				timerSprite -= ANIM_TIME;
				sprite->Next(0, 3);
			}
		}
	}
}

void Player::Jump()
{
	if (onStair == 1)
		return;
	if (isHitted)
		return;
	if (ChangingScene > 0)
		return;
	if (isJump)
		return;
	if (isAttack)
		return;
	if (isCrouch)
		return;
	isJump = true;
	sprite->_Index = 4;
	velocityY = 320;
	
}

void Player::Attack()
{
	if (isHitted)
		return;
	if (ChangingScene > 0)
		return;
	//truong hop dang danh ma nhan phim danh
	if (isAttack || isUsingWeapon)
		return;
	if (isClimTime)
		return;


	//danh hop le
	isAttack = true;

	//normal attack
	if (onStair <= 0)
	{
		//kiem tra co dang ngoi khong?
		if (isCrouch)
			sprite->_Index = 14;
		else
			sprite->_Index = 11;

		timerSprite = 0;
	}
	//tấn công khi đang leo cầu thang
	else
	{
		//kiểm tra Player đang leo lên hay đi xuống
		if (isClimbingUp)
			sprite->_Index = 20;
		else
			sprite->_Index = 17;

		timerSprite = 0;
	}

	//if (!isUsingWeapon)
		manager->whip->Init(postX, postY);
}

void Player::Down(int downkey)
{
	if (isHitted)
		return;
	if (ChangingScene > 0)
		return;
	if (isJump)
	{
		return;
	}
	if (isAttack)
	{
		return;
	}

	//truong hop nhan nut xuong khi dang o dau cau thang di xuong
	if (downkey == -1)
	{
		if (stairType == STAIR_DOWNLEFT || stairType == STAIR_DOWNRIGHT)
		{
			onStair = 1;
			MovingOnStair(-1);
			return;
		}
	}

	if (downkey == 0)
	{
		isCrouch = false;
	}
	else
	{
		isCrouch = true;
		if (isRight)
			sprite = spriteRight;
		else
			sprite = spriteLeft;
		sprite->_Index = 4;
	}
}

void Player::Injured()
{

	if (isRight)
		velocityX = -70;
	else
		velocityX = 70;
	
	// thời gian bất tử tối đa đc set
	thoiGianBatTu = ANIM_TIME * 10;

	// mất máu
	health -= 2;
	// còn ít máu quá thì tèo
	if (health <= 0)
	{
		health = 0;
		Destroy();
	}
	//Chuyển Sprite sang bất tử
	spriteRight = potionRight;
	spriteLeft = potionLeft;
	if (isRight)
		sprite = potionRight;
	else
		sprite = potionLeft;
	
	//-------------
	sprite->_Index = 9;
	velocityY = 150;
	isHitted = true;
	isImmortal = true;

	onStair = -1;
	stairMoveKey = 0;
	isClimTime = false;
	isCrouch = false;
	isAttack = false;
	isChangeFrame = false;
}

void Player::MovingOnStair(int keyMove)
{
	if (isJump  || isHitted)
	{
		onStair = 0;
		isMoveToX = false;
		return;
	}
	if (isAttack || isUsingWeapon)
	{
		return;
	}
	if (isClimTime)
		return;
	stairMoveKey = keyMove;
	if (stairMoveKey != 0)
	{
		if (keyMove == 1)
			isClimbingUp = true;
		else
			isClimbingUp = false;
		timeStairAnim = 0;
		isClimTime = true;
	}

	if (TempPostX != 0)
		postX = TempPostX;
}


// ==============================================================
// ==============================================================

// =================UPDATE HERE======================

// ==============================================================
// ==============================================================

void Player::UpdateWhenAttackOnStair(float _DeltaTime)
{
	timerSprite += _DeltaTime;

	//truong hop đang đi lên
	if (isClimbingUp)
	{
		isChangeFrame = false;
		if (timerSprite >= ANIM_TIME/1.5f)
		{
			timerSprite -= ANIM_TIME/1.5f;
			sprite->Next(21, 23);
			isChangeFrame = true;
			if (!isUsingWeapon)
				manager->whip->Update(_DeltaTime);
		}
		if (sprite->_Index == 23)
		{
			isChangeFrame = false;
			isAttack = false;
			isUsingWeapon = false;
			sprite->_Index = 7;
			if (!isUsingWeapon)
				manager->whip->Disappear();
		}
	}
	else // trường hợp đang đi xuống
	{
		isChangeFrame = false;
		if (timerSprite >= ANIM_TIME/1.5f)
		{
			timerSprite -= ANIM_TIME/1.5f;
			sprite->Next(18, 20);
			isChangeFrame = true;
			if (!isUsingWeapon)
				manager->whip->Update(_DeltaTime);
		}
		if (sprite->_Index == 20)
		{
			isChangeFrame = false;
			isAttack = false;
			sprite->_Index = 5;
			isUsingWeapon = false;
			if (!isUsingWeapon)
				manager->whip->Disappear();
		}
	}
}


void Player::UpdateWhenOnStair(float _DeltaTime)
{
	velocityX = 0;
	velocityY = 0;
	if (stairMoveKey == 0)
	{
		isClimTime = false;
		return;
	}
	else // truong hop di chuyen
	{
		timeStairAnim += _DeltaTime;
		if (timeStairAnim >= ANIM_TIME / 1.1f)
		{
			timeStairAnim -= ANIM_TIME / 1.1f;

			//truong hop nhan phim len
			if (stairMoveKey == 1)
			{
				// neu dang o cau thang nghieng ben phai "/"
				if (stairType == STAIR_UPRIGHT || stairType == STAIR_DOWNLEFT)
				{
					sprite = spriteRight;
					isRight = true;
					sprite->Next(6, 7);
					postX += 8;
					postY += 8;
					if (sprite->_Index == 7)
						isClimTime = false;
				}
				// neu dang o cau thang nghieng ben trai "\"	
				else
				{
					sprite = spriteLeft;
					isRight = false;
					sprite->Next(6, 7);
					postX -= 8;
					postY += 8;
					if (sprite->_Index == 7)
						isClimTime = false;
				}
			}

			//truong hop bam phim xuong
			else
			{
				// neu dang o cau thang nghieng ben phai "/"
				if (stairType == STAIR_UPRIGHT || stairType == STAIR_DOWNLEFT)
				{
					sprite = spriteLeft;
					isRight = false;
					sprite->Next(6,7);
					if (sprite->_Index == 7)
						sprite->_Index = 5;
					postX -= 8;
					postY -= 8;
					if (sprite->_Index == 5)
						isClimTime = false;
				}
				// neu dang o cau thang nghieng ben trai "\"
				else
				{
					sprite = spriteRight;
					isRight = true;
					sprite->Next(6, 7);
					if (sprite->_Index == 7)
						sprite->_Index = 5;
					postX += 8;
					postY -= 8;
					if (sprite->_Index == 5)
						isClimTime = false;
				}
			}
		}

	}


}


void Player::UpdateCamera(float cameraX, float cameraY, float cameraXLeft, float cameraXRight)
{

	Sprite::cameraX = cameraX;
	Sprite::cameraY = cameraY;
	Sprite::cameraXLeft = cameraXLeft;
	Sprite::cameraXRight = cameraXRight;
	if (Sprite::cameraX < Sprite::cameraXLeft)
	{
		Sprite::cameraX = Sprite::cameraXLeft;	
	}
	else if (Sprite::cameraX > Sprite::cameraXRight)
	{
		Sprite::cameraX = Sprite::cameraXRight;
	}
}

void Player::UpdateWhenJumping(float _DeltaTime)
{
	//velocityY -= 900*_DeltaTime;
	if (!isAttack && velocityY<0)
	{
		sprite->Next(0, 0);
	}
}

void Player::UpdateWhenAttack(float _DeltaTime)
{
	timerSprite += _DeltaTime;
	if (isHitted)
		return;

	//truong hop ngoi danh
	if (isCrouch)
	{
		isChangeFrame = false;
		if (timerSprite >= ANIM_TIME / 1.5f)
		{
			timerSprite -= ANIM_TIME / 1.5f;
			sprite->Next(15, 17);
			isChangeFrame = true;
			if (!isUsingWeapon)
				manager->whip->Update(_DeltaTime);
			
		}
		if (sprite->_Index == 17)
		{
			isChangeFrame = false;
			isAttack = false;
			sprite->_Index = 4;
			isUsingWeapon = false;
			if (!isUsingWeapon)
				manager->whip->Disappear();
		}
	}
	else
	{
		isChangeFrame = false;
		if (timerSprite >= ANIM_TIME / 1.5f)
		{
			timerSprite -= ANIM_TIME / 1.5f;
			sprite->Next(12, 14);
			isChangeFrame = true;
			if (!isUsingWeapon)
				manager->whip->Update(_DeltaTime);
		}


		if (sprite->_Index == 14)
		{
			isChangeFrame = false;
			isAttack = false;
			sprite->_Index = 0;
			isUsingWeapon = false;
			if (!isUsingWeapon)
				manager->whip->Disappear();
		}
	}
}
void Player::UpdateWhenMoveToPossionX(float _DeltaTime)
{
	//nếu player đang ở tại vi tri cần đến (sai số không quá 1.0f) thì di chuyển hoàn tất
	if (postX > DestinationX - 1 && postX <= DestinationX + 1)
	{
		isMoveToX = false;
		postX = DestinationX;
		Move(0, _DeltaTime);
		if (ChangingScene > 0)
			ChangingScene++;
		
		return;
	}

	if (postX < DestinationX)
	{
		Move(1, _DeltaTime);
	}
	switch (typeZone)
	{
	case ZONE_GATE:
		postX += velocityX / 5 * _DeltaTime;
		break;
	case ZONE_DOOR:
		postX += velocityX / 2 * _DeltaTime;
		break;
	}


}

void Player::UpdateWhenChangingScene(float _DeltaTime)
{// update...
	switch (typeZone)
	{
	case ZONE_GATE:
		switch (ChangingScene)
		{
		case 1:
			isMoveToX = true;
			UpdateWhenMoveToPossionX(_DeltaTime);
			break;
		case 2:
			ChangingScene = 0;
			manager->gate->Collision(this, _DeltaTime);
			manager->Temp++;
			manager->tilemap->maplvl++;
			break;
		}
		break;
	case ZONE_DOOR:
		switch (ChangingScene)
		{

		case 1: // update camera lan 1
		{
			UpdateCamera(Sprite::cameraX + 2, Sprite::cameraY, Sprite::cameraXLeft, Sprite::cameraXRight + 2);
			if (Sprite::cameraX > manager->door[TempDoor]->postX - SCREENWIDTH / 2)
				//ChangingScene++;
			{
				manager->door[TempDoor]->Update(_DeltaTime);
			}
		}
		break;

		case 2: // hieu ung di qua cua
		{
			isMoveToX = true;
			UpdateWhenMoveToPossionX(_DeltaTime);
			break;
		}
		case 3:
		{
			manager->door[TempDoor]->Update(_DeltaTime);
			break;
		}
		case 4:	// update camera lan 2
		{
			UpdateCamera(Sprite::cameraX + 2, Sprite::cameraY, Sprite::cameraXLeft, Sprite::cameraXRight + 2);
			if (Sprite::cameraX > manager->door[TempDoor]->postX+16)
			{

				UpdateCamera(Sprite::cameraX +2 , Sprite::cameraY, Sprite::cameraX + 2, savedCamXRight);
				ChangingScene++;
			}
			break;
		}
		case 5:
		{
			TempDoor++;
			ChangingScene = 0;
			break;
		}
		}
	}
}


void Player::ActivateWeapon() 
{
	if (isHitted)
		return;
	if (ChangingScene > 0)
		return;
	//truong hop dang danh ma nhan phim danh
	if (isAttack || isUsingWeapon)
		return;
	if (isClimTime)
		return;

	if (heart > 0 && subWeapon!=0)
	{

		//kiểm tra xem weapon còn trên camera không
		if (manager->axeW->isActive)
			return;
		if (manager->knifeW->isActive)
			return;
		if (manager->boomerangW->isActive)
			return;
		if (manager->holyWaterW->isActive)
			return;
		if (manager->isPause == true)
			return;

		isUsingWeapon = true;
		isAttack = true;

		if (isCrouch)
			sprite->_Index = 14;
		else
			sprite->_Index = 11;
		timerSprite = 0;

		switch (subWeapon)
		{
		case AXE:
			manager->axeW->Init(postX, postY);
			heart--;
			break;
		case KNIFE:
			manager->knifeW->Init(postX, postY);
			heart--;
			break;
		case BOOMERANG:
			manager->boomerangW->Init(postX, postY);
			heart--;
			break;
		case HOLYWATER:
			manager->holyWaterW->Init(postX, postY);
			heart--;
			break;
		case CLOCK:
			if (heart >= 5)
			{
				manager->isPause = true;
				heart -= 5;
			}
			break;
		default:
			break;
		}
	}

}


//-------------Collision


void Player::CollisionObject(float _DeltaTime)
{
	if (onStair == 0)
		onStair = -1;
	TempPostX = 0;
	typeZone = 0;
	// -------------------------------------------------------------------------------------
	// -- MÔ HÌNH XÉT COLLISION MỚI, những cái này để ở hàm CollisionObject() trong mỗi object
	//						CollisionObject() gọi ở đầu Update() trong mỗi object
	// -------------------------------------------------------------------------------------
	float collisionScale = 0;
	GameObject* tempObject;
	

	for (int i = 1; i < 30; i++)
	{ 
		if (manager->vaCham[i]->kickHoat)
			for (int j = 0; j < manager->vaCham[i]->objects.size(); j++)
			{
				//-----------------------GROUND-----------------------------
				tempObject = manager->vaCham[i]->objects[j];
				if (tempObject->objectType==BRICK_TYPE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					//-----------TRƯỜNG HỢP LEO CẦU THANG------------
					if (collisionScale == 0.0f && velocityY != 0)
					{
						this->postY = (tempObject->postY + tempObject->collider->top - this->collider->bottom) + 1.1f;
						isJump = false;
						isHitted = false;
					}

					if (collisionScale < 1.0f)
					{							
						if (normaly > 0.1f)//chạm từ trên xuống
						{
							isJump = false;
							isHitted = false;
						}
						SlideFromGround(tempObject, _DeltaTime, collisionScale);
					}
				}

				if (!isImmortal)
				{
					if (tempObject->objectType == STAIR_UPRIGHT || tempObject->objectType == STAIR_DOWNLEFT || tempObject->objectType == STAIR_UPLEFT || tempObject->objectType == STAIR_DOWNRIGHT)
					{
						if (IsCollide(tempObject))
						{
							stairType = tempObject->objectType;
							if (!isClimTime)
							{
								onStair = 0;
								if (stairType == STAIR_UPRIGHT)
									TempPostX = tempObject->postX + 4;
								else if (stairType == STAIR_DOWNLEFT)
								{
									TempPostX = tempObject->postX - 20;

								}
								else if (stairType == STAIR_UPLEFT)
									TempPostX = tempObject->postX - 4;
								else if (stairType == STAIR_DOWNRIGHT)
								{
									TempPostX = tempObject->postX + 20;

								}
							}
						}
					}
				}

				if (tempObject->objectType == DEADWATER)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						Destroy();
					}
				}


				//-----------------ZONE-----------------------------------
				if (tempObject->objectType == ZONE_GATE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						if (ChangingScene == 0)
						{
							typeZone = manager->gate->objectType;
							DestinationX = manager->gate->postX + 64;
							ChangingScene = 1;
						}

					}
				}

				if (tempObject->objectType == ZONE_DOOR)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						typeZone = tempObject->objectType;
						DestinationX = tempObject->postX + 100;
						ChangingScene = 1;
						PostXMax = 480;
						checkpointX = tempObject->postX + 100;
						checkpointY = this->postY + 10;
						if (TempDoor == 1)
							savedCamXRight = 3620;
						else if (TempDoor == 2)
							savedCamXRight = 5158;
					}
				}

				//-----------------ITEMS----------------------------
				if (tempObject->objectType == HEART)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						heart += 1;
						tempObject->Destroy();
					}
				}

				if (tempObject->objectType == BIGHEART)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						heart += 5;
						tempObject->Destroy();
					}
				}

				if (tempObject->objectType == WHIPUPGRADE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (manager->whip->sprite->_Index == 9)
					{
						if (collisionScale < 1.0f)
						{
							if (manager->whip->whipLevel < 2)
							{
								manager->whip->whipLevel++;
								sprite->Next(23, 26);
							}
							else
								score += 100;
							tempObject->Destroy();
						}
					}
				}

				if (tempObject->objectType == GETAXE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
						if (subWeapon == AXE)
							score += 100;
						subWeapon = AXE;
					}
				}

				if (tempObject->objectType == GETCLOCK)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
						if (subWeapon == CLOCK)
							score += 100;
						subWeapon = CLOCK;
					}
				}

				if (tempObject->objectType == CHICKEN)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						if (health < 12)
							health += 5;
						else
							health = 16;
						tempObject->Destroy();
					}
				}

				if (tempObject->objectType == CROSS)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
						manager->tilemap->switchColor = true;
						//-----DESTROY ALL ENEMIES
						for (int l = 1; l < 30; l++)
						{
							if (manager->vaCham[l]->kickHoat)
								for (int m = 0; m < manager->vaCham[l]->objects.size(); m++)
								{
									tempObject = manager->vaCham[l]->objects[m];
									if (tempObject->objectType == ENEMY_TYPE)
									{
										tempObject->Destroy();
									}
								}
						}
					}
				}

				if (tempObject->objectType == GETKNIFE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
						if (subWeapon == KNIFE)
							score += 100;
						subWeapon = KNIFE;
					}
				}

				if (tempObject->objectType == GETHOLYWATER)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
						if (subWeapon == HOLYWATER)
							score += 100;
						subWeapon = HOLYWATER;
					}
				}

				if (tempObject->objectType == GETBOOMERANG)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
						if (subWeapon == BOOMERANG)
							score += 100;
						subWeapon = BOOMERANG;
					}
				}

				if (tempObject->objectType == GENIE)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
						isImmortal = true;
						thoiGianBatTu = ANIM_TIME * 40;
						spriteRight = potionRight;
						spriteLeft = potionLeft;
						if (isRight)
							sprite = potionRight;
						else
							sprite = potionLeft;
					}
				}

				if (tempObject->objectType == POWER)
				{
					collisionScale = SweptAABB(tempObject, _DeltaTime);
					if (collisionScale < 1.0f)
					{
						tempObject->Destroy();
					}
				}

				// -------------ENEMY ---------------------------------------------

				if (!isImmortal)
				{
					if (tempObject->objectType == ENEMY_TYPE)
					{
						collisionScale = SweptAABB(tempObject, _DeltaTime);
						if (collisionScale < 1.0f)
						{
							Injured();
						}
					}

					if (tempObject->objectType == BOSS_TYPE)
					{
						collisionScale = SweptAABB(tempObject, _DeltaTime);
						if (collisionScale < 1.0f)
						{
							Injured();
							manager->vamBat->AttackSimon = false;
							tempObject->velocityX = 0;
							tempObject->velocityY = 0;
						}
					}
				}
		}
	}

	tempObject = manager->brickGround;
	collisionScale = SweptAABB(tempObject, _DeltaTime);
		if (collisionScale < 1.0f)
		{
			if (normaly > 0.1f)//chạm từ trên xuống
			{
				isJump = false;
				isHitted = false;
				this->postY = (manager->brickGround->postY + manager->brickGround->collider->top - this->collider->bottom) + 0.1f;
				velocityY = 0.0f;
			}
		}
}