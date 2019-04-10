#ifndef _MODULEAUDIO_H_
#define _MODULEAUDIO_H_

#include "Module.h"
#include "Globals.h"

#define MAX_MUSIC 50
#define MAX_FX 50

struct _Mix_Music;
struct Mix_Chunk;

class ModuleAudio :public Module {
public:
	//inicialitzar 
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	//LOAD MUSIC AND FX
	_Mix_Music * const LoadMus(const char * direction);
	Mix_Chunk *const LoadFX(const char *direction);

public:
	//Create variables
	_Mix_Music* musicH[MAX_MUSIC];
	Mix_Chunk* fxH[MAX_FX];

	//REMOVE MUSIC AND FX
	bool RemoveMusic(_Mix_Music* music);
	bool RemoveFX(Mix_Chunk* fx);
};
#endif //_MODULEAUDIO_H_