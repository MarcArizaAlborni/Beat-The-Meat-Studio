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

	//Character Grid
	characterGrid.x = 225;
	characterGrid.y = 340;
	characterGrid.w = 128;
	characterGrid.h = 64;

	//Character Icon


	//CountryFlag
	if (brazil)
	{
		countryFlag.x = 338;
		countryFlag.y = 202;
		countryFlag.w = 25;
		countryFlag.h = 13;
	}

	if (usa)
	{
		countryFlag.x = 366;
		countryFlag.y = 202;
		countryFlag.w = 25;
		countryFlag.h = 13;
	}

	if (usaII)
	{
		countryFlag.x = 366;
		countryFlag.y = 202;
		countryFlag.w = 25;
		countryFlag.h = 13;
	}

	if (urss)
	{
		countryFlag.x = 282;
		countryFlag.y = 202;
		countryFlag.w = 25;
		countryFlag.h = 13;
	}

	if (india)
	{
		countryFlag.x = 310;
		countryFlag.y = 202;
		countryFlag.w = 25;
		countryFlag.h = 13;
	}

	if (china)
	{
		countryFlag.x = 254;
		countryFlag.y = 202;
		countryFlag.w = 25;
		countryFlag.h = 13;
	}

	if (japan)
	{
		countryFlag.x = 225;
		countryFlag.y = 202;
		countryFlag.w = 25;
		countryFlag.h = 13;
	}

	if (japanII)
	{
		countryFlag.x = 225;
		countryFlag.y = 202;
		countryFlag.w = 25;
		countryFlag.h = 13;
	}

	//CountryFlagII
	countryFlag.x = 366;
	countryFlag.y = 202;
	countryFlag.w = 25;
	countryFlag.h = 13;

	//Plane
	//Vertical
	plane.x = 264;
	plane.y = 27;
	plane.w = 14;
	plane.h = 15;

	//Turning right
	plane.x = 280;
	plane.y = 27;
	plane.w = 15;
	plane.h = 13;
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
	if (stage)
	{
		App->render->Blit(graphicsUI, 30, 20, &healthbar, 1.0f, false); //healthbar
		App->render->Blit(graphicsUI, 31, 23, &health, 1.0f, false); //health
		App->render->Blit(graphicsUI, 207, 23, &health2, 1.0f, false); //health

		App->render->Blit(graphicsUI, 32, 34, &name, 1.0f, false); //name p1
		App->render->Blit(graphicsUI, 322, 34, &name2, 1.0f, false); //name p2
		App->render->Blit(graphicsUI, 6, 1, &score, 1.0f, false); //score
		App->render->Blit(graphicsUI, 178, 34, &timer, 1.0f, false); //timer
	}
	
	if (character_select)
	{
		App->render->Blit(graphicsUI, 128, 143, &characterGrid, 1.0f, false); //Character Grid.
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleUI::CleanUp()
{
	LOG("Unloading UI assets");
	App->textures->Unload(graphicsUI);

	return true;
}
