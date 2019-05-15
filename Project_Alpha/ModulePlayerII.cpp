#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayerII.h"
#include "Animation.h"
#include "ModuleFonts.h"
#include "ModuleCollision.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayer.h"
#include <stdio.h>


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

int speedII = 2;
Uint8 alphakaII = 255;
float gravityII = 1;
int groundLevelII = 205;
int maxHeightII = 120;
bool airkickII = true;
bool alreadyHit2 = false;

ModulePlayer2::ModulePlayer2()
{
	graphicsP2 = NULL;
	currentP2_animation = NULL;

	score = 0;

	healthP2.x = 100;
	healthP2.y = 400;
	healthP2.w = 200;
	healthP2.h = 20;

	

	//Idle animation (arcade sprite sheet)
	idleP2.PushBack({ 28, 27, 105, 100 });
	idleP2.PushBack({ 133, 27, 100, 100 });
	idleP2.PushBack({ 233, 27, 100, 100 });
	idleP2.speed = 0.08f;

	//Walk FORWARD Animation
	forwardP2.PushBack({ 699, 127, 97, 84 });
	forwardP2.PushBack({ 232, 127, 90, 84 });
	forwardP2.PushBack({ 322, 127, 100, 84 });
	forwardP2.PushBack({ 422, 127, 100, 84 });
	forwardP2.PushBack({ 522, 127, 88, 84 });
	forwardP2.PushBack({ 609, 127, 90, 84 });
	forwardP2.PushBack({ 132, 127, 100, 84 });
	forwardP2.PushBack({ 29, 127, 105, 84 });
	forwardP2.loop = true;
	forwardP2.speed = 0.1f;

	//Walk backwards animation
	backwardP2.PushBack({ 694, 211, 101, 101 });
	backwardP2.PushBack({ 609, 211, 85, 101 });
	backwardP2.PushBack({ 522, 211, 87, 101 });
	backwardP2.PushBack({ 232, 211, 91, 101 });
	backwardP2.PushBack({ 322, 211, 105, 101 });
	backwardP2.PushBack({ 427, 211, 95, 101 });
	backwardP2.PushBack({ 132, 211, 100, 101 });
	backwardP2.PushBack({ 29, 211, 104, 101 });
	backwardP2.loop = true;
	backwardP2.speed = 0.1f;

	//Crouch Animation
	crouchP2.PushBack({ 427, 323, 99, 94 });
	crouchP2.PushBack({ 526, 323, 89, 94 });
	crouchP2.PushBack({ 615, 323, 93, 94 });
	crouchP2.speed = 0.5f;
	crouchP2.loop = false;
	
}

ModulePlayer2::~ModulePlayer2()
{

}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");


	graphicsP2 = App->textures->Load("Sprites/BlankaP2.png"); // JA TE LA FOTO BONA

	//Player 2 stest collider
	playerP2_collider = App->collision->AddCollider({ positionP2.x, positionP2.y - 100,56,93 }, COLLIDER_PLAYER2, App->player2);
	attackP2_collider = nullptr;


	return true;
}


bool ModulePlayer2::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphicsP2);

	return true;
}


