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
	graphics = NULL;
	current_animation = NULL;
	
	position.x = 100;
	position.y = 205;
	score = 0;

	health.x = 100;
	health.y = 400; 
	health.w = 200;
	health.h = 20;
	
	//App->render->DrawQuad(health, 255, 0, 0, alphaka);

	// idle animation (arcade sprite sheet)
	idle.PushBack({25, 54, 68, 98});
	idle.PushBack({93, 54, 67, 98});
	idle.PushBack({160, 54, 68, 98});
	idle.PushBack({223, 54, 67, 98});
	idle.speed = 0.15f;

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
	backward.PushBack({ 97, 155, 67, 100 });
	backward.PushBack({ 171, 155, 67, 100 });
	backward.PushBack({ 239, 155, 60, 94 });
	backward.PushBack({ 300, 155, 63, 100 });
	backward.PushBack({ 362, 155, 67, 94 });
	backward.loop = true;
	backward.speed = 0.1f;

	//Crouch Animation
	crouch.PushBack({ 519,156,67,95 });
	crouch.PushBack({ 587,156,68,95 });
	crouch.PushBack({ 654,156,68,95 });
	crouch.speed = 0.5f;
	crouch.loop = false;

	//Ryu jump
	jump.PushBack({ 17, 580, 63,105 });
	jump.PushBack({ 80, 580, 62, 115 });
	jump.PushBack({ 149, 580, 54, 100 });
	jump.PushBack({ 207, 580, 61, 100 });
	jump.PushBack({ 282, 580, 56,100 });
	jump.PushBack({ 343, 580, 61,120 });
	jump.loop = false;
	jump.speed = 0.10f;

	//Forward Jump Animation
	forwardjump.PushBack({ 13, 716, 62, 111  });
	forwardjump.PushBack({ 75, 716, 65, 91 });
	forwardjump.PushBack({ 140, 716, 112, 49 });
	forwardjump.PushBack({ 420, 695, 58, 85 });
	forwardjump.PushBack({ 140, 777, 129, 51 });
	forwardjump.PushBack({ 328, 767, 77, 93 });
	forwardjump.PushBack({ 343, 580, 61, 120 });
	forwardjump.speed = 0.1f;
	forwardjump.loop = false;

	//Backward Jump Animation
	backwardjump.PushBack({ 328, 767, 77, 93 });
	backwardjump.PushBack({ 140, 777, 129, 51 });
	backwardjump.PushBack({ 420, 695, 58, 85 });
	backwardjump.PushBack({ 140, 716, 112, 49 });
	backwardjump.PushBack({ 75, 716, 65, 91 });
	backwardjump.PushBack({ 13, 716, 62, 111 });
	backwardjump.speed = 0.1f;
	backwardjump.loop = false;

	//Ryu Hadouken movement
	hadouken.PushBack({ 18, 870, 80, 95 });
	hadouken.PushBack({ 100, 875, 90, 95 });
	hadouken.PushBack({ 190, 875, 97, 95 });
	hadouken.PushBack({ 290, 875, 110, 95 });
	hadouken.loop = false;
	hadouken.speed = 0.1f;


	//Damaged Animation

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

	//punchcrouch Animation
	crouchpunch.PushBack({ 34, 2038, 90, 72 });
	crouchpunch.PushBack({ 120, 2037, 105 , 73 });
	crouchpunch.speed = 0.15f;
	crouchpunch.loop = false;

	//kickcrouch Animation
	crouchkick.PushBack({ 32, 2296, 80, 70 });
	crouchkick.PushBack({ 109, 2296, 121, 70 });
	crouchkick.speed = 0.15f;
	crouchkick.loop = false;

	//Neutral punch jump Animation
	jumppunch.PushBack({ 259, 1693, 83, 91 });
	jumppunch.PushBack({ 353, 1693, 200, 78 });
	jumppunch.speed = 0.1f;
	jumppunch.loop = false;

	//Neutral kick jump Animation
	jumpkick.PushBack({ 33, 1802, 82, 95 });
	jumpkick.speed = 0.05f;
	jumpkick.loop = false;

	//Jumpbackkick Animation
	jumpbackkick.PushBack({347, 1925, 80, 91});
	jumpbackkick.PushBack({ 427, 1925, 135, 91 });
	jumpbackkick.loop = false;
	jumpbackkick.speed = 0.08f;
	
	
	//jumpbackpunch Animation
	jumpbackpunch.PushBack({ 23, 1689, 74, 91 });
	jumpbackpunch.PushBack({ 99, 1689, 104, 92 });
	jumpbackpunch.loop = false;
	jumpbackpunch.speed = 0.08f;

	//jumpfrontkick Animation
	jumpfrontkick.PushBack({ 347, 1925, 80, 91 });
	jumpfrontkick.PushBack({ 427, 1925, 135, 91 });
	jumpfrontkick.loop = false;
	jumpfrontkick.speed = 0.08f;
	
	// jumpfrontpunch Animation 
	jumpfrontpunch.PushBack({23, 1689, 74, 91});
	jumpfrontpunch.PushBack({ 99, 1689, 104, 92 });
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
	graphics = App->textures->Load("RyuP1_Def.png"); // JA TE LA FOTO BONA
	LightDamage_Sound = App->audio->LoadFx("Audios/FX/25H.wav");
	Hadoken_Sound = App->audio->LoadFx("Audios/Voices/Ryu&Ken hadouken.wav");

	position.x = 75;
	position.y = 205;


	//Player 2 stest collider
	player_collider = App->collision->AddCollider({ position.x , position.y - 100, 60, 93 }, COLLIDER_PLAYER, App->player);
	

	

	

	return ret;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphics);
	App->audio->UnLoadFX(LightDamage_Sound);
	App->audio->UnLoadFX(Hadoken_Sound);

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
	inputplayer1.Punch1_active = App->input->keyboard[SDL_SCANCODE_C] == KEY_DOWN;
	//LIGHT KICK
	inputplayer1.Kick1_active = App->input->keyboard[SDL_SCANCODE_V] == KEY_DOWN;
	//HADOKEN
	inputplayer1.Special1_active = App->input->keyboard[SDL_SCANCODE_B] == KEY_DOWN;

	{
		if (currentstate == punchlight) {
			
			if (current_animation->Finished()) {
				
				attack_collider->to_delete = true;
				currentstate = idlestate;
				alreadyHit = false;
				lightPunch.Reset();
				LOG("PUNCH TO IDLE");

			}
			LOG("PUNCH");
		}

		if (currentstate == kicklight) {

			if (current_animation->Finished()) {
				currentstate = idlestate;
				attack_collider->to_delete = true;
				alreadyHit = false;
				lightKick.Reset();
				LOG("KICK TO IDLE");
			}
		}

		if (currentstate == jumpstate) {
			if (airkick) {
				if (inputplayer1.Punch1_active) {
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate =jumppunchstate;
				}
					if (inputplayer1.Kick1_active) {
						App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
						currentstate = jumpkickstate;
					}
			}
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
			if (inputplayer1.Kick1_active) {
				currentstate = kicklight;
				attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER_ATTACK, App->player);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				LOG("IDLE TO kick");
			}
			if (inputplayer1.Punch1_active) {
				currentstate = punchlight;
				attack_collider = App->collision->AddCollider({ position.x+65 ,position.y-80 ,35 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				alreadyHit = false;
				LOG("IDLE TO punch");
			}
			if (inputplayer1.Special1_active) {
				App->audio->PlayFx(Hadoken_Sound); //PONER HADOUKEN SOUNDS 
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
			if (inputplayer1.Punch1_active){
				currentstate = punchlight;
				attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				LOG("BACK TO PUNCH");
			}
			if (inputplayer1.W_active) {
				currentstate =jumpbackward;
				LOG("BACK TO JUMP");
			}
			if (inputplayer1.Kick1_active) {
				currentstate = kicklight;
				attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER_ATTACK, App->player);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				LOG("BACK TO KICK");
			}
			if (inputplayer1.S_active) {
				currentstate = crouched;
				LOG("BACK TO KICK");
			}
		}

		if (currentstate == forwardstate) {
			if (!inputplayer1.D_active) {
				LOG("FORWARD TO IDLE");
				currentstate = idlestate;
			}
			if (inputplayer1.Kick1_active) {
				currentstate = kicklight;
				attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER_ATTACK, App->player);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				LOG("FORWARD TO KICK");
			}
			if (inputplayer1.Punch1_active) {
				currentstate = punchlight;
				attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				LOG("FORWARD TO PUNCH");
			}
			if (inputplayer1.W_active) {
				currentstate = jumpforward; 
				LOG("FORWARD TO JUMP");
			}
			if (inputplayer1.S_active) {
				currentstate = crouched;
				LOG("BACK TO KICK");
			}
		}

		if (currentstate == jumpbackward) {
			LOG("BACKWARDJUMP TO IDLE"); 
			if (airkick) {
			if (inputplayer1.Punch1_active) {
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = jumpbackwardpunch;
				LOG("BACKWARDJUMP TO BACKWARDJUMPPUNCH");
			}
				if (inputplayer1.Kick1_active) {
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS 
					currentstate = jumpbackwardkick;
					LOG("BACKWARDJUMP TO BACKWARDJUMPKICK");
				}
			}
		}
		if (currentstate == jumpforward) {
			LOG("FORWARDJUMP TO IDLE");
			if (airkick) {
			if (inputplayer1.Punch1_active) {
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = jumpforwardpunch;
				LOG("FORWARDJUMP TO FORWARDJUMPPUNCH");
			}
			if (inputplayer1.Kick1_active) {
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = jumpforwardkick;
					LOG("FORWARDJUMP TO FORWARDJUMPKICK");
				}
			}
		}

		if (currentstate == jumpbackwardkick) {	
			LOG("BACKWARDJUMPKICK TO JUMP");
			if (jumpbackkick.Finished()) {
				currentstate = jumpbackward;
				airkick = false;
				jumpbackkick.Reset();
			}
		}
		
		if (currentstate == jumpbackwardpunch) {
			LOG("BACKWARDJUMPPUNCH TO JUMP");
		}

		if (airkick) {
			if (currentstate == jumpforwardkick) {
				if (jumpfrontkick.Finished()) {
					LOG("FORWARDJUMPKICK TO JUMPFORWARD")
					currentstate = jumpforward;
					airkick = false;
				}
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
			if (inputplayer1.Punch1_active) {
				App->audio->PlayFx(LightDamage_Sound);
				currentstate = punchcrouch;
			}
			if (inputplayer1.Kick1_active) {
				App->audio->PlayFx(LightDamage_Sound);
				currentstate = kickcrouch;
			}
			if (!inputplayer1.S_active) {
				currentstate = idlestate;
				LOG("CROUCH TO IDLE");
			}
		}
	
		if (currentstate == jumpkickstate) {
			LOG("KICKJUMP TO IDLE");
				
			if (jumpkick.Finished()) {
				currentstate = jumpstate;
				airkick = false;
			}
		}
	
		if (currentstate == jumppunchstate) {
			LOG("PUNCHJUMP ACTIVE");
			if (current_animation->Finished()&& (position.y == groundLevel)) {
				currentstate = jumpstate;
				jumpbackpunch.Reset();
			}
		}
		
		if (currentstate == jumpfalling) {
			if (current_animation->Finished()); {
				currentstate = idlestate;
				jump.Reset();
			}
		}
	}
	return UPDATE_CONTINUE;
}

