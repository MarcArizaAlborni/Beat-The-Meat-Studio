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
	icoin_screen = { 2688, 2016, SCREEN_WIDTH, SCREEN_HEIGHT };
	
	small_turn.PushBack({ 0, 0, 384, 224});
	small_turn.PushBack({ 384, 0, 384, 224 });
	small_turn.PushBack({ 768, 0, 384, 224 });
	small_turn.PushBack({ 1152, 0, 384, 224 });
	small_turn.PushBack({ 1536, 0, 384, 224 });
	small_turn.PushBack({ 1920, 0, 384, 224 });
	small_turn.PushBack({ 2304, 0, 384, 224 });
	small_turn.PushBack({ 2688, 0, 384, 224 });
	small_turn.PushBack({ 3072, 0, 384, 224 });
	small_turn.PushBack({ 3456, 0, 384, 224 });
	small_turn.PushBack({ 0, 224, 384, 224 });
	small_turn.PushBack({ 384, 224, 384, 224 });
	small_turn.PushBack({ 768, 224, 384, 224 });
	small_turn.PushBack({ 1152, 224, 384, 224 });
	small_turn.PushBack({ 1536, 224, 384, 224 });
	small_turn.PushBack({ 1920, 224, 384, 224 });
	small_turn.PushBack({ 2304, 224, 384, 224 });
	small_turn.PushBack({ 2688, 224, 384, 224 });
	small_turn.PushBack({ 3072, 224, 384, 224 });
	small_turn.PushBack({ 3456, 224, 384, 224 });
	small_turn.PushBack({ 0, 448, 384, 224 });
	small_turn.PushBack({ 384, 448, 384, 224 });
	small_turn.PushBack({ 768, 448, 384, 224 });
	small_turn.PushBack({ 1152, 448, 384, 224 });
	small_turn.PushBack({ 1536, 448, 384, 224 });
	small_turn.PushBack({ 1920, 448, 384, 224 });
	small_turn.PushBack({ 2304, 448, 384, 224 });
	small_turn.PushBack({ 2688, 448, 384, 224 });
	small_turn.PushBack({ 3072, 448, 384, 224 });
	small_turn.PushBack({ 3456, 448, 384, 224 });

	small_turn.speed = 0.4f;

	
	big_turn.PushBack({ 0, 672, 384, 224 });
	big_turn.PushBack({ 384, 672, 384, 224 });
	big_turn.PushBack({ 768, 672, 384, 224 });
	big_turn.PushBack({ 1152, 672, 384, 224 });
	big_turn.PushBack({ 1536, 672, 384, 224 });
	big_turn.PushBack({ 1920, 672, 384, 224 });
	big_turn.PushBack({ 2304, 672, 384, 224 });
	big_turn.PushBack({ 2688, 672, 384, 224 });
	big_turn.PushBack({ 3072, 672, 384, 224 });
	big_turn.PushBack({ 3456, 672, 384, 224 });
	big_turn.PushBack({ 0, 896, 384, 224 });
	big_turn.PushBack({ 384, 896, 384, 224 });
	big_turn.PushBack({ 768, 896, 384, 224 });
	big_turn.PushBack({ 1152, 896, 384, 224 });
	big_turn.PushBack({ 1536, 896, 384, 224 });
	big_turn.PushBack({ 1920, 896, 384, 224 });
	big_turn.PushBack({ 2304, 896, 384, 224 });
	big_turn.PushBack({ 2688, 896, 384, 224 });
	big_turn.PushBack({ 3072, 896, 384, 224 });
	big_turn.PushBack({ 3456, 896, 384, 224 });
	big_turn.PushBack({ 0, 1120, 384, 224 });
	big_turn.PushBack({ 384, 1120, 384, 224 });
	big_turn.PushBack({ 768, 1120, 384, 224 });
	big_turn.PushBack({ 1152, 1120, 384, 224 });
	big_turn.PushBack({ 1536, 1120, 384, 224 });
	big_turn.PushBack({ 1920, 1120, 384, 224 });
	big_turn.PushBack({ 2304, 1120, 384, 224 });
	big_turn.PushBack({ 2688, 1120, 384, 224 });
	big_turn.PushBack({ 3072, 1120, 384, 224 });
	big_turn.PushBack({ 3456, 1120, 384, 224 });

	big_turn.speed = 0.4f;

	horitzontal_dis.PushBack({ 0, 1344, 384, 224 });
	horitzontal_dis.PushBack({ 384, 1344, 384, 224 });
	horitzontal_dis.PushBack({ 768, 1344, 384, 224 });
	horitzontal_dis.PushBack({ 1152, 1344, 384, 224 });
	horitzontal_dis.PushBack({ 1536, 1344, 384, 224 });
	horitzontal_dis.PushBack({ 1920, 1344, 384, 224 });
	horitzontal_dis.PushBack({ 2304, 1344, 384, 224 });
	horitzontal_dis.PushBack({ 2688, 1344, 384, 224 });
	horitzontal_dis.PushBack({ 3072, 1344, 384, 224 });
	horitzontal_dis.PushBack({ 3456, 1344, 384, 224 });
	horitzontal_dis.PushBack({ 0, 1568, 384, 224 });
	horitzontal_dis.PushBack({ 384, 1568, 384, 224 });
	horitzontal_dis.PushBack({ 768, 1568, 384, 224 });
	horitzontal_dis.PushBack({ 1152, 1568, 384, 224 });
	horitzontal_dis.PushBack({ 1536, 1568, 384, 224 });
	horitzontal_dis.PushBack({ 1920, 1568, 384, 224 });
	horitzontal_dis.PushBack({ 2304, 1568, 384, 224 });
	horitzontal_dis.PushBack({ 2688, 1568, 384, 224 });
	horitzontal_dis.PushBack({ 3072, 1568, 384, 224 });
	horitzontal_dis.PushBack({ 3456, 1568, 384, 224 });
	horitzontal_dis.PushBack({ 0, 1792, 384, 224 });
	horitzontal_dis.PushBack({ 384, 1792, 384, 224 });
	horitzontal_dis.PushBack({ 768, 1792, 384, 224 });
	horitzontal_dis.PushBack({ 1152, 1792, 384, 224 });
	horitzontal_dis.PushBack({ 1536, 1792, 384, 224 });
	horitzontal_dis.PushBack({ 1920, 1792, 384, 224 });
	horitzontal_dis.PushBack({ 2304, 1792, 384, 224 });
	horitzontal_dis.PushBack({ 2688, 1792, 384, 224 });
	horitzontal_dis.PushBack({ 3072, 1792, 384, 224 });
	horitzontal_dis.PushBack({ 3456, 1792, 384, 224 });
	horitzontal_dis.PushBack({ 0, 2016, 384, 224 });
	horitzontal_dis.PushBack({ 384, 2016, 384, 224 });
	horitzontal_dis.PushBack({ 768, 2016, 384, 224 });
	horitzontal_dis.PushBack({ 1152, 2016, 384, 224 });
	horitzontal_dis.PushBack({ 1536, 2016, 384, 224 });
	horitzontal_dis.PushBack({ 1920, 2016, 384, 224 });
	horitzontal_dis.PushBack({ 2304, 2016, 384, 224 });
	horitzontal_dis.PushBack({ 2688, 2016, 384, 224 });

	horitzontal_dis.speed = 0.4f;



}

ModuleIcoinScreen::~ModuleIcoinScreen()
{

}

// Load assets
bool ModuleIcoinScreen::Start()
{
	LOG("Loading Welcome screen");
	graphics = App->textures->Load("Sprites/SFanimation.png");
	App->render->camera.y = 0;
	App->ui->Enable();
	App->ui->StreetLogo = true;
	return true;
}

// UnLoad assets
bool ModuleIcoinScreen::CleanUp()
{
	LOG("Unloading Introduce coin Screen");
	App->textures->Unload(graphics);
	App->ui->Disable();
	App->ui->StreetLogo = false;
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
		cur_anim = &icoin_screen;
	}



	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleIcoinScreen::Update()
{
	
	App->render->Blit(graphics, 0, 0, cur_anim);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_2] == KEY_DOWN) {

		App->fade->FadeToBlack(App->icoin_screen, App->start_screen, 1.0f);

	}

	return UPDATE_CONTINUE;
}