#ifndef _VamBat_H_
#define _VamBat_H_

#include "GameObject.h"
//---------------////
#define TIMEPAUSEBOSS 6.0f
#define PAUSINGBOSS 7.05f
#define ATTACKSIMONTIME 7.5f

class VamBat :
	public GameObject

{
public:
	int healthBoss;
	float timeActive;
	float timePause;
	bool BossTime;
	bool AttackSimon;
	float timeAttackSimon;

	VamBat();
	VamBat(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~VamBat();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void CollisionObject(float _DeltaTime);

	virtual void Dead();
	virtual void CheckActive();
};
#endif // !_VamBat_H_

