#include "Application.h"
#include "Enemy_FlyingCookie.h"
#include "ModuleCollision.h"
#include "Path.h"
#include "Animation.h"

Enemy_FlyingCookie::Enemy_FlyingCookie(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 5,72,21,22 });
	
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_FlyingCookie::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	
	pathcookie.PushBack(speedcookie, steps.frames, steps.animation);
	//position.x -= position.x * 0.5;
	if (position.y <= 50) {
		position.x -= 0.5;
		position.y -= 0.5;
	}

	/*if (position.y > 50) {

		position.x += 0.5;
		position.y += 0.5;


	}*/

	
	
}
