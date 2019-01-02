#include "audio.hpp"

#include <iostream>
#include <map>
#include <string>

#include <SDL_mixer.h>

std::map<std::string, Mix_Music *> AudioLibrary::musicList;

void playMusic(std::string path) {
    if (!AudioLibrary::musicList[path]) {
        AudioLibrary::musicList[path] = Mix_LoadMUS(path.c_str());
        if (!AudioLibrary::musicList[path]) {
            std::cerr << "Failed to open music " << path << std::endl;
        }
    }
    if (Mix_FadeInMusic(AudioLibrary::musicList[path], -1, 100) == -1) {
        std::cerr << "Failed to start music " << path << std::endl;
    }
}

void stopMusic() {
    Mix_FadeOutMusic(100);
}

void freeMusic(std::string path) {
    if (AudioLibrary::musicList[path]) {
        Mix_FreeMusic(AudioLibrary::musicList[path]);
        AudioLibrary::musicList[path] = nullptr;
    }
}