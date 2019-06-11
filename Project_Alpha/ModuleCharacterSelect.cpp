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
	CS_sound = App->audio->LoadMus("Audios/Music/03 Player Select.ogg");
	App->audio->PlayMusic(CS_sound, 0);
	cursor_sound = App->audio->LoadFx("Audios/FX/21H.wav");
	accept_sound = App->audio->LoadFx("Audios/FX/22H.wav");
	plane_sound = App->audio->LoadFx("Audios/FX/Enviroment/Plane.wav");
	flag_sound = App->audio->LoadFx("Audios/Voices/USA.wav");

	App->ui->Enable();
	App->ui->character_select = true;

	App->ui->p1_pointerPosX = 129;
	App->ui->p1_pointerPosY = 141;

	App->ui->p2_pointerPosX = 129;
	App->ui->p2_pointerPosY = 173;

	deltaTimeCh = SDL_GetTicks() / 1000;
	startTimeCh = deltaTimeCh;

	

	return true;
}

// UnLoad assets
bool ModuleCharacterSelect::CleanUp()
{
	LOG("Unloading Character Select Screen");
	App->textures->Unload(graphics);
	App->ui->character_select = false;

	App->ui->p1_characterSelect = false;
	App->ui->p2_characterSelect = false;
	App->ui->brazilP1 = false;
	App->ui->brazilP2 = false;
	App->ui->stageFlag = false;
	App->ui->ryuIconP1 = false;
	App->ui->kenIconP1 = false;
	App->ui->blankaIconP1 = false;
	App->ui->ryuIconP2 = false;
	App->ui->kenIconP2 = false;
	App->ui->blankaIconP2 = false;
	landing = false;
	playedplane = false;
	flagplayed = false;
	App->ui->planePosX = 269.0f;
	App->ui->planePosY = 96.0f;
	App->ui->Disable();

	App->audio->UnLoadMusic(CS_sound);
	App->audio->UnLoadFX(cursor_sound);
	App->audio->UnLoadFX(accept_sound);
	App->audio->UnLoadFX(plane_sound);
	App->audio->UnLoadFX(flag_sound);
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

		if (App->ui->p1_characterSelect) { App->render->Blit(App->ui->graphicsUI, App->ui->p1_pointerPosX, App->ui->p1_pointerPosY, &App->ui->p1_pointer, 1.0f, false); } //Pointer P1 remains no longer blinks once a character is selected.
		if (App->ui->p2_characterSelect) { App->render->Blit(App->ui->graphicsUI, App->ui->p2_pointerPosX, App->ui->p2_pointerPosY, &App->ui->p2_pointer, 1.0f, false); } //Pointer P2 remains no longer blinks once a character is selected.

		if (App->ui->brazilP1) { App->render->Blit(App->ui->graphicsUI, 264, 95, &App->ui->countryFlagP1, 1.0f, false); } //Country Flag
		if (App->ui->brazilP2) { App->render->Blit(App->ui->graphicsUI, 264, 95, &App->ui->countryFlagP2, 1.0f, false); } //Country Flag

		if (App->ui->stageFlag)
		{
			//App->render->Blit(App->ui->graphicsUI, 282, 59, &App->ui->countryFlagStage, 1.0f, false); //Stage Flag
			App->render->Blit(App->ui->graphicsUI, 282, 59, &(App->ui->stageFlagAnimation.GetCurrentFrame()));
			App->render->Blit(App->ui->graphicsUI, App->ui->planePosX, App->ui->planePosY, &App->ui->plane, 1.0f, false); //Plane
		}

		if (App->ui->p1_characterSelect) { App->render->Blit(App->ui->graphicsUI, 264, 87, &App->ui->p1_pointer, 1.0f, false); } //Flag Marker P1
		if (App->ui->p2_characterSelect) { App->render->Blit(App->ui->graphicsUI, 264, 87, &App->ui->p2_pointer, 1.0f, false); } //Flag Marker P2

		if (App->ui->ryuIconP1) { App->render->Blit(App->ui->graphicsUI, 0, 113, &App->ui->characterIconRyuP1, 1.0f, false); } // P1 Ryu Icon
		if (App->ui->kenIconP1) { App->render->Blit(App->ui->graphicsUI, 0, 113, &App->ui->characterIconKenP1, 1.0f, false); } // P1 Ken Icon
		if (App->ui->blankaIconP1) { App->render->Blit(App->ui->graphicsUI, 0, 113, &App->ui->characterIconBlankaP1, 1.0f, false); } //P1 Blanka Icon

		if (App->ui->ryuIconP2) { App->render->Blit(App->ui->graphicsUI, 288, 113, &App->ui->characterIconRyuP2, 1.0f, false); } //P2 Ryu Icon
		if (App->ui->kenIconP2) { App->render->Blit(App->ui->graphicsUI, 288, 113, &App->ui->characterIconKenP2, 1.0f, false); } // P2 Ken Icon
		if (App->ui->blankaIconP2) { App->render->Blit(App->ui->graphicsUI, 288, 113, &App->ui->characterIconBlankaP2, 1.0f, false); } //P2 Blanka Icon
	}
	
	//Pointer Flags
	if (App->ui->p1_pointerPosX == 193 && App->ui->p1_pointerPosY == 141 && App->input->keyboard[SDL_SCANCODE_U] == 1 || App->input->game_pad[SDL_CONTROLLER_BUTTON_X][GAME_PAD_1] == KEY_DOWN)
	{
		App->audio->PlayFx(accept_sound);
		App->ui->p1_characterSelect = true;
	}

	if (App->ui->p2_pointerPosX == 193 && App->ui->p2_pointerPosY == 141 && App->input->keyboard[SDL_SCANCODE_KP_7] == 1 || App->input->game_pad[SDL_CONTROLLER_BUTTON_X][GAME_PAD_2] == KEY_DOWN)
	{
		App->audio->PlayFx(accept_sound);
		App->ui->p2_characterSelect = true;
	}

	if (App->ui->p1_characterSelect == true && App->ui->p2_characterSelect == true) { App->ui->stageFlag = true;} //Enables the flag Animation



	if (App->ui->p1_characterSelect == false)
	{
		//Pointer movement player 1
		if (App->input->keyboard[SDL_SCANCODE_W] == 1|| SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000)
		{
		
			if (App->ui->p1_pointerPosY != 141) { App->ui->p1_pointerPosY -= 32; App->audio->PlayFx(cursor_sound);}
			else { App->ui->p1_pointerPosY = 141; }
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == 1|| SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) >= 10000)
		{
			if (App->ui->p1_pointerPosY != 173) { App->ui->p1_pointerPosY += 32; App->audio->PlayFx(cursor_sound);}
			else { App->ui->p1_pointerPosY = 173; }
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == 1|| SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_LEFT) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) <= -10000)
		{
		
			if (App->ui->p1_pointerPosX != 129) { App->ui->p1_pointerPosX -= 32; App->audio->PlayFx(cursor_sound);}
			else { App->ui->p1_pointerPosX != 129; }
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == 1 || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) >= 10000)
		{
			
			if (App->ui->p1_pointerPosX != 225) { App->ui->p1_pointerPosX += 32; App->audio->PlayFx(cursor_sound);}
			else { App->ui->p1_pointerPosX = 225; }
		}

		//Activation or deactivation of the character icons depending on where the p1's cursor is
		if (App->ui->p1_pointerPosX == 129 && App->ui->p1_pointerPosY == 141) { App->ui->ryuIconP1 = true; }
		else { App->ui->ryuIconP1 = false; }

		if (App->ui->p1_pointerPosX == 129 && App->ui->p1_pointerPosY == 173) { App->ui->kenIconP1 = true; }
		else { App->ui->kenIconP1 = false; }

		if (App->ui->p1_pointerPosX == 193 && App->ui->p1_pointerPosY == 141) { App->ui->blankaIconP1 = true; App->ui->brazilP1 = true; }
		else { App->ui->blankaIconP1 = false; App->ui->brazilP1 = false; }
	}
	
	if (App->ui->p2_characterSelect == false)
	{
		//Pointer movement player 2
		if (App->input->keyboard[SDL_SCANCODE_UP] == 1|| SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTY) <= -10000)
		{
			if (App->ui->p2_pointerPosY != 141) { App->ui->p2_pointerPosY -= 32; App->audio->PlayFx(cursor_sound);}
			else { App->ui->p2_pointerPosY = 141; }
		}

		if (App->input->keyboard[SDL_SCANCODE_DOWN] == 1|| SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTY) >= 10000)
		{
			if (App->ui->p2_pointerPosY != 173) { App->ui->p2_pointerPosY += 32; App->audio->PlayFx(cursor_sound);}
			else { App->ui->p2_pointerPosY = 173; }
		}

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1 || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_LEFT) || SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTX) <= -10000)
		{
			if (App->ui->p2_pointerPosX != 129) { App->ui->p2_pointerPosX -= 32; App->audio->PlayFx(cursor_sound);}
			else { App->ui->p2_pointerPosX = 129; }
		}

		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == 1 || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTX) >= 10000)
		{
			if (App->ui->p2_pointerPosX != 225) { App->ui->p2_pointerPosX += 32; App->audio->PlayFx(cursor_sound);}
			else { App->ui->p2_pointerPosX = 225; }
		}

		//Activation or deactivation of the character icons depending on where the p2's cursor is
		if (App->ui->p2_pointerPosX == 129 && App->ui->p2_pointerPosY == 141) { App->ui->ryuIconP2 = true; }
		else { App->ui->ryuIconP2 = false; }

		if (App->ui->p2_pointerPosX == 129 && App->ui->p2_pointerPosY == 173) { App->ui->kenIconP2 = true; }
		else { App->ui->kenIconP2 = false; }

		if (App->ui->p2_pointerPosX == 193 && App->ui->p2_pointerPosY == 141) { App->ui->blankaIconP2 = true; App->ui->brazilP2 = true; }
		else { App->ui->blankaIconP2 = false; App->ui->brazilP2 = false; }
	}
	
	//Puts a time limit to the character selection screen
	deltaTimeCh = SDL_GetTicks() / 1000;
	timeLimitCh = deltaTimeCh - startTimeCh;

	if (timeLimitCh >= 30)
	{
		//Putting both cursors on Blanka's space in the character grid
		App->ui->p1_pointerPosX = 193;
		App->ui->p1_pointerPosY = 141;
		App->ui->p2_pointerPosX = 193;
		App->ui->p2_pointerPosY = 141;

		//Deactivation of all icons and activation of the Blanka Icons
		App->ui->ryuIconP1 = false;
		App->ui->ryuIconP2 = false;
		App->ui->kenIconP1 = false;
		App->ui->kenIconP2 = false;
		App->ui->blankaIconP1 = true;
		App->ui->blankaIconP2 = true;

		//The character/s is/are selected
		App->ui->p1_characterSelect = true;
		App->ui->p2_characterSelect = true;

		App->ui->stageFlag = true;
	}
	
	
	//Plane Movement
	if (App->ui->stageFlag == true)
	{
		if (App->ui->planePosX <= 296.0f && App->ui->planePosY >= 66.0f)
		{
			
				App->ui->planePosX += 0.3f;
				App->ui->planePosY -= 0.55f;
				
			if (!playedplane) {
				App->audio->PlayFx(plane_sound);
				playedplane = true;
			}
		}
		else
		{
			landing = true;
		}
		if (landing)
		{
			if (!flagplayed) {
				App->audio->PlayFx(flag_sound);
				flagplayed = true;
			}

			App->fade->FadeToBlack(App->character_select, App->vs_screen, 3.7f);
			App->audio->FinishMusic(2000);
			
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_RETURN] || App->input->game_pad[SDL_CONTROLLER_BUTTON_START][GAME_PAD_1] == KEY_DOWN)
	{
		
		App->fade->FadeToBlack(App->character_select, App->vs_screen, 3.7f);
		App->audio->FinishMusic(2000);

	}
	return UPDATE_CONTINUE;
}