#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "Globals.h"

#define NUM_MODULES 26

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleSceneRyu;
class ModuleSceneHonda;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleStartScreen;
class ModuleWarningScreen;
class ModuleGuys;
class ModuleWelcomeScreen;
class ModuleIcoinScreen;
class ModuleCharacterSelect;
class ModuleVsScreen;
class ModuleSceneGuile;
class ModuleWinScreen;
class ModuleLoseScreen;
class ModuleCongratScreen;
class ModuleUI;
class ModuleFonts;
class ModuleAudio;
class ModuleSounds;

class Module;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneRyu* scene_ryu;
	ModuleSceneHonda* scene_honda;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleWelcomeScreen* welcome_screen;
	ModuleGuys *guys_screen;
	ModuleWarningScreen* warning_screen;
	ModuleIcoinScreen* icoin_screen;
	ModuleStartScreen* start_screen;
	ModuleCharacterSelect * character_select;
	ModuleVsScreen * vs_screen;
	ModuleSceneGuile* scene_guile;
	ModuleWinScreen * win_screen;
	ModuleLoseScreen * lose_screen;
	ModuleCongratScreen * congrat_screen;
	ModuleUI * ui;
	ModuleFonts* fonts;
	ModuleAudio* audio;
	ModuleSounds* sounds;
	

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__