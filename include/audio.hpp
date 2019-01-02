#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <map>
#include <string>

#include <SDL_mixer.h>

struct AudioLibrary {
    static std::map<std::string, Mix_Music *> musicList;
};

// Plays music found at path
// Will load the song if necessary
void playMusic(std::string path);

// Stop all music
void stopMusic();

// Frees a track
void freeMusic(std::string path);

#endif