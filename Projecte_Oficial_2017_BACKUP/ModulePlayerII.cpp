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
#include <stdio.h>


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

int speedII = 2;
Uint8 alphakaII = 255;
float gravityII = 1;

bool airkickII = true;

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 100;
	position.y = 220;
	score = 0;

	health.x = 100;
	health.y = 400;
	health.w = 200;
	health.h = 20;

	//App->render->DrawQuad(health, 255, 0, 0, alphaka);

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 996, 61, 59, 90 });
	idle.PushBack({ 931, 59, 58, 92 });
	idle.PushBack({ 867, 58, 55, 93 });
	idle.PushBack({ 798, 62, 60, 89 });
	idle.speed = 0.15f;

	//Crouch Animation
	crouch.PushBack({ 502, 162, 53, 87 });
	crouch.PushBack({ 435, 178, 57, 69 });
	crouch.PushBack({ 366, 186, 61, 61 });
	crouch.speed = 0.5f;
	crouch.loop = false;


	//punchcrouch Animation
	crouchpunch.PushBack({ 979, 2046, 69, 61 });
	crouchpunch.PushBack({ 865, 2046, 95, 61 });

	crouchpunch.speed = 0.15f;
	crouchpunch.loop = false;

	//kickcrouch Animation

	crouchkick.PushBack({ 32,2296,80,70 });
	crouchkick.PushBack({ 109,2296,121,70 });

	crouchkick.speed = 0.15f;
	crouchkick.loop = false;
	// forward Jump Animation
	forwardjump.PushBack({ 13,716,62,111 });
	forwardjump.PushBack({ 75,716,65,91 });
	forwardjump.PushBack({ 140,716,112,49 });
	forwardjump.PushBack({ 420,695,58,85 });
	forwardjump.PushBack({ 140,777,129,51 });
	forwardjump.PushBack({ 328,767,77,93 });

	forwardjump.speed = 0.1f;
	forwardjump.loop = false;
	//Backward Jump Animation
	backwardjump.PushBack({ 328,767,77,93 });
	backwardjump.PushBack({ 140,777,129,51 });
	backwardjump.PushBack({ 420,695,58,85 });
	backwardjump.PushBack({ 140,716,112,49 });
	backwardjump.PushBack({ 75,716,65,91 });
	backwardjump.PushBack({ 13,716,62,111 });
	backwardjump.speed = 0.1f;
	backwardjump.loop = false;
	//punch jump Animation
	jumppunch.PushBack({ 259,1693,83,91 });
	jumppunch.PushBack({ 353,1693,200,78 });
	jumppunch.speed = 0.1f;
	jumppunch.loop = false;

	// kick jump Animation

	jumpkick.PushBack({ 242,1791,68,124 });
	jumpkick.PushBack({ 331,1791,110,115 });
	jumpkick.speed = 0.1f;
	jumpkick.loop = false;

	//Damaged Animation

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});

	//Walk FORWARD Animation
	forward.PushBack({ 27,250, 66, 100 });
	forward.PushBack({ 92, 250, 66, 100 });
	forward.PushBack({ 160, 248, 70, 100 });
	forward.PushBack({ 236, 250, 67, 100 });
	forward.PushBack({ 306, 250, 67, 100 });
	forward.PushBack({ 369, 250, 67, 100 });

	forward.loop = true;
	forward.speed = 0.1f;

	//Walk backwards animation
	backward.PushBack({ 27, 155, 67, 100 });
	backward.PushBack({ 27, 155, 67, 100 });
	backward.PushBack({ 171, 155, 67, 100 });
	backward.PushBack({ 233, 155, 67, 100 });
	backward.PushBack({ 300, 155, 63, 100 });
	backward.PushBack({ 362, 155, 67, 102 });
	backward.loop = true;
	backward.speed = 0.1f;

	//Ryu light punch
	lightPunch.PushBack({ 34, 1368, 70, 96 });
	lightPunch.PushBack({ 112, 1368, 101, 96 });
	lightPunch.PushBack({ 34, 1368, 70, 96 });
	lightPunch.loop = true;
	lightPunch.speed = 0.1f;

	//Ryu light kick
	lightKick.PushBack({ 35, 1586, 69, 97 });
	lightKick.PushBack({ 125, 1585, 120, 98 });
	lightKick.loop = false;
	lightKick.speed = 0.1f;

	//Ryu jump
	jump.PushBack({ 17, 580, 63,105 });
	jump.PushBack({ 80, 580, 62, 115 });
	jump.PushBack({ 149, 580, 54, 100 });
	jump.PushBack({ 207, 580, 61, 100 });
	jump.PushBack({ 282, 580, 56,100 });
	jump.PushBack({ 343, 580, 61,120 });
	jump.loop = false;
	jump.speed = 0.10f;

	//Ryu Hadouken movement
	hadouken.PushBack({ 18, 870, 80, 95 });
	hadouken.PushBack({ 100, 875, 90, 95 });
	hadouken.PushBack({ 190, 875, 97, 95 });
	hadouken.PushBack({ 290, 875, 110, 95 });
	hadouken.loop = false;
	hadouken.speed = 0.1f;


	//Jumpbackkick Animation
	jumpbackkick.PushBack({ 347,1925,80,91 });
	jumpbackkick.PushBack({ 427,1925,135,91 });
	jumpbackkick.loop = false;
	jumpbackkick.speed = 0.08f;


	// jumpbackpunch Animation
	jumpbackpunch.PushBack({ 23,1689,74,91 });
	jumpbackpunch.PushBack({ 99,1689,104,92 });
	jumpbackpunch.loop = false;
	jumpbackpunch.speed = 0.08f;

	//jumpfrontkick Animation
	jumpfrontkick.PushBack({ 347,1925,80,91 });
	jumpfrontkick.PushBack({ 427,1925,135,91 });
	jumpfrontkick.loop = false;
	jumpfrontkick.speed = 0.08f;

	// jumpfrontpunch Animation 

	jumpfrontpunch.PushBack({ 23,1689,74,91 });
	jumpfrontpunch.PushBack({ 99,1689,104,92 });
	jumpfrontpunch.loop = false;
	jumpfrontpunch.speed = 0.08f;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("RyuP1_Inv.png"); // JA TE LA FOTO BONA
	LP = App->audio->LoadFx("");
	Hadoken_Sound = App->audio->LoadFx("Audios/Voices/Ryu&Ken hadouken.wav");

	position.x = 400;
	position.y = 220;

	// TODO 7.2: Add a collider to the player
	player_collider = App->collision->AddCollider({ position.x, position.y - 100, 60, 93 }, COLLIDER_PLAYER, App->player2);
	//Player 2 stest collider

	player2_collider = App->collision->AddCollider({ position.x, position.y - 100,60,93 }, COLLIDER_PLAYER2, App->player2);



	return ret;
}


