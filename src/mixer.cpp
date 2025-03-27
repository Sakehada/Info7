#include "mixer.hpp"

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
}

void free_sample(Mix_chunk* sample){
    Mix_FreeChunk(sample);
}

void close_audio(){
    for(int i = 0; i < sizeof(Audios) / sizeof(char*); i++){
        free_sample(samples[i]);
    }

    Mix_CloseAudio();
}

void set_volume(Sample sample, int volume){
    Mix_VolumeChannel((int)sample, volume);
}

void mute_audio_type(int type){
    switch(type){
        case 0:
            for(int i = 0; i < sizeof(Effects) / sizeof(Sample); i++){
                Mix_VolumeChannel(samples[Effects[i]], 0);
            }
            break;
        case 1:
            for(int i = 0; i < sizeof(Songs) / sizeof(Sample); i++){
                Mix_VolumeChannel(samples[Songs[i]], 0);
            }
            break;
    }
}

void play(Sample sample){
    Mix_PlayChannel(sample, samples[sample], -1);
}

void play(Sample sample, int duree){
    Mix_PlayChannelTimed(sample, samples[sample], -1, duree);
}