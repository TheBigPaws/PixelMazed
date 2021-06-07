#include "AudioManager.h"
#include <iostream>


#define TITLE_MUS_PATH "sfx/Music/Violin Plucking.wav"
#define GAME_MUS_PATH "sfx/Music/Temple of the Summoner.wav"


void my_audio_callback(void* userdata, Uint8* stream, int len) {


	AudioData* audio = (AudioData*)userdata;

	if (audio->length == 0)
	return;		   

	len = (len > audio->length ? audio->length : len);

	SDL_memcpy(stream, audio->pos, len);

	SDL_MixAudioFormat(stream, audio->pos, AUDIO_S16, len, SDL_MIX_MAXVOLUME / 2);// mix from one buffer into another

	audio->pos += len;
	audio->length -= len;

}



void AudioManager::endMusic() {
	SDL_CloseAudioDevice(device);
	SDL_FreeWAV(wavStart);
	
}

AudioManager::AudioManager() {

	// enable SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_AUDIO);

	play_Title_Song();
}

void AudioManager::play_Title_Song() {
	
	playing = 0;
	if (SDL_LoadWAV(TITLE_MUS_PATH, &wavSpec, &wavStart, &wavLength) == NULL)
	{
		// TODO: Proper error handling
		std::cerr << "Error: " << TITLE_MUS_PATH
			<< " could not be loaded as an audio file" << std::endl;
	}

	audio.pos = wavStart;
	audio.length = wavLength;

	wavSpec.callback = my_audio_callback;
	wavSpec.userdata = &audio;

	device = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL,0);
	if (device == 0)
	{
		// TODO: Proper error handling
		std::cerr << "Error: " << SDL_GetError() << std::endl;
	}

	SDL_PauseAudioDevice(device, 0);//start playing

}

void AudioManager::play_Game_Song() {
	playing = 1;
	if (SDL_LoadWAV(GAME_MUS_PATH, &wavSpec, &wavStart, &wavLength) == NULL)
	{
		// TODO: Proper error handling
		std::cerr << "Error: " << GAME_MUS_PATH
			<< " could not be loaded as an audio file" << std::endl;
	}

	audio.pos = wavStart;
	audio.length = wavLength;

	wavSpec.callback = my_audio_callback;
	wavSpec.userdata = &audio;

	device = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	if (device == 0)
	{
		// TODO: Proper error handling
		std::cerr << "Error: " << SDL_GetError() << std::endl;
	}

	SDL_PauseAudioDevice(device, 0);//start playing
}

void AudioManager::updateSound(){
	if (audio.length < 10000) {
		endMusic();

		if (playing == 0) {
			play_Title_Song();
		}
		else { play_Game_Song(); }
	}
	
}

