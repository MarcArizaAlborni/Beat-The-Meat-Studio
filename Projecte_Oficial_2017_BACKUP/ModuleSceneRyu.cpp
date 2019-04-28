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
#include "ModuleAudio.h"


Uint32 timeLimit = 0;
Uint32 deltaTime = SDL_GetTicks() / 1000;;
Uint32 startTime = 0;

bool godOn = false;


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
	Background_Sound = App->audio->LoadMus("Audios/Music/05 Japan (Ryu) I.ogg");

	App->audio->PlayMusic(Background_Sound, 0);

	App->player->currentstate = idlestate;
	App->player->position.x = 100;
	App->player->position.y = 205;
	
	// TODO 1: Enable (and properly disable) the player module
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
	App->audio->UnLoadMusic(Background_Sound);

	//Resets the healthbars at the end of the duel / scene.
	health.x = 189;
	health2.w = 144;



	//Resets the timer
	//currentTime += deltaTime;

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
		health.x -= damage;
	}
	if (health.x <= 45) //45 instead of 0 because it doesnt exactly fit. If the duel ends then reset the healthbars
	{
		App->fade->FadeToBlack(App->scene_ryu, App->lose_screen, 1.0f);
		App->audio->FinishMusic(1000);
	}
	if (App->input->keyboard[SDL_SCANCODE_F6] == 1) //Health-substracting button
	{
		health2.w -= damage;
	}
	if (health2.w <= 0) //If the duel ends then reset the healthbars
	{
		App->fade->FadeToBlack(App->scene_ryu, App->win_screen, 1.0f);
		App->audio->FinishMusic(1000);
	}
	if (App->input->keyboard[SDL_SCANCODE_F3] == 1) //Insta-Win Input Button
	{
		App->fade->FadeToBlack(App->scene_ryu, App->win_screen, 1.0f);
		
		App->audio->FinishMusic(1000);
	}
	 
	if (App->input->keyboard[SDL_SCANCODE_F4] == 1) //Insta-Lose Input Button
	{
		App->fade->FadeToBlack(App->scene_ryu, App->lose_screen, 1.0f);
		App->audio->FinishMusic(1000);
	}

	
	//Win/lose condition using time:
	deltaTime = SDL_GetTicks() / 1000; //GetTicks counts the amount of milliseconds that have elapsed since the SDL_library has been executed. Milliseconds to seconds.
	timeLimit = deltaTime - startTime;

	if (timeLimit >= 99)
	{
		if (health.x == health2.w + 45)
		{
			App->fade->FadeToBlack(App->scene_ryu, App->win_screen, 1.0f);
		}
		
		if (health.x - 45 != health2.w) //p1 and p2 have the same amount of hp.
		{
			if (health.x > health2.w + 45) //p1 has more  health than p2
			{
				App->fade->FadeToBlack(App->scene_ryu, App->win_screen, 1.0f);
			}

			if (health.x < health2.w + 45)//p2 has more  health than p1
			{
				App->fade->FadeToBlack(App->scene_ryu, App->lose_screen, 1.0f);
			}
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F1]) //God Mode
	{
		if (!godOn)
		{
			damage = 0;
			godOn = true;
		}

		else
		{
			damage = 10;
			godOn = false;
		}
	}

	return UPDATE_CONTINUE;
}