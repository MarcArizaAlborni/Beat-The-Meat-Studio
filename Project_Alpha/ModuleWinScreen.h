#pragma once
#ifndef __MODULEWINSCREEN_H__
#define __MODULEWINSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleWinScreen : public Module
{
public:
	ModuleWinScreen();
	~ModuleWinScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Uint32 timeLimitW = 0;
	Uint32 deltaTimeW = SDL_GetTicks() / 1000;;
	Uint32 startTimeW = 0;

	SDL_Texture* graphics = nullptr;
	SDL_Rect win_screen;

};

#endif // __MODULEWINSCREEN_H__