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
#include "ModuleWarningScreen.h"
#include "ModuleStartScreen.h"

ModuleWelcomeScreen::ModuleWelcomeScreen()
{
	welcome_screen.x = 0;
	welcome_screen.y = 0;
	welcome_screen.w = SCREEN_WIDTH;
	welcome_screen.h = SCREEN_HEIGHT;
}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{}

// Load assets
bool ModuleWelcomeScreen::Start()
{
	LOG("Loading Welcome screen");
	graphics = App->textures->Load("Sprites/First_text.png");
	return true;
}

// UnLoad assets
bool ModuleWelcomeScreen::CleanUp()
{
	LOG("Unloading Welcome Screen");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleWelcomeScreen::Update()
{
	App->render->Blit(graphics, 0, 0, &welcome_screen, 0.75f); 
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->welcome_screen, App->warning_screen,1.0f);

	}

	if (App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_2] == KEY_DOWN) {
		App->fade->FadeToBlack(App->welcome_screen, App->warning_screen, 1.0f);

	}
	return UPDATE_CONTINUE;
}