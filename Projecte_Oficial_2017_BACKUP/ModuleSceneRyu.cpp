#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleWinScreen.h"
#include "ModuleLoseScreen.h"
#include "MemLeaks.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneRyu::ModuleSceneRyu()
{
	// ground
	//ESTA MAL
	ground.x = 44;
	ground.y = 605.3;
	ground.w = 620;
	ground.h = 47.7;

	// foreground
	foreground.x = 49;
	foreground.y = 372;
	foreground.w = 620;
	foreground.h = 176.3;

	// Sky
	background.x = 49;
	background.y = 45;
	background.w = 1409,8;
	background.h = 176.3;

	//Castle

	castle.x = 398;
	castle.y = 270;
	castle.w = 504.3;
	castle.h = 212.3;

	//Healthbar & health
	healthbar.x = 188;
	healthbar.y = 254;
	healthbar.w = 322;
	healthbar.h = 14;

	health.x = 189;
	health.y = 274;
	health.w = 144;
	health.h = 9;

	health2.x = 365;
	health2.y = 274;
	health2.w = 144;
	health2.h = 9;

	
}	

ModuleSceneRyu::~ModuleSceneRyu()
{}

// Load assets
bool ModuleSceneRyu::Start()
{
	LOG("Loading Ryu scene");
	graphics = App->textures->Load("ryu_stage.png");
	graphics2 = App->textures->Load("UI_Spritesheet.png");

	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneRyu::CleanUp()
{
	LOG("Unloading ken scene");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	App->player->Disable(); 
	App->collision->Disable();
	App->particles->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneRyu::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); //sky

	App->render->Blit(graphics, 0, 0, &castle);

	//App->render->Blit(graphics, 0, 1, &foreground);

	App->render->Blit(graphics2, 30, 20, &healthbar); //healthbar
	App->render->Blit(graphics2, 31, 23, &health); //health
	App->render->Blit(graphics2, 207, 23, &health2); //health

	
	App->render->Blit(graphics, 0, 177, &ground);


	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) 
	{
		App->fade->FadeToBlack(App->scene_ryu, App->win_screen, 1.0f);
	}

	if (App->input->keyboard[SDL_SCANCODE_H] == 1) //Health-substracting button
	{
		health.x -= 10;

		if (health.x < 40) //40 instead of 0 because it doesnt exactly fit. If the duel ends then reset the healthbars
		{
			App->fade->FadeToBlack(App->scene_ryu, App->lose_screen, 1.0f);
			health.x = 189;
			health2.w = 144;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_J] == 1) //Health-substracting button
	{
		health2.w -= 10;

		if (health2.w < 0) //If the duel ends then reset the healthbars
		{
			App->fade->FadeToBlack(App->scene_ryu, App->win_screen, 1.0f);
			health2.w = 144;
			health.x = 189;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_V] == 1) //Insta-Win Input Button
	{
		App->fade->FadeToBlack(App->scene_ryu, App->win_screen, 1.0f);
		health2.w = 144;
		health.x = 189;
	}

	if (App->input->keyboard[SDL_SCANCODE_X] == 1) //Insta-Lose Input Button
	{
		App->fade->FadeToBlack(App->scene_ryu, App->lose_screen, 1.0f);
		health.x = 189;
		health2.w = 144;
	}

	return UPDATE_CONTINUE;
}