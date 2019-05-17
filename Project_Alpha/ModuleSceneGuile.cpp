#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneGuile.h"
#include "ModulePlayer.h"
#include "ModulePlayerII.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleWinScreen.h"
#include "ModuleLoseScreen.h"
#include "MemLeaks.h"
#include "ModuleAudio.h"


ModuleSceneGuile::ModuleSceneGuile()
{
	//PLANE && GROUND
	plane_ground = {59, 413, 673, 224};

	//SKY
	sky = {59, 40, 673, 54 };

	//BACKGROUND
	background = {59, 207, 673, 160};

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

ModuleSceneGuile::~ModuleSceneGuile()
{}

bool ModuleSceneGuile::Start()
{
	LOG("Loading Guile scene");
	graphics = App->textures->Load("Sprites/guile_stage.png");
	graphics2 = App->textures->Load("Sprites/UI_Spritesheet.png");
	//Background_Sound = App->audio->LoadMus("Audios/Music/05 Japan (Ryu) I.ogg");

	//App->audio->PlayMusic(Background_Sound, 0);

	App->player->currentstateP1 = idlestateP1;
	App->player->positionP1.x = 50;
	App->player->positionP1.y = 205;
	App->player2->currentstateP2 = idlestateP2;
	App->player2->positionP2.x = 230;
	App->player2->positionP2.y = 205;


	App->player->Enable();
	App->player2->Enable();
	App->particles->Enable();
	App->collision->Enable();

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
	App->textures->Unload(graphics2);
	App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->audio->UnLoadMusic(Background_Sound);

	//Resets the healthbars at the end of the duel / scene.
	health.x = 189;
	health2.w = 144;

	return true;
}

update_status ModuleSceneGuile::Update()
{ 
	App->render->Blit(graphics, -160, 0, &sky); //sky
	App->render->Blit(graphics, -160, 0, &background); //background
	App->render->Blit(graphics, -160, 0, &plane_ground); //plane_ground
	App->render->Blit(graphics, -160, 70, &fence); //fence
	App->render->Blit(graphics, 34, 79, &(left_guys.GetCurrentFrame())); //left_guys
	App->render->Blit(graphics, 140, 110, &(mid_guys.GetCurrentFrame())); //mid_guys
	App->render->Blit(graphics, 300, 101, &(right_guys.GetCurrentFrame())); //right_guys

	App->render->Blit(graphics2, 30, 20, &healthbar, 1.0f, false); //healthbar
	App->render->Blit(graphics2, 31, 23, &health, 1.0f, false); //health
	App->render->Blit(graphics2, 207, 23, &health2, 1.0f, false); //health

	App->render->Blit(graphics2, 32, 34, &name, 1.0f, false); //name p1
	App->render->Blit(graphics2, 322, 34, &name2, 1.0f, false); //name p2
	App->render->Blit(graphics2, 6, 1, &score, 1.0f, false); //score
	App->render->Blit(graphics2, 178, 34, &timer, 1.0f, false); //timer

	if (App->input->keyboard[SDL_SCANCODE_F5] == 1) //Health-substracting button
	{
		health.x -= damage;
	}
	if (health.x <= 45) //45 instead of 0 because it doesnt exactly fit. If the duel ends then reset the healthbars
	{
		App->fade->FadeToBlack(App->scene_guile, App->lose_screen, 1.0f);
		App->audio->FinishMusic(1000);
	}
	if (App->input->keyboard[SDL_SCANCODE_F6] == 1) //Health-substracting button
	{
		health2.w -= damage;
	}
	if (health2.w <= 0) //If the duel ends then reset the healthbars
	{
		App->fade->FadeToBlack(App->scene_guile, App->win_screen, 1.0f);
		App->audio->FinishMusic(1000);
	}
	if (App->input->keyboard[SDL_SCANCODE_F3] == 1) //Insta-Win Input Button
	{
		App->fade->FadeToBlack(App->scene_guile, App->win_screen, 1.0f);

		App->audio->FinishMusic(1000);
	}

	if (App->input->keyboard[SDL_SCANCODE_F4] == 1) //Insta-Lose Input Button
	{
		App->fade->FadeToBlack(App->scene_guile, App->lose_screen, 1.0f);
		App->audio->FinishMusic(1000);
	}


	//Win/lose condition using time:
	deltaTime = SDL_GetTicks() / 1000; //GetTicks counts the amount of milliseconds that have elapsed since the SDL_library has been executed. Milliseconds to seconds.
	timeLimit = deltaTime - startTime;

	if (timeLimit >= 99)
	{
		if (health.x == health2.w + 45)
		{
			App->fade->FadeToBlack(App->scene_guile, App->win_screen, 1.0f);
		}

		if (health.x - 45 != health2.w) //p1 and p2 have the same amount of hp.
		{
			if (health.x > health2.w + 45) //p1 has more  health than p2
			{
				App->fade->FadeToBlack(App->scene_guile, App->win_screen, 1.0f);
			}

			if (health.x < health2.w + 45)//p2 has more  health than p1
			{
				App->fade->FadeToBlack(App->scene_guile, App->lose_screen, 1.0f);
			}
		}
	}

	return UPDATE_CONTINUE;
}