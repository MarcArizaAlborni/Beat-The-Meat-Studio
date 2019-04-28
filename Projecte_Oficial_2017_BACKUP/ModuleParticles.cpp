#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayerII.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("RyuP1_def.png");

	//Hadouken Particle
	hadouken.anim.PushBack({ 183, 975, 65, 39 });
	hadouken.anim.PushBack({ 134, 975, 49, 39 });
	//ESTAS TRES SON PARA EL IMPACTO
	//hadouken.anim.PushBack({ 614, 1569, 26, 20 });
	//hadouken.anim.PushBack({ 652, 1566, 15, 25 });
	//hadouken.anim.PushBack({ 677, 1565, 28, 28 });
	hadouken.anim.loop = true;
	hadouken.anim.speed = 0.1f;


	hadouken2.anim.PushBack({ 2177, 975, 60, 39 });
	hadouken2.anim.PushBack({ 2237, 975, 56, 39 });
	hadouken2.anim.loop = true;
	hadouken2.anim.speed = 0.1f;

	// TODO 2: Create the template for a new particle "laser"
	/*laser.anim.PushBack({ 200, 121, 32, 10 });
	laser.anim.PushBack({ 233, 121, 32, 10 });
	laser.anim.PushBack({ 200, 121, 32, 10 });
	laser.anim.PushBack({ 233, 121, 32, 10 });
	laser.anim.loop = true;
	laser.anim.speed = 0.1f;*/

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x ;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

// TODO 7.5: Make so every time a particle hits a wall it triggers an explosion particle
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Before it's destroyed we decrese player 2 health
		if (active[i] != nullptr && active[i]->collider == c1 && c2 == App->player2->player2_collider)
		{
			App->scene_ryu->health2.w -= 10;
		}

		if (active[i] != nullptr && active[i]->collider == c1 && c2 == App->player->player_collider)
		{
			App->scene_ryu->health.x -= 10;
		}

		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
		
	}
}

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	//rect.x = (int)(-camera.x * speed) + x * SCREEN_SIZE;
	//(App->render->camera.x * speed.x) + position.x *SCREEN_SIZE;
	position.x +=  speed.x ; // speed.x ; 
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos( position.x - App->render->camera.x , position.y);

	return ret;
}