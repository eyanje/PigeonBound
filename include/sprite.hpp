#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <map>
#include <vector>

#include "opengl_wrappers.hpp"

class Image {
    private:
        glw::VAO vao;
        glw::Buffer uvBuffer;
        glw::Buffer elementBuffer;
        glw::Program program;
        glw::Texture texture;

        unsigned int subWidth, subHeight;
        unsigned int subX, subY;
    public:
        Image(const std::string path);
        Image(const std::string path, const unsigned int width, const unsigned int height);
        Image(const std::string path, const unsigned int xOffset, const unsigned int yOffset,
            const unsigned int width, const unsigned int height);
        void render(const int x, const int y) const;
        void render(const int x, const int y, const int width, const int height) const;
};

class Animation {
    private:
        std::vector<Image> frames;
        std::vector<unsigned int> frameLengths;
        unsigned int frame;
        unsigned int subFrame;
    public:
        Image &getCurrentImage();
        Image &operator[](const int frame);

        void addFrame(const unsigned int length, const std::string path);
        void addFrame(const unsigned int length, const std::string path, const unsigned int width, const unsigned int height);
        void addFrame(const unsigned int length, const std::string path,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height);

        void render(const int x, const int y) const;
        void render(const int x, const int y, const int width, const int height) const;
    
        // Increases the subframe by 1
        void tick();
};

class Sprite {
    private:
        std::map<std::string, Animation> animations;
        std::string currentAnimation;
    public:
        Sprite(const std::string path);

        Animation &operator[](const std::string animationName);

        void addAnimation(const std::string, const Animation &a);

        std::string getCurrentAnimationName() const;
        Animation &getCurrentAnimation();

        void render(const int x, const int y) const;
        void render(const int x, const int y, const int width, const int height) const;

        // Increases the frame by 1
        void tick();
};

#endif