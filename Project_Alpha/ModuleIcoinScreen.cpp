#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "MemLeaks.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleIcoinScreen.h"
#include "ModuleStartScreen.h"
#include "Animation.h"
#include "ModuleSceneRyu.h"

ModuleIcoinScreen::ModuleIcoinScreen()
{
	icoin_screen.x = 0;
	icoin_screen.y = 0;
	icoin_screen.w = SCREEN_WIDTH;
	icoin_screen.h = SCREEN_HEIGHT;

	
}

ModuleIcoinScreen::~ModuleIcoinScreen()
{

}

// Load assets
bool ModuleIcoinScreen::Start()
{
	LOG("Loading Welcome screen");
	graphics = App->textures->Load("Sprites/StartScreenIII_II.png");
	insert_coin = App->audio->LoadMus("Audios/Music/02 Credit.ogg");
	App->render->camera.y = 0;
	return true;
}

// UnLoad assets
bool ModuleIcoinScreen::CleanUp()
{
	LOG("Unloading Introduce coin Screen");
	App->textures->Unload(graphics);
	App->audio->UnLoadMusic(insert_coin);
	return true;
}

// Update: draw background
update_status ModuleIcoinScreen::Update()
{


	App->render->Blit(graphics, 0, 0, &icoin_screen, 0.75f);
	
	if (App->input->keyboard[SDL_SCANCODE_F3] || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_2] == KEY_DOWN) {

		App->audio->PlayMusic(insert_coin, NULL);
		App->audio->FinishMusic(1000);
		
		coin_inserted = true;

		if (coin_inserted == true) {
			App->fade->FadeToBlack(App->icoin_screen, App->start_screen, 0.5f);
		}
	}

	
	return UPDATE_CONTINUE;
}