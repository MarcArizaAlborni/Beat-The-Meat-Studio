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
#include "ModuleCongratScreen.h"
#include "ModuleWelcomeScreen.h"

ModuleCongratScreen::ModuleCongratScreen()
{
	congrat_screen.x = 0;
	congrat_screen.y = 0;
	congrat_screen.w = SCREEN_WIDTH;
	congrat_screen.h = SCREEN_HEIGHT;
}

ModuleCongratScreen::~ModuleCongratScreen()
{}

// Load assets
bool ModuleCongratScreen::Start()
{
	LOG("Loading Welcome screen");
	graphics = App->textures->Load("Sprites/Ryu_Wins_Honda.png");
	return true;
}

// UnLoad assets
bool ModuleCongratScreen::CleanUp()
{
	LOG("Unloading Welcome Screen");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleCongratScreen::Update()
{
	App->render->Blit(graphics, 0, 0, &congrat_screen, 0.75f,true);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->congrat_screen, App->welcome_screen, 2.5f);

	}
	return UPDATE_CONTINUE;
}