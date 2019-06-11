#pragma once
#ifndef __MODULECHARACTERSELECT_H__
#define __MODULECHARACTERSELECT_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleCharacterSelect : public Module
{
public:
	ModuleCharacterSelect();
	~ModuleCharacterSelect();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Uint32 timeLimitCh = 0;
	Uint32 deltaTimeCh = SDL_GetTicks() / 1000;
	Uint32 startTimeCh = 0;
	Uint32 lapseVs = 0;

	bool landing = false;

	SDL_Texture* graphics = nullptr;
	SDL_Rect character_screen;

};

#endif // __MODULECHARACTERSELECT_H__