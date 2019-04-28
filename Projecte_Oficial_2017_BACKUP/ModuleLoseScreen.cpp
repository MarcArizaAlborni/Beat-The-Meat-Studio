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
#include "ModuleSceneHonda.h"
#include "ModuleLoseScreen.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleStartScreen.h"

ModuleLoseScreen::ModuleLoseScreen()
{
	lose_screen.x = 0;
	lose_screen.y = 0;
	lose_screen.w = SCREEN_WIDTH;
	lose_screen.h = SCREEN_HEIGHT;
}

ModuleLoseScreen::~ModuleLoseScreen()
{}

// Load assets
bool ModuleLoseScreen::Start()
{
	LOG("Loading Win screen");
	graphics = App->textures->Load("Sprites/Ken_Wins_Ryu.png");
	return true;
}

// UnLoad assets
bool ModuleLoseScreen::CleanUp()
{
	LOG("Unloading Win Screen");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleLoseScreen::Update()
{
	App->render->camera.x = 0;
	App->render->Blit(graphics, 0, 0, &lose_screen, 0.75f);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->lose_screen, App->start_screen, 1.0f);

	}
	return UPDATE_CONTINUE;
}