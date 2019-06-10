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
#include "ModuleFonts.h"

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
	characterGrid.w = 129;
	characterGrid.h = 65;

	//Character Pointers
	p1_pointer.x = 226;
	p1_pointer.y = 84;
	p1_pointer.w = 32;
	p1_pointer.h = 36;

	p2_pointer.x = 265;
	p2_pointer.y = 84;
	p2_pointer.w = 32;
	p2_pointer.h = 36;

	p1_pointerAnim.PushBack({ 226, 84, 32, 36 });
	p1_pointerAnim.PushBack({ 226, 84, 32, 36 });
	p1_pointerAnim.PushBack({ 226, 84, 32, 36 });
	p1_pointerAnim.PushBack({ 302, 84 ,32, 36 });
	p1_pointerAnim.PushBack({ 302, 84 ,32, 36 });
	

	p2_pointerAnim.PushBack({ 265, 84, 32, 36 });
	p2_pointerAnim.PushBack({ 265, 84, 32, 36 });
	p2_pointerAnim.PushBack({ 265, 84, 32, 36 });
	p2_pointerAnim.PushBack({ 340, 84, 32, 36 });
	p2_pointerAnim.PushBack({ 340, 84, 32, 36 });

	//Character Icons

	//Ryu P1
	characterIconP1.x = 28;
	characterIconP1.y = 474;
	characterIconP1.w = 96;
	characterIconP1.h = 111;
	
	//Blanka P1
	characterIconP1II.x = 28;
	characterIconP1II.y = 611;
	characterIconP1II.w = 96;
	characterIconP1II.h = 111;

	//Ryu P2
	characterIconP2.x = 126;
	characterIconP2.y = 474;
	characterIconP2.w = 96;
	characterIconP2.h = 111;

	//Blanka P2
	characterIconP2II.x = 126;
	characterIconP2II.y = 611;
	characterIconP2II.w = 96;
	characterIconP2II.h = 111;

	//CountryFlag
	countryFlagP1.x = 364;
	countryFlagP1.y = 431;
	countryFlagP1.w = 32;
	countryFlagP1.h = 24;

	countryFlagP2.x = 364;
	countryFlagP2.y = 431;
	countryFlagP2.w = 32;
	countryFlagP2.h = 24;

	//Stage's Country Flag 
	countryFlagStage.x = 400;
	countryFlagStage.y = 431;
	countryFlagStage.w = 30;
	countryFlagStage.h = 24;

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

	Logo = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
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
	graphics = App->textures->Load("Sprites/StreetFighter.png");
	App->fonts->Load("Fonts/numbers.png", "0123456789aaaaaaaaaa",1);
	return ret;
}
update_status ModuleUI::Update()
{
	
	
	int timerint = 100 - App->scene_guile->timeLimit;
	timechar[0] = timerint / 10 + '0';
	timechar[1] = timerint % 10 + '0';

	//Blits
	if (stage)
	{
		App->render->Blit(graphicsUI, 30, 20, &healthbar, 1.0f, false); //healthbar
		App->render->Blit(graphicsUI, 31, 23, &health, 1.0f, false); //health
		App->render->Blit(graphicsUI, 207, 23, &health2, 1.0f, false); //health

		App->render->Blit(graphicsUI, 32, 34, &name, 1.0f, false); //name p1
		App->render->Blit(graphicsUI, 322, 34, &name2, 1.0f, false); //name p2
		App->render->Blit(graphicsUI, 6, 1, &score, 1.0f, false); //score
		App->fonts->BlitText(178, 36, 0, timechar); //timer
		//App->render->Blit(graphicsUI, 178, 34, &timer, 1.0f, false); //timer
	}
	
	if (character_select)
	{
		App->render->Blit(graphicsUI, 128, 144, &characterGrid, 1.0f, false); //Character Grid.
		App->render->Blit(graphicsUI, p1_pointerPosX, p1_pointerPosY, &(p1_pointerAnim.GetCurrentFrame())); //Character Pointer 1.
		App->render->Blit(graphicsUI, p2_pointerPosX, p2_pointerPosY, &(p2_pointerAnim.GetCurrentFrame())); //Character Pointer 2.

		if (brazilP1) { App->render->Blit(graphicsUI, 264, 95, &countryFlagP1, 1.0f, false); } //Country Flag
		if (brazilP2) { App->render->Blit(graphicsUI, 264, 95, &countryFlagP2, 1.0f, false); } //Country Flag
		if (stageFlag) { App->render->Blit(graphicsUI, 282, 59, &countryFlagStage, 1.0f, false); } //Stage Flag

		if (p1_characterSelect) { App->render->Blit(graphicsUI, 264, 87, &p1_pointer, 1.0f, false); } //Flag Marker P1
		if (p2_characterSelect) { App->render->Blit(graphicsUI, 264, 87, &p2_pointer, 1.0f, false); } //Flag Marker P2

		if (ryuIconP1) { App->render->Blit(graphicsUI, 0, 113, &characterIconP1, 1.0f, false); } // P1 Ryu Icon
		if (blankaIconP1) { App->render->Blit(graphicsUI, 0, 113, &characterIconP1II, 1.0f, false); } //P1 Blanka Icon
		if (ryuIconP2) { App->render->Blit(graphicsUI, 288, 113, &characterIconP2, 1.0f, false); } //P2 Ryu Icon
		if (blankaIconP2) { App->render->Blit(graphicsUI, 288, 113, &characterIconP2II, 1.0f, false); } //P2 Blanka Icon
	}

	if (StreetLogo)   
	{
		if (App->guys_screen != nullptr) {
			App->render->Blit(graphics, 0, -351, &Logo, 0.75f); //Street Fighter
		}
		else 
		{
			App->render->Blit(graphics, 0, 0, &Logo, 0.75f); //Street Fighter
		}
		
	}
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleUI::CleanUp()
{
	LOG("Unloading UI assets");
	App->textures->Unload(graphicsUI);
	App->textures->Unload(graphics);

	return true;
}
