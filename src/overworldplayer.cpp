#include "entity.hpp"

#include <string>

OverworldPlayer::OverworldPlayer(const std::string spritePath, const int x, const int y)
: OverworldEntity(spritePath, x, y, 10, 10)
{

}

OverworldPlayer::~OverworldPlayer() {

}

void OverworldPlayer::update() {

}

void OverworldPlayer::render(const int xPersp, const int yPersp) const {
    const int spriteWidth = sprite.getCurrentAnimation().getCurrentFrame().getWidth();
    const int spriteHeight = sprite.getCurrentAnimation().getCurrentFrame().getHeight();
    sprite.render(x - spriteWidth/2 - xPersp, y - spriteHeight/2 - yPersp, spriteWidth, spriteHeight);
}
