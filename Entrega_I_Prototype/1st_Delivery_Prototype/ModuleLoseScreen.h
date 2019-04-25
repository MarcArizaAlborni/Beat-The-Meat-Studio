#pragma once
#ifndef __MODULELOSESCREEN_H__
#define __MODULELOSESCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleLoseScreen : public Module
{
public:
	ModuleLoseScreen();
	~ModuleLoseScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect lose_screen;

};

#endif // __MODULELOSESCREEN_H__