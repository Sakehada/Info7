#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;

enum Sample{
Break,
Bong,
Music1,
Music2
};

string audioFolder = "assets/audio/";

struct Mixer{  
    const string pathes[]{"ball.wav", "break.wav", "music1.wav", "music2.wav"};
    const Sample Effects[]{Break, Bong};
    bool effects{true};
    const Sample Songs[]{Music1, Music2};
    bool songs{true};
    Mix_Chunk** samples;
};

void init_audio();

void close_audio();

void free_sample(Mix_chunk* sample);

void set_volume(Mix_chunk* sample, int volume);

void mute_audio_type(int type);

void play(Sample sample);

void play(Sample sample, int duree);

