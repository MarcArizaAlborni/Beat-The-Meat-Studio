#pragma once

#ifndef _ModuleAudio_H_
#define _ModulesAudio_H_

#include "Module.h"
#include "Globals.h"

#define MAX_MUSIC 50
#define MAX_FX 50


struct Mixed_Music;
struct Mixed_FX;

class ModuleAudio:public Module {
public:

	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mixed_Music * const LoadMus(const char * direction);
	Mixed_FX * const LoadFX(const char * direction);


	

	//LOAD MUSIC AND FX
	
	

	Mixed_Music* musicH[MAX_MUSIC];
	Mixed_FX* fxH[MAX_FX];

	

	//REMOVE MUSIC AND FX
	bool RemoveMusic(Mixed_Music* music);
	bool RemoveFX(Mixed_FX* fx);


};
#endif _ModuleAudio_H_