#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "ModuleFonts.h"
#include "ModuleCollision.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayerII.h"
#include <stdio.h>


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

int speed = 2;
Uint8 alphaka= 255;
int groundLevel = 205;
int maxHeight = 120; 
bool airkick = true;
bool alreadyHit = false;


ModulePlayer::ModulePlayer()
{
	graphicsP1 = NULL;
	currentP1_animation = NULL;

	score = 0;

	healthP1.x = 100;
	healthP1.y = 400; 
	healthP1.w = 200;
	healthP1.h = 20;
	
	//Idle animation (arcade sprite sheet)
	idleP1.PushBack({ 28, 27, 105, 100 });
	idleP1.PushBack({ 133, 27, 100, 100 });
	idleP1.PushBack({ 233, 27, 100, 100 });
	idleP1.speed = 0.08f;

	//Walk FORWARD Animation
	forwardP1.PushBack({ 699, 127, 97, 84 });
	forwardP1.PushBack({ 232, 127, 90, 84 });
	forwardP1.PushBack({ 322, 127, 100, 84 });
	forwardP1.PushBack({ 422, 127, 100, 84 });
	forwardP1.PushBack({ 522, 127, 88, 84 });
	forwardP1.PushBack({ 609, 127, 90, 84 });
	forwardP1.PushBack({ 132, 127, 100, 84 });
	forwardP1.PushBack({ 29, 127, 105, 84 });
	forwardP1.loop = true;
	forwardP1.speed = 0.1f;

	//Walk backwards animation
	backwardP1.PushBack({ 694, 211, 101, 101 });
	backwardP1.PushBack({ 609, 211, 85, 101 });
	backwardP1.PushBack({ 522, 211, 87, 101 });
	backwardP1.PushBack({ 232, 211, 91, 101 });
	backwardP1.PushBack({ 322, 211, 105, 101 });
	backwardP1.PushBack({ 427, 211, 95, 101 });
	backwardP1.PushBack({ 132, 211, 100, 101 });
	backwardP1.PushBack({ 29, 211, 104, 101 });
	backwardP1.loop = true;
	backwardP1.speed = 0.1f;

	//Crouch Animation
	crouchP1.PushBack({ 427, 323, 99, 94 });
	crouchP1.PushBack({ 526, 323, 89, 94 });
	crouchP1.PushBack({ 615, 323, 93, 94 });
	crouchP1.speed = 0.5f;
	crouchP1.loop = false;


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	graphicsP1 = App->textures->Load("Sprites/BlankaP1.png"); // JA TE LA FOTO BONA
	
	//Player 2 stest collider
	playerP1_collider = App->collision->AddCollider({ positionP1.x , positionP1.y - 100, 60, 93 }, COLLIDER_PLAYER, App->player);
	attackP1_collider = nullptr;
	return true;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphicsP1);
	return true;
}


