#include "gamemode.hpp"

#include <string>

#include <SDL_events.h>

#include "audio.hpp"
#include "defines.h"
#include "entity.hpp"

GameGameMode::GameGameMode()
: background("sprites/player/player.spr"),
player("sprites/player/player.spr", 0, 0) {
    playMusic("audio/title-bit.ogg");
}

GameGameMode::~GameGameMode() {
    stopMusic();
}

void GameGameMode::processEvent(const SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        keycodes[event.key.keysym.sym] = true;
        scancodes[event.key.keysym.scancode] = true;
    } else if (event.type == SDL_KEYUP) {
        keycodes[event.key.keysym.sym] = false;
        scancodes[event.key.keysym.scancode] = false;
    }
}

GameMode *GameGameMode::nextGameMode() const {
    return nullptr;
}

void GameGameMode::update() {
    if (keycodes[SDLK_UP] != keycodes[SDLK_DOWN]
    || keycodes[SDLK_LEFT] != keycodes[SDLK_RIGHT]) {
        if (keycodes[SDLK_UP] != keycodes[SDLK_DOWN]) {
            if (keycodes[SDLK_UP]) {
                player.translate(0, -1);
            } else {
                player.translate(0, 1);
            }
            player.setAnimation("walk");
        }
        if (keycodes[SDLK_LEFT] != keycodes[SDLK_RIGHT]) {
            if (keycodes[SDLK_LEFT]) {
                player.translate(-1, 0);
            } else {
                player.translate(1, 0);
            }
            player.setAnimation("walk");
        }
    } else {
        player.setAnimation("stand");
    }

    background.tick();
    player.tick();
}

void GameGameMode::render() const {
    glClearColor(0, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    const int xCenter = player.getX() - WIDTH/2;
    const int yCenter = player.getY() - HEIGHT/2;

    background.render(-xCenter, -yCenter);

    player.render(xCenter, yCenter);
}