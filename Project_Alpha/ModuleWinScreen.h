#pragma once
#ifndef __MODULEWINSCREEN_H__
#define __MODULEWINSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleWinScreen : public Module
{
public:
	ModuleWinScreen();
	~ModuleWinScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect win_screen;

};

#endif // __MODULEWINSCREEN_H__