#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayer.h"
#include "ModulePlayerII.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleWinScreen.h"
#include "ModuleLoseScreen.h"
#include "MemLeaks.h"

ModuleSceneRyu::ModuleSceneRyu()
{
	//313.3
	// ground
	ground.x = 45;
	ground.y = 298;
	ground.w = 620;
	ground.h = 237.3;

	// Sky
	background.x = 49;
	background.y = 45;
	background.w = 1409,8;
	background.h = 176.3;

	background_pos = 0;
	forward = true;

	//Castle
	castle.x = 1477;
	castle.y = 10;
	castle.w = 504;
	castle.h = 182;

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

	//Names
	name.x = 226;
	name.y = 292;
	name.w = 28;
	name.h = 9;

	name2.x = 226;
	name2.y = 292;
	name2.w = 28;
	name2.h = 9;

	//Score
	score.x = 226;
	score.y = 313;
	score.w = 241;
	score.h = 10;

	//Timer
	timer.x = 340;
	timer.y = 292;
	timer.w = 28;
	timer.h = 15;
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
	App->player2->Enable();
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
	App->player2->Disable();
	App->collision->Disable();
	App->particles->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneRyu::Update()
{

	// Draw everything --------------------------------------
	if (background_pos > 1000.0f)
	forward = true;

	if (forward)
		background_pos -= 0.15f;

	App->render->Blit(graphics, -77 + (int)background_pos, 0, &background); //sky

	App->render->Blit(graphics, 0, -3.25, &castle); //castle

	App->render->Blit(graphics, -115, -13, &ground); //ground

	App->render->Blit(graphics2, 30, 20, &healthbar,1.0f,false); //healthbar
	App->render->Blit(graphics2, 31, 23, &health, 1.0f, false); //health
	App->render->Blit(graphics2, 207, 23, &health2, 1.0f, false); //health

	App->render->Blit(graphics2, 32, 34, &name, 1.0f, false); //name p1
	App->render->Blit(graphics2, 322, 34, &name2, 1.0f, false); //name p2
	App->render->Blit(graphics2, 6, 1, &score, 1.0f, false); //score
	App->render->Blit(graphics2, 178, 34, &timer, 1.0f, false); //timer

	if (App->input->keyboard[SDL_SCANCODE_F5] == 1) //Health-substracting button
	{
		health.x -= 10;
	}
	if (health.x <= 40) //40 instead of 0 because it doesnt exactly fit. If the duel ends then reset the healthbars
	{
		App->fade->FadeToBlack(App->scene_ryu, App->lose_screen, 1.0f);
		health.x = 189;
		health2.w = 144;
	}
	if (App->input->keyboard[SDL_SCANCODE_F6] == 1) //Health-substracting button
	{
		health2.w -= 10;
	}
	if (health2.w <= 0) //If the duel ends then reset the healthbars
	{
		App->fade->FadeToBlack(App->scene_ryu, App->win_screen, 1.0f);
		health2.w = 144;
		health.x = 189;
	}
	if (App->input->keyboard[SDL_SCANCODE_F3] == 1) //Insta-Win Input Button
	{
		App->fade->FadeToBlack(App->scene_ryu, App->win_screen, 1.0f);
		health2.w = 144;
		health.x = 189;
	}
	 
	if (App->input->keyboard[SDL_SCANCODE_F4] == 1) //Insta-Lose Input Button
	{
		App->fade->FadeToBlack(App->scene_ryu, App->lose_screen, 1.0f);
		health.x = 189;
		health2.w = 144;
	}

	return UPDATE_CONTINUE;
}