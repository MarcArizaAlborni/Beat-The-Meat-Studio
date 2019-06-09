
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

	bool GuileStage = false;
	Mix_Music* GuileStage_Sound;
};