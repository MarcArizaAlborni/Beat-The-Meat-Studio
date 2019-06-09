#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "MemLeaks.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleIcoinScreen.h"
#include "ModuleStartScreen.h"
#include "Animation.h"
#include "ModuleSceneRyu.h"
#include "ModuleUI.h"

ModuleIcoinScreen::ModuleIcoinScreen()
{
	icoin_screen = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	
	small_turn.PushBack({});
}

ModuleIcoinScreen::~ModuleIcoinScreen()
{

}

// Load assets
bool ModuleIcoinScreen::Start()
{
	LOG("Loading Welcome screen");
	graphics = App->textures->Load("Sprites/StreetFighter.png");
	graphics2 = App->textures->Load("Sprites/StartScreenIII_I.png");
	App->render->camera.y = 0;
	App->ui->Enable();
	App->ui->insert_coin = true;
	return true;
}

// UnLoad assets
bool ModuleIcoinScreen::CleanUp()
{
	LOG("Unloading Introduce coin Screen");
	App->textures->Unload(graphics);
	App->ui->Disable();
	App->ui->insert_coin = false;
	return true;
}

update_status ModuleIcoinScreen::PreUpdate()
{
	cur_anim = &small_turn.GetCurrentFrame();

	if (small_turn.Finished()) {

		cur_anim = &big_turn.GetCurrentFrame();
	}

	if (big_turn.Finished()) 
	{
		cur_anim = &horitzontal_dis.GetCurrentFrame();
	}

	if (horitzontal_dis.Finished())
	{
		cur_anim = &icon_screen2;
	}

	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleIcoinScreen::Update()
{
	
	App->render->Blit(graphics, 0, 0, &icoin_screen);
	App->render->Blit(graphics2, 0, 0, cur_anim);

	return UPDATE_CONTINUE;
}