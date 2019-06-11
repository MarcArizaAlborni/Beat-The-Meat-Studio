#pragma once
#ifndef __MODULELOSESCREEN_H__
#define __MODULELOSESCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleLoseScreen : public Module
{
public:
	ModuleLoseScreen();
	~ModuleLoseScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Uint32 timeLimitL = 0;
	Uint32 deltaTimeL = SDL_GetTicks() / 1000;;
	Uint32 startTimeL = 0;

	SDL_Texture* graphics = nullptr;
	SDL_Rect lose_screen;

};

#endif // __MODULELOSESCREEN_H__