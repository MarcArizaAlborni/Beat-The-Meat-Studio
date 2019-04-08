
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleAudio.h"





#include "SDL_Mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"
#pragma comment(lib,"SDL_Mixer/SDL2_mixer.lib")



ModuleAudio::ModuleAudio():Module() {

	for (uint i = 0; i < MAX_MUSIC; ++i) {

		musicH[i] = nullptr;


	}

	for (uint i = 0; i < MAX_FX; ++i) {

		fxH[i] = nullptr;
	}





}

ModuleAudio::~ModuleAudio() {}


bool ModuleAudio::Init() {

//INICIATE AUDIO FOR OGG FILES
	bool ret1 = true;


	int flags = MIX_INIT_OGG;

	int initiate = Mix_Init(flags);

	if (initiate != flags) {


		SDL_Log("Mix_Initiation failed (OGG FILES");


		ret1= false;
	}

	//AIXO NO SE QUINS VALORS S'HAURIEN DE POSAR, JO POSO ELS D'INTERNET
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);


	return ret1;

}




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




Mixed_Music* const ModuleAudio::LoadMus(const char *direction)
{

	//LOAD AUDIO MUSIC
	Mixed_Music*  backgroundmusic = nullptr;
	

	backgroundmusic = Mix_LoadMUS(direction);

 return  backgroundmusic;

}



Mixed_FX* const ModuleAudio::LoadFX(const char *direction)
{

	//LOAD AUDIO fx
	Mixed_FX*  fx = nullptr;


	fx = Mix_LoadWAV(direction);

	return fx;

}


bool ModuleAudio::RemoveMusic(Mixed_Music* music) {


	bool ret1 = false;



	if (music != nullptr) {

		for (uint i; i < MAX_MUSIC; ++i) {

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


bool ModuleAudio::RemoveFX(Mixed_FX* fx) {


	bool ret1 = false;



	if (fxH != nullptr) {

		for (uint i; i < MAX_MUSIC; ++i) {

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




