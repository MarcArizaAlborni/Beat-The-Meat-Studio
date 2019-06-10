#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleSounds.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleWarningScreen.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")



ModuleSounds::ModuleSounds() :Module() {

	insert_coin.PushBack({ 768, 2240, 384, 224 });
	insert_coin.PushBack({ 1152, 2240, 384, 224 });
	insert_coin.speed = 0.05f;
}

ModuleSounds::~ModuleSounds() {}

bool ModuleSounds::Start() {
	LOG("Loading Sounds");

	coin_Music = App->audio->LoadMus("Audios/Music/02 Credit.ogg");

	graphics = App->textures->Load("Sprites/SFanimation.png");

	return true;
}

bool ModuleSounds::CleanUp() {
	
	App->audio->UnLoadMusic(coin_Music);
	App->textures->Unload(graphics);

	return true;
}

update_status ModuleSounds::Update(){

	if (App->input->keyboard[SDL_SCANCODE_F3]) {

		App->audio->PlayMusic(coin_Music, 0);

		App->audio->FinishMusic(1000);

		coin_inserted = true;

	}

	if (coin_inserted == false) {

		if (!App->welcome_screen->IsEnabled()) {

			if (!App->warning_screen->IsEnabled()) {

			
			SDL_Rect r = insert_coin.GetCurrentFrame();

			App->render->Blit(graphics, 0, 0, &r, 0, false);

			}
		}
	}

	

	return UPDATE_CONTINUE;
}