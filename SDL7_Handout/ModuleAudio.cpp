#include "ModuleRender.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/x86/SDL2_mixer.lib")


ModuleAudio::ModuleAudio() : Module() {

	for (uint i = 0; i < MAX_MUSIC; ++i) {

		musicH[i] = nullptr;

	}

	for (uint i = 0; i < MAX_FX; ++i) {

		fxH[i] = nullptr;
	}

}

ModuleAudio::~ModuleAudio() {}

//INICIATE AUDIO MODULE
bool ModuleAudio::Init() {


	bool ret1 = true;

	int flags = MIX_INIT_OGG;

	int initiate = Mix_Init(flags);

	if (initiate != flags) {


		SDL_Log("Mix_Initiation failed (OGG FILES");


		ret1 = false;
	}

	//AIXO NO SE QUINS VALORS S'HAURIEN DE POSAR, JO POSO ELS D'INTERNET
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);


	return ret1;

}



//CLEANUP DE AUDIO MODULE
bool ModuleAudio::CleanUp() {


	for (uint i = 0; i < MAX_MUSIC; ++i) {

		if (musicH[i] != nullptr) {

			Mix_FreeMusic(musicH[i]);
			musicH[i] = nullptr;

		}


	}

	for (uint i = 0; i < MAX_MUSIC; ++i) {

		if (fxH[i] != nullptr) {

			(fxH[i]);
			fxH[i] = nullptr;

		}


	}
	Mix_CloseAudio();
	Mix_Quit();
	return true;



}


//LOAD MUSIC (OGG FILES)

Mix_Music* const ModuleAudio::LoadMus(const char *path)
{

	//LOAD AUDIO MUSIC
	Mix_Music*  backgroundmusic = nullptr;


	backgroundmusic = Mix_LoadMUS(path);

	return  backgroundmusic;

}


//LOAD FX (WAV FILES)
Mix_Chunk* const ModuleAudio::LoadFX(const char *path)
{

	//LOAD AUDIO fx
	Mix_Chunk*  fx = nullptr;


	fx = Mix_LoadWAV(path);

	return fx;

}

//REMOVING MUSIC (OGG FILES)
bool ModuleAudio::RemoveMusic(Mix_Music* music) {

	bool ret1 = false;

	if (music != nullptr) {

		for (uint i = 0; i < MAX_MUSIC; ++i) {

			if (musicH[i] == music) {

				Mix_FreeMusic(music);
				musicH[i] = nullptr;
				ret1 = true;
				break;
			}
		}
	}
	return ret1;
}

//REMOVING FX (WAV FILES)
bool ModuleAudio::RemoveFX(Mix_Chunk* fx) {


	bool ret1 = false;



	if (fxH != nullptr) {

		for (uint i = 0; i < MAX_MUSIC; ++i) {

			if (fxH[i] == fx) {

				Mix_FreeChunk(fx);
				fxH[i] = nullptr;
				ret1 = true;
				break;

			}
		}
	}
	return ret1;

}




