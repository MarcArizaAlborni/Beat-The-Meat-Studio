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
void deleteCollider2(Collider* coll) {
	if (coll != nullptr) { coll->to_delete = true; };
}


ModulePlayer2::ModulePlayer2()
{
	graphicsP2 = NULL;
	currentP2_animation = NULL;

	score = 0;

	healthP2.x = 100;
	healthP2.y = 400;
	healthP2.w = 200;
	healthP2.h = 20;


	{ //BASIC MOVEMENTS ANIMATIONS

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

		//Neutral Jump Animation
		NjumpP2.PushBack({ 28, 525, 97, 128 });
		NjumpP2.PushBack({ 125, 525, 85, 128 });
		NjumpP2.PushBack({ 210, 525, 83, 128 });
		NjumpP2.PushBack({ 293, 525, 86, 128 });
		NjumpP2.PushBack({ 210, 525, 83, 128 });
		NjumpP2.PushBack({ 125, 525, 85, 128 });
		NjumpP2.PushBack({ 28, 525, 97, 128 });
		NjumpP2.speed = 0.1f;
		NjumpP2.loop = false;

		//Forward Jump Animation
		FjumpP2.PushBack({ 28, 525, 97, 128 });
		FjumpP2.PushBack({ 125, 525, 85, 128 });
		FjumpP2.PushBack({ 210, 525, 83, 128 });
		FjumpP2.PushBack({ 293, 525, 86, 128 });
		FjumpP2.PushBack({ 379, 525, 90, 128 });
		FjumpP2.PushBack({ 469, 525, 98, 128 });
		FjumpP2.PushBack({ 567, 525, 119, 128 });
		FjumpP2.PushBack({ 686, 525, 96, 128 });
		FjumpP2.PushBack({ 379, 525, 90, 128 });
		FjumpP2.PushBack({ 293, 525, 86, 128 });
		FjumpP2.speed = 0.17f;
		FjumpP2.loop = false;

		//Backward Jump Animation
		BjumpP2.PushBack({ 28, 525, 97, 128 });
		BjumpP2.PushBack({ 125, 525, 85, 128 });
		BjumpP2.PushBack({ 210, 525, 83, 128 });
		BjumpP2.PushBack({ 293, 525, 86, 128 });
		BjumpP2.PushBack({ 210, 525, 83, 128 });
		BjumpP2.PushBack({ 125, 525, 85, 128 });
		BjumpP2.PushBack({ 28, 525, 97, 128 });
		BjumpP2.speed = 0.17f;
		BjumpP2.loop = false;

		//Standing Turn Animation
		SturnP2.PushBack({ 36, 418, 89, 105 });
		SturnP2.PushBack({ 125, 418, 103, 105 });
		SturnP2.PushBack({ 228, 418, 97, 105 });

		//Crouch Turn Animation
		CturnP2.PushBack({ 622, 451, 82, 71 });
		CturnP2.PushBack({ 516, 451, 106, 71 });
		CturnP2.PushBack({ 428, 451, 88, 71 });

		//Standing Block Animation
		SblockP2.PushBack({ 730, 2169, 100, 96 });
		SblockP2.PushBack({ 630, 2169, 100, 96 });

		//Crouch Block Animation
		CblockP2.PushBack({ 730, 2100, 100, 63 });
		CblockP2.PushBack({ 630, 2100, 100, 63 });

		//Standing Damage 
		SdamageP2.PushBack({ 730, 2169, 100, 96 });  //AQUEST ESTA MALAMENT ES PER ANAR PROVANT MENTRES POSEU EL BO
		SdamageP2.PushBack({ 630, 2169, 100, 96 });//AQUEST ESTA MALAMENT ES PER ANAR PROVANT MENTRES POSEU EL BO
		SdamageP2.loop = false;//AQUEST ESTA MALAMENT ES PER ANAR PROVANT MENTRES POSEU EL BO
		SdamageP2.speed = 0.05;//AQUEST ESTA MALAMENT ES PER ANAR PROVANT MENTRES POSEU EL BO
		

		//Standing Damage Low Attack
		SdamagelowP2.PushBack({});

		//Crouch Damage
		CdamageP2.PushBack({});

		//Electric Thunder Damage
		ETdamgeP2.PushBack({});

		//Recovery
		RecoveryP2.PushBack({});

		

	}

	{ //ATTACKS ANIMATIONS

	  //Standing LP
		SLFP_P2.PushBack({ 28, 658, 104, 105 });
		SLFP_P2.PushBack({ 132, 658, 143, 105 });
		SLFP_P2.PushBack({ 275, 658, 123, 105 });
		SLFP_P2.speed = 0.2f;
		SLFP_P2.loop = false;

		//Standing FAR HP
		SFHP_P2.PushBack({ 27, 929, 107, 95 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 275, 906, 99, 118 });
		SFHP_P2.PushBack({ 275, 906, 99, 118 });
		SFHP_P2.PushBack({ 275, 906, 99, 118 });
		SFHP_P2.PushBack({ 275, 906, 99, 118 });
		SFHP_P2.PushBack({ 275, 906, 99, 118 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 140, 926, 128, 98 });
		SFHP_P2.PushBack({ 27, 929, 107, 95 });
		SFHP_P2.PushBack({ 27, 929, 107, 95 });
		SFHP_P2.PushBack({ 27, 929, 107, 95 });
		SFHP_P2.PushBack({ 27, 929, 107, 95 });
		SFHP_P2.speed = 0.5f;
		SFHP_P2.loop = false;

		//Standing FAR MP 
		SFMP_P2.PushBack({ 31, 765, 88, 104 });
		SFMP_P2.PushBack({ 134, 788, 120, 108 });
		SFMP_P2.PushBack({ 264, 799, 130, 97 });
		SFMP_P2.PushBack({ 403, 803, 103, 93 }); //This is not correct I think
		SFMP_P2.speed = 0.2f;

		//Crouch LP
		CLP_P2.PushBack({ 610, 709, 109, 56 });
		CLP_P2.PushBack({ 727, 715, 154, 50 });
		CLP_P2.PushBack({ 890, 713, 142, 52 });
		CLP_P2.speed = 0.2f;
		CLP_P2.loop = false;

		//Jumping LP
		JLP_P2.PushBack({});

		//Standing MP
		//Crouch MP
		//Jump MP

		//Standing HP
		//Crouch HP
		//Jump HP

		//Electric Thunder 
		Ethunder_P2.PushBack({});

		//Rolling Attack
		RollingP2.PushBack({});

	}
	
}

