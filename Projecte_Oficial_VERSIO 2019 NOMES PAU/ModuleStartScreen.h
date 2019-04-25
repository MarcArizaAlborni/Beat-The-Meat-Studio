#pragma once
#ifndef __MODULESTARTSCREEN_H__
#define __MODULESTARTSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStartScreen : public Module
{
public:
	ModuleStartScreen();
	~ModuleStartScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect start_screen;

};

#endif // __MODULEWELCOMESCREEN_H__