update_status ModulePlayer::PreUpdate() {

	//MOVE BACKWARD
	//inputplayerP1.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
	//MOVE FORWARD
	//inputplayerP1.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
	//CROUCH
	//inputplayerP1.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
	//JUMP
//	inputplayerP1.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 
	// SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	/* inputplayerP1.right_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP1.down_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP1.up_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;
	 inputplayerP1.down_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;*/
	 App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN;
	 App->input->game_pad[SDL_CONTROLLER_BUTTON_B][GAME_PAD_1] == KEY_DOWN;
     App->input->game_pad[SDL_CONTROLLER_BUTTON_X][GAME_PAD_1] == KEY_DOWN;
	 inputplayerP1.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)|| SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP1.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_LEFT)|| SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	 inputplayerP1.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP1.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) >= -10000;
		
	{
		//IDLE STATE
		if (currentstateP1 == idlestateP1) {
			if (inputplayerP1.A_active ) {
				currentstateP1 = backwardstateP1;
				blockP1_collider = App->collision->AddCollider({ positionP1.x - App->render->camera.x +50 ,positionP1.y -50, 10, 30 }, COLLIDER_PLAYER_BLOCK, App->player);
				LOG("IDLE TO BACK");
			}
			if (inputplayerP1.D_active) {
				currentstateP1 = forwardstateP1;
				LOG("IDLE TO forward");
			}
			if (inputplayerP1.S_active) {
				currentstateP1 = crouchstateP1;
				LOG("IDLE to CROUCH");
			}
		}

		//BACKWARDS STATE
		if (currentstateP1 == backwardstateP1) {
			if (!inputplayerP1.A_active) {
				currentstateP1 = idlestateP1;
				blockP1_collider->to_delete = true;
				LOG("BACK to IDLE");
			}
			if (inputplayerP1.S_active) {
				currentstateP1 = crouchstateP1;
				blockP1_collider->to_delete = true;
				LOG("BACK to CROUCH");
			}
		}
		//FORWARD STATE
		if (currentstateP1 == forwardstateP1) {
			if (!inputplayerP1.D_active) {
				currentstateP1 = idlestateP1;
				LOG("FOR to IDLE");
			}
			if (inputplayerP1.A_active) {
				currentstateP1 = backwardstateP1;
				blockP1_collider = App->collision->AddCollider({ positionP1.x - App->render->camera.x +55, positionP1.y -80, 7, 30 }, COLLIDER_PLAYER_BLOCK, App->player);
				LOG("FOR to BACK");
			}

			if (inputplayerP1.S_active) {
				currentstateP1 = crouchstateP1;
				LOG("FOR to CROUCH");
			}
		}
		//COUCH STATE
		if (currentstateP1 == crouchstateP1) {
			if (!inputplayerP1.S_active) {
				crouchP1.Reset();
				currentstateP1 = idlestateP1;
				LOG("CROUCH to IDLE");
			}
		}


		return UPDATE_CONTINUE;
	}
}

update_status ModulePlayer::Update() {

	switch (currentstateP1)
	{

	case idlestateP1:
		playerP1_collider->rect.h = 93;
		//playerP1_collider->SetPos(positionP1.x - App->render->camera.x + 5, positionP1.y - 93 - App->render->camera.y);
		currentP1_animation = &idleP1;
		LOG("IDLE ANIMATION ACTIVE");
		break;

	case backwardstateP1:
		playerP1_collider->rect.h = 93;
		blockP1_collider->SetPos(positionP1.x + 55 - App->render->camera.x  *2, positionP1.y -80 );
		//playerP1_collider->SetPos(positionP1.x - App->render->camera.x + 5, positionP1.y - 93 - App->render->camera.y);
		currentP1_animation = &backwardP1;
		positionP1.x -= speed;
		LOG("BACK ANIMATION ACTIVE");
		break;

	case forwardstateP1:
		//playerP1_collider->SetPos(positionP1.x - App->render->camera.x + 5, positionP1.y - 93 - App->render->camera.y);
		currentP1_animation = &forwardP1;
		positionP1.x += speed;
		LOG("FORWARD ANIMATION ACTIVE");
		break;

	case crouchstateP1:
		currentP1_animation = &crouchP1;
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x - App->render->camera.x *2  , positionP1.y - 68 - App->render->camera.y);
		LOG("CROUCHED ANIMATION ACTIVE");
		break;
	}

	if ( currentstateP1 != crouchstateP1) {
		playerP1_collider->SetPos(positionP1.x  - App->render->camera.x *2  , positionP1.y - 93 - App->render->camera.y);
	}

	SDL_Rect r = currentP1_animation->GetCurrentFrame();
	SDL_Rect shadow = {796,27,100,20};

	App->render->Blit(graphicsP1, positionP1.x - 10, positionP1.y -15, &shadow , 1.0f, true);


	if (playerP1_collider->rect.x < App->player2->playerP2_collider->rect.x ) {
		App->render->Blit(graphicsP1, positionP1.x, positionP1.y - r.h, &r, 1.0f, true, SDL_FLIP_NONE);
	}
	else {
		App->render->Blit(graphicsP1, positionP1.x, positionP1.y - r.h, &r, 1.0f, true, SDL_FLIP_HORIZONTAL);
	}

	if (positionP1.x <= (App->render->camera.x - 10))
	{
		positionP1.x = (App->render->camera.x - 10);
	}
	if (positionP1.x >= (App->render->camera.x) + SCREEN_WIDTH)
	{
		positionP1.x = (App->render->camera.x) +SCREEN_WIDTH;
	}






	return UPDATE_CONTINUE;
}

//TODO 7.4: Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_PLAYER2 && inputplayerP1.D_active) {

		speed = 0;
	}
	else
	{
		speed = 2;
	}

}