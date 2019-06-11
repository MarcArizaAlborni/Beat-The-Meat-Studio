
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

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

	Mix_Music* Title_sound;
	Mix_Chunk* punch_sound;

	Uint32 timeLimit = 0;
	Uint32 deltaTime = SDL_GetTicks() / 1000;;
	Uint32 startTime = 0;

	float speed = 2.5f;
};