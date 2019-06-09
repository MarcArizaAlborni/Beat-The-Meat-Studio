
#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleAudio.h"

class ModuleSounds : public Module {
public:
	ModuleSounds();
	~ModuleSounds();
	bool Start();
	bool CleanUp();
	update_status Update();

	Mix_Music* coin_Music;
	bool coin_inserted = false;
};