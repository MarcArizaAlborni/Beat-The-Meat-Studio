
#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleGuys.h"
#include "Animation.h"
#include "ModuleUI.h"
#include "ModuleFadeToBlack.h"
#include "ModuleIcoinScreen.h"



ModuleGuys::ModuleGuys()
{

	sky = { 669, 598, SCREEN_WIDTH, 351 };

	building = { 285, 374, SCREEN_WIDTH, 575 };

	people.PushBack({ 285, 949, 384, 224 });
	people.PushBack({ 669, 949, 384, 224 });
	people.speed = 0.02; 

	punch.PushBack({ 1053, 53, 384, 224 });
	punch.PushBack({ 1437, 53, 384, 224 });
	punch.PushBack({ 1821, 53, 384, 224 });
	punch.PushBack({ 2205, 53, 384, 224 });
	punch.PushBack({ 1053, 53, 384, 224 });
	punch.PushBack({ 1437, 53, 384, 224 });
	punch.PushBack({ 1821, 53, 384, 224 });
	punch.PushBack({ 2205, 53, 384, 224 });
	punch.PushBack({ 1053, 53, 384, 224 });
	punch.PushBack({ 1437, 53, 384, 224 });
	punch.PushBack({ 1821, 53, 384, 224 });
	punch.PushBack({ 2205, 53, 384, 224 });
	punch.speed = 0.04f;

	punch2.PushBack({ 1053, 277, 384, 224 });
	punch2.PushBack({ 1437, 277, 384, 224 });
	punch2.PushBack({ 1821, 277, 384, 224 });
	punch2.PushBack({ 2205, 277, 384, 224 });
	punch2.PushBack({ 2589, 277, 384, 224 });
	punch2.PushBack({ 2973, 277, 384, 224 });

	punch2.PushBack({ 1053, 501, 384, 224 });
	punch2.PushBack({ 1437, 501, 384, 224 });
	punch2.PushBack({ 1821, 501, 384, 224 });
	punch2.PushBack({ 2205, 501, 384, 224 });
	punch2.PushBack({ 2589, 501, 384, 224 });
	punch2.PushBack({ 2973, 501, 384, 224 });

	punch2.PushBack({ 1053, 725, 384, 224 });
	punch2.PushBack({ 1437, 725, 384, 224 });
	punch2.PushBack({ 1821, 725, 384, 224 });
	punch2.PushBack({ 2205, 725, 384, 224 });
	punch2.PushBack({ 2589, 725, 384, 224 });
	punch2.PushBack({ 2973, 725, 384, 224 });

	punch2.PushBack({ 1053, 949, 384, 224 });
	punch2.PushBack({ 1437, 949, 384, 224 });
	punch2.PushBack({ 1821, 949, 384, 224 });
	punch2.PushBack({ 2205, 949, 384, 224 });
	punch2.PushBack({ 2589, 949, 384, 224 });
	punch2.PushBack({ 2973, 949, 384, 224 });

	punch2.PushBack({ 1053, 1173, 384, 224 });
	punch2.PushBack({ 1437, 1173, 384, 224 });
	punch2.PushBack({ 1821, 1173, 384, 224 });
	punch2.PushBack({ 2205, 1173, 384, 224 });
	punch2.PushBack({ 2589, 1173, 384, 224 });
	punch2.PushBack({ 2973, 1173, 384, 224 });

	punch2.PushBack({ 1053, 1397, 384, 224 });
	punch2.PushBack({ 1437, 1397, 384, 224 });
	punch2.PushBack({ 1821, 1397, 384, 224 });
	punch2.PushBack({ 2205, 1397, 384, 224 });
	punch2.PushBack({ 2589, 1397, 384, 224 });
	punch2.PushBack({ 2973, 1397, 384, 224 });

	punch2.PushBack({ 1053, 1621, 384, 224 });
	punch2.PushBack({ 1437, 1621, 384, 224 });
	punch2.PushBack({ 1821, 1621, 384, 224 });
	punch2.PushBack({ 2205, 1621, 384, 224 });
	punch2.PushBack({ 2589, 1621, 384, 224 });
	punch2.PushBack({ 2973, 1621, 384, 224 });

	punch2.PushBack({ 1053, 1845, 384, 224 });
	punch2.PushBack({ 1437, 1845, 384, 224 });
	punch2.PushBack({ 1821, 1845, 384, 224 });
	punch2.PushBack({ 2205, 1845, 384, 224 });
	punch2.PushBack({ 2589, 1845, 384, 224 });
	punch2.PushBack({ 2973, 1845, 384, 224 });

	punch2.PushBack({ 1053, 2069, 384, 224 });
	punch2.PushBack({ 1437, 2069, 384, 224 });
	punch2.PushBack({ 1821, 2069, 384, 224 });
	punch2.PushBack({ 2205, 2069, 384, 224 });
	punch2.PushBack({ 2589, 2069, 384, 224 });
	punch2.PushBack({ 2973, 2069, 384, 224 });

	punch2.PushBack({ 1053, 2293, 384, 224 });
	punch2.PushBack({ 1437, 2293, 384, 224 });
	punch2.PushBack({ 1821, 2293, 384, 224 });
	punch2.PushBack({ 2205, 2293, 384, 224 });
	punch2.PushBack({ 2589, 2293, 384, 224 });
	punch2.PushBack({ 2973, 2293, 384, 224 });
	punch2.speed = 0.8f;

	punch3.PushBack({ 1053, 2517, 384, 224 });
	punch3.PushBack({ 1437, 2517, 384, 224 });
	punch3.PushBack({ 1821, 2517, 384, 224 });
	punch3.PushBack({ 2205, 2517, 384, 224 });
	punch3.PushBack({ 2589, 2517, 384, 224 });
	punch3.PushBack({ 2973, 2517, 384, 224 });

	punch3.PushBack({ 1053, 2741, 384, 224 });
	punch3.PushBack({ 1437, 2741, 384, 224 });
	punch3.PushBack({ 1821, 2741, 384, 224 });
	punch3.PushBack({ 2205, 2741, 384, 224 });
	punch3.PushBack({ 2589, 2741, 384, 224 });
	punch3.PushBack({ 2973, 2741, 384, 224 });

	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.PushBack({ 2973, 53, 384, 224 });
	punch3.speed = 0.4f;
}

