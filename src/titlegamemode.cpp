#include "gamemode.hpp"

#include <iostream>

#include <SDL_events.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>

TitleGameMode::TitleGameMode()
: transition(false),
background("sprites/title/title.spr"),
bgMusic(Mix_LoadMUS("audio/title.ogg")) {
    if (!bgMusic) {
        std::cerr << "Unable to load background music! " << Mix_GetError() << std::endl;
    } else if (Mix_PlayMusic(bgMusic, -1) == -1) {
        std::cerr << "Unable to play music! " << Mix_GetError() << std::endl;
    }

    std::cout << "Successfully created Title GameMode" << std::endl;
}

TitleGameMode::~TitleGameMode() {
    Mix_FreeMusic(bgMusic);

}

void TitleGameMode::processEvent(const SDL_Event event) {
    if (event.type == SDL_KEYDOWN
        && event.key.keysym.scancode == SDL_SCANCODE_Z) {
        transition = true;
    }
}

GameMode *TitleGameMode::nextGameMode() const {
    if (transition) {
        return new MenuGameMode();
    }
    return nullptr;
}

void TitleGameMode::update() {

}

void TitleGameMode::render() const {
    glClearColor(0.5, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    background.render(0, 0);
}
