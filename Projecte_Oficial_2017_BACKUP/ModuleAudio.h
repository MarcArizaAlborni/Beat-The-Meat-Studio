#pragma once
#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_MUSIC 50
#define MAX_FX 50


class ModuleAudio : public Module {
public:

	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();
	//LOAD MUSIC AND FX
	Mix_Music * const LoadMus(const char * path);
	bool PlayMusic(Mix_Music *music, uint time);
	bool FinishMusic(uint time);
	Mix_Chunk *const LoadFx(const char *path);
	bool PlayFx(Mix_Chunk* chunk);
	//REMOVE MUSIC AND FX
	bool UnLoadMusic(Mix_Music* music);
	bool UnLoadFX(Mix_Chunk* chunk);

public:
	//Create variables
	Mix_Music* Music[MAX_MUSIC];
	Mix_Chunk* Fx[MAX_FX];

};

#endif // __MODULEAUDIO_H__