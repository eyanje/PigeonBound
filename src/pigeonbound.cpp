#include <iostream>

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL.h>

#include "defines.h"
#include "gamemode.hpp"

SDL_Window *window = nullptr;
GameMode *gameMode = nullptr;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "Failed to init SDL" << std::endl;
        return 1;
    }

    const char *sdlError = SDL_GetError();
    if (sdlError && *sdlError) {
        std::cout << "SDL Error " << sdlError << std::endl;
    }

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    // Create SDL window
    window = SDL_CreateWindow("PigeonBound",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Failed to create SDL GL context!" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
    
    sdlError = SDL_GetError();
    if (sdlError && *sdlError) {
        std::cout << "SDL Error " << sdlError << std::endl;
    }

    glewExperimental = true;
    GLenum glewInitError = glewInit();
    if (glewInitError != GLEW_OK) {
        std::cerr << "Failed to init glew " << glewGetErrorString(glewInitError) << std::endl;
        
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
    if (!glGenBuffers) {
        std::cerr << "GLEW still failed" << std::endl;
        
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    bool running = true;
    std::cout << "Construction GameMode" << std::endl;

    gameMode = new TitleGameMode();

    while (running) {

        // Switch to the next gamemode, if necessary
        GameMode *nextGameMode = gameMode->nextGameMode();
        if (nextGameMode) {
            if (gameMode) {
                delete gameMode;
            }
            gameMode = nextGameMode;
        }

        // Update and render
        gameMode->update();
        gameMode->render();

        SDL_GL_SwapWindow(window);

        SDL_Delay(17);

        // Process events for next time
        // Also set running to false if necessary
        // Keep this at the end to prevent the game from looping twice before exiting
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT ||
                event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                running = false;
            }
            gameMode->processEvent(event);
        }
    }

    if (gameMode) {
        delete gameMode;
    }
    
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
