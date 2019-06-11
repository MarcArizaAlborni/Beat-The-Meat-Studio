#pragma once
#ifndef __MODULEVSSCREEN_H__
#define __MODULEVSSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleVsScreen : public Module
{
public:
	ModuleVsScreen();
	~ModuleVsScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Uint32 timeLimitVs = 0;
	Uint32 deltaTimeVs = SDL_GetTicks() / 1000;;
	Uint32 startTimeVs = 0;

	SDL_Texture* graphics = nullptr;
	SDL_Rect vs_screen;

	Mix_Music* vs_sound;

};

#endif // __MODULEVSSCREEN_H__