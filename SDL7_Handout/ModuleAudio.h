#pragma once

#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"

#define MAX_MUSIC 50
#define MAX_FX 50


struct Mix_Music;
struct Mix_Chunk;

class ModuleAudio : public Module {
public:
	//inicialitzar 
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();
	//LOAD MUSIC AND FX
	Mix_Music *const LoadMus(const char* path);
	Mix_Chunk *const LoadFX(const char* path);






public:
	//Create variables
	Mix_Music *musicH[MAX_MUSIC];
	Mix_Chunk *fxH[MAX_FX];



	//REMOVE MUSIC AND FX
	bool RemoveMusic (Mix_Music* music);
	bool RemoveFX (Mix_Chunk* fx);


};
#endif // __ModuleAudio_H__