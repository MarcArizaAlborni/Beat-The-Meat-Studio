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
	/*forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.1f;*/

	forward.PushBack({ 78, 131, 60, 88 });
	forward.PushBack({ 162, 128, 64, 92 });
	forward.PushBack({ 259, 128, 63, 90 });
	forward.PushBack({ 352, 128, 54, 91 });
	forward.PushBack({ 432, 131, 50, 89 });
	forward.speed = 0.1f;

	//Walk backwards animation
	backward.PushBack({ 542, 131, 61, 87 });
	backward.PushBack({ 628, 129, 59, 90 });
	backward.PushBack({ 713, 128, 57, 91 });
	backward.PushBack({ 797, 126, 58, 91 });
	//backward.PushBack({ 883, 128, 58, 91 }); 
	backward.PushBack({ 974, 129, 58, 89 });
	backward.speed = 0.1f;

	//Ryu light punch
	lightPunch.PushBack({ 16, 272, 63, 91 });
	lightPunch.PushBack({ 108, 272, 92, 91 });
	lightPunch.speed = 0.2f;

	//Ryu light kick
	lightKick.PushBack({ 12, 657, 60, 94 });
	//lightKick.speed = 0.005f;
	lightKick.PushBack({ 95, 657, 48, 94 });
	lightKick.speed = 0.05f;
	lightKick.PushBack({ 167, 658, 80, 93 });
	lightKick.speed = 0.15f;

	//Ryu jump
	jump.PushBack({ 19, 847, 53, 85 });
	jump.PushBack({ 95, 823, 56, 104 });
	jump.PushBack({ 176, 805, 50, 89 });
	jump.PushBack({ 251, 798, 54, 77 });
	jump.PushBack({ 327, 813, 48, 70 });
	jump.PushBack({ 397, 810, 48, 89 });
	jump.PushBack({ 464, 819, 55, 109 });
	jump.speed = 0.1f;
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

bool ModulePlayer::CleanUp()
{
	LOG("Unloading Welcome Screen");
	App->textures->Unload(graphics);
	return true;
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

	if (App->input->keyboard[SDL_SCANCODE_U] == 1)
	{
		current_animation = &lightPunch;
	}

	if (App->input->keyboard[SDL_SCANCODE_J] == 1)
	{
		current_animation = &lightKick;
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &jump;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}