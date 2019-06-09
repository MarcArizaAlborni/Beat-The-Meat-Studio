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
#include "ModuleSceneGuile.h"
#include "ModuleSounds.h"

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
	
	App->sounds->Enable();
	App->sounds->GuileStage = true;
	return true;
}

// UnLoad assets
bool ModuleWelcomeScreen::CleanUp()
{
	LOG("Unloading Welcome Screen");
	App->textures->Unload(graphics);
	App->sounds->Disable();
	return true;
}

// Update: draw background
update_status ModuleWelcomeScreen::Update()
{
	App->render->Blit(graphics, 0, 0, &welcome_screen, 0.75f); 
	
	
	if (SDL_GetTicks() > 3000)
	{
		App->fade->FadeToBlack(App->welcome_screen, App->warning_screen, 2.0f);
		App->sounds->GuileStage = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_2] == KEY_DOWN) {

		App->fade->FadeToBlack(App->welcome_screen, App->scene_guile, 1.0f);
		App->sounds->GuileStage = false;
	}

	return UPDATE_CONTINUE;
}