bool ModulePlayer2::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphics);
	App->audio->UnLoadFX(LP);
	App->audio->UnLoadFX(Hadoken_Sound);

	return true;
}


update_status ModulePlayer2::PreUpdate() {



	//MOVE BACKWARD
	inputplayer2.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
	//MOVE FORWARD
	inputplayer2.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
	//CROUCH
	inputplayer2.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
	//JUMP
	inputplayer2.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
	//LIGHT PUNCH
	inputplayer2.I_active = App->input->keyboard[SDL_SCANCODE_I] == KEY_DOWN;
	//LIGHT KICK
	inputplayer2.K_active = App->input->keyboard[SDL_SCANCODE_K] == KEY_DOWN;
	//HADOKEN
	inputplayer2.R_active = App->input->keyboard[SDL_SCANCODE_R] == KEY_DOWN;

	{
		if (currentstate == punchlight2) {

			if (current_animation->Finished()) {

				currentstate = idlestate2;
				lightPunch.Reset();
				//lightPunch.Reset();
				LOG("PUNCH TO IDLE");

			}
			LOG("PUNCH");
		}

		if (currentstate == kicklight2) {

			if (current_animation->Finished()) {

				currentstate = idlestate2;
				lightKick.Reset();
				LOG("KICK TO IDLE");
			}
		}

		if (currentstate == jumpstate2) {
			if (airkickII) {
				if (inputplayer2.I_active) {
					currentstate = jumppunchstate2;
				}

				if (inputplayer2.K_active) {
					currentstate = jumpkickstate2;
				}
			}
			/*if (current_animation->Finished()) {
				jump.Reset();
				currentstate = idlestate;

				LOG("JUMP TO IDLE");
			}*/
		}
		if (currentstate == hadoukenstate2) {

			if (current_animation->Finished()) {
				App->particles->hadouken.speed.x = 5;
				App->particles->hadouken.life = 2000;
				App->particles->AddParticle(App->particles->hadouken, position.x + 25, position.y - 70, COLLIDER_PLAYER_SHOT);
				currentstate = idlestate2;
				hadouken.Reset();
			}
		}

		if (currentstate == idlestate2) {

			if (inputplayer2.A_active) {
				currentstate = backwardstate2;
				LOG("IDLE TO BACK");
			}
			if (inputplayer2.D_active) {
				currentstate = forwardstate2;
				LOG("IDLE TO forward");
			}
			if (inputplayer2.S_active) {
				currentstate = crouched2;
				LOG("IDLE to CROUCH");
			}
			if (inputplayer2.K_active) {
				currentstate = kicklight2;
				LOG("IDLE TO kick");
			}
			if (inputplayer2.I_active) {
				currentstate = punchlight2;
				LOG("IDLE TO punch");
			}
			if (inputplayer2.R_active) {
				currentstate = hadoukenstate2;
				App->audio->PlayFx(Hadoken_Sound);
				LOG("IDLE TO hadouken");
			}
			if (inputplayer2.W_active) {
				currentstate = jumpstate2;
				LOG("IDLE TO jump");
				current_animation = &jump;
			}
		}

		if (currentstate == backwardstate2) {

			if (!inputplayer2.A_active) {
				currentstate = idlestate2;
				LOG("BACK TO IDLE");
			}
			if (inputplayer2.I_active) {
				currentstate = punchlight2;
				LOG("BACK TO PUNCH");
			}
			if (inputplayer2.W_active) {
				currentstate = jumpbackward2;
				LOG("BACK TO JUMP");
			}
			if (inputplayer2.K_active) {
				currentstate = kicklight2;
				LOG("BACK TO KICK");
			}
		}

		if (currentstate == forwardstate2) {
			if (!inputplayer2.D_active) {
				LOG("FORWARD TO IDLE");
				currentstate = idlestate2;
			}
			if (inputplayer2.K_active) {
				currentstate = kicklight2;
				LOG("FORWARD TO KICK");
			}
			if (inputplayer2.I_active) {
				currentstate = punchlight2;
				LOG("FORWARD TO PUNCH");
			}
			if (inputplayer2.W_active) {
				currentstate = jumpforward2; // Aquest hauria de ser jump FORWARD pero no tenim l'animacio posada encara
				LOG("FORWARD TO JUMP");
			}
		}

		if (currentstate == jumpbackward2) {
			LOG("BACKWARDJUMP TO IDLE");
			if (airkickII) {
				if (inputplayer2.I_active) {

					currentstate = jumpbackwardpunch2;
					LOG("BACKWARDJUMP TO BACKWARDJUMPPUNCH");
				}

				if (inputplayer2.K_active) {


					currentstate = jumpbackwardkick2;
					LOG("BACKWARDJUMP TO BACKWARDJUMPKICK");
				}
			}
			/*if (current_animation->Finished()) { // Aquest d'aqui no el poseu perque per ara trenca el jumpbackward.
				currentstate = idlestate;
				backwardjump.Reset();
			}*/
		}
		if (currentstate == jumpforward2) {
			LOG("FORWARDJUMP TO IDLE");
			if (airkickII) {
				if (inputplayer2.I_active) {

					currentstate = jumpforwardpunch2;
					LOG("FORWARDJUMP TO FORWARDJUMPPUNCH");

				}

				if (inputplayer2.K_active) {

					currentstate = jumpforwardkick2;
					LOG("FORWARDJUMP TO FORWARDJUMPKICK");
				}
			}
			/*if (current_animation->Finished()) {  // Aquest d'aqui no el poseu perque per ara trenca el jumpforward.
				currentstate = idlestate;
				forwardjump.Reset();
			}*/
		}

		if (currentstate == jumpbackwardkick2) {


			LOG("BACKWARDJUMPKICK TO JUMP");
			if (jumpbackkick.Finished()) {

				currentstate = jumpbackward2;
				airkickII = false;
				jumpbackkick.Reset();
			}

		}

		if (currentstate == jumpbackwardpunch2) {

			LOG("BACKWARDJUMPPUNCH TO JUMP");

		}
		if (airkickII) {
			if (currentstate == jumpforwardkick2) {
				if (jumpfrontkick.Finished()) {
					LOG("FORWARDJUMPKICK TO JUMPFORWARD")
						currentstate = jumpforward2;
					airkickII = false;
				}
			}
		}

		if (currentstate == jumpforwardpunch2) {

			LOG("FORWARDJUMPPUNCH TO JUMPFORWARD");



		}
		if (currentstate == punchcrouch2) {
			LOG("CROUCH TO CROUCHPUNCH");
			if (current_animation->Finished()) {
				currentstate = crouched2;
				crouchpunch.Reset();
			}
		}

		if (currentstate == kickcrouch2) {
			LOG("CROUCH TO KICKCROUCH");
			if (current_animation->Finished()) {
				currentstate = crouched2;
				crouchkick.Reset();
			}
		}

		if (currentstate == crouched2) {
			if (inputplayer2.I_active) {
				currentstate = punchcrouch2;
			}

			if (inputplayer2.K_active) {
				currentstate = kickcrouch2;
			}

			if (!inputplayer2.S_active) {
				currentstate = idlestate2;
				LOG("CROUCH TO IDLE");
			}
		}

		if (currentstate == jumpkickstate2) {
			LOG("KICKJUMP TO IDLE");
			//if (current_animation->Finished()&& (position.y == 220)) {
			//	currentstate = jumpstate;//-----------------------------------------------
			//	jumpkick.Reset();
			//}
			if (jumpkick.Finished()) {
				currentstate = jumpstate2;
				airkickII = false;
			}
		}

		if (currentstate == jumppunchstate2) {
			LOG("PUNCHJUMP ACTIVE");
			if (current_animation->Finished() && (position.y == 220)) {
				currentstate = jumpstate2;//-----------------------------------------------
				jumpbackpunch.Reset();
			}
		}


		if (currentstate == jumpfalling2) {

			if (current_animation->Finished()); {

				currentstate = idlestate2; //----------------------------------------------
				jump.Reset();
			}
		}
	}
	return UPDATE_CONTINUE;

}

