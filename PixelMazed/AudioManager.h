#include <SDL.h>
#include <SDL_audio.h>
#undef main


//AUDIO PLAYBACK base functions BY BennyQBD
//https://github.com/BennyQBD/AudioTutorial/commit/091c4da6b4ab52472b3a9f3d65304bb6882e444b
struct AudioData
{
	Uint8* pos;
	Uint32 length;
};
  

class AudioManager
{
private:
	int playing = 0;//0 for title 1 for game
	bool paused;
	AudioData audio;
	SDL_AudioSpec wavSpec;
	Uint8* wavStart;
	Uint32 wavLength;
	SDL_AudioDeviceID device;
public:
	//void mixaudio(void* unused, Uint8* stream, int len);
	AudioManager();
	~AudioManager() {
		SDL_Quit();
	}
	void play_Title_Song();
	void play_Game_Song();
	void endMusic();
	void updateSound();
};
