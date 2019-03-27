#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({7, 14, 60, 90});
	idle.PushBack({95, 15, 60, 89});
	idle.PushBack({184, 14, 60, 90});
	idle.PushBack({276, 11, 60, 93});
	idle.PushBack({366, 12, 60, 92});
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations
	backward.PushBack({ 541, 125, 60, 88 });
	backward.PushBack({ 622, 125, 60, 88 });
	backward.PushBack({ 709, 125, 60, 88 });
	backward.PushBack({ 795, 125, 60, 88 });
	backward.PushBack({ 880, 125, 60, 88 });
	backward.PushBack({ 972, 125, 60, 88 });
	
	backward.speed = 0.1f;

	//Ryu Punch Animation
	punch.PushBack({ 252, 263, 60, 100 });
	punch.PushBack({ 333, 263, 75, 100 });
	punch.PushBack({ 433, 263, 110, 100 });
	
	
	punch.speed = 0.1f;


	//Ryu Kick Animation
	kick.PushBack({ 605, 263, 65, 100 });
	kick.PushBack({ 688, 263, 70, 100 });
	kick.PushBack({ 776, 263, 120, 100 });


	kick.speed = 0.1f;

	
	//Ryu Jump Animation

	jump.PushBack({ 16,844,57,100 });
	jump.PushBack({ 97,819,65,120 });
	jump.PushBack({ 176,803,55,130 });
	jump.PushBack({ 235,797,75,140 });
	jump.PushBack({ 324,812,53,120 });
	jump.PushBack({ 394,805,51,120 });
	jump.PushBack({ 463,815,59,120 });
	jump.PushBack({ 16,844,57,100 });


	jump.speed = 0.2f;


	//Ryu Hadouken Animation

	special.PushBack({ 32,1543,76,92 });
	special.PushBack({ 133,1543,87,93 });
	special.PushBack({ 243,1543,93,93 });
	special.PushBack({ 354,1543,110,93 });
	special.PushBack({ 354,1543,182,93 });
	
	
	


	special.speed = 0.15f;


	//Projectile Hadouken Animation

	

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_K] == 1)
	{
		current_animation = &punch;
		
	}
	if (App->input->keyboard[SDL_SCANCODE_L] == 1)
	{
		current_animation = &kick;

	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &jump;

	}
	if (App->input->keyboard[SDL_SCANCODE_Z] == 1)
	{
		current_animation = &special;

	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}