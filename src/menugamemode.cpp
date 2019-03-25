#include "gamemode.hpp"

#include <iostream>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "audio.hpp"
#include "defines.h"

MenuGameMode::MenuGameMode()
: selection(0),
transition(false),
transitionTimer(0),
label1("New Game"),
label2("Continue"),
label3("Settings"),
arrow("sprites/thatg.png") {

}

MenuGameMode::~MenuGameMode() {
    stopMusic();
    freeMusic("audio/title.ogg");
}

void MenuGameMode::processEvent(SDL_Event event) {
    if (transitionTimer > 0) {
        --transitionTimer;
    }
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                selection = (selection + 2) % 3;
                break;
            case SDLK_DOWN:
                selection = (selection + 1) % 3;
                break;
        }
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_Z:
                transition = true;
                break;
        }
    }
}

GameMode *MenuGameMode::nextGameMode() const {
    if (transition) {
        switch (selection) {
            case 0:
                std::cout << "New Game" << std::endl;
                return new GameGameMode();
                break;
            case 1:
                std::cout << "Continue Game" << std::endl;
                break;
            case 2:
                std::cout << "Options" << std::endl;
                break;
        }
    }
    return nullptr;
}

void MenuGameMode::update() {
}

void MenuGameMode::render() const {
    glClearColor(0, 1, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    arrow.render(0, HEIGHT / 2 + selection * 32, 20, 20);
    
    label1.render(50, HEIGHT / 2 + 32, WIDTH / 2);
    label2.render(50, HEIGHT / 2 + 2 * 32, WIDTH / 2);
    label3.render(50, HEIGHT / 2 + 3 * 32, WIDTH / 2);
    if (transition) {
        // Fade out
    }
}