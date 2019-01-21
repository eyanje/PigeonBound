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
sample("Sample lorem ipsum text how doth the text run so I wonder? what horrible fate awaits"),
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
                transitionTimer = 30;
                break;
        }
    }
}

GameMode *MenuGameMode::nextGameMode() const {
    if (transition && transitionTimer <= 0) {
        switch (selection) {
            case 0:
                std::cout << "New Game" << std::endl;
                break;
            case 1:
                std::cout << "Continue Game" << std::endl;
                break;
            case 2:
                std::cout << "Options" << std::endl;
                break;
        }
        
        SDL_Event quitEvent;
        quitEvent.type = SDL_QUIT;
        SDL_PushEvent(&quitEvent);
    }
    return nullptr;
}

void MenuGameMode::update() {

}

void MenuGameMode::render() const {
    glClearColor(0, 1, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    arrow.render(0, HEIGHT / 2 + selection * 16, 20, 20);
    
    sample.render(10, 10, WIDTH / 2);
    if (transition) {
        // Fade out
    }
}