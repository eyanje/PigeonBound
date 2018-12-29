#include "gamemode.hpp"

#include <iostream>

#include <SDL_events.h>
#include <GL/glew.h>
#include <GL/gl.h>

TitleGameMode::TitleGameMode()
: transition(false),
background("sprites/title/title.spr") {
    std::cout << "Successfully created Title GameMode" << std::endl;
}

TitleGameMode::~TitleGameMode() {

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
