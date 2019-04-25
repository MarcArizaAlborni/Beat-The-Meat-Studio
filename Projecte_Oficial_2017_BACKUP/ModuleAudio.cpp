#include "Application.h"
#include "ModuleAudio.h"

#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

ModuleAudio::ModuleAudio() :Module() {}

ModuleAudio::~ModuleAudio() {}

//INICIATE AUDIO MODULE
bool ModuleAudio::Init() {

	int flags = MIX_INIT_OGG;
	Mix_Init(SDL_INIT_AUDIO);

	int initiate = Mix_Init(flags);

	if (initiate != flags) {


		LOG("Mix_Init failed", Mix_GetError());

		return false;

	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {

		LOG("Mix_OpenAudio failed", Mix_GetError());

		return false;
	}

	return true;
}



//CLEANUP DE AUDIO MODULE
bool ModuleAudio::CleanUp() {

	for (uint i = 0; i < MAX_MUSIC; ++i) {

		if (Music[i] != nullptr) {
			Music[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_MUSIC; ++i) {

		if (Fx[i] != nullptr) {
			Fx[i] = nullptr;
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

	if (!backgroundmusic) {
		LOG("Mix_LoadMUS failed", Mix_GetError());
	}
	for (uint i = 0; i < MAX_MUSIC; i++) {

		if (Music[i] == nullptr)
		{
			Music[i] = backgroundmusic;

		}
	}

	return  backgroundmusic;
}


//LOAD FX (WAV FILES)
Mix_Chunk* const ModuleAudio::LoadFx(const char *path)
{

	//LOAD AUDIO fx
	Mix_Chunk*  effects = nullptr;

	effects = Mix_LoadWAV(path);

	if (!effects) {
		LOG("Mix_LoadWAV failed", Mix_GetError());
	}

	for (uint i = 0; i < MAX_FX; i++) {

		if (Fx[i] == nullptr)
		{
			Fx[i] = effects;
		}
	}

	return effects;

}

bool ModuleAudio::PlayMusic(Mix_Music* music, uint time) {

	if (Mix_FadeInMusic(music, -1, time) == -1) {
		LOG("Mix_PlayMusic failed", Mix_GetError());
		return false;
	}

	return true;
}

bool ModuleAudio::PlayFx(Mix_Chunk* chunk) {

	if (Mix_PlayChannel(-1, chunk, 0) == -1) {
		LOG("Mix:PlayChannel failed", Mix_GetError());
		return false;
	}

	return true;
}

bool ModuleAudio::FinishMusic(uint time) {

	while (!Mix_FadeOutMusic(time)) {
		// wait for any fades to complete
		SDL_Delay(100);
		return true;
	}

}

//REMOVING MUSIC (OGG FILES)
bool ModuleAudio::UnLoadMusic(Mix_Music* music) {

	if (music != nullptr) {

		for (uint i = 0; i < MAX_MUSIC; ++i) {

			if (Music[i] == music) {

				Mix_FreeMusic(music);
				Music[i] = nullptr;
				return false;
				break;
			}
		}
	}
	return true;
}

//REMOVING FX (WAV FILES)
bool ModuleAudio::UnLoadFX(Mix_Chunk* fx) {

	if (fx != nullptr) {

		for (uint i = 0; i < MAX_MUSIC; ++i) {

			if (Fx[i] == fx) {

				Mix_FreeChunk(fx);
				Fx[i] = nullptr;
				return false;
				break;

			}
		}
	}
	return true;

}