// Update: draw background
update_status ModulePlayer2::Update()
{


	switch (currentstate) {
	case jumpfalling2:

		current_animation = &jump;

		position.y -= speedII * gravityII;


		if (position.y <= 150)
		{
			gravityII = -1;
		}

		else if (position.y == 220) {
			jump.Reset();
			airkickII = true;
			currentstate = idlestate2;
			gravityII = 1;
		}
		LOG("JUMPFALLING ANIMATION ACTIVE");
		break;

	case jumpbackwardkick2:

		current_animation = &jumpbackkick;
		position.x -= speedII;
		position.y -= speedII * gravityII;


		if (position.y <= 150)
		{
			gravityII = -1;
		}

		else if (position.y == 220) {
			jump.Reset();
			jumpbackkick.Reset();
			backwardjump.Reset();
			airkickII = true;
			currentstate = idlestate2;
			gravityII = 1;
		}
		LOG("JUMPBACKKICK ANIMATION ACTIVE");
		break;

	case jumpbackwardpunch2:

		current_animation = &jumpbackpunch;
		position.x -= speedII;
		position.y -= speedII * gravityII;


		if (position.y <= 150)
		{
			gravityII = -1;
		}

		else if (position.y == 220) {
			jump.Reset();
			airkickII = true;
			jumpbackpunch.Reset();
			currentstate = idlestate2;
			gravityII = 1;
		}
		LOG("JUMPBACKPUNCH ANIMATION ACTIVE");
		break;


	case jumpforwardkick2:

		current_animation = &jumpfrontkick;

		position.x += speedII;

		position.y -= speedII * gravityII;


		if (position.y <= 150)
		{
			gravityII = -1;
		}

		else if (position.y == 220) {
			jump.Reset();
			airkickII = true;
			jumpfrontkick.Reset();
			currentstate = idlestate2;
			gravityII = 1;
			forwardjump.Reset();
		}
		LOG("JUMPFRONTKICK ANIMATION ACTIVE");
		break;

	case  jumpforwardpunch2:

		current_animation = &jumpfrontpunch;
		position.x += speedII;
		position.y -= speedII * gravityII;


		if (position.y <= 150)
		{
			gravityII = -1;
		}

		else if (position.y == 220) {
			jumpfrontpunch.Reset();
			jump.Reset();
			airkickII = true;
			currentstate = idlestate2;
			gravityII = 1;
		}
		LOG("JUMPFRONTPUNCH ANIMATION ACTIVE");
		break;


	case damagedstate2:

		current_animation = &damaged;
		LOG("DAMAGED ANIMATION ACTIVE");
		break;

	case jumpforward2:
		position.x += speedII;
		position.y -= speedII * gravityII;
		if (position.y <= 150)
		{
			gravityII = -1;
		}
		else if (position.y == 220) {
			jump.Reset();
			airkickII = true;
			currentstate = idlestate2;
			jumpfrontkick.Reset();
			gravityII = 1;
			forwardjump.Reset();
		}
		current_animation = &forwardjump;

		LOG("FORWARD JUMP ANIMATION ACTIVE");

		break;

	case jumpbackward2:

		current_animation = &backwardjump;
		position.x -= speedII;
		position.y -= speedII * gravityII;
		if (position.y <= 150)
		{
			gravityII = -1;

		}
		else if (position.y == 220) {
			jump.Reset();
			airkickII = true;
			currentstate = idlestate2;
			gravityII = 1;
			jumpbackkick.Reset();
			backwardjump.Reset();
		}

		LOG("backward JUMP ANIMATION ACTIVE");

		break;
	case punchcrouch2:

		current_animation = &crouchpunch;
		LOG("CROUCH PUNCH ANIMATION ACTIVE")
			break;


	case kickcrouch2:

		current_animation = &crouchkick;
		LOG("CROUCH KICK ANIMATION ACTIVE");
		break;

		/*case kickjump:

			current_animation = &jumpkick;
			LOG("JUMP KICK ANIMATION ACTIVE");
			break;*/

			/*case punchjump:

				current_animation = &jumppunch;
				LOG("JUMP PUNCH ANIMATION ACTIVE");
				break;*/

	case idlestate2:
		crouch.Reset();
		player_collider->SetPos(position.x - App->render->camera.x, position.y - 93 - App->render->camera.y);
		current_animation = &idle;
		LOG("IDLE ANIMATION ACTIVE");
		break;


	case backwardstate2:
		player_collider->SetPos(position.x - App->render->camera.x, position.y - 93 - App->render->camera.y);
		current_animation = &backward;
		position.x -= speedII;
		LOG("BACKWARD ANIMATION ACTIVE");
		break;


	case forwardstate2:
		player_collider->SetPos(position.x - App->render->camera.x, position.y - 93 - App->render->camera.y);
		current_animation = &forward;
		position.x += speedII;
		LOG("FORWARD ANIMATION ACTIVE");
		break;


	case jumpstate2:

		current_animation = &jump;

		position.y -= speedII * gravityII;


		if (position.y <= 150)
		{
			gravityII = -1;
		}

		else if (position.y == 220) {
			jump.Reset();

			airkickII = true;
			jumpkick.Reset();
			currentstate = idlestate2;
			gravityII = 1;
		}
		LOG("JUMP ANIMATION ACTIVE");
		break;

	case punchlight2:
		current_animation = &lightPunch;
		LOG("PUNCH ANIMATION ACTIVE");
		break;

	case kicklight2:

		current_animation = &lightKick;
		LOG("KICK ANIMATION ACTIVE");
		break;

	case crouched2:

		current_animation = &crouch;

		LOG("CROUCHED ANIMATION ACTIVE");
		break;

	case hadoukenstate2:

		current_animation = &hadouken;
		LOG("KADOUKEN ANIMATION ACTIVE");
		break;

	case jumpkickstate2:

		current_animation = &jumpkick;
		position.y -= speedII * gravityII;
		if (position.y <= 150)
		{
			gravityII = -1;

		}
		else if (position.y == 220) {
			jump.Reset();
			airkickII = true;
			currentstate = idlestate2;
			gravityII = 1;
			backwardjump.Reset();
		}
		LOG("JUMP KICK ACTIVE");
		break;

	case jumppunchstate2:
		current_animation = &jumpbackpunch;
		position.y -= speedII * gravityII;
		if (position.y <= 150)
		{
			gravityII = -1;

		}
		else if (position.y == 220) {
			jump.Reset();
			airkickII = true;
			currentstate = idlestate2;
			gravityII = 1;
			backwardjump.Reset();
		}
		LOG("JUMP PUNCH ACTIVE");
		break;

	}








	//Limits ben fets
	if (position.x <= App->render->camera.x / SCREEN_SIZE)
	{
		position.x = App->render->camera.x / SCREEN_SIZE;
	}
	if (position.x >= SCREEN_WIDTH - 60 + App->render->camera.x / SCREEN_SIZE) { //Hardcodeado una mica, s'haura de revisar
		position.x = SCREEN_WIDTH - 60 + App->render->camera.x / SCREEN_SIZE;
	}

	// TODO 7.3: Update collider position to player position
	//PONER LOS COLLIDERS  DENTRO DE LOS STATES
	//player_collider->SetPos(position.x - App->render->camera.x, position.y - 93- App->render->camera.y);

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	sprintf_s(score_text, 10, "%7d", score);

	App->render->Blit(graphics, position.x, position.y - r.h, &r);



	return UPDATE_CONTINUE;
}

//TODO 7.4: Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	//App->particles->hadouken.collider
	/*if (  c1->type == COLLIDER_PLAYER_SHOT) {

		App->scene_ryu->health2.w -= 10;
	}*/


}