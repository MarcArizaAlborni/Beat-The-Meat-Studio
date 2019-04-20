#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#define _DEBUG
#include "Globals.h"

#define NUM_MODULES 17

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleSceneKen;
class ModuleSceneHonda;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleWelcomeScreen;
class ModuleCongratScreen;
class ModuleIcoinScreen;
class ModuleStartScreen;
class ModuleWarningScreen;
class ModuleWinScreen;
class ModuleFonts;

class Module;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneKen* scene_ken;
	ModuleSceneHonda* scene_honda;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleWelcomeScreen* welcome_screen;
	ModuleWarningScreen* warning_screen;
	ModuleIcoinScreen* icoin_screen;
	ModuleStartScreen* start_screen;
	ModuleWinScreen * win_screen;
	ModuleCongratScreen * congrat_screen;
	ModuleFonts* fonts;

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