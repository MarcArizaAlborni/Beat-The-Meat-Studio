#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "MemLeaks.h"
#include "ModuleIcoinScreen.h"
#include "ModuleStartScreen.h"
#include "ModuleCharacterSelect.h"
#include "Animation.h"
#include "ModuleSceneGuile.h"
#include "ModuleUI.h"

ModuleCharacterSelect::ModuleCharacterSelect()
{
	character_screen.x = 0;
	character_screen.y = 0;
	character_screen.w = SCREEN_WIDTH;
	character_screen.h = SCREEN_HEIGHT;
}

ModuleCharacterSelect::~ModuleCharacterSelect()
{

}

// Load assets
bool ModuleCharacterSelect::Start()
{
	LOG("Loading Character Select screen");
	graphics = App->textures->Load("Sprites/Character_Select_WorldMap.png");

	App->ui->Enable();
	App->ui->character_select = true;

	App->ui->p1_pointerPosX = 129;
	App->ui->p1_pointerPosY = 141;

	App->ui->p2_pointerPosX = 129;
	App->ui->p2_pointerPosY = 173;

	//character_screen = App->audio->LoadMus("Audios/Music/02 Credit.ogg");
	return true;
}

// UnLoad assets
bool ModuleCharacterSelect::CleanUp()
{
	LOG("Unloading Character Select Screen");
	App->textures->Unload(graphics);
	App->ui->character_select = false;
	App->ui->Disable();
	//App->audio->UnLoadMusic();
	return true;
}

// Update: draw background
update_status ModuleCharacterSelect::Update()
{
	App->render->Blit(graphics, 0, 0, &character_screen, 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN) 
	{
		App->fade->FadeToBlack(App->character_select, App->scene_guile, 5.0f);
	}

	//Pointer player 1
	if (App->input->keyboard[SDL_SCANCODE_UP] == 1)
	{
		if (App->ui->p1_pointerPosY != 141) { App->ui->p1_pointerPosY -= 32; }
		else { App->ui->p1_pointerPosY = 141; }
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == 1)
	{
		if (App->ui->p1_pointerPosY != 173) { App->ui->p1_pointerPosY += 32; }
		else { App->ui->p1_pointerPosY = 173; }
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1)
	{
		if (App->ui->p1_pointerPosX != 129) { App->ui->p1_pointerPosX -= 32; }
		else { App->ui->p1_pointerPosX != 129; }
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == 1)
	{
		if (App->ui->p1_pointerPosX != 225) { App->ui->p1_pointerPosX += 32; }
		else { App->ui->p1_pointerPosX = 225; }
	}

	//Pointer player 2
	if (App->input->keyboard[SDL_SCANCODE_U] == 1)
	{
		if(App->ui->p2_pointerPosY != 141) { App->ui->p2_pointerPosY -= 32; }
		else { App->ui->p2_pointerPosY = 141; }
	}

	if (App->input->keyboard[SDL_SCANCODE_J] == 1)
	{
		if (App->ui->p2_pointerPosY != 173) { App->ui->p2_pointerPosY += 32; }
		else { App->ui->p2_pointerPosY = 173; }
	}

	if (App->input->keyboard[SDL_SCANCODE_H] == 1)
	{
		if (App->ui->p2_pointerPosX != 129) { App->ui->p2_pointerPosX -= 32; }
		else { App->ui->p2_pointerPosX = 129; }
	}

	if (App->input->keyboard[SDL_SCANCODE_K] == 1)
	{
		if (App->ui->p2_pointerPosX != 225) { App->ui->p2_pointerPosX += 32; }
		else { App->ui->p2_pointerPosX = 225; }
	}

	//Pointer Flags


	return UPDATE_CONTINUE;
}