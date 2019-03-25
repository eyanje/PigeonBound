#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include "sprite.hpp"

class Entity {
    protected:
        Sprite sprite;

        int x;
        int y;
        unsigned int width;
        unsigned int height;
        
    public:
        Entity(std::string spritePath, int x, int y);
        
        Entity(std::string spritePath,
        const int x, const int y,
        const int width, const int height);
        
        virtual ~Entity() = 0;

        inline int getX() const { return x; }
        inline int getY() const { return y; }
        unsigned int getWidth() const;
        unsigned int getHeight() const;
        void translate(const int x, const int y);

        const inline Sprite &getSprite() const { return sprite; }
        inline void tick() { sprite.tick(); }
        virtual void update() = 0;
        virtual void render() const;

        inline void setAnimation(std::string animation) { sprite.setCurrentAnimation(animation); }
};

class OverworldEntity : public Entity {
    private:
    public:
        OverworldEntity();
        OverworldEntity(const std::string spritePath, const int x, const int y);
        OverworldEntity(const std::string spritePath, const int x, const int y, const int width, const int height);
        virtual ~OverworldEntity() = 0;

        virtual void render(const int xPersp, const int yPersp) const;
};

class OverworldPlayer : public OverworldEntity {
    public:
        OverworldPlayer(const std::string spritePath, const int x, const int y);
        ~OverworldPlayer();

        void update();
        void render(const int xPersp, const int yPersp) const;
};

#endif