#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 50

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_PLAYER,
	COLLIDER_PLAYER2,
	
	COLLIDER_PLAYER_ATTACK,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_PLAYER2_ATTACK,
	COLLIDER_PLAYER2_SHOT,
	COLLIDER_PLAYER_BLOCK,
	COLLIDER_PLAYER2_BLOCK,
	COLLIDER_MAX
};
enum ATTACK_TYPE 
{
	NOATTACK,
	SFLP,
	SFMP,
	SFHP,
	SFLK,
	SFMK,
	SFHK,
	SCLP,
	SCMP,
	SCHP,
	SCLK,
	SCMK,
	SCHK,
	CLP,
	CMP,
	CHP,
	CLK,
	CMK,
	CHK

};



struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	ATTACK_TYPE attack;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type,  ATTACK_TYPE attack, Module* callback = nullptr ) :
		rect(rectangle),
		type(type),
		attack(attack),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type,  ATTACK_TYPE attackModule , Module* callback = nullptr);
	void DebugDraw();
	bool debug = true;
private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	
};

#endif // __ModuleCollision_H__