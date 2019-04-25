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
#include "ModuleWinScreen.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleStartScreen.h"

ModuleWinScreen::ModuleWinScreen()
{
	win_screen.x = 0;
	win_screen.y = 0;
	win_screen.w = SCREEN_WIDTH;
	win_screen.h = SCREEN_HEIGHT;
}

ModuleWinScreen::~ModuleWinScreen()
{}

// Load assets
bool ModuleWinScreen::Start()
{
	LOG("Loading Win screen");
	graphics = App->textures->Load("Ryu_Wins_Ken.png");
	return true;
}

// UnLoad assets
bool ModuleWinScreen::CleanUp()
{
	LOG("Unloading Win Screen");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleWinScreen::Update()
{
	App->render->Blit(graphics, 0, 0, &win_screen, 0.75f);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->win_screen, App->start_screen, 1.0f);

	}
	return UPDATE_CONTINUE;
}