ModuleGuys::~ModuleGuys() {}
 
bool ModuleGuys::Start()
{
	LOG("Loading Building Screen");
	graphics = App->textures->Load("Sprites/Guys.png");
	App->ui->Enable();
	App->ui->StreetLogo = true;
	return true;
}

bool ModuleGuys::CleanUp()
{
	LOG("Unloading Building Screen");
	App->textures->Unload(graphics);

	return true;

}


update_status ModuleGuys::PreUpdate() 
{
	cur_anim = &punch.GetCurrentFrame();

	if (punch.Finished()) {
		cur_anim = &punch2.GetCurrentFrame();
	}

	if(punch2.Finished())
	{ 
		cur_anim = &punch3.GetCurrentFrame();
		App->render->camera.y -= speed;
	}

	if (punch3.Finished())
	{
		cur_anim = 0;
	}

	return UPDATE_CONTINUE;

}
update_status ModuleGuys::Update()
{
	SDL_Rect r = people.GetCurrentFrame();
	
	App->render->Blit(graphics, 0, -127, &sky, 0.67f);
	App->render->Blit(graphics, 0, -351, &building, 1.87f);
	App->render->Blit(graphics, 0, 0, &r, 1.75f);
	App->render->Blit(graphics, 0, 0, cur_anim, 1.75f);
	

	if (App->render->camera.y <=  -935) {

		speed = 0;
		
		App->fade->FadeToBlack(App->guys_screen, App->icoin_screen, 4.f);

	}

	return UPDATE_CONTINUE;
}