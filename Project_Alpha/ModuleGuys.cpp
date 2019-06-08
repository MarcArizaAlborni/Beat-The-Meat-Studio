
#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleGuys.h"
#include "Animation.h"


ModuleGuys::ModuleGuys()
{

	building.x = 0;
	building.y = 0;
	building.w = SCREEN_WIDTH;
	building.h = SCREEN_HEIGHT;

	punch.PushBack({ 1053, 27, 384, 224 });



}

ModuleGuys::~ModuleGuys() {}
 
bool ModuleGuys::Start()
{
	LOG("Loading Building Screen");
	graphics = App->textures->Load("Sprites/Building.png");
	graphics2 = App->textures->Load("Sprites/Guys.png");


	return true;
}

bool ModuleGuys::CleanUp()
{
	LOG("Unloading Building Screen");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2); 
	return true;

}

update_status ModuleGuys::Update()
{
	SDL_Rect animation = punch.GetCurrentFrame();

	App->render->Blit(graphics, 0, 0, &building, 0.75f);
	App->render->Blit(graphics2, 0, 0, &animation, 0.75f);

	return UPDATE_CONTINUE;
}