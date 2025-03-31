#include "window_audio.hpp"

string audioFolder = "assets/audio/";

using namespace std;

void init_audio(Mixer* mixer){
    int sampleNbr = sizeof(mixer->pathes) / sizeof(string);
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
        std::cout << "Erreur lors l'ouverture de l'audio !" << std::endl;
        return;
    }

    Mix_AllocateChannels(sampleNbr);

    mixer->samples = new Mix_Chunk*[sampleNbr];
    for(int i = 0; i < sampleNbr; i++){
        mixer->samples[i] = Mix_LoadWAV((audioFolder + mixer->pathes[i]).c_str());
    }

    set_volume(mixer, Music1, 30);
    set_volume(mixer, Music2, 50);
    set_volume(mixer, Break, 90);
    set_volume(mixer, Bong, 120);
}

void free_sample(Mix_Chunk* sample){
    Mix_FreeChunk(sample);
}

void close_audio(Mixer* mixer){
    for(int i = 0; i < (int)(sizeof(mixer->samples) / sizeof(ESample)); i++){
        free_sample(mixer->samples[i]);
    }

    Mix_CloseAudio();
}

void set_volume(Mixer* mixer, ESample sample, int volume){
    Mix_VolumeChunk(mixer->samples[sample], volume);
}

void mute_audio_type(Mixer* mixer, int type){
    switch(type){
        case 0:
            for(int i = 0; i < (int)(sizeof(mixer->Effects) / sizeof(ESample)); i++){
                Mix_VolumeChunk(mixer->samples[mixer->Effects[i]], 0);
            }
            break;
        case 1:
            for(int i = 0; i < (int)(sizeof(mixer->Songs) / sizeof(ESample)); i++){
                Mix_VolumeChunk(mixer->samples[mixer->Songs[i]], 0);
            }
            break;
    }
}

void play(Mixer* mixer, ESample sample){
    Mix_PlayChannel(sample, mixer->samples[sample], -1);
}

void play(Mixer* mixer, ESample sample, int duree){
    Mix_PlayChannelTimed(sample, mixer->samples[sample], -1, duree);
}