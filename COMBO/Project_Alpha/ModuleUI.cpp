#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleSceneGuile.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayerII.h"

ModuleUI::ModuleUI() : Module()
{
	//Sprites
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

// Destructor
ModuleUI::~ModuleUI()
{}

// Called before render is available
bool ModuleUI::Start()
{
	LOG("Loading UI assets");
	bool ret = true;
	graphicsUI = App->textures->Load("Sprites/UI_Spritesheet.png");
	return ret;
}
update_status ModuleUI::Update()
{
	//Blits
	App->render->Blit(graphicsUI, 30, 20, &healthbar, 1.0f, false); //healthbar
	App->render->Blit(graphicsUI, 31, 23, &health, 1.0f, false); //health
	App->render->Blit(graphicsUI, 207, 23, &health2, 1.0f, false); //health

	App->render->Blit(graphicsUI, 32, 34, &name, 1.0f, false); //name p1
	App->render->Blit(graphicsUI, 322, 34, &name2, 1.0f, false); //name p2
	App->render->Blit(graphicsUI, 6, 1, &score, 1.0f, false); //score
	App->render->Blit(graphicsUI, 178, 34, &timer, 1.0f, false); //timer

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleUI::CleanUp()
{
	LOG("Unloading UI assets");
	App->textures->Unload(graphicsUI);

	return true;
}
