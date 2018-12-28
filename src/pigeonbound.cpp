#include <iostream>

#include <GL/glew.h>
#include <SDL.h>

#include "gamemode.hpp"

SDL_Window *window = nullptr;
GameMode *gameMode = nullptr;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "Failed to init SDL" << std::endl;
        return 1;
    }

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    // Create SDL window
    window = SDL_CreateWindow("PigeonBound",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        320,
        180,
        SDL_WINDOW_OPENGL);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    
    GLenum glewInitError = glewInit();
    if (glewInitError != GLEW_OK) {
        std::cerr << "Failed to init glew " << glewGetErrorString(glewInitError) << std::endl;
        return 1;
    }

    bool running = true;
    gameMode = new TitleGameMode();

    while (running) {

        // Switch to the next gamemode, if necessary
        GameMode *nextGameMode = gameMode->nextGameMode();
        if (nextGameMode) {
            delete gameMode;
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

    delete gameMode;
    
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
