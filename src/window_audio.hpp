#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;

enum ESample{
Break,
Bong,
Music1,
Music2
};

struct Mixer{  
    const string pathes[4]{"break.wav", "ball.wav", "music1.wav", "music2.wav"};
    const ESample Effects[2]{Break, Bong};
    bool effects{true};
    const ESample Songs[2]{Music1, Music2};
    bool songs{true};
    Mix_Chunk** samples;
};

void init_audio(Mixer* mixer);

void close_audio(Mixer* mixer);

void free_sample(Mix_Chunk* sample);

void set_volume(Mix_Chunk* sample, int volume);

void mute_audio_type(int type);

void play(Mixer* mixer, ESample sample);

void play(Mixer* mixer, ESample sample, int duree);


