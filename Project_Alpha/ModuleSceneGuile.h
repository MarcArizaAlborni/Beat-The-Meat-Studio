#ifndef __MODULESCENEGUILE_H__
#define __MODULESCENEGUILE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleSceneGuile : public Module
{
public:
	ModuleSceneGuile();
	~ModuleSceneGuile();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Rect plane_ground;
	SDL_Rect background;
	SDL_Rect sky;
	SDL_Rect fence;
	SDL_Rect healthbar;
	SDL_Rect health;
	SDL_Rect health2;
	SDL_Rect name;
	SDL_Rect name2;
	SDL_Rect score;
	SDL_Rect timer;
	Animation box;
	Animation left_guys;
	Animation mid_guys;
	Animation right_guys;
	

	Uint32 timeLimit = 0;
	Uint32 deltaTime = SDL_GetTicks() / 1000;;
	Uint32 startTime = 0;

	int damage = 10;
	float background_pos;
	bool forward;
};

#endif // __MODULESCENERYU_H__