float gravity = 1;
update_status ModulePlayer::Update()
{
	switch (currentstate) {

	case jumpfalling:

		current_animation = &jump;
		position.y -= speed * gravity;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);

		if (position.y <= maxHeight)
		{
			gravity = -1;
		}

		else if (position.y == groundLevel) {
			jump.Reset();
			airkick = true;
			currentstate = idlestate;
			gravity = 1;
		}
		LOG("JUMPFALLING ANIMATION ACTIVE");
		break;

	case jumpbackwardkick:

		current_animation = &jumpbackkick;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		position.x -= speed;
		position.y -= speed * gravity;

		if (position.y <= maxHeight)
		{
			gravity = -1;
		}

		else if (position.y == groundLevel) {
			jump.Reset();
			jumpbackkick.Reset();
			backwardjump.Reset();
			airkick = true;
			currentstate = idlestate;
			gravity = 1;
		}
		LOG("JUMPBACKKICK ANIMATION ACTIVE");
		break;

	case jumpbackwardpunch:

		current_animation = &jumpbackpunch;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		position.x -= speed;
		position.y -= speed * gravity;

		if (position.y <= maxHeight)
		{
			gravity = -1;
		}

		else if (position.y == groundLevel) {
			jump.Reset();
			airkick = true;
			jumpbackpunch.Reset();
			backwardjump.Reset();
			currentstate = idlestate;
			gravity = 1;
		}
		LOG("JUMPBACKPUNCH ANIMATION ACTIVE");
		break;

	case jumpforwardkick:

		current_animation = &jumpfrontkick;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		position.x += speed;
		position.y -= speed * gravity;

		if (position.y <= maxHeight)
		{
			gravity = -1;
		}

		else if (position.y == groundLevel) {
			jump.Reset();
			airkick = true;
			jumpfrontkick.Reset();
			currentstate = idlestate;
			gravity = 1;
			forwardjump.Reset();
		}
		LOG("JUMPFRONTKICK ANIMATION ACTIVE");
		break;

	case  jumpforwardpunch:

		current_animation = &jumpfrontpunch;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		position.x += speed;
		position.y -= speed * gravity;

		if (position.y <= maxHeight)
		{
			gravity = -1;
		}

		else if (position.y == groundLevel) {
			jumpfrontpunch.Reset();
			jump.Reset();
			forwardjump.Reset();
			airkick = true;
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
		current_animation = &forwardjump;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		if (position.y <= maxHeight)
		{
			gravity = -1;
		}
		else if (position.y == groundLevel) {
			jump.Reset();
			airkick = true;
			currentstate = idlestate;
			jumpfrontkick.Reset();
			gravity = 1;
			forwardjump.Reset();
		}
		LOG("FORWARD JUMP ANIMATION ACTIVE");
		break;

	case jumpbackward:

		current_animation = &backwardjump;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		position.x -= speed;
		position.y -= speed * gravity;
		if (position.y <= maxHeight)
		{
			gravity = -1;
		}
		else if (position.y == groundLevel) {
			jump.Reset();
			airkick = true;
			currentstate = idlestate;
			gravity = 1;
			jumpbackkick.Reset();
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

	case idlestate:

		crouch.Reset();
		player_collider->rect.h = 93;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		current_animation = &idle;
		LOG("IDLE ANIMATION ACTIVE");
		break;

	case backwardstate:
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		current_animation = &backward;
		position.x -= speed;
		LOG("BACKWARD ANIMATION ACTIVE");
		break;

	case forwardstate:
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		current_animation = &forward;
		position.x += speed;
		LOG("FORWARD ANIMATION ACTIVE");
		break;

	case jumpstate:

		current_animation = &jump;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		position.y -= speed * gravity;

		if (position.y <= maxHeight)
		{
			gravity = -1;
		}

		else if (position.y == groundLevel) {
			jump.Reset();
 			airkick = true;
			jumpkick.Reset();
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
		player_collider->rect.h = 65;
		player_collider->SetPos(position.x - App->render->camera.x +5, position.y - 68 - App->render->camera.y);
		LOG("CROUCHED ANIMATION ACTIVE");
		break;

	case hadoukenstate:
		
		current_animation = &hadouken;
		LOG("KADOUKEN ANIMATION ACTIVE");
		break;

	case jumpkickstate:

		current_animation = &jumpkick;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		position.y -= speed * gravity;
		if (position.y <= maxHeight)
		{
			gravity = -1;

		}
		else if (position.y == groundLevel) {
			jump.Reset();
			airkick = true;
			currentstate = idlestate;
			gravity = 1;
			backwardjump.Reset();
		}
		LOG("JUMP KICK ACTIVE");
		break;

	case jumppunchstate:
		current_animation = &jumpbackpunch;
		player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
		position.y -= speed * gravity;

		if (position.y <= maxHeight)
		{
			gravity = -1;
		}
		else if (position.y == groundLevel) {
			jump.Reset();
			airkick = true;
			currentstate = idlestate;
			gravity = 1;
			backwardjump.Reset();
		}
		LOG("JUMP PUNCH ACTIVE");
		break;

	}
	//Limits ben fets
	if (position.x <= App->render->camera.x - 10 / SCREEN_SIZE)
	{
		position.x = App->render->camera.x - 10/ SCREEN_SIZE;
	}
	if (position.x >= SCREEN_WIDTH - 60 + App->render->camera.x -10/ SCREEN_SIZE) { //Hardcodeado una mica, s'haura de revisar
		position.x = SCREEN_WIDTH - 60 + App->render->camera.x -10/ SCREEN_SIZE;
	}

	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}

//TODO 7.4: Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (!alreadyHit) {
		if (c1->type==COLLIDER_PLAYER_ATTACK) {
			App->scene_ryu->health2.w -= 10;
			alreadyHit = true;
		}
	}


}