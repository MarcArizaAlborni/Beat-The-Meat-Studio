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
	idle2.PushBack({ 1152, 14, 154, 96});
	idle2.PushBack({ 990, 14, 154, 96 });
	idle2.PushBack({ 836, 14, 154, 96 });
	idle2.PushBack({ 681 , 14, 154, 96 });
	idle2.speed = 0.15f;

	//Walk FORWARD Animation 
	forward2.PushBack({ 1152, 206, 154, 96 });
	forward2.PushBack({ 990, 206, 154, 96 });
	forward2.PushBack({ 836, 206, 154, 96 });
	forward2.PushBack({ 681, 206, 154, 96 });
	forward2.PushBack({ 528, 206, 154, 96 });
	forward2.PushBack({ 371, 206, 154, 96 });

	forward2.loop = true;
	forward2.speed = 0.1f;

	//Walk backwards animation
	backward2.PushBack({ 1152, 110, 154, 96 });
	backward2.PushBack({ 990, 110, 154, 96 });
	backward2.PushBack({ 836, 110, 154, 96 });
	backward2.PushBack({ 681, 110, 154, 96 });
	backward2.PushBack({ 528, 110, 154, 96 });
	backward2.PushBack({ 371, 110, 154, 96 });
	backward2.loop = true;
	backward2.speed = 0.1f;

	//Crouch Animation
	crouch2.PushBack({ 371, 14, 154, 96 });
	crouch2.PushBack({ 210, 14, 154, 96 });
	crouch2.PushBack({ 57, 14, 154, 96 });
	crouch2.speed = 0.5;
	crouch2.loop = false;

	//Ryu jump
	jump2.PushBack({ 1151, 514, 154, 111 });
	jump2.PushBack({ 989, 514, 154, 111 });
	jump2.PushBack({ 835, 514, 154, 111 });
	jump2.PushBack({ 681, 504, 154, 111 });
	jump2.PushBack({ 527, 504, 154, 111 });
	jump2.PushBack({ 371, 514, 154, 111 });
	jump2.loop = false;
	jump2.speed = 0.10f;
	
	//Forward Jump Animation
	forwardjump2.PushBack({ 1151, 625, 154, 111 });
	forwardjump2.PushBack({ 989, 625, 154, 111 });
	forwardjump2.PushBack({ 371, 625, 154, 111 });
	forwardjump2.PushBack({ 527, 625, 154, 111 });
	forwardjump2.PushBack({ 836, 625, 154, 111 });
	forwardjump2.PushBack({ 681, 625, 154, 111 });
	forwardjump2.PushBack({ 371, 514, 154, 111 });
	forwardjump2.speed = 0.1f;
	forwardjump2.loop = false;

	//Backward Jump Animation
	backwardjump2.PushBack({ 681, 625, 154, 111 });
	backwardjump2.PushBack({ 836, 625, 154, 111 });
	backwardjump2.PushBack({ 527, 625, 154, 111 });
	backwardjump2.PushBack({ 371, 625, 154, 111 });
	backwardjump2.PushBack({ 989, 625, 154, 111 });
	backwardjump2.PushBack({ 1151, 625, 154, 111 });
	backwardjump2.speed = 0.1f;
	backwardjump2.loop = false;

	//Ryu Hadouken movement
	hadouken2.PushBack({ 1151, 740, 154, 95 });
	hadouken2.PushBack({ 989, 740, 154, 95 });
	hadouken2.PushBack({ 836, 740, 154, 95 });
	hadouken2.PushBack({ 681, 740, 154, 95 });
	hadouken2.loop = false;
	hadouken2.speed = 0.1f;
	 
	//Damaged Animation

	//Ryu light punch
	lightPunch2.PushBack({ 1151, 1171, 154, 96 });
	lightPunch2.PushBack({ 989, 1171, 154, 96 });
	lightPunch2.PushBack({ 1151, 1171, 154, 96 });
	lightPunch2.loop = true;
	lightPunch2.speed = 0.1f;

	//Ryu light kick
	lightKick2.PushBack({ 1151, 1274, 154, 97 });
	lightKick2.PushBack({ 989, 1274, 154, 98 });
	lightKick2.loop = false;
	lightKick2.speed = 0.1f;
	
	//punchcrouch Animation
	crouchpunch2.PushBack({ 1151, 1663, 164, 81 });
	crouchpunch2.PushBack({ 989, 1663, 164, 81 });
	crouchpunch2.speed = 0.15f;
	crouchpunch2.loop = false;

	//kickcrouch Animation  
	crouchkick2.PushBack({ 1151, 1912, 164, 71 });
	crouchkick2.PushBack({ 989, 1912, 164, 71 });
	crouchkick2.speed = 0.15f;
	crouchkick2.loop = false;

	//Neutral punch jump Animation
	jumppunch2.PushBack({ 1151, 1375, 162, 86 });
	jumppunch2.PushBack({ 989, 1375, 162, 86 });
	jumppunch2.speed = 0.1f;
	jumppunch2.loop = false;
	
	//Neutral kick jump Animation
	jumpkick2.PushBack({ 1151, 1456, 162, 121 });
	jumpkick2.speed = 0.05f;
	jumpkick2.loop = false;

	//Jumpbackkick Animation
	jumpbackkick2.PushBack({ 681, 1578, 164, 91 });
	jumpbackkick2.PushBack({ 528, 1578, 164, 91 });
	jumpbackkick2.loop = false;
	jumpbackkick2.speed = 0.08f;

	//jumpbackpunch Animation
	jumpbackpunch2.PushBack({ 1151, 1375, 162, 86 });
	jumpbackpunch2.PushBack({ 989, 1375, 162, 86 });
	jumpbackpunch2.loop = false;
	jumpbackpunch2.speed = 0.08f; 
	
	//jumpfrontkick Animation
	jumpfrontkick2.PushBack({ 681,1578, 164, 91 });
	jumpfrontkick2.PushBack({ 528,1578, 164, 91 });
	jumpfrontkick2.loop = false;
	jumpfrontkick2.speed = 0.08f;
	
	//jumpfrontpunch Animation 

	jumpfrontpunch2.PushBack({ 1151, 1375, 162, 86 });
	jumpfrontpunch2.PushBack({ 989, 1375, 162, 86 });
	jumpfrontpunch2.loop = false;
	jumpfrontpunch2.speed = 0.08f;
}

