
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
#include "ModuleStartScreen.h"
#include "ModuleWarningScreen.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleGuys.h"
#include "ModuleIcoinScreen.h"
#include "ModuleCharacterSelect.h"
#include "ModuleVsScreen.h"
#include "ModuleCongratScreen.h"
#include "ModuleWinScreen.h"
#include "ModuleLoseScreen.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "ModuleSounds.h"


Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = welcome_screen = new ModuleWelcomeScreen();
	modules[i++] = guys_screen = new ModuleGuys();
	modules[i++] = warning_screen = new ModuleWarningScreen();
	modules[i++] = start_screen = new ModuleStartScreen();
	modules[i++] = icoin_screen = new ModuleIcoinScreen();
	modules[i++] = character_select = new ModuleCharacterSelect();
	modules[i++] = vs_screen = new ModuleVsScreen();
	modules[i++] = scene_honda = new ModuleSceneHonda();
	modules[i++] = scene_guile = new ModuleSceneGuile();
	modules[i++] = scene_ryu = new ModuleSceneRyu();
	modules[i++] = win_screen = new ModuleWinScreen();
	modules[i++] = lose_screen = new ModuleLoseScreen();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = player2 = new ModulePlayer2();
	modules[i++] = congrat_screen = new ModuleCongratScreen();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = sounds = new ModuleSounds();
	modules[i++] = fade = new ModuleFadeToBlack();
	modules[i++] = ui = new ModuleUI();
	modules[i++] = fonts = new ModuleFonts();
	modules[i++] = audio = new ModuleAudio();

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
	start_screen->Disable();
	warning_screen->Disable();
	icoin_screen->Disable();
	character_select->Disable();
	vs_screen->Disable();
	win_screen->Disable();
	lose_screen->Disable();
	congrat_screen->Disable();
	ui->Disable();
	guys_screen->Disable();
	//welcome_screen->Disable();

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