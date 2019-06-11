#pragma once
#ifndef __MODULEWELCOMESCREEN_H__
#define __MODULEWELCOMESCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleWelcomeScreen : public Module
{
public:
	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Uint32 timeLimitWlcm = 0;
	Uint32 deltaTimeWlcm = SDL_GetTicks() / 1000;;
	Uint32 startTimeWlcm = 0;

	SDL_Texture* graphics = nullptr;
	SDL_Rect welcome_screen;	

};

#endif // __MODULEWELCOMESCREEN_H__