#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneGuile.h"
#include "ModuleVsScreen.h"
#include "MemLeaks.h"

ModuleVsScreen::ModuleVsScreen()
{

	vs_screen.x = 0;
	vs_screen.y = 0;
	vs_screen.w = SCREEN_WIDTH;
	vs_screen.h = SCREEN_HEIGHT;
}

ModuleVsScreen::~ModuleVsScreen()
{}

// Load assets
bool ModuleVsScreen::Start()
{
	LOG("Loading Vs screen");
	graphics = App->textures->Load("Sprites/BlankaVsBlanka.png");
	vs_sound = App->audio->LoadMus("Audios/Music/04 VS.ogg");

	App->audio->PlayMusic(vs_sound, 0);
	deltaTimeVs = SDL_GetTicks() / 1000;
	startTimeVs = deltaTimeVs;

	return true;
}

// UnLoad assets
bool ModuleVsScreen::CleanUp()
{
	LOG("Unloading Vs Screen");
	App->textures->Unload(graphics);
	App->audio->UnLoadMusic(vs_sound);
	return true;
}

// Update: draw background
update_status ModuleVsScreen::Update()
{
	App->render->camera.x = 0;
	App->render->Blit(graphics, 0, 0, &vs_screen, 0.75f);

	deltaTimeVs = SDL_GetTicks() / 1000; //GetTicks counts the amount of milliseconds that have elapsed since the SDL_library has been executed. Milliseconds to seconds.
	timeLimitVs = deltaTimeVs - startTimeVs;

	if (timeLimitVs >= 1 || App->input->keyboard[SDL_SCANCODE_RETURN] == 1) { App->fade->FadeToBlack(App->vs_screen, App->scene_guile, 1.0f);  }
	return UPDATE_CONTINUE;
}