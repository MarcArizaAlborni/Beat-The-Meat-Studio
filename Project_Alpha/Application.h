#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "Globals.h"

#define NUM_MODULES 20

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
class ModuleWelcomeScreen;
class ModuleCongratScreen;
class ModuleIcoinScreen;
class ModuleStartScreen;
class ModuleWarningScreen;
class ModuleWinScreen;
class ModuleLoseScreen;
class ModuleFonts;
class ModuleAudio;


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
	ModuleWarningScreen* warning_screen;
	ModuleIcoinScreen* icoin_screen;
	ModuleStartScreen* start_screen;
	ModuleWinScreen * win_screen;
	ModuleLoseScreen * lose_screen;
	ModuleCongratScreen * congrat_screen;
	ModuleFonts* fonts;
	ModuleAudio* audio;
	

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