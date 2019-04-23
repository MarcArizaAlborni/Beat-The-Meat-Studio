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

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;
	
	position.x = 100;
	position.y = 220;
	score = 0;

	// idle animation (arcade sprite sheet)
	idle.PushBack({25, 54, 68, 100});
	idle.PushBack({93, 54, 67, 100});
	idle.PushBack({160, 54, 68, 100});
	idle.PushBack({223, 54, 67, 100});
	idle.speed = 0.15f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	
	//Walk FORWARD Animation
	forward.PushBack({ 27,250, 64, 92 });
	forward.PushBack({ 92, 250, 64, 92 });
	forward.PushBack({ 160, 248, 63, 90 });
	forward.PushBack({ 236, 250, 64, 91 });
	forward.PushBack({ 306, 250, 64, 89 });
	forward.PushBack({ 369, 250, 64, 89 });

	forward.loop = true;
	forward.speed = 0.1f;

	//Walk backwards animation
	backward.PushBack({ 27, 155, 67, 94 });
	backward.PushBack({ 94, 155, 67, 94 });
	backward.PushBack({ 162, 155, 67, 94 });
	backward.PushBack({ 236, 155, 67, 94 });
	backward.PushBack({ 298, 155, 67, 94});
	backward.PushBack({ 362, 155, 67, 94 });
	backward.loop = true;
	backward.speed = 0.1f;

	//Ryu light punch
	lightPunch.PushBack({ 34, 1368, 70, 96 });
	lightPunch.PushBack({ 112, 1368, 101, 96 } );
	lightPunch.loop = true;
	lightPunch.speed = 0.09f;

	//Ryu light kick
	lightKick.PushBack({ 35, 1586, 69, 97 });
	lightKick.PushBack({ 125, 1585, 120, 98 });
	lightKick.loop = true;
	lightKick.speed = 0.05f;

	//Ryu jump
	jump.PushBack({ 17, 600, 63, 89 });
	jump.PushBack({ 80, 600, 62, 107 });
	jump.PushBack({ 149, 600, 54, 93 });
	jump.PushBack({ 207, 600, 61, 81 });
	jump.PushBack({ 282, 600, 56, 81 });
	jump.PushBack({ 343, 600, 61,114 });
	jump.loop = true;
	jump.speed = 0.015f;

	//Ryu Hadouken movement
	hadouken.PushBack({18, 875, 80, 95});
	hadouken.PushBack({100, 875, 90, 95});
	hadouken.PushBack({190, 875, 97, 95});
	hadouken.PushBack({290, 875, 110, 95});
	hadouken.loop = true;
	hadouken.speed = 0.1f;
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

// Update: draw background
update_status ModulePlayer::Update()
{
	
	Animation* current_animation = &idle;
	//MOVE FWD
	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		current_animation = &forward;

		if (current_animation != &forward)
		{
			forward.Reset();
			current_animation = &forward;
		}
	}
	//MOVE BCKWD
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		current_animation = &backward;
		
		if (current_animation != &backward)
		{
			backward.Reset();
			current_animation = &backward;
		}
	}
	
	int i=0;
	//LIGHT PUNCH  I
	if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
	{
		
		i = 1;
		
		
		current_animation = &lightPunch;
			

			if (current_animation != &lightPunch)
			{
				lightPunch.Reset();
				current_animation = &lightPunch;

			}
			
		

	}
	
	

	

	
	
	if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &lightKick;

		if (current_animation != &lightKick)
		{
			lightKick.Reset();
			current_animation = &lightKick;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &jump;

		if (current_animation != &jump )
		{
			jump.Reset();
			current_animation = &jump;
		}
	
		
	}
	
	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_REPEAT)
	{
		
		current_animation = &hadouken;


		if (current_animation != &hadouken)
		{
			hadouken.Reset();
			current_animation = &hadouken;
		}
		

	}
	/*if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_UP)
	{
		finishedhadouken = true;
	}*/

	//if (finishedhadouken = true) {


	//	current_animation = &hadouken;
	//}

	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_UP ) // AIXO ha de ser key UP perque el projectil no apareix fins que tota l'animacio del hadouken s'ha fet.
	{
		App->particles->AddParticle(App->particles->hadouken, position.x + 25, position.y - 70, COLLIDER_PLAYER_SHOT);
		App->particles->hadouken.speed.x = 5;
		App->particles->hadouken.life = 2000;
	}

	//Screen Limits super cutres pero efectius
	if (position.x<=0 + App->render->camera.x)
	{
		position.x = 0 + App->render->camera.x;
	}
	if (position.x >= SCREEN_WIDTH-60 + App->render->camera.x) { //Hardcodeado una mica, s'haura de revisar
		position.x = SCREEN_WIDTH-60 + App->render->camera.x;
	}



	// TODO 7.3: Update collider position to player position
	player_collider->SetPos(position.x - App->render->camera.x, position.y - 93- App->render->camera.y);
	
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