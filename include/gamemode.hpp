#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <SDL_events.h>

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
    public:
        MenuGameMode();
        ~MenuGameMode();
        void processEvent(const SDL_Event event);
        GameMode *nextGameMode() const;
        void update();
        void render() const;
};

#endif