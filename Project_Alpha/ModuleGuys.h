
#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleGuys : public Module
{
public:
	ModuleGuys();
	~ModuleGuys();

	bool Start();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation punch;
	Animation punch2;
	Animation punch3;
	SDL_Rect *cur_anim;
	SDL_Rect building;
	SDL_Rect sky;
	Animation people;

	float speed = 2.5f;
};