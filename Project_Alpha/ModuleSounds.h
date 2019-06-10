
#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleSounds : public Module {
public:
	ModuleSounds();
	~ModuleSounds();
	bool Start();
	bool CleanUp();
	update_status Update();

	SDL_Texture* graphics = nullptr;
	
	SDL_Rect credits1;
	SDL_Rect credits2;

	Animation insert_coin;

	Mix_Music* coin_Music;
	bool coin_inserted = false;
};