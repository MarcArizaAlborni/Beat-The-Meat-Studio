#pragma once
#ifndef __MODULEICOINSCREEN_H__
#define __MODULEICOINSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleIcoinScreen : public Module
{
public:
	ModuleIcoinScreen();
	~ModuleIcoinScreen();

	bool Start();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect icoin_screen;
	SDL_Rect *cur_anim;
	Animation small_turn;
	Animation big_turn;
	Animation horitzontal_dis;


};

#endif // __MODULEICOINSCREEN_H__#pragma once
