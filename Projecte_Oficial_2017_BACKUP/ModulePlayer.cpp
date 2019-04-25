#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "ModuleFonts.h"
#include <stdio.h>


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

int speed = 2;
Uint8 alphaka= 255;

ModulePlayer::ModulePlayer()
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
	idle.PushBack({25, 54, 68, 100});
	idle.PushBack({93, 54, 67, 100});
	idle.PushBack({160, 54, 68, 100});
	idle.PushBack({223, 54, 67, 100});
	idle.speed = 0.15f;

	//Crouch Animation
	crouch.PushBack({ 519,156,67,95 });
	crouch.PushBack({ 587,156,68,95 });
	crouch.PushBack({ 654,156,68,95 });
	crouch.speed = 0.1f;
	crouch.loop = false;


	//punchcrouch Animation
	crouchpunch.PushBack({ 34,2038,86,72 });
	crouchpunch.PushBack({120,2037,100,73});

	crouchpunch.speed = 0.15f;
	crouchpunch.loop = false;

	//kickcrouch Animation

	crouchkick.PushBack({32,2296,80,70});
	crouchkick.PushBack({ 109,2296,121,70});

	crouchkick.speed = 0.15f;
	crouchkick.loop = false;
	// forward Jump Animation
	forwardjump.PushBack({ 13,716,62,111  });
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
	jumppunch.PushBack({259,1693,83,91});
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
	forward.PushBack({ 236, 250, 67, 100});
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
	lightPunch.PushBack({ 112, 1368, 101, 96 } );
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
	hadouken.PushBack({18, 875, 80, 95});
	hadouken.PushBack({100, 875, 90, 95});
	hadouken.PushBack({190, 875, 97, 95});
	hadouken.PushBack({290, 875, 110, 95});
	hadouken.loop = false;
	hadouken.speed = 0.1f;


	//Jumpbackkick Animation
	jumpbackkick.PushBack({347,1925,80,91});
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

	jumpfrontpunch.PushBack({23,1689,74,91});
	jumpfrontpunch.PushBack({ 99,1689,104,92 });
	jumpfrontpunch.loop = false;
	jumpfrontpunch.speed = 0.08f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("RyuP1.png"); // JA TE LA FOTO BONA

	position.x = 100;
	position.y = 220;

	// TODO 7.2: Add a collider to the player
	player_collider = App->collision->AddCollider({ position.x, position.y - 100, 60, 93 }, COLLIDER_PLAYER, App->player);

	font_score = App->fonts->Load("Fonts/font1.png", "! @,./0123456789;<&?abcdefghijklmnopqrstuvwxyz", 2);

	return ret;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphics);

	return true;
}