ModulePlayer2::~ModulePlayer2()
{

}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");

	graphicsP2 = App->textures->Load("Sprites/BlankaP2.png"); // JA TE LA FOTO BONA
	currentstateP2 = idlestateP2;

	//Player 2 stest collider
	playerP2_collider = App->collision->AddCollider({ positionP2.x, positionP2.y - 100, 56, 93 }, COLLIDER_PLAYER2,NOATTACK, App->player2);
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


	time2 = SDL_GetTicks() / 20;

	//MOVE BACKWARD
	//inputplayerP2.Right_active = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_REPEAT;
	////MOVE FORWARD
	//inputplayerP2.Left_active = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_REPEAT;
	////JUMP
	//inputplayerP2.Up_active = App->input->keyboard[SDL_SCANCODE_UP] == KEY_REPEAT;  
	////CROUCH
	//inputplayerP2.Down_active = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_REPEAT;

	
	App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_2] = KEY_DOWN;
	App->input->game_pad[SDL_CONTROLLER_BUTTON_B][GAME_PAD_2] = KEY_DOWN;
	App->input->game_pad[SDL_CONTROLLER_BUTTON_X][GAME_PAD_2] = KEY_DOWN;

	 inputplayerP2.Right_active = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)|| SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP2.Left_active = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_LEFT)|| SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	 inputplayerP2.Down_active = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP2.Up_active = App->input->keyboard[SDL_SCANCODE_UP] == KEY_REPEAT  || SDL_GameControllerGetButton(App->input->controller_player_2, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetAxis(App->input->controller_player_2, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;
	 if (inputplayerP2.Left_active && inputplayerP2.Right_active) {
		 inputplayerP2.Left_active = false;
		 inputplayerP2.Right_active = false;
	 }
	 inputplayerP2.Num7_active = App->input->keyboard[SDL_SCANCODE_KP_7] == KEY_REPEAT;
	 inputplayerP2.Num8_active = App->input->keyboard[SDL_SCANCODE_KP_8] == KEY_REPEAT;
	 inputplayerP2.Num9_active = App->input->keyboard[SDL_SCANCODE_KP_9] == KEY_REPEAT;


	{
		 //BASIC MOVEMENTS
		 if (currentstateP2 == standingfarLPP2) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 SLFP_P2.Reset();
			 }
		 }
		 if (currentstateP2 == standingfarMPP1) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 SFMP_P2.Reset();
			 }
		 }
		 if (currentstateP2 == standingfarHPP1) {
			 if (currentP2_animation->Finished()) {
				 deleteCollider2(attackP2_collider);
				 currentstateP2 = idlestateP2;
				 SFHP_P2.Reset();
			 }
		 }






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
			if (inputplayerP2.Up_active){
				jumping2 = true;
				currentstateP2 = NjumpstateP2;
				jumpstart2 = time2;
				jumpTimer2 = 0;
				LOG("IDLE to JUMP");
			}
			if (inputplayerP2.Num7_active) {
				currentstateP2 = standingfarLPP2;
				attackP2_collider = App->collision->AddCollider({ positionP2.x -20 - App->render->camera.x, positionP2.y - 80 - App->render->camera.y * 2, 50, 15 }, COLLIDER_PLAYER2_ATTACK,SFLP, App->player);
				LOG("IDLE to LP");
			}
			if (inputplayerP2.Num8_active) {
				currentstateP2 = standingfarMPP2;
				attackP2_collider = App->collision->AddCollider({ positionP2.x - 20 - App->render->camera.x, positionP2.y - 80 - App->render->camera.y * 2, 50, 15 }, COLLIDER_PLAYER2_ATTACK,SFMP, App->player);
				LOG("IDLE to LP");
			}
			if (inputplayerP2.Num9_active) {
				currentstateP2 = standingfarHPP2;
				attackP2_collider = App->collision->AddCollider({ positionP2.x - 20 - App->render->camera.x, positionP2.y - 80 - App->render->camera.y * 2, 50, 15 }, COLLIDER_PLAYER2_ATTACK,SFHP, App->player);
				LOG("IDLE to LP");
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
			if (inputplayerP2.Left_active) {
				
				currentstateP2 = forwardstateP2;
				LOG("BACK to FORWARD");
			}
			if (inputplayerP2.Up_active) {
				jumping2 = true;
				
				jumpstart2 = time2;
				jumpTimer2 = 0;
				currentstateP2 = BjumpstateP2;
				LOG("BACK to FORWARD");
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
			if (inputplayerP2.Up_active) {
				jumping2 = true;
				
				jumpstart2 = time2;
				jumpTimer2 = 0;
				currentstateP2 = FjumpstateP2;
				LOG("BACK to FORWARD");
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
		//JUMP STATE
		if (jumping2 == true ) {

			if (positionP2.y >= groundLevelII +5) {
				positionP2.y = groundLevelII;
				currentstateP2 = idlestateP2;
				NjumpP2.Reset();
				FjumpP2.Reset();
				BjumpP2.Reset();
				jumping2 = false;
				jumpTimer2 = 0;

			}

		}

		//ATTACKS
		//STANDING FAR LP
		if (currentstateP2 == standingfarLPP2) {
			if (currentP2_animation->Finished() && !inputplayerP2.Num7_active) {
				
				currentstateP2 = idlestateP2;
				//alreadyHit = false;
				SLFP_P2.Reset();
				LOG("LP to IDLE");
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
		currentP2_animation = &idleP2;
		//LOG("IDLE ANIMATION ACTIVE");
		break;

	case backwardstateP2:
		playerP2_collider->rect.h = 93;
		
		
		currentP2_animation = &backwardP2;
		positionP2.x += speedII;
		LOG("BACK ANIMATION ACTIVE");
		break;
	case forwardstateP2:
		
		currentP2_animation = &forwardP2;
		positionP2.x -= speedII;
		LOG("FORWARD ANIMATION ACTIVE");
		break;

	case crouchstateP2:
		currentP2_animation = &crouchP2;
		playerP2_collider->rect.h = 65;
		playerP2_collider->SetPos(positionP2.x - App->render->camera.x * 2, positionP2.y - 68 - App->render->camera.y * 2);
		LOG("CROUCHED ANIMATION ACTIVE");
		break;

	case NjumpstateP2:
		currentP2_animation = &NjumpP2;
		positionP2.y = groundLevelII - (yvel2*jumpTimer2) + (0.5*(gravity2) * (jumpTimer2 * jumpTimer2));
		LOG(" NEUTRAL JUMP ANIMATION ACTIVE");
		break;

	case FjumpstateP2:

		currentP2_animation = &FjumpP2;

		positionP2.x -= speedII;

		positionP2.y = groundLevelII - (yvel2*jumpTimer2) + (0.5*(gravity2) * (jumpTimer2 * jumpTimer2));
		LOG(" NEUTRAL JUMP ANIMATION ACTIVE");
		break;

	case BjumpstateP2:

		currentP2_animation = &BjumpP2;

		positionP2.x += speedII;

		positionP2.y = groundLevelII - (yvel2*jumpTimer2) + (0.5*(gravity2) * (jumpTimer2 * jumpTimer2));

		LOG(" NEUTRAL JUMP ANIMATION ACTIVE");
		break;
	case standingfarLPP2:

		currentP2_animation = &SLFP_P2;

		LOG(" NEUTRAL JUMP ANIMATION ACTIVE");
		break;
	case standingfarMPP2:

		currentP2_animation = &SFMP_P2;

		LOG(" NEUTRAL JUMP ANIMATION ACTIVE");
		break;
	case standingfarHPP2:

		currentP2_animation = &SFHP_P2;

		LOG(" NEUTRAL JUMP ANIMATION ACTIVE");
		break;
	}

	if (currentstateP2 != crouchstateP2) {
		playerP2_collider->SetPos(positionP2.x - App->render->camera.x * 2, positionP2.y - 93 - App->render->camera.y * 2);
	}
	SDL_Rect r = currentP2_animation->GetCurrentFrame();
	//SHADOW
	shadowP2 = { 796,27,100,20 };

	if (jumping2) {

		jumpTimer2 = time2 - jumpstart2;

		playerP2_collider->SetPos(positionP2.x - App->render->camera.x * 2, positionP2.y - 80 - App->render->camera.y * 2);
	}

	if (positionP2.x <= (App->render->camera.x/5 - 10))
	{
		positionP2.x = (App->render->camera.x/5 - 10);
	}
	if (positionP2.x >= (180 + App->render->camera.x/5) + 127)
	{
		positionP2.x = (180 + App->render->camera.x/5) + 127;
	}



	if (!App->player->flipP1) {
		App->render->Blit(graphicsP2, positionP2.x + 10, App->player->groundLevelP1 - 15, &shadowP2, 1.0f, true,SDL_FLIP_HORIZONTAL);
		App->render->Blit(graphicsP2, positionP2.x, positionP2.y - r.h, &r, 1.0f, true, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		App->render->Blit(graphicsP2, positionP2.x + 10, App->player->groundLevelP1 - 15, &shadowP2, 1.0f, true, SDL_FLIP_NONE);
		App->render->Blit(graphicsP2, positionP2.x, positionP2.y - r.h, &r, 1.0f, true, SDL_FLIP_NONE);
	}


	return UPDATE_CONTINUE;
}


void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	//if(c1->type == COLLIDER_PLAYER2 && c2->type == COLLIDER_PLAYER && inputplayerP2.Left_active ){

	//	speedII = 0;
	//}
	//else
	//{
	//	speedII = 3;
	//}

}