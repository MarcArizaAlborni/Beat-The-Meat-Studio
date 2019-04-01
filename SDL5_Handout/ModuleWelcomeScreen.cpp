#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneKen.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneHonda.h"
#include "MemLeaks.h"
#include "ModuleWelcomeScreen.h"

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
	graphics = App->textures->Load("First_text.png");
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

		App->fade->FadeToBlack(App->welcome_screen, App->scene_ken, 2.5f);

	}
	return UPDATE_CONTINUE;
}