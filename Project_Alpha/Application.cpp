
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneRyu.h"
#include "ModuleSceneHonda.h"
#include "ModuleSceneGuile.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayerII.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleCharacterSelect.h"
#include "ModuleCongratScreen.h"
#include "ModuleIcoinScreen.h"
#include "ModuleStartScreen.h"
#include "ModuleWarningScreen.h"
#include "ModuleWinScreen.h"
#include "ModuleLoseScreen.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = welcome_screen = new ModuleWelcomeScreen();
	modules[5] = warning_screen = new ModuleWarningScreen();
	modules[6] = icoin_screen = new ModuleIcoinScreen();
	modules[7] = start_screen = new ModuleStartScreen();
	modules[8] = character_select = new ModuleCharacterSelect();
	modules[9] = scene_honda = new ModuleSceneHonda();
	modules[10] = scene_guile = new ModuleSceneGuile();
	modules[11] = scene_ryu = new ModuleSceneRyu();
	modules[12] = win_screen = new ModuleWinScreen();
	modules[13] = lose_screen = new ModuleLoseScreen();
	modules[14] = player = new ModulePlayer();
	modules[15] = player2 = new ModulePlayer2();
	modules[16] = congrat_screen = new ModuleCongratScreen();
	modules[17] = particles = new ModuleParticles();
	modules[18] = collision = new ModuleCollision();
	modules[19] = fade = new ModuleFadeToBlack();
	modules[20] = ui = new ModuleUI();
	modules[21] = fonts = new ModuleFonts();
	modules[22] = audio = new ModuleAudio();

}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player->Disable();
	player2->Disable();
	collision->Disable();
	// Disable the map that you do not start with
	scene_honda->Disable();
	scene_guile->Disable();
	scene_ryu->Disable();
	congrat_screen->Disable();
	icoin_screen->Disable();
	warning_screen->Disable();
	character_select->Disable();
	win_screen->Disable();
	start_screen->Disable();
	lose_screen->Disable();
	ui->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	
	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}