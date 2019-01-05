#include "Misc.h"



// ============ COLLIDER ============


Collider::Collider()
{
	top = 0;
	bottom = 0;
	left = 0;
	right = 0;

	owner = NULL;
}


void Collider::setCollider(int _top, int _bottom, int _left, int _right)
{
	top = _top;
	bottom = _bottom;
	left = _left;
	right = _right;
}

// có 1 con trỏ đến owner (GameObject)
Collider::~Collider() {}
// mà GameObject có sẵn Destructor rồi