update_status ModulePlayer2::PreUpdate() {



	//MOVE BACKWARD
	//inputplayerP2.Right_active = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_REPEAT;
	////MOVE FORWARD
	//inputplayerP2.Left_active = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_REPEAT;
	////JUMP
	//inputplayerP2.Up_active = App->input->keyboard[SDL_SCANCODE_UP] == KEY_REPEAT;  
	////CROUCH
	//inputplayerP2.Down_active = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_REPEAT;

	
	App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_2] == KEY_DOWN;
	App->input->game_pad[SDL_CONTROLLER_BUTTON_B][GAME_PAD_2] == KEY_DOWN;
	App->input->game_pad[SDL_CONTROLLER_BUTTON_X][GAME_PAD_2] == KEY_DOWN;

	 inputplayerP2.Right_active = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)|| SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP2.Left_active = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_LEFT)|| SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	 inputplayerP2.Down_active = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP2.Up_active = App->input->keyboard[SDL_SCANCODE_UP] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTY) >= -10000;


	{
		//IDLE STATE
		if (currentstateP2 == idlestateP2) {
			if (inputplayerP2.Right_active) {
				currentstateP2 = backwardstateP2;
				LOG("IDLE TO BACK");
			}
			if (inputplayerP2.Left_active) {
				currentstateP2 = forwardstateP2;
LOG("IDLE TO forward");
			}
			if (inputplayerP2.Down_active) {
				currentstateP2 = crouchstateP2;
				LOG("IDLE to CROUCH");
			}
		}
		//BACKWARDS STATE
		if (currentstateP2 == backwardstateP2) {
			if (!inputplayerP2.Right_active) {
				currentstateP2 = idlestateP2;
				LOG("BACK to IDLE");
			}
			if (inputplayerP2.Down_active) {
				currentstateP2 = crouchstateP2;
				LOG("BACK to CROUCH");
			}
		}
		//FORWARD STATE
		if (currentstateP2 == forwardstateP2) {
			if (!inputplayerP2.Left_active) {
				currentstateP2 = idlestateP2;
				LOG("FOR to IDLE");
			}
			if (inputplayerP2.Right_active) {
				currentstateP2 = backwardstateP2;
				LOG("FOR to BACK");
			}

			if (inputplayerP2.Down_active) {
				currentstateP2 = crouchstateP2;
				LOG("FOR to CROUCH");
			}
		}
		//COUCH STATE
		if (currentstateP2 == crouchstateP2) {
			if (!inputplayerP2.Down_active) {
				crouchP2.Reset();
				currentstateP2 = idlestateP2;
				LOG("CROUCH to IDLE");
			}
		}
	}

	return UPDATE_CONTINUE;

}

// Update: draw background
update_status ModulePlayer2::Update()
{

	switch (currentstateP2)
	{
	case idlestateP2:
		playerP2_collider->rect.h = 93;
		playerP2_collider->SetPos(positionP2.x - App->render->camera.x + 5 , positionP2.y - 93 - App->render->camera.y);
		currentP2_animation = &idleP2;
		LOG("IDLE ANIMATION ACTIVE");
		break;

	case backwardstateP2:
		playerP2_collider->rect.h = 93;
		playerP2_collider->SetPos(positionP2.x - App->render->camera.x + 5, positionP2.y - 93 - App->render->camera.y);
		currentP2_animation = &backwardP2;
		positionP2.x += speedII;
		LOG("BACK ANIMATION ACTIVE");
		break;
	case forwardstateP1:
		playerP2_collider->SetPos(positionP2.x - App->render->camera.x + 5, positionP2.y - 93 - App->render->camera.y);
		currentP2_animation = &forwardP2;
		positionP2.x -= speedII;
		LOG("FORWARD ANIMATION ACTIVE");
		break;

	case crouchstateP1:
		currentP2_animation = &crouchP2;
		playerP2_collider->rect.h = 65;
		playerP2_collider->SetPos(positionP2.x - App->render->camera.x + 5, positionP2.y - 68 - App->render->camera.y);
		LOG("CROUCHED ANIMATION ACTIVE");
		break;
	}

	SDL_Rect r = currentP2_animation->GetCurrentFrame();

	if (positionP2.x <= (App->render->camera.x - 10))
	{
		positionP2.x = (App->render->camera.x - 10);
	}
	if (positionP2.x >= (180 + App->render->camera.x) + 127)
	{
		positionP2.x = (180 + App->render->camera.x) + 127;
	}

	if (playerP2_collider->rect.x > App->player->playerP1_collider->rect.x) {
		App->render->Blit(graphicsP2, positionP2.x, positionP2.y - r.h, &r, 1.0f, true, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		App->render->Blit(graphicsP2, positionP2.x, positionP2.y - r.h, &r, 1.0f, true, SDL_FLIP_NONE);
	}


	return UPDATE_CONTINUE;
}


void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	if(c1->type == COLLIDER_PLAYER2 && c2->type == COLLIDER_PLAYER && inputplayerP2.Left_active ){

		speedII = 0;
	}
	else
	{
		speedII = 2;
	}

}