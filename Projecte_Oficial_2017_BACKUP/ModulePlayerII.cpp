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
int groundLevelII = 205;
int maxHeightII = 120;
bool airkickII = true;

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
	idle.PushBack({ 1152, 14, 154, 96});
	idle.PushBack({ 990, 14, 154, 96 });
	idle.PushBack({ 836, 14, 154, 96 });
	idle.PushBack({ 681 , 14, 154, 96 });
	idle.speed = 0.15f;

	//Walk FORWARD Animation 
	forward.PushBack({ 1152, 206, 154, 96 });
	forward.PushBack({ 990, 206, 154, 96 });
	forward.PushBack({ 836, 206, 154, 96 });
	forward.PushBack({ 681, 206, 154, 96 });
	forward.PushBack({ 528, 206, 154, 96 });
	forward.PushBack({ 371, 206, 154, 96 });

	forward.loop = true;
	forward.speed = 0.1f;

	//Walk backwards animation
	backward.PushBack({ 1152, 110, 154, 96 });
	backward.PushBack({ 990, 110, 154, 96 });
	backward.PushBack({ 836, 110, 154, 96 });
	backward.PushBack({ 681, 110, 154, 96 });
	backward.PushBack({ 528, 110, 154, 96 });
	backward.PushBack({ 371, 110, 154, 96 });
	backward.loop = true;
	backward.speed = 0.1f;

	//Crouch Animation
	crouch.PushBack({ 371, 14, 154, 96 });
	crouch.PushBack({ 210, 14, 154, 96 });
	crouch.PushBack({ 57, 14, 154, 96 });
	crouch.speed = 0.5;
	crouch.loop = false;

	//Ryu jump
	jump.PushBack({ 1151, 514, 154, 111 });
	jump.PushBack({ 989, 514, 154, 111 });
	jump.PushBack({ 835, 514, 154, 111 });
	jump.PushBack({ 681, 504, 154, 111 });
	jump.PushBack({ 527, 504, 154, 111 });
	jump.PushBack({ 371, 514, 154, 111 });
	jump.loop = false;
	jump.speed = 0.10f;
	
	//Forward Jump Animation
	forwardjump.PushBack({ 1151, 625, 154, 111 });
	forwardjump.PushBack({ 989, 625, 154, 111 });
	forwardjump.PushBack({ 371, 625, 154, 111 });
	forwardjump.PushBack({ 527, 625, 154, 111 });
	forwardjump.PushBack({ 836, 625, 154, 111 });
	forwardjump.PushBack({ 681, 625, 154, 111 });
	forwardjump.PushBack({ 371, 514, 154, 111 });
	forwardjump.speed = 0.1f;
	forwardjump.loop = false;

	//Backward Jump Animation
	backwardjump.PushBack({ 681, 625, 154, 111 });
	backwardjump.PushBack({ 836, 625, 154, 111 });
	backwardjump.PushBack({ 527, 625, 154, 111 });
	backwardjump.PushBack({ 371, 625, 154, 111 });
	backwardjump.PushBack({ 989, 625, 154, 111 });
	backwardjump.PushBack({ 1151, 625, 154, 111 });
	backwardjump.speed = 0.1f;
	backwardjump.loop = false;

	//Ryu Hadouken movement
	hadouken2.PushBack({ 1151, 740, 154, 95 });
	hadouken2.PushBack({ 989, 740, 154, 95 });
	hadouken2.PushBack({ 836, 740, 154, 95 });
	hadouken2.PushBack({ 681, 740, 154, 95 });
	hadouken2.loop = false;
	hadouken2.speed = 0.1f;
	 
	//Damaged Animation

	//Ryu light punch
	lightPunch.PushBack({ 1151, 1171, 154, 96 });
	lightPunch.PushBack({ 989, 1171, 154, 96 });
	lightPunch.PushBack({ 1151, 1171, 154, 96 });
	lightPunch.loop = true;
	lightPunch.speed = 0.1f;

	//Ryu light kick
	lightKick.PushBack({ 1151, 1274, 154, 97 });
	lightKick.PushBack({ 989, 1274, 154, 98 });
	lightKick.loop = false;
	lightKick.speed = 0.1f;
	
	//punchcrouch Animation
	crouchpunch.PushBack({ 1151, 1663, 164, 81 });
	crouchpunch.PushBack({ 989, 1663, 164, 81 });
	crouchpunch.speed = 0.15f;
	crouchpunch.loop = false;

	//kickcrouch Animation  
	crouchkick.PushBack({ 1151, 1912, 164, 71 });
	crouchkick.PushBack({ 989, 1912, 164, 71 });
	crouchkick.speed = 0.15f;
	crouchkick.loop = false;

	//Neutral punch jump Animation
	jumppunch.PushBack({ 1151, 1375, 162, 86 });
	jumppunch.PushBack({ 989, 1375, 162, 86 });
	jumppunch.speed = 0.1f;
	jumppunch.loop = false;
	
	//Neutral kick jump Animation
	jumpkick.PushBack({ 1151, 1456, 162, 121 });
	jumpkick.speed = 0.05f;
	jumpkick.loop = false;

	//Jumpbackkick Animation
	jumpbackkick.PushBack({ 681, 1578, 164, 91 });
	jumpbackkick.PushBack({ 528, 1578, 164, 91 });
	jumpbackkick.loop = false;
	jumpbackkick.speed = 0.08f;

	//jumpbackpunch Animation
	jumpbackpunch.PushBack({ 1151, 1375, 162, 86 });
	jumpbackpunch.PushBack({ 989, 1375, 162, 86 });
	jumpbackpunch.loop = false;
	jumpbackpunch.speed = 0.08f; 
	
	//jumpfrontkick Animation
	jumpfrontkick.PushBack({ 681,1578, 164, 91 });
	jumpfrontkick.PushBack({ 528,1578, 164, 91 });
	jumpfrontkick.loop = false;
	jumpfrontkick.speed = 0.08f;
	
	//jumpfrontpunch Animation 

	jumpfrontpunch.PushBack({ 1151, 1375, 162, 86 });
	jumpfrontpunch.PushBack({ 989, 1375, 162, 86 });
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
	LightDamage_Sound = App->audio->LoadFx("Audios/FX/25H.wav");
	Hadoken_Sound = App->audio->LoadFx("Audios/Voices/Ryu&Ken hadouken.wav");

	position.x = 180;
	position.y = 205;

	//Player 2 stest collider
	player2_collider = App->collision->AddCollider({ position.x, position.y - 100,60,93 }, COLLIDER_PLAYER2, App->player2);



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
				if (inputplayer2.Punch2_active) {
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = jumppunchstate2;
				}

				if (inputplayer2.Kick2_active) {
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

			if (current_animation->Finished()) {
				App->particles->hadouken2.speed.x = -5;
				App->particles->hadouken2.life = 2000;
				App->particles->AddParticle(App->particles->hadouken2, position.x + 25, position.y - 70, COLLIDER_PLAYER2_SHOT);
				currentstate = idlestate2;
				hadouken2.Reset();
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
				currentstate = crouched2;
				LOG("IDLE to CROUCH");
			}
			if (inputplayer2.Kick2_active) {
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = kicklight2;
				LOG("IDLE TO kick");
			}
			if (inputplayer2.Punch2_active) {
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = punchlight2;
				LOG("IDLE TO punch");
			}
			if (inputplayer2.Special2_active) {
				currentstate = hadoukenstate2;
				App->audio->PlayFx(Hadoken_Sound);  //PONER HADOUKEN SOUNDS
				LOG("IDLE TO hadouken");
			}
			if (inputplayer2.Up_active) {
				currentstate = jumpstate2;
				LOG("IDLE TO jump");
				current_animation = &jump;
			}
		}

		if (currentstate == backwardstate2) {

			if (!inputplayer2.Right_active) {
				currentstate = idlestate2;
				LOG("BACK TO IDLE");
			}
			if (inputplayer2.Punch2_active) {
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = punchlight2;
				LOG("BACK TO PUNCH");
			}
			if (inputplayer2.Up_active) {
				currentstate = jumpbackward2;
				LOG("BACK TO JUMP");
			}
			if (inputplayer2.Kick2_active) {
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
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = kicklight2;
				LOG("FORWARD TO KICK");
			}
			if (inputplayer2.Punch2_active) {
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
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = jumpbackwardpunch2;
					LOG("BACKWARDJUMP TO BACKWARDJUMPPUNCH");
				}

				if (inputplayer2.Kick2_active) {
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
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = jumpforwardpunch2;
					LOG("FORWARDJUMP TO FORWARDJUMPPUNCH");

				}

				if (inputplayer2.Kick2_active) {
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
			if (inputplayer2.Punch2_active) {
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = punchcrouch2;
			}

			if (inputplayer2.Kick2_active) {
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = kickcrouch2;
			}

			if (!inputplayer2.Down_active) {
				currentstate = idlestate2;
				LOG("CROUCH TO IDLE");
			}
		}

		if (currentstate == jumpkickstate2) {
			LOG("KICKJUMP TO IDLE");
			//if (current_animation->Finished()&& (position.y == groundLevelII)) {
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
			if (current_animation->Finished() && (position.y == groundLevelII)) {
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
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		position.y -= speedII * gravityII;


		if (position.y <= maxHeightII)
		{
			gravityII = -1;
		}

		else if (position.y == groundLevelII) {
			jump.Reset();
			airkickII = true;
			currentstate = idlestate2;
			gravityII = 1;
		}
		LOG("JUMPFALLING ANIMATION ACTIVE");
		break;

	case jumpbackwardkick2:

		current_animation = &jumpbackkick;
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		position.x -= speedII;
		position.y -= speedII * gravityII;


		if (position.y <= maxHeightII)
		{
			gravityII = -1;
		}

		else if (position.y == groundLevelII) {
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
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		position.x -= speedII;
		position.y -= speedII * gravityII;


		if (position.y <= maxHeightII)
		{
			gravityII = -1;
		}

		else if (position.y == groundLevelII) {
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
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		position.x += speedII;

		position.y -= speedII * gravityII;


		if (position.y <= maxHeightII)
		{
			gravityII = -1;
		}

		else if (position.y == groundLevelII) {
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
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		position.x += speedII;
		position.y -= speedII * gravityII;


		if (position.y <= maxHeightII)
		{
			gravityII = -1;
		}

		else if (position.y == groundLevelII) {
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
		position.x -= speedII;
		position.y -= speedII * gravityII;
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		if (position.y <= maxHeightII)
		{
			gravityII = -1;
		}
		else if (position.y == groundLevelII) {
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
		position.x += speedII;
		position.y -= speedII * gravityII;
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		if (position.y <= maxHeightII)
		{
			gravityII = -1;

		}
		else if (position.y == groundLevelII) {
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
		player2_collider->rect.h = 93;
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		current_animation = &idle;
		LOG("IDLE ANIMATION ACTIVE");
		break;


	case backwardstate2:
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		current_animation = &backward;
		position.x += speedII;
		LOG("BACKWARD ANIMATION ACTIVE");
		break;


	case forwardstate2:
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		current_animation = &forward;
		position.x -= speedII;
		LOG("FORWARD ANIMATION ACTIVE");
		break;


	case jumpstate2:

		current_animation = &jump;
		
		player2_collider->SetPos(position.x + 90  - App->render->camera.x, position.y - 93 - App->render->camera.y);
		position.y -= speedII * gravityII;


		if (position.y <= maxHeightII)
		{
			gravityII = -1;
		}

		else if (position.y == groundLevelII) {
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
		player2_collider->SetPos(position.x + 90 - App->render->camera.x + 5, position.y - 68 - App->render->camera.y);
		player2_collider->rect.h = 65;
		LOG("CROUCHED ANIMATION ACTIVE");
		break;

	case hadoukenstate2:

		current_animation = &hadouken2;
		LOG("KADOUKEN ANIMATION ACTIVE");
		break;

	case jumpkickstate2:

		current_animation = &jumpkick;
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		position.y -= speedII * gravityII;
		if (position.y <= maxHeightII)
		{
			gravityII = -1;

		}
		else if (position.y == groundLevelII) {
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
		player2_collider->SetPos(position.x + 90 - App->render->camera.x, position.y - 93 - App->render->camera.y);
		position.y -= speedII * gravityII;
		if (position.y <= maxHeightII)
		{
			gravityII = -1;

		}
		else if (position.y == groundLevelII) {
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
	if (position.x <= App->render->camera.x - 180 / SCREEN_SIZE)
	{
		position.x = App->render->camera.x - 180 / SCREEN_SIZE;
	}
	if (position.x >= SCREEN_WIDTH - 60 + App->render->camera.x - 180 / SCREEN_SIZE) { //Hardcodeado una mica, s'haura de revisar
		position.x = SCREEN_WIDTH - 60 + App->render->camera.x - 180/ SCREEN_SIZE;
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