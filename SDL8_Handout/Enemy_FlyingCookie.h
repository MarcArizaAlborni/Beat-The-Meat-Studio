#ifndef __ENEMY_FLYING_COOKIE_H__
#define __ENEMY_FLYING_COOKIE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_FlyingCookie : public Enemy
{
private:
	float wave = -3.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	Path pathcookie;
	fPoint speedcookie;
	uint frames;
	Step steps;

public:

	Enemy_FlyingCookie(int x, int y);

	void Move();
};

#endif // __ENEMY_FLYING_COOKIE_H__