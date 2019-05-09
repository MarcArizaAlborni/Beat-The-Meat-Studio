#pragma once
#ifndef __MODULECONGRATSCREEN_H__
#define __MODULECONGRATSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleCongratScreen : public Module
{
public:
	ModuleCongratScreen();
	~ModuleCongratScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect congrat_screen;

};

#endif // __MODULECONGRATSCREEN_H__