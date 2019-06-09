#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleSounds.h"
#include "ModuleInput.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")



ModuleSounds::ModuleSounds() :Module() {}

ModuleSounds::~ModuleSounds() {}

bool ModuleSounds::Start() {
	LOG("Loading Sounds");

	coin_Music = App->audio->LoadMus("Audios/Music/02 Credit.ogg");

	

	return true;
}

bool ModuleSounds::CleanUp() {
	
	App->audio->UnLoadMusic(coin_Music);

	return true;
}

update_status ModuleSounds::Update(){

	if (App->input->keyboard[SDL_SCANCODE_F3]) {

		App->audio->PlayMusic(coin_Music, 0);

		App->audio->FinishMusic(1000);

		coin_inserted = true;
	}

	return UPDATE_CONTINUE;
}