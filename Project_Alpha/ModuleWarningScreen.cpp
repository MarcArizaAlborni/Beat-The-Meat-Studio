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
#include "ModuleGuys.h"
#include "ModuleWarningScreen.h"
#include "ModuleSounds.h"
#include "ModuleStartScreen.h"

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

	App->fade->FadeToBlack(App->warning_screen, App->guys_screen, 5.0f);

	if (App->sounds->coin_inserted == true) {

		App->fade->FadeToBlack(App->warning_screen, App->start_screen, 5.0f);

	}

	return UPDATE_CONTINUE;
}