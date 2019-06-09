#ifndef __MODULESCENERYU_H__
#define __MODULESCENERYU_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleSceneRyu : public Module
{
public:
	ModuleSceneRyu();
	~ModuleSceneRyu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Rect ground;
	SDL_Rect foreground;
	SDL_Rect background;
	SDL_Rect castle;
	SDL_Rect healthbar;
	SDL_Rect health;
	SDL_Rect health2;
	SDL_Rect name;
	SDL_Rect name2;
	SDL_Rect score;
	SDL_Rect timer;
	Animation cartel;


	
	
	int damage = 10;
	float background_pos;
	bool forward;
};

#endif // __MODULESCENERYU_H__