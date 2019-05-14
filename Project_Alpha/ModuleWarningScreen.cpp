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
#include "ModuleIcoinScreen.h"
#include "ModuleWarningScreen.h"

ModuleWarningScreen::ModuleWarningScreen()
{
	warning_screen.x = 0;
	warning_screen.y = 0;
	warning_screen.w = SCREEN_WIDTH;
	warning_screen.h = SCREEN_HEIGHT;
}

ModuleWarningScreen::~ModuleWarningScreen()
{}

// Load assets
bool ModuleWarningScreen::Start()
{
	LOG("Loading Warning screen");
	graphics = App->textures->Load("Sprites/StartScreenII.png");
	return true;
}

// UnLoad assets
bool ModuleWarningScreen::CleanUp()
{
	LOG("Unloading Warning Screen");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleWarningScreen::Update()
{
	App->render->Blit(graphics, 0, 0, &warning_screen, 0.75f);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->warning_screen, App->icoin_screen, 1.0f);

	}

	if (App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_2] == KEY_DOWN) {
		App->fade->FadeToBlack(App->warning_screen, App->icoin_screen, 1.0f);

	}
	return UPDATE_CONTINUE;
}