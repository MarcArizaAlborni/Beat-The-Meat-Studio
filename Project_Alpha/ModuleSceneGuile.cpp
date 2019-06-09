#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneGuile.h"
#include "ModulePlayer.h"
#include "ModulePlayerII.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleWinScreen.h"
#include "ModuleLoseScreen.h"
#include "MemLeaks.h"
#include "ModuleSounds.h"



ModuleSceneGuile::ModuleSceneGuile()
{
	//PLANE && GROUND
	plane_ground = {59, 400, 673, 237};

	//SKY
	sky = {59, 40, 673, 54 };

	//BACKGROUND
	background = {59, 208, 673, 177};

	//FENCE

	fence = { 1123, 207, 125, 119 };

	//LEFT GUYS

	left_guys.PushBack({ 911, 33, 65, 112 });
	left_guys.PushBack({ 985, 33, 65, 112 });
	left_guys.PushBack({ 911, 33, 65, 112 });
	left_guys.PushBack({ 985, 33, 65, 112 });
	left_guys.PushBack({ 911, 33, 65, 112 });
	left_guys.PushBack({ 985, 33, 65, 112 });
	left_guys.PushBack({ 911, 33, 65, 112 });
	left_guys.PushBack({ 1059, 33, 65, 112 });
	left_guys.PushBack({ 911, 33, 65, 112 });
	left_guys.PushBack({ 985, 33, 65, 112 });
	left_guys.PushBack({ 911, 33, 65, 112 });
	left_guys.PushBack({ 1059, 33, 65, 112 });
	left_guys.speed = 0.05f;
	left_guys.loop = true;

	//MID GUYS

	mid_guys.PushBack({ 1250, 64, 154, 81 });
	mid_guys.PushBack({ 1423, 64, 154, 81 });
	mid_guys.PushBack({ 1596, 64, 154, 81 });
	mid_guys.speed = 0.05;
	mid_guys.loop = true;
	//RIGHT GUYS

	right_guys.PushBack({ 1774, 55, 97, 91 });
	right_guys.PushBack({ 1880, 55, 97, 91 });
	right_guys.PushBack({ 1986, 55, 97, 91 });
	right_guys.speed = 0.05;
	right_guys.loop = true;
}

ModuleSceneGuile::~ModuleSceneGuile()
{}

bool ModuleSceneGuile::Start()
{
	LOG("Loading Guile scene");
	graphics = App->textures->Load("Sprites/guile_stage.png");
	
	App->player->currentstateP1 = idlestateP1;
	App->player->positionP1.x = 50;
	App->player->positionP1.y = 205;
	App->player2->currentstateP2 = idlestateP2;
	App->player2->positionP2.x = 230;
	App->player2->positionP2.y = 205;


	App->player->Enable();
	App->player2->Enable();
	App->ui->Enable();
	App->particles->Enable();
	App->collision->Enable();


	App->ui->stage = true;


	//Declares the scene start timer. / Resets the timer. 
	deltaTime = SDL_GetTicks() / 1000;
	startTime = deltaTime;

	background_pos = 0.0f;

	return true;
}

bool ModuleSceneGuile::CleanUp()
{
	LOG("Unloading Guile Scene");
	App->textures->Unload(graphics);
	App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->ui->Disable();
	

	App->ui->stage = false;

	//Resets the healthbars at the end of the duel / scene.
	App->ui->health.x = 189;
	App->ui->health2.w = 144;

	return true;
}

update_status ModuleSceneGuile::Update()
{ 
	
	App->render->Blit(graphics, -146, -13, &background); //background
	App->render->Blit(graphics, -146, -13, &sky); //sky
	App->render->Blit(graphics, -146, -13, &plane_ground); //plane_ground
	App->render->Blit(graphics, -146, 70, &fence); //fence
	App->render->Blit(graphics, 44, 79, &(left_guys.GetCurrentFrame())); //left_guys
	App->render->Blit(graphics, 150, 110, &(mid_guys.GetCurrentFrame())); //mid_guys
	App->render->Blit(graphics, 310, 101, &(right_guys.GetCurrentFrame())); //right_guys

	//Debug mode
	if (App->input->keyboard[SDL_SCANCODE_F5] == 1) //Health-substracting button
	{
		App->ui->health.x -= damage;
	}

	if (App->input->keyboard[SDL_SCANCODE_F6] == 1) //Health-substracting button
	{
		App->ui->health2.w -= damage;
	}

	if (App->input->keyboard[SDL_SCANCODE_F3] == 1) //Insta-Win Input Button
	{
		App->fade->FadeToBlack(App->scene_guile, App->win_screen, 1.0f);

	}

	if (App->input->keyboard[SDL_SCANCODE_F4] == 1) //Insta-Lose Input Button
	{
		App->fade->FadeToBlack(App->scene_guile, App->lose_screen, 1.0f);
	
	}

	//Win/Lose condition taking into account the remaining health.
	if (App->ui->health.x <= 45) //45 instead of 0 because it doesnt exactly fit.
	{
		App->fade->FadeToBlack(App->scene_guile, App->lose_screen, 1.0f);
		
	}

	if (App->ui->health2.w <= 0)
	{
		App->fade->FadeToBlack(App->scene_guile, App->win_screen, 1.0f);
	
	}

	//Win/lose condition using time:
	deltaTime = SDL_GetTicks() / 1000; //GetTicks counts the amount of milliseconds that have elapsed since the SDL_library has been executed. Milliseconds to seconds.
	timeLimit = deltaTime - startTime;

	if (timeLimit >= 99)
	{
		if (App->ui->health.x == App->ui->health2.w + 45)
		{
			App->fade->FadeToBlack(App->scene_guile, App->win_screen, 1.0f);
		}

		if (App->ui->health.x - 45 != App->ui->health2.w) //p1 and p2 have the same amount of hp.
		{
			if (App->ui->health.x > App->ui->health2.w + 45) //p1 has more  health than p2
			{
				App->fade->FadeToBlack(App->scene_guile, App->win_screen, 1.0f);
			}

			if (App->ui->health.x < App->ui->health2.w + 45)//p2 has more  health than p1
			{
				App->fade->FadeToBlack(App->scene_guile, App->lose_screen, 1.0f);
			}
		}
	}

	return UPDATE_CONTINUE;
}