#pragma once
#ifndef __MODULECHARACTERSELECT_H__
#define __MODULECHARACTERSELECT_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

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

	Mix_Music* CS_sound;
	Mix_Chunk* cursor_sound;
	Mix_Chunk* accept_sound;
	Mix_Chunk* plane_sound;
	Mix_Chunk* flag_sound;

};

#endif // __MODULECHARACTERSELECT_H__