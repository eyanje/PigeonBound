#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_mixer.h>

#include "entity.hpp"
#include "sprite.hpp"
#include "ui.hpp"

class GameMode {
    public:
        GameMode() {}
        virtual ~GameMode() {}
        virtual void processEvent(const SDL_Event event) = 0;
        virtual GameMode *nextGameMode() const = 0;
        virtual void update() = 0;
        virtual void render() const = 0;
};

class TitleGameMode : public GameMode {
    private:
        bool transition;
        Sprite background;
    public:
        TitleGameMode();
        ~TitleGameMode();
        void processEvent(const SDL_Event event);
        GameMode *nextGameMode() const;
        void update();
        void render() const;
};

class MenuGameMode : public GameMode {
    private:
        int selection;
        bool transition;
        int transitionTimer;
        Text label1;
        Text label2;
        Text label3;
        Image arrow;
    public:
        MenuGameMode();
        ~MenuGameMode();
        void processEvent(const SDL_Event event);
        GameMode *nextGameMode() const;
        void update();
        void render() const;
};

class GameGameMode : public GameMode {
    private:
        Sprite background;
        OverworldPlayer player;
        std::map<SDL_Keycode, bool> keycodes;
        std::map<SDL_Scancode, bool> scancodes;
    public:
        GameGameMode();
        ~GameGameMode();
        void processEvent(const SDL_Event event);
        GameMode *nextGameMode() const;
        void update();
        void render() const;
};

#endif