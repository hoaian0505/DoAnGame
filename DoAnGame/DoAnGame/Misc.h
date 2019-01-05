#ifndef _MISC_H_
#define _MISC_H_

#include "ThamSo.h"

// ========= COLLIDER ===========
class Collider
{
public:
	// các biến
		// trục Y hướng lên
	float top;	// luôn > 0
	float bottom;	// luôn < 0

		// trục X hướng qua phải
	float left;	// luôn < 0
	float right;	// luôn > 0

	GameObject *owner;

	//Khởi tạo và huỷ
	Collider();

	~Collider();

	void setCollider(int _top, int _bottom, int _left, int _right);
};

#endif // !_MISC_H_