update_status ModulePlayer::PreUpdate() {

	

	//MOVE BACKWARD
	inputplayer1.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
	//MOVE FORWARD
	inputplayer1.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
	//CROUCH
	inputplayer1.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
	//JUMP
	inputplayer1.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
	//LIGHT PUNCH
	inputplayer1.I_active = App->input->keyboard[SDL_SCANCODE_I] == KEY_DOWN;
	//LIGHT KICK
	inputplayer1.K_active = App->input->keyboard[SDL_SCANCODE_K] == KEY_DOWN;
	//HADOKEN
	inputplayer1.R_active = App->input->keyboard[SDL_SCANCODE_R] == KEY_DOWN;

	{
		if (currentstate == punchlight) {

			if (current_animation->Finished()) {

				currentstate = idlestate;
				lightPunch.Reset();
				//lightPunch.Reset();
				LOG("PUNCH TO IDLE");

			}

			LOG("PUNCH");
		}

		if (currentstate == kicklight) {

			if (current_animation->Finished()) {

				currentstate = idlestate;
				lightKick.Reset();
				LOG("KICK TO IDLE");
			}



		}



		if (currentstate == jumpstate) {

			if (inputplayer1.I_active) {
				currentstate =jumppunchstate;
			}
			if (inputplayer1.K_active){
				currentstate = jumpkickstate;
			}
			/*if (current_animation->Finished()) {
				jump.Reset();
				currentstate = idlestate;

				LOG("JUMP TO IDLE");
			}*/
		}
		if (currentstate == hadoukenstate) {

			if (current_animation->Finished()) {
				App->particles->hadouken.speed.x = 5;
				App->particles->hadouken.life = 2000;
				App->particles->AddParticle(App->particles->hadouken, position.x + 25, position.y - 70, COLLIDER_PLAYER_SHOT);
			currentstate = idlestate;
				hadouken.Reset();
			}
		}
		
		if (currentstate == idlestate) {

			if (inputplayer1.A_active) {
				currentstate = backwardstate;
				LOG("IDLE TO BACK");
			}
			if (inputplayer1.D_active) {
				currentstate = forwardstate;
				LOG("IDLE TO forward");
			}
			if (inputplayer1.S_active) {
				currentstate = crouched;
				LOG("IDLE to CROUCH");
			}
			if (inputplayer1.K_active) {
				currentstate = kicklight;
				LOG("IDLE TO kick");
			}
			if (inputplayer1.I_active) {
				currentstate = punchlight;
				LOG("IDLE TO punch");
			}
			if (inputplayer1.R_active) {
				currentstate = hadoukenstate;
				LOG("IDLE TO hadouken");
			}
			if (inputplayer1.W_active) {
				currentstate = jumpstate;
				LOG("IDLE TO jump");
				current_animation = &jump;
			}
		}

		if (currentstate == backwardstate) {

			if (!inputplayer1.A_active) {
				currentstate = idlestate;
				LOG("BACK TO IDLE");
			}
			if (inputplayer1.I_active){
				currentstate = punchlight;
				LOG("BACK TO PUNCH");
			}
			if (inputplayer1.W_active) {
				currentstate =jumpbackward;
				LOG("BACK TO JUMP");
			}
			if (inputplayer1.K_active) {
				currentstate = kicklight;
				LOG("BACK TO KICK");
			}
		}

		if (currentstate == forwardstate) {
			if (!inputplayer1.D_active) {
				LOG("FORWARD TO IDLE");
				currentstate = idlestate;
			}
			if (inputplayer1.K_active) {
				currentstate = kicklight;
				LOG("FORWARD TO KICK");
			}
			if (inputplayer1.I_active) {
				currentstate = punchlight;
				LOG("FORWARD TO PUNCH");
			}
			if (inputplayer1.W_active) {
				currentstate = jumpforward; // Aquest hauria de ser jump FORWARD pero no tenim l'animacio posada encara
				LOG("FORWARD TO JUMP");
			}
		}
		if (currentstate == jumpbackward) {
			LOG("BACKWARDJUMP TO IDLE");

			if (inputplayer1.I_active) {

				currentstate = jumpbackwardpunch;
				LOG("BACKWARDJUMP TO BACKWARDJUMPPUNCH");
			}
			if (inputplayer1.K_active) {


				currentstate = jumpbackwardkick;
				LOG("BACKWARDJUMP TO BACKWARDJUMPKICK");

			}
			/*if (current_animation->Finished()) { // Aquest d'aqui no el poseu perque per ara trenca el jumpbackward.
				currentstate = idlestate;
				backwardjump.Reset();
			}*/
		}
		if (currentstate == jumpforward) {
			LOG("FORWARDJUMP TO IDLE");

			if (inputplayer1.I_active) {

				currentstate = jumpforwardpunch;
				LOG("FORWARDJUMP TO FORWARDJUMPPUNCH");

			}
			if (inputplayer1.K_active) {

				currentstate = jumpforwardkick;
				LOG("FORWARDJUMP TO FORWARDJUMPKICK");

			}
			/*if (current_animation->Finished()) {  // Aquest d'aqui no el poseu perque per ara trenca el jumpforward.
				currentstate = idlestate;
				forwardjump.Reset();
			}*/
		}
		if (currentstate == jumpbackwardkick) {

			LOG("BACKWARDJUMPKICK TO JUMP");
			if (current_animation->Finished()) {
				currentstate = jumpbackward;
				jumpbackkick.Reset();

			}
		}
		if (currentstate == jumpbackwardpunch) {

			LOG("BACKWARDJUMPPUNCH TO JUMP");
			
		}
		if (currentstate == jumpforwardkick){

			LOG("FORWARDJUMPKICK TO JUMPFORWARD")
				if (current_animation->Finished()) {

					currentstate = jumpforward;
					jumpfrontkick.Reset();
				}

			}

		if (currentstate == jumpforwardpunch) {

			LOG("FORWARDJUMPPUNCH TO JUMPFORWARD");
			


		}
		if (currentstate == punchcrouch) {
			LOG("CROUCH TO CROUCHPUNCH");
			if (current_animation->Finished()) {
				currentstate = crouched;
				crouchpunch.Reset();
			}
		}

		if (currentstate == kickcrouch) {
			LOG("CROUCH TO KICKCROUCH");
			if (current_animation->Finished()) {
				currentstate = crouched;
				crouchkick.Reset();
			}
		}
		
		if (currentstate == crouched) {
			if (inputplayer1.I_active) {
				currentstate = punchcrouch;
			}

			if (inputplayer1.K_active) {
				currentstate = kickcrouch;
			}

			if (!inputplayer1.S_active) {
				currentstate = idlestate;
				LOG("CROUCH TO IDLE");
			}
		}
		if (currentstate == kickjump) {
			LOG("KICKJUMP TO IDLE");
			if (current_animation->Finished()) {
				currentstate = idlestate;
				jumpkick.Reset();
			}
		}
		if (currentstate == punchjump) {
			LOG("PUNCHJUMP TO IDLE");
			if (current_animation->Finished()) {
				currentstate = idlestate;
				jumppunch.Reset();
			}
		}
		if (currentstate==jumpkickstate) {
			if (current_animation->Finished()) {
				currentstate = jumpstate;
				jumpbackkick.Reset();
			}
		}
		
	}
	return UPDATE_CONTINUE;

}
float gravity = 1;
// Update: draw background
update_status ModulePlayer::Update()
{


	switch (currentstate) {
	case jumpbackwardkick:

		current_animation = &jumpbackkick;
		position.x -= speed;
		position.y -= speed * gravity;


		if (position.y <= 150)
		{
			gravity = -1;
		}

		else if (position.y == 220) {
			jump.Reset();
			currentstate = idlestate;
			gravity = 1;
		}
		LOG("JUMPBACKKICK ANIMATION ACTIVE");
		break;

	case jumpbackwardpunch:

		current_animation = &jumpbackpunch;
		position.x -= speed;
		position.y -= speed * gravity;


		if (position.y <= 150)
		{
			gravity = -1;
		}

		else if (position.y == 220) {
			jump.Reset();
			jumpbackpunch.Reset();
			currentstate = idlestate;
			gravity = 1;
		}
		LOG("JUMPBACKPUNCH ANIMATION ACTIVE");
		break;


	case jumpforwardkick:

		current_animation = &jumpfrontkick;

		position.x += speed;

		position.y -= speed * gravity;


		if (position.y <= 150)
		{
			gravity = -1;
		}

		else if (position.y == 220) {
			jump.Reset();
			currentstate = idlestate;
			gravity = 1;
		}
		LOG("JUMPFRONTKICK ANIMATION ACTIVE");
		break;

	case  jumpforwardpunch:

		current_animation = &jumpfrontpunch;
		position.x += speed;
		position.y -= speed * gravity;


		if (position.y <= 150)
		{
			gravity = -1;
		}

		else if (position.y == 220) {
			jumpfrontpunch.Reset();
			jump.Reset();
			currentstate = idlestate;
			gravity = 1;
		}
		LOG("JUMPFRONTPUNCH ANIMATION ACTIVE");
		break;


	case damagedstate:

		current_animation = &damaged;
		LOG("DAMAGED ANIMATION ACTIVE");
		break;

	case jumpforward:


		position.x += speed;
		position.y -= speed * gravity;
		if (position.y <= 150)
		{
			gravity = -1;
		}
		else if (position.y == 220) {
			jump.Reset();
			currentstate = idlestate;

			gravity = 1;
			forwardjump.Reset();
		}
		current_animation = &forwardjump;

		LOG("FORWARD JUMP ANIMATION ACTIVE");

		break;

	case jumpbackward:

		current_animation = &backwardjump;
		position.x -= speed;
		position.y -= speed * gravity;
		if (position.y <= 150)
		{
			gravity = -1;

		}
		else if (position.y == 220) {
			jump.Reset();
			currentstate = idlestate;
			gravity = 1;
			backwardjump.Reset();
		}

		LOG("backward JUMP ANIMATION ACTIVE");

		break;
	case punchcrouch:

		current_animation = &crouchpunch;
		LOG("CROUCH PUNCH ANIMATION ACTIVE")
			break;


	case kickcrouch:

		current_animation = &crouchkick;
		LOG("CROUCH KICK ANIMATION ACTIVE");
		break;

	case kickjump:

		current_animation = &jumpkick;
		LOG("JUMP KICK ANIMATION ACTIVE");
		break;

	case punchjump:

		current_animation = &jumppunch;
		LOG("JUMP PUNCH ANIMATION ACTIVE");
		break;

	case idlestate:

		player_collider->SetPos(position.x - App->render->camera.x, position.y - 93 - App->render->camera.y);
		current_animation = &idle;
		LOG("IDLE ANIMATION ACTIVE");
		break;


	case backwardstate:
		player_collider->SetPos(position.x - App->render->camera.x, position.y - 93 - App->render->camera.y);
		current_animation = &backward;
		position.x -= speed;
		LOG("BACKWARD ANIMATION ACTIVE");
		break;


	case forwardstate:
		player_collider->SetPos(position.x - App->render->camera.x, position.y - 93 - App->render->camera.y);
		current_animation = &forward;
		position.x += speed;
		LOG("FORWARD ANIMATION ACTIVE");
		break;


	case jumpstate:

		current_animation = &jump;

		position.y -= speed * gravity;


		if (position.y <= 150)
		{
			gravity = -1;
		}

		else if (position.y == 220) {
			jump.Reset();
			currentstate = idlestate;
			gravity = 1;
		}
		LOG("JUMP ANIMATION ACTIVE");
		break;

	case punchlight:

		current_animation = &lightPunch;
		LOG("PUNCH ANIMATION ACTIVE");
		break;

	case kicklight:

		current_animation = &lightKick;
		LOG("KICK ANIMATION ACTIVE");
		break;

	case crouched:

		current_animation = &crouch;
		LOG("CROUCHED ANIMATION ACTIVE");
		break;

	case hadoukenstate:
		current_animation = &hadouken;
		LOG("KADOUKEN ANIMATION ACTIVE");
		break;

	case jumpkickstate:

		current_animation = &jumpbackkick;
		position.y -= speed * gravity;
		if (position.y <= 150)
		{
			gravity = -1;

		}
		else if (position.y == 220) {
			jump.Reset();
			currentstate = idlestate;
			gravity = 1;
			backwardjump.Reset();
		}
		LOG("JUMP KICK ACTIVE");
		break;

	case jumppunchstate:
		current_animation = &jumpbackpunch;
		position.y -= speed * gravity;
		if (position.y <= 150)
		{
			gravity = -1;

		}
		else if (position.y == 220) {
			jump.Reset();
			currentstate = idlestate;
			gravity = 1;
			backwardjump.Reset();
		}
		LOG("JUMP PUNCH ACTIVE");
		break;

	}
	
	


		
		
	

	//Screen Limits super cutres pero efectius
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

	//App->fonts->BlitText(100, 100, font_score, "h");
	
	return UPDATE_CONTINUE;
}

//TODO 7.4: Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	//THIS IS USELESS
	if (c2->type == COLLIDER_WALL) 
	{
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
			{
				speed = 0;
			}

			else
			{
				speed = 1;
			}
	}


}