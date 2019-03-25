#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <map>
#include <vector>

#include "opengl_wrappers.hpp"

class Image {
    private:
        std::string path;

        glw::VAO vao;
        glw::Texture texture;
        glw::Buffer uvBuffer;
        glw::Buffer elementBuffer;
        glw::Program program;

        unsigned int subX;
        unsigned int subY;
        unsigned int subWidth;
        unsigned int subHeight;
    public:
        Image(const std::string path);
        Image(const std::string path, const unsigned int width, const unsigned int height);
        Image(const std::string path, const unsigned int xOffset, const unsigned int yOffset,
            const unsigned int width, const unsigned int height);
        Image(const void *data, const unsigned int width, const unsigned int height, const unsigned int bytesPerPixel);
        Image(const void *data, const unsigned int dataWidth, const unsigned int dataHeight, const unsigned int bytesPerPixel,
            const unsigned int width, const unsigned int height);
        Image(const void *data, const unsigned int dataWidth, const unsigned int dataHeight, const unsigned int bytesPerPixel,
            const unsigned int xOffset, const unsigned int yOffset,
            const unsigned int width, const unsigned int height);
        Image(const Image &image);
        Image(Image &&image) noexcept;
        ~Image();

        unsigned int getWidth() const;
        unsigned int getHeight() const;

        void render(const int x, const int y) const;
        void render(const int x, const int y, const int width, const int height) const;
};

class Animation {
    private:
        std::vector<Image> frames;
        std::vector<unsigned int> frameLengths;
        unsigned int frame = 0;
        unsigned int subFrame = 0;
    public:
        Animation();
        ~Animation();

        const Image &getCurrentFrame() const;
        Image &getCurrentFrame();
        Image &operator[](const int frame);

        void addFrame(const unsigned int length, const std::string path);
        void addFrame(const unsigned int length, const std::string path, const unsigned int width, const unsigned int height);
        void addFrame(const unsigned int length, const std::string path,
        const unsigned int x, const unsigned int y,
        const unsigned int width, const unsigned int height);

        void render(const int x, const int y) const;
        void render(const int x, const int y, const int width, const int height) const;
    
        // Resets the animation
        void reset();
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
        const Animation &getCurrentAnimation() const;
        Animation &getCurrentAnimation();

        void setCurrentAnimation(std::string currentAnimation);

        void render(const int x, const int y) const;
        void render(const int x, const int y, const int width, const int height) const;

        // Increases the frame by 1
        void tick();
};

#endif