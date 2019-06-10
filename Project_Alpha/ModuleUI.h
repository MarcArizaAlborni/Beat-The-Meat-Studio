#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphicsUI = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Rect healthbar;
	SDL_Rect health;
	SDL_Rect health2;
	SDL_Rect name;
	SDL_Rect name2;
	SDL_Rect score;
	SDL_Rect timer;
	SDL_Rect characterGrid;
	SDL_Rect characterIconP1;
	SDL_Rect characterIconP1II;
	SDL_Rect characterIconP2;
	SDL_Rect characterIconP2II;
	SDL_Rect countryFlagP1;
	SDL_Rect countryFlagP2;
	SDL_Rect countryFlagStage;
	SDL_Rect p1_pointer;
	SDL_Rect p2_pointer;
	SDL_Rect plane;
	SDL_Rect Logo;

	//Flag Pointer
	int p1_FlagPosX = 0;
	int p1_FlagPosY = 0;

	int p2_FlagPosX = 0;
	int p2_FlagPosY = 0;

	//Character Pointer
	Animation p1_pointerAnim;
	int p1_pointerPosX = 129;
	int p1_pointerPosY = 141;

	Animation p2_pointerAnim;
	int p2_pointerPosX = 129;
	int p2_pointerPosY = 173;

	float planePosX = 269.0f;
	float planePosY = 96.0f;

	bool stage;
	bool character_select;
	char timechar[2];

	//Flags
	bool brazilP1 = false;
	bool brazilP2 = false;
	bool stageFlag = false;

	//Flag Markers
	bool p1_characterSelect = false;
	bool p2_characterSelect = false;

	//Character Icons
	bool ryuIconP1 = false;
	bool blankaIconP1 = false;
	bool ryuIconP2 = false;
	bool blankaIconP2 = false;
	

	bool StreetLogo = false;
	
};

#endif // __MODULEUI_H__