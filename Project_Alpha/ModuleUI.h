#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
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
	SDL_Rect characterIcon;
	SDL_Rect countryFlag;
	SDL_Rect countryFlagII;
	SDL_Rect p1_pointer;
	SDL_Rect p2_pointer;
	SDL_Rect plane;
	SDL_Rect coin;

	Animation p1_pointerAnim;
	int p1_pointerPosX = 0;
	int p1_pointerPosY = 0;

	Animation p2_pointerAnim;
	int p2_pointerPosX = 0;
	int p2_pointerPosY = 0;


	iPoint positionPointerP1;

	bool stage;
	bool character_select;
	char timechar[2];
	bool brazil;
	bool usa;
	bool usaII;
	bool urss;
	bool india;
	bool china;
	bool japan;
	bool japanII;

	bool insert_coin = false;
	
};

#endif // __MODULEUI_H__