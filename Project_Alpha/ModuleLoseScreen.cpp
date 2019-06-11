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
	graphics = App->textures->Load("Sprites/Player2_Wins.png");
	lose_sound = App->audio->LoadMus("Audios/Music/07 Stage End.ogg");
	App->audio->PlayMusic(lose_sound, 0);
	deltaTimeL = SDL_GetTicks() / 1000;
	startTimeL = deltaTimeL;

	return true;
}

// UnLoad assets
bool ModuleLoseScreen::CleanUp()
{
	LOG("Unloading Win Screen");
	App->textures->Unload(graphics);
	App->audio->UnLoadMusic(lose_sound);
	return true;
}

// Update: draw background
update_status ModuleLoseScreen::Update()
{
	App->render->camera.x = 0;
	App->render->Blit(graphics, 0, 0, &lose_screen, 0.75f);

	deltaTimeL = SDL_GetTicks() / 1000;
	timeLimitL = deltaTimeL - startTimeL;

	if (timeLimitL > 4 || App->input->keyboard[SDL_SCANCODE_SPACE] == 1) { App->fade->FadeToBlack(App->lose_screen, App->start_screen, 1.0f); App->audio->FinishMusic(1000);
	}
	return UPDATE_CONTINUE;
}