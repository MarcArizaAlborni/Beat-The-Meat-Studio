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
#include "ModuleVsScreen.h"
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

	deltaTimeCh = SDL_GetTicks() / 1000;
	startTimeCh = deltaTimeCh;

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

	//Renders
	if (App->ui->character_select)
	{
		App->render->Blit(App->ui->graphicsUI, 128, 144, &App->ui->characterGrid, 1.0f, false); //Character Grid.
		App->render->Blit(App->ui->graphicsUI, App->ui->p1_pointerPosX, App->ui->p1_pointerPosY, &(App->ui->p1_pointerAnim.GetCurrentFrame())); //Character Pointer 1.
		App->render->Blit(App->ui->graphicsUI, App->ui->p2_pointerPosX, App->ui->p2_pointerPosY, &(App->ui->p2_pointerAnim.GetCurrentFrame())); //Character Pointer 2.

		if (App->ui->brazilP1) { App->render->Blit(App->ui->graphicsUI, 264, 95, &App->ui->countryFlagP1, 1.0f, false); } //Country Flag
		if (App->ui->brazilP2) { App->render->Blit(App->ui->graphicsUI, 264, 95, &App->ui->countryFlagP2, 1.0f, false); } //Country Flag

		if (App->ui->stageFlag)
		{
			App->render->Blit(App->ui->graphicsUI, 282, 59, &App->ui->countryFlagStage, 1.0f, false); //Stage Flag
			App->render->Blit(App->ui->graphicsUI, App->ui->planePosX, App->ui->planePosY, &App->ui->plane, 1.0f, false); //Plane
		}

		if (App->ui->p1_characterSelect) { App->render->Blit(App->ui->graphicsUI, 264, 87, &App->ui->p1_pointer, 1.0f, false); } //Flag Marker P1
		if (App->ui->p2_characterSelect) { App->render->Blit(App->ui->graphicsUI, 264, 87, &App->ui->p2_pointer, 1.0f, false); } //Flag Marker P2

		if (App->ui->ryuIconP1) { App->render->Blit(App->ui->graphicsUI, 0, 113, &App->ui->characterIconP1, 1.0f, false); } // P1 Ryu Icon
		if (App->ui->blankaIconP1) { App->render->Blit(App->ui->graphicsUI, 0, 113, &App->ui->characterIconP1II, 1.0f, false); } //P1 Blanka Icon
		if (App->ui->ryuIconP2) { App->render->Blit(App->ui->graphicsUI, 288, 113, &App->ui->characterIconP2, 1.0f, false); } //P2 Ryu Icon
		if (App->ui->blankaIconP2) { App->render->Blit(App->ui->graphicsUI, 288, 113, &App->ui->characterIconP2II, 1.0f, false); } //P2 Blanka Icon
	}
	
	//Pointer Flags
	if (App->ui->p1_pointerPosX == 193 && App->ui->p1_pointerPosY == 141 && App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		App->ui->p1_characterSelect = true;
	}

	if (App->ui->p2_pointerPosX == 193 && App->ui->p2_pointerPosY == 141 && App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		App->ui->p2_characterSelect = true;
	}

	if (App->ui->p1_characterSelect == true && App->ui->p2_characterSelect == true) { App->ui->stageFlag = true; }



	if (App->ui->p1_characterSelect == false)
	{
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

		if (App->ui->p1_pointerPosX == 129) { App->ui->ryuIconP1 = true; }
		else { App->ui->ryuIconP1 = false; }

		if (App->ui->p1_pointerPosX == 193) { App->ui->blankaIconP1 = true; App->ui->brazilP1 = true; }
		else { App->ui->blankaIconP1 = false; App->ui->brazilP1 = false; }
	}
	
	if (App->ui->p2_characterSelect == false)
	{
		//Pointer player 2
		if (App->input->keyboard[SDL_SCANCODE_U] == 1)
		{
			if (App->ui->p2_pointerPosY != 141) { App->ui->p2_pointerPosY -= 32; }
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

		if (App->ui->p2_pointerPosX == 129) { App->ui->ryuIconP2 = true; }
		else { App->ui->ryuIconP2 = false; }

		if (App->ui->p2_pointerPosX == 193) { App->ui->blankaIconP2 = true; App->ui->brazilP2 = true; }
		else { App->ui->blankaIconP2 = false; App->ui->brazilP2 = false; }
	}
	
	deltaTimeCh = SDL_GetTicks() / 1000;
	timeLimitCh = deltaTimeCh - startTimeCh;

	if (timeLimitCh >= 40)
	{
		App->ui->p1_pointerPosX = 193;
		App->ui->p1_pointerPosY = 141;
		App->ui->p2_pointerPosX = 193;
		App->ui->p2_pointerPosY = 141;

		App->ui->p1_characterSelect = true;
		App->ui->p2_characterSelect = true;
		App->ui->stageFlag = true;
	}
	
	
	
	if (App->ui->stageFlag == true)
	{
		if (App->ui->planePosX <= 296.0f && App->ui->planePosY >= 66.0f)
		{
			App->ui->planePosX += 0.3f;
			App->ui->planePosY -= 0.55f;
		}

		else
		{
			landing = true;
		}

		if (landing)
		{
			deltaTimeCh = SDL_GetTicks() / 1000;
			lapseVs = deltaTimeCh - startTimeCh;

			if (lapseVs >= 3)
			{
				App->fade->FadeToBlack(App->character_select, App->vs_screen, 5.0f);
			}
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->character_select, App->vs_screen, 5.0f);

	}


	return UPDATE_CONTINUE;
}