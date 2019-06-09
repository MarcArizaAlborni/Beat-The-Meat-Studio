#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleSounds.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")



ModuleSounds::ModuleSounds() :Module() {}

ModuleSounds::~ModuleSounds() {}

bool ModuleSounds::Start() {
	LOG("Loading Sounds");

	
	GuileStage_Sound = App->audio->LoadMus("Audios/Music/10 U.S.A. (Guile) I.ogg");
		
	if (GuileStage == true) {

		App->audio->PlayMusic(GuileStage_Sound, 0);
	}

	return true;
}

bool ModuleSounds::CleanUp() {
	
	App->audio->UnLoadMusic(GuileStage_Sound);

	return true;
}

update_status ModuleSounds::Update(){

	if (GuileStage == false)
	{
		App->audio->FinishMusic(1000);
	}

	return UPDATE_CONTINUE;
}