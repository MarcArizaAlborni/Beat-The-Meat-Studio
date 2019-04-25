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
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleWinScreen.h"
#include "ModuleLoseScreen.h"
#include "MemLeaks.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// foreground
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 521;
	foreground.h = 181;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	//Healthbar
	healthbar.x = 100;
	healthbar.y = 100;
	healthbar.w = 100;
	healthbar.h = 100;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// Girl Animation
	girl.PushBack({ 624, 16, 32, 54 });
	girl.PushBack({ 624, 80, 32, 54 });
	girl.PushBack({ 624, 144, 32, 54 });
	girl.PushBack({ 624, 80, 32, 54 });
	girl.speed = 0.1f;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}	

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	graphics = App->textures->Load("ken_stage.png");
	graphics2 = App->textures->Load(" .png");
	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	// Colliders ---
	//App->collision->AddCollider({ 4, 0, 50, 400 }, COLLIDER_WALL);
	//App->collision->AddCollider({ 340, 0, 50, 400 }, COLLIDER_WALL);
	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");
	App->textures->Unload(graphics);
	App->player->Disable(); 
	App->collision->Disable();
	App->particles->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// Calculate boat Y position -----------------------------
	if(foreground_pos < -6.0f)
		forward = false;
	else if(foreground_pos > 0.0f)
		forward = true;
	
	if(forward)
		foreground_pos -= 0.02f;
	else
		foreground_pos += 0.02f;

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	App->render->Blit(graphics, 0, (int)foreground_pos, &foreground, 0.92f);
	App->render->Blit(graphics, 192, 104 + (int)foreground_pos, &(girl.GetCurrentFrame()), 0.92f); // girl animation
	
	App->render->Blit(graphics, 0, 170, &ground);







	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) 
	{
		App->fade->FadeToBlack(App->scene_ken, App->win_screen, 1.0f);
	}

	if (App->input->keyboard[SDL_SCANCODE_V] == 1) //Insta-Win Input Button
	{
		App->fade->FadeToBlack(App->scene_ken, App->win_screen, 1.0f);
	}

	if (App->input->keyboard[SDL_SCANCODE_X] == 1) //Insta-Lose Input Button
	{
		App->fade->FadeToBlack(App->scene_ken, App->lose_screen, 1.0f);
	}

	return UPDATE_CONTINUE;
}