ModulePlayer2::~ModulePlayer2()
{

}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/RyuP1_Inv.png"); // JA TE LA FOTO BONA
	graphics2 = App->textures->Load("Sprites/RyuP1_Def.png"); // JA TE LA FOTO BONA
	LightDamage_Sound = App->audio->LoadFx("Audios/FX/25H.wav");
	Hadoken_Sound = App->audio->LoadFx("Audios/Voices/Ryu&Ken hadouken.wav");

	position.x = 180;
	position.y = 205;

	//Player 2 stest collider
	player2_collider = App->collision->AddCollider({ position.x, position.y - 100,56,93 }, COLLIDER_PLAYER2, App->player2);
	attack_collider2 = nullptr;


	return ret;
}


bool ModulePlayer2::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphics);
	App->audio->UnLoadFX(LightDamage_Sound);
	App->audio->UnLoadFX(Hadoken_Sound);

	return true;
}


update_status ModulePlayer2::PreUpdate() {



	//MOVE BACKWARD
	inputplayer2.Right_active = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_REPEAT;
	//MOVE FORWARD
	inputplayer2.Left_active = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_REPEAT;
	//JUMP
	inputplayer2.Up_active = App->input->keyboard[SDL_SCANCODE_UP] == KEY_REPEAT;
	//CROUCHzzz
	inputplayer2.Down_active = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_REPEAT;
	//LIGHT PUNCH
	inputplayer2.Punch2_active = App->input->keyboard[SDL_SCANCODE_P] == KEY_DOWN;
	//LIGHT KICK
	inputplayer2.Kick2_active = App->input->keyboard[SDL_SCANCODE_O] == KEY_DOWN;
	//HADOKEN 
	inputplayer2.Special2_active = App->input->keyboard[SDL_SCANCODE_I ] == KEY_DOWN;

	{
		if (currentstate == punchlight2) {

			if (!App->player->flip){
				if (current_animation->Finished()) {
					attack_collider2->to_delete = true;
					currentstate = idlestate2;
					lightPunch2.Reset();
					alreadyHit2 = false;
					//lightPunch.Reset();
					LOG("PUNCH TO IDLE");
				}
		}
			if (App->player->flip) {
				if (current_animation->Finished()) {
					attack_collider2->to_delete = true;
					currentstate = idlestate2;
					App->player->lightPunch.Reset();
					alreadyHit2 = false;
					//lightPunch.Reset();
					LOG("PUNCH TO IDLE");
				}
			}
			
			LOG("PUNCH");
		}

		if (currentstate == kicklight2) {
			
			if (App->player->flip) {
				if (current_animation->Finished()) {
					attack_collider2->to_delete = true;
					currentstate = idlestate2;
					alreadyHit2 = false;
					App->player->lightKick.Reset();

					LOG("KICK TO IDLE");
				}
			}
			if (!App->player->flip) {
				if (current_animation->Finished()) {
					attack_collider2->to_delete = true;
					currentstate = idlestate2;
					alreadyHit2 = false;
					lightKick2.Reset();

					LOG("KICK TO IDLE");
				}
			}

		}

		if (currentstate == jumpstate2) {
			if (airkickII) {
				if (inputplayer2.Punch2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x + 65 ,position.y - 80 ,35 ,40 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = jumppunchstate2;
				}

				if (inputplayer2.Kick2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x + 65 ,position.y - 90 ,35 ,40 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
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
			if (!App->player->flip) {
				if (current_animation->Finished()) {
					App->particles->hadouken2.speed.x = -5;
					App->particles->hadouken2.life = 2000;
					App->particles->AddParticle(App->particles->hadouken2, position.x + 25, position.y - 70, COLLIDER_PLAYER2_SHOT);
					currentstate = idlestate2;
					hadouken2.Reset();
				}
			}
			if (App->player->flip) {
				if (current_animation->Finished()) {
					App->particles->hadouken.speed.x = 5;
					App->particles->hadouken.life = 2000;
					App->particles->AddParticle(App->particles->hadouken, position.x +100, position.y - 70, COLLIDER_PLAYER2_SHOT);
					currentstate = idlestate2;
					App->player->hadouken.Reset();
				}
			}
		}

		if (currentstate == idlestate2) {

			if (inputplayer2.Right_active) {
				currentstate = backwardstate2;
				LOG("IDLE TO BACK");
			}
			if (inputplayer2.Left_active) {
				currentstate = forwardstate2;
				LOG("IDLE TO forward");
			}
			if (inputplayer2.Down_active) {
				crouch2.Reset();
				currentstate = crouched2;
				LOG("IDLE to CROUCH");
			}
			if (!App->player->flip) {
				if (inputplayer2.Kick2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x + 40,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = kicklight2;
					LOG("IDLE TO kick");
				}
				if (inputplayer2.Punch2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x + 50,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = punchlight2;
					LOG("IDLE TO punch");
				}
			}
			if (App->player->flip) {
				if (inputplayer2.Kick2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x + 157,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = kicklight2;
					LOG("IDLE TO kick");
				}
				if (inputplayer2.Punch2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x + 152,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = punchlight2;
					LOG("IDLE TO punch");
				}
			}
			if (inputplayer2.Special2_active) {
				currentstate = hadoukenstate2;
				App->audio->PlayFx(Hadoken_Sound);  //PONER HADOUKEN SOUNDS
				LOG("IDLE TO hadouken");
			}
			if (inputplayer2.Up_active) {
				currentstate = jumpstate2;
				LOG("IDLE TO jump");
				current_animation = &jump2;
			}
		}

		if (currentstate == backwardstate2) {

			if (!inputplayer2.Right_active) {
				currentstate = idlestate2;
				LOG("BACK TO IDLE");
			}
			if (inputplayer2.Punch2_active) {
				attack_collider2 = App->collision->AddCollider({ position.x + 50,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER2_ATTACK, App->player2);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = punchlight2;
				LOG("BACK TO PUNCH");
			}
			if (inputplayer2.Up_active) {
				currentstate = jumpbackward2;
				LOG("BACK TO JUMP");
			}
			if (inputplayer2.Kick2_active) {
				attack_collider2 = App->collision->AddCollider({ position.x + 40,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER2_ATTACK, App->player2);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = kicklight2;
				LOG("BACK TO KICK");
			}
			if (inputplayer2.Down_active) {
				currentstate = crouched2;
				LOG("BACK TO CROUCH");
			}
		}

		if (currentstate == forwardstate2) {
			if (!inputplayer2.Left_active) {
				LOG("FORWARD TO IDLE");
				currentstate = idlestate2;
			}
			if (inputplayer2.Kick2_active) {
				attack_collider2 = App->collision->AddCollider({ position.x + 40,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER2_ATTACK, App->player2);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = kicklight2;
				LOG("FORWARD TO KICK");
			}
			if (inputplayer2.Punch2_active) {
				attack_collider2 = App->collision->AddCollider({ position.x + 50,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER2_ATTACK, App->player2);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = punchlight2;
				LOG("FORWARD TO PUNCH");
			}
			if (inputplayer2.Up_active) {
				currentstate = jumpforward2; // Aquest hauria de ser jump FORWARD pero no tenim l'animacio posada encara
				LOG("FORWARD TO JUMP");
			}
			if (inputplayer2.Down_active) {
				currentstate = crouched2;
				LOG("BACK TO CROUCH");
			}
		}

		if (currentstate == jumpbackward2) {
			LOG("BACKWARDJUMP TO IDLE");
			if (airkickII) {
				if (inputplayer2.Punch2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x + 65 ,position.y - 70 ,35 ,30 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = jumpbackwardpunch2;
					LOG("BACKWARDJUMP TO BACKWARDJUMPPUNCH");
				}

				if (inputplayer2.Kick2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x + 25 ,position.y - 70 ,60 ,30 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
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
				if (inputplayer2.Punch2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x + 65 ,position.y - 70 ,35 ,30 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = jumpforwardpunch2;
					LOG("FORWARDJUMP TO FORWARDJUMPPUNCH");

				}

				if (inputplayer2.Kick2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x +25 ,position.y - 70 ,60 ,30 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
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

			if (!App->player->flip) {
				LOG("BACKWARDJUMPKICK TO JUMP");
				if (jumpbackkick2.Finished()) {
					attack_collider2->to_delete = true;
					currentstate = jumpbackward2;
					airkickII = false;
					alreadyHit2 = false;
					jumpbackkick2.Reset();
				}
			}
			if (App->player->flip) {
				if (App->player->jumpfrontkick.Finished()) {
					attack_collider2->to_delete = true;
					currentstate = jumpbackward2;
					airkickII = false;
					alreadyHit2 = false;
					App->player->jumpfrontkick.Reset();
				}
			}

		}

		if (currentstate == jumpbackwardpunch2) {

			LOG("BACKWARDJUMPPUNCH TO JUMP");

		}

		if (airkickII) {
		
				if (currentstate == jumpforwardkick2) {
					if (!App->player->flip) {
						if (jumpfrontkick2.Finished()) {
							LOG("FORWARDJUMPKICK TO JUMPFORWARD")
								attack_collider2->to_delete = true;
							currentstate = jumpforward2;
							airkickII = false;
							alreadyHit2 = false;
						}
					}
					if (App->player->flip) {
						if (App->player->jumpfrontkick.Finished()) {
							attack_collider2->to_delete = true;
							currentstate = jumpforward2;
							airkickII = false;
							alreadyHit2 = false;
							jumpbackkick2.Reset();
						}
					}
				}
			
			
		}

		if (currentstate == jumpforwardpunch2) {

			LOG("FORWARDJUMPPUNCH TO JUMPFORWARD");

		}

		if (currentstate == punchcrouch2) {
			LOG("CROUCH TO CROUCHPUNCH");
			if (current_animation->Finished()) {
				attack_collider2->to_delete = true;
				currentstate = crouched2;
				App->player->crouchpunch.Reset();
				alreadyHit2 = false;
			}
		}

		if (currentstate == kickcrouch2) {
			LOG("CROUCH TO KICKCROUCH");
			if (current_animation->Finished()) {
				attack_collider2->to_delete = true;
				currentstate = crouched2;
				App->player->crouchkick.Reset();
				alreadyHit2 = false;
			}
		}

		if (currentstate == crouched2) {
			if (!App->player->flip) {
				if (inputplayer2.Punch2_active) {

					attack_collider2 = App->collision->AddCollider({ position.x + 60 ,position.y - 60 ,38 ,20 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = punchcrouch2;
				}

				if (inputplayer2.Kick2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x + 45 ,position.y - 24 ,50 ,25 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = kickcrouch2;
				}

				if (!inputplayer2.Down_active) {
					App->player->crouch;
					currentstate = idlestate2;
					LOG("CROUCH TO IDLE");
				}
			}
			if (App->player->flip) {
				if (inputplayer2.Punch2_active) {

					attack_collider2 = App->collision->AddCollider({ position.x +155 ,position.y - 60 ,38 ,20 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = punchcrouch2;
				}

				if (inputplayer2.Kick2_active) {
					attack_collider2 = App->collision->AddCollider({ position.x +155 ,position.y - 24 ,50 ,25 }, COLLIDER_PLAYER2_ATTACK, App->player2);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = kickcrouch2;
				}

				if (!inputplayer2.Down_active) {
					App->player->crouch;
					currentstate = idlestate2;
					LOG("CROUCH TO IDLE");
				}
			}
		}

		if (currentstate == jumpkickstate2) {
			LOG("KICKJUMP TO IDLE");
		
			if(!App->player->flip){
				if (jumpkick2.Finished()) {
					attack_collider2->to_delete = true;
					currentstate = jumpstate2;
					airkickII = false;
					alreadyHit2 = false;
				}
			}
			if (App->player->flip) {
				if (App->player->jumpkick.Finished()) {
					App->player->jumpkick.Reset();
					attack_collider2->to_delete = true;
					currentstate = jumpstate2;
					airkickII = false;
					alreadyHit2 = false;
				}

			}
		}

		if (currentstate == jumppunchstate2) {
			LOG("PUNCHJUMP ACTIVE");
			if (position.y == groundLevelII) {
				currentstate = jumpstate2;//-----------------------------------------------
				jumpbackpunch2.Reset();
				alreadyHit2 = false;
			}
		}


		if (currentstate == jumpfalling2) {

			if (current_animation->Finished()); {

				currentstate = idlestate2; //----------------------------------------------
				jump2.Reset();
			}
		}
	}
	return UPDATE_CONTINUE;

}

// Update: draw background
update_status ModulePlayer2::Update()
{
	if(!App->player->flip){
		switch (currentstate) {
		case jumpfalling2:

			current_animation = &jump2;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.y -= speedII * gravityII;


			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				jump2.Reset();
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
			}
			LOG("JUMPFALLING ANIMATION ACTIVE");
			break;

		case jumpbackwardkick2:

			current_animation = &jumpbackkick2;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.x += speedII;
			position.y -= speedII * gravityII;
			attack_collider2->rect.x = position.x + 35 - App->render->camera.x;
			attack_collider2->rect.y = position.y - 45;

			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				jump2.Reset();
				jumpbackkick2.Reset();
				backwardjump2.Reset();
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
			}
			LOG("JUMPBACKKICK ANIMATION ACTIVE");
			break;

		case jumpbackwardpunch2:

			current_animation = &jumpbackpunch2;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.x += speedII;
			position.y -= speedII * gravityII;

			attack_collider2->rect.x = position.x + 70 - App->render->camera.x;
			attack_collider2->rect.y = position.y - 65;
			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				jump2.Reset();
				airkickII = true;
				jumpbackpunch2.Reset();
				currentstate = idlestate2;
				gravityII = 1;
				alreadyHit2 = false;
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMPBACKPUNCH ANIMATION ACTIVE");
			break;


		case jumpforwardkick2:

			current_animation = &jumpfrontkick2;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.x -= speedII;

			position.y -= speedII * gravityII;
			attack_collider2->rect.x = position.x + 35 - App->render->camera.x;
			attack_collider2->rect.y = position.y -45 ;

			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				
				airkickII = true;
				
				currentstate = idlestate2;
				gravityII = 1;
				jumpfrontkick2.Reset();
				forwardjump2.Reset();
				backwardjump2.Reset();
				jump2.Reset();
			}
			LOG("JUMPFRONTKICK ANIMATION ACTIVE");
			break;

		case  jumpforwardpunch2:

			current_animation = &jumpfrontpunch2;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.x -= speedII;
			position.y -= speedII * gravityII;
			attack_collider2->rect.x = position.x + 70 - App->render->camera.x;
			attack_collider2->rect.y = position.y - 65;

			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				jumpfrontpunch2.Reset();
				jump2.Reset();
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
				alreadyHit2 = false;
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMPFRONTPUNCH ANIMATION ACTIVE");
			break;


		case damagedstate2:

			current_animation = &damaged2;
			LOG("DAMAGED ANIMATION ACTIVE");
			break;

		case jumpforward2:
			position.x -= speedII;
			position.y -= speedII * gravityII;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}
			else if (position.y == groundLevelII) {
				
				airkickII = true;
				currentstate = idlestate2;
				
				gravityII = 1;
				jump2.Reset();
				forwardjump2.Reset();
				backwardjump2.Reset();
				jumpfrontkick2.Reset();
			}
			current_animation = &forwardjump2;

			LOG("FORWARD JUMP ANIMATION ACTIVE");

			break;

		case jumpbackward2:

			current_animation = &backwardjump2;
			position.x += speedII;
			position.y -= speedII * gravityII;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			if (position.y <= maxHeightII)
			{
				gravityII = -1;

			}
			else if (position.y == groundLevelII) {
				
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
				jump2.Reset();
				jumpbackkick2.Reset();
				forwardjump2.Reset();
				backwardjump2.Reset();
			}

			LOG("backward JUMP ANIMATION ACTIVE");

			break;
		case punchcrouch2:

			current_animation = &crouchpunch2;
			LOG("CROUCH PUNCH ANIMATION ACTIVE")
				break;


		case kickcrouch2:

			current_animation = &crouchkick2;
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
			player2_collider->rect.h = 93;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			current_animation = &idle2;
			LOG("IDLE ANIMATION ACTIVE");
			break;


		case backwardstate2:
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			current_animation = &backward2;
			position.x += speedII;
			LOG("BACKWARD ANIMATION ACTIVE");
			break;


		case forwardstate2:
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			current_animation = &forward2;
			position.x -= speedII;
			LOG("FORWARD ANIMATION ACTIVE");
			break;


		case jumpstate2:

			current_animation = &jump2;

			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.y -= speedII * gravityII;


			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				jump2.Reset();

				airkickII = true;
				jumpkick2.Reset();
				currentstate = idlestate2;
				gravityII = 1;
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMP ANIMATION ACTIVE");
			break;

		case punchlight2:
			current_animation = &lightPunch2;
			LOG("PUNCH ANIMATION ACTIVE");
			break;

		case kicklight2:

			current_animation = &lightKick2;
			LOG("KICK ANIMATION ACTIVE");
			break;

		case crouched2:

			current_animation = &crouch2;

			player2_collider->SetPos(position.x + 90 - App->render->camera.x + 5, position.y - 68 - App->render->camera.y);
			player2_collider->rect.h = 65;
			LOG("CROUCHED ANIMATION ACTIVE");
			break;

		case hadoukenstate2:

			current_animation = &hadouken2;
			LOG("KADOUKEN ANIMATION ACTIVE");
			break;

		case jumpkickstate2:

			current_animation = &jumpkick2;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.y -= speedII * gravityII;
			attack_collider2->rect.y = position.y-90;
			attack_collider2->rect.x = position.x + 65 -App->render->camera.x;
			if (position.y <= maxHeightII)
			{
				gravityII = -1;

			}
			else if (position.y == groundLevelII) {
				jump2.Reset();
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
				backwardjump2.Reset();
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMP KICK ACTIVE");
			break;

		case jumppunchstate2:
			current_animation = &jumpbackpunch2;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.y -= speedII * gravityII;
			attack_collider2->rect.y = position.y - 80;
			attack_collider2->rect.x = position.x + 65 - App->render->camera.x;
			if (position.y <= maxHeightII)
			{
				gravityII = -1;

			}
			else if (position.y == groundLevelII) {
				jump2.Reset();
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
				backwardjump2.Reset();
				alreadyHit2 = false;
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMP PUNCH ACTIVE");
			break;
		}
	}
	if (App->player->flip) { //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

		switch (currentstate) {
		case jumpfalling2:

			current_animation = &App->player->jump;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.y -= speedII * gravityII;


			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				jump2.Reset();
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
			}
			LOG("JUMPFALLING ANIMATION ACTIVE");
			break;

		case jumpbackwardkick2:

			current_animation = &App->player->jumpfrontkick;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.x += speedII;
			position.y -= speedII * gravityII;
			attack_collider2->rect.x = position.x + 150 - App->render->camera.x;
			attack_collider2->rect.y = position.y - 45;

			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				
				
				currentstate = idlestate2;
				gravityII = 1;
				App->player->jumpfrontkick.Reset();
				App->player->forwardjump.Reset();
				App->player->backwardjump.Reset();
				airkickII = true;
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMPBACKKICK ANIMATION ACTIVE");
			break;

		case jumpbackwardpunch2:

			current_animation = &App->player->jumpbackpunch;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.x += speedII;
			position.y -= speedII * gravityII;
			attack_collider2->rect.x = position.x + 145 - App->render->camera.x;
			attack_collider2->rect.y = position.y - 65;

			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
			
				airkickII = true;
				
				currentstate = idlestate2;
				gravityII = 1;
				alreadyHit2 = false;
				App->player->jumpbackpunch.Reset();
				App->player->forwardjump.Reset();
				App->player->backwardjump.Reset();
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMPBACKPUNCH ANIMATION ACTIVE");
			break;


		case jumpforwardkick2:

			current_animation = &App->player->jumpfrontkick;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.x -= speedII;
			position.y -= speedII * gravityII;
			attack_collider2->rect.x = position.x + 150 - App->render->camera.x;
			attack_collider2->rect.y = position.y - 45;


			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
				App->player->jumpfrontkick.Reset();
				App->player->forwardjump.Reset();
				App->player->backwardjump.Reset();
				
				alreadyHit2 = false;
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMPFRONTKICK ANIMATION ACTIVE");
			break;

		case  jumpforwardpunch2:

			current_animation = &App->player->jumpfrontpunch;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.x -= speedII;
			position.y -= speedII * gravityII;
			attack_collider2->rect.x = position.x + 145 - App->render->camera.x;
			attack_collider2->rect.y = position.y - 65;

			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
				alreadyHit2 = false;
				App->player->jumpfrontpunch.Reset();
				App->player->forwardjump.Reset();
				App->player->backwardjump.Reset();

				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMPFRONTPUNCH ANIMATION ACTIVE");
			break;


		case damagedstate2:

			//current_animation = &App->player->damaged;
			LOG("DAMAGED ANIMATION ACTIVE");
			break;

		case jumpforward2:
			position.x -= speedII;
			position.y -= speedII * gravityII;
			current_animation = &App->player->backwardjump;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}
			else if (position.y == groundLevelII) {
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
				App->player->backwardjump.Reset();
				App->player->forwardjump.Reset();
				App->player->jumpfrontkick.Reset();
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			

			LOG("FORWARD JUMP ANIMATION ACTIVE");

			break;

		case jumpbackward2:

			current_animation = &App->player->forwardjump;
			position.x += speedII;
			position.y -= speedII * gravityII;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			if (position.y <= maxHeightII)
			{
				gravityII = -1;

			}
			else if (position.y == groundLevelII) {
				
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
				App->player->forwardjump.Reset();
				App->player->backwardjump.Reset();
				App->player->jumpfrontkick.Reset();
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}

			}

			LOG("backward JUMP ANIMATION ACTIVE");

			break;
		case punchcrouch2:

			current_animation = &App->player->crouchpunch;
			
			LOG("CROUCH PUNCH ANIMATION ACTIVE")
				break;


		case kickcrouch2:

			current_animation = &App->player->crouchkick;
			LOG("CROUCH KICK ANIMATION ACTIVE");
			break;

			

		case idlestate2:
			
			player2_collider->rect.h = 93;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			current_animation = &App->player->idle ;
			LOG("IDLE ANIMATION ACTIVE");
			break;


		case backwardstate2:
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			current_animation = &App->player->forward;
			position.x += speedII;
			LOG("BACKWARD ANIMATION ACTIVE");
			break;


		case forwardstate2:
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			current_animation = &App->player->backward;
			position.x -= speedII;
			LOG("FORWARD ANIMATION ACTIVE");
			break;


		case jumpstate2:

			current_animation = &App->player->jump;

			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.y -= speedII * gravityII;


			if (position.y <= maxHeightII)
			{
				gravityII = -1;
			}

			else if (position.y == groundLevelII) {
				
				airkickII = true;
				App->player->jumpkick.Reset();
				App->player->jump.Reset();
				App->player->jumppunch.Reset();

				currentstate = idlestate2;
				gravityII = 1;
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMP ANIMATION ACTIVE");
			break;

		case punchlight2:
			current_animation = &App->player->lightPunch;
			LOG("PUNCH ANIMATION ACTIVE");
			break;

		case kicklight2:

			current_animation = &App->player->lightKick;
			LOG("KICK ANIMATION ACTIVE");
			break;

		case crouched2:

			current_animation = &App->player->crouch;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x + 5, position.y - 68 - App->render->camera.y);
			player2_collider->rect.h = 65;
			LOG("CROUCHED ANIMATION ACTIVE");
			break;

		case hadoukenstate2:

			current_animation = &App->player->hadouken;
			LOG("KADOUKEN ANIMATION ACTIVE");
			break;

		case jumpkickstate2:

			current_animation = &App->player->jumpkick;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.y -= speedII * gravityII;

			attack_collider2->rect.x = position.x + 145 - App->render->camera.x;
			attack_collider2->rect.y = position.y - 90;
			if (position.y <= maxHeightII)
			{
				gravityII = -1;

			}
			else if (position.y == groundLevelII) {
				
				airkickII = true;
				currentstate = idlestate2;
				gravityII = 1;
				App->player->jumpkick.Reset();
				App->player->jump.Reset();
				App->player->jumppunch.Reset();
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}
			}
			LOG("JUMP KICK ACTIVE");
			break;

		case jumppunchstate2:
			current_animation = &App->player->jumppunch;
			player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
			position.y -= speedII * gravityII;
			attack_collider2->rect.x = position.x + 145 - App->render->camera.x;
			attack_collider2->rect.y = position.y - 60;

			if (position.y <= maxHeightII)
			{
				gravityII = -1;

			}
			else if (position.y == groundLevelII) {
				
				airkickII = true;
				alreadyHit2 = false;
				currentstate = idlestate2;
				gravityII = 1;
				App->player->jumpkick.Reset();
				App->player->jump.Reset();
				App->player->jumppunch.Reset();
				if (attack_collider2 != nullptr) {
					attack_collider2->to_delete = true;
				}

			}
			LOG("JUMP PUNCH ACTIVE");
			break;
		}
	}
	 
	//Limits ben fets
	if (position.x <= (App->render->camera.x ) / SCREEN_SIZE -90)
	{
		position.x = (App->render->camera.x ) / SCREEN_SIZE -90 ;
	}
	if (position.x >= (SCREEN_WIDTH   + App->render->camera.x) / SCREEN_SIZE +42) { 
		position.x = (SCREEN_WIDTH  + App->render->camera.x) / SCREEN_SIZE +42;
	}

	SDL_Rect r = current_animation->GetCurrentFrame();
	
	if (!App->player->flip) {
		App->render->Blit(graphics, position.x, position.y - r.h, &r);

	}
	else{
		App->render->Blit(graphics2, position.x + 87, position.y - r.h, &r);

	}


	// TODO 7.3: Update collider position to player position
	//PONER LOS COLLIDERS  DENTRO DE LOS STATES
	//player_collider->SetPos(position.x - App->render->camera.x, position.y - 93- App->render->camera.y);

	// Draw everything --------------------------------------
	

	

	


	return UPDATE_CONTINUE;
}

//TODO 7.4: Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	if (!alreadyHit2) {
		if (c1->type == COLLIDER_PLAYER2_ATTACK) {
			App->scene_ryu->health.x -= App->scene_ryu->damage;
			alreadyHit2 = true;
		}
	}

}