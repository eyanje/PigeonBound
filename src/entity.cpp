#include "entity.hpp"

#include "audio.hpp"

Entity::Entity(std::string spritePath, const int x, const int y)
: Entity(spritePath, x, y, 0, 0) {

}

Entity::Entity(std::string spritePath,
const int x, const int y,
const int width, const int height)
: sprite(spritePath),
x(x),
y(y),
width(width),
height(height) {

}

Entity::~Entity() {

}

unsigned int Entity::getWidth() const {
    if (width) {
        return width;
    } else {
        return sprite.getCurrentAnimation().getCurrentFrame().getWidth();
    }
}

unsigned int Entity::getHeight() const {
    if (height) {
        return height;
    } else {
        return sprite.getCurrentAnimation().getCurrentFrame().getHeight();
    }
}

void Entity::translate(const int x, const int y) {
    this->x += x;
    this->y += y;
}

void Entity::render() const {
    sprite.render(x, y, width, height);
}

OverworldEntity::OverworldEntity()
: Entity("sprites/empty.spr", 0, 0) {
    // Do nothing
}

OverworldEntity::OverworldEntity(const std::string spritePath, const int x, const int y) 
: Entity(spritePath, x, y) {
}

OverworldEntity::OverworldEntity(const std::string spritePath, const int x, const int y, const int width, const int height) 
: Entity(spritePath, x, y, width, height) {
}

OverworldEntity::~OverworldEntity() {
}

void OverworldEntity::render(const int xPersp, const int yPersp) const {
    sprite.render(x - xPersp, y - yPersp);
}