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
	name.w = 57;
	name.h = 9;

	name2.x = 226;
	name2.y = 292;
	name2.w = 57;
	name2.h = 9;

	//Score
	score.x = 149;
	score.y = 314;
	score.w = 370;
	score.h = 10;

	//Timer
	timer.x = 340;
	timer.y = 292;
	timer.w = 28;
	timer.h = 15;

	//Round Tokens
	roundTokenP1.x = 0;
	roundTokenP1.y = 0;
	roundTokenP1.w = 0;
	roundTokenP1.h = 0;

	roundTokenP1II.x = 0;
	roundTokenP1II.y = 0;
	roundTokenP1II.w = 0;
	roundTokenP1II.h = 0;

	roundTokenP2.x = 0;
	roundTokenP2.y = 0;
	roundTokenP2.w = 0;
	roundTokenP2.h = 0;

	roundTokenP2II.x = 0;
	roundTokenP2II.y = 0;
	roundTokenP2II.w = 0;
	roundTokenP2II.h = 0;


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
	p1_pointerAnim.PushBack({ 302, 84 ,32, 36 });
	p1_pointerAnim.PushBack({ 378 , 84 ,32, 36 });
	

	p2_pointerAnim.PushBack({ 265, 84, 32, 36 });
	p2_pointerAnim.PushBack({ 265, 84, 32, 36 });
	p2_pointerAnim.PushBack({ 340, 84, 32, 36 });
	p2_pointerAnim.PushBack({ 416, 84, 32, 36 });

	//Character Icons
	//Ryu P1
	characterIconRyuP1.x = 28;
	characterIconRyuP1.y = 458;
	characterIconRyuP1.w = 96;
	characterIconRyuP1.h = 126;
	
	//Ken P1
	characterIconKenP1.x = 28;
	characterIconKenP1.y = 734;
	characterIconKenP1.w = 96;
	characterIconKenP1.h = 126;

	//Blanka P1
	characterIconBlankaP1.x = 28;
	characterIconBlankaP1.y = 595;
	characterIconBlankaP1.w = 96;
	characterIconBlankaP1.h = 126;

	//Ryu P2
	characterIconRyuP2.x = 126;
	characterIconRyuP2.y = 458;
	characterIconRyuP2.w = 96;
	characterIconRyuP2.h = 126;

	//Ken P2
	characterIconKenP2.x = 126;
	characterIconKenP2.y = 734;
	characterIconKenP2.w = 96;
	characterIconKenP2.h = 126;


	//Blanka P2
	characterIconBlankaP2.x = 126;
	characterIconBlankaP2.y = 595;
	characterIconBlankaP2.w = 96;
	characterIconBlankaP2.h = 126;

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
	
	//Stage Flag Animation
	for (int i = 0; i < 10; i++)
	{
		stageFlagAnimation.PushBack({ 400, 431, 30, 24 });
	}

	for (int i = 0; i < 10; i++)
	{
		stageFlagAnimation.PushBack({ 400, 400, 30, 24 });
	}

	//Plane
	//Vertical
	/*plane.x = 264;
	plane.y = 27;
	plane.w = 14;
	plane.h = 15;*/

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
	if (App->scene_guile->IsEnabled) {
		timechar[0] = timerint / 10 + '0';
		timechar[1] = timerint % 10 + '0';
	}

	//Blits
	if (stage)
	{
		timerint = 99 - App->scene_guile->timeLimit;
		
		App->render->Blit(graphicsUI, 30, 20, &healthbar, 1.0f, false); //healthbar
		App->render->Blit(graphicsUI, 31, 23, &health, 1.0f, false); //health
		App->render->Blit(graphicsUI, 207, 23, &health2, 1.0f, false); //health

		App->render->Blit(graphicsUI, 31, 35, &name, 1.0f, false); //name p1
		App->render->Blit(graphicsUI, 293, 35, &name2, 1.0f, false); //name p2
		App->render->Blit(graphicsUI, 6, 1, &score, 1.0f, false); //score
		App->fonts->BlitText(178, 36, 0, timechar); //timer

		App->render->Blit(graphicsUI, 293, 35, &name2, 1.0f, false); //Round Token P1
		//App->render->Blit(graphicsUI, 178, 34, &timer, 1.0f, false); //timer
	}
	
	/*if (character_select)
	{
		App->render->Blit(graphicsUI, 128, 144, &characterGrid, 1.0f, false); //Character Grid.
		App->render->Blit(graphicsUI, p1_pointerPosX, p1_pointerPosY, &(p1_pointerAnim.GetCurrentFrame())); //Character Pointer 1.
		App->render->Blit(graphicsUI, p2_pointerPosX, p2_pointerPosY, &(p2_pointerAnim.GetCurrentFrame())); //Character Pointer 2.

		if (brazilP1) { App->render->Blit(graphicsUI, 264, 95, &countryFlagP1, 1.0f, false); } //Country Flag
		if (brazilP2) { App->render->Blit(graphicsUI, 264, 95, &countryFlagP2, 1.0f, false); } //Country Flag
		
		if (stageFlag) 
		{ 
			App->render->Blit(graphicsUI, 282, 59, &countryFlagStage, 1.0f, false); //Stage Flag
			App->render->Blit(graphicsUI, planePosX, planePosY, &plane, 1.0f, false); //Plane
		}

		if (p1_characterSelect) { App->render->Blit(graphicsUI, 264, 87, &p1_pointer, 1.0f, false); } //Flag Marker P1
		if (p2_characterSelect) { App->render->Blit(graphicsUI, 264, 87, &p2_pointer, 1.0f, false); } //Flag Marker P2

		if (ryuIconP1) { App->render->Blit(graphicsUI, 0, 113, &characterIconP1, 1.0f, false); } // P1 Ryu Icon
		if (blankaIconP1) { App->render->Blit(graphicsUI, 0, 113, &characterIconP1II, 1.0f, false); } //P1 Blanka Icon
		if (ryuIconP2) { App->render->Blit(graphicsUI, 288, 113, &characterIconP2, 1.0f, false); } //P2 Ryu Icon
		if (blankaIconP2) { App->render->Blit(graphicsUI, 288, 113, &characterIconP2II, 1.0f, false); } //P2 Blanka Icon
	}*/

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
