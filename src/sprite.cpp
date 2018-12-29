#include "sprite.hpp"

#include "defines.h"

Image::Image(std::string path)
: subX(0), subY(0),
elementBuffer(GL_ELEMENT_ARRAY_BUFFER),
program("shaders/basic.vert", "shaders/basic.frag"),
texture(path),
subWidth(texture.getWidth()),
subHeight(texture.getHeight())
{
    int vertices[] {
        texture.getWidth(), 0,
        0, 0,
        0, texture.getHeight(),
        texture.getWidth(), texture.getHeight()
    };
    vao.setVertexData(vertices, sizeof(vertices));

    constexpr unsigned char indices[] {
        0, 1, 2,
        0, 2, 3
    };
    elementBuffer.setData(indices, sizeof(indices));

}

Image::Image(const unsigned width, const unsigned height)
: subX(0), subY(0),
elementBuffer(GL_ELEMENT_ARRAY_BUFFER),
program("shaders/basic.vert", "shaders/basic.frag"),
texture(path),
subWidth(width),
subHeight(height)
{
    unsigned int vertices[] {
        width, 0,
        0, 0,
        0, height,
        height, height
    };
    vao.setVertexData(vertices, sizeof(vertices));

    constexpr unsigned char indices[] {
        0, 1, 2,
        0, 2, 3
    };
    elementBuffer.setData(indices, sizeof(indices));
}

Image::Image(std::string path,
const unsigned int xOffset, const unsigned int yOffset,
const unsigned int width, const unsigned int height)
: subX(xOffset), subY(yOffset),
elementBuffer(GL_ELEMENT_ARRAY_BUFFER),
program("shaders/basic.vert", "shaders/basic.frag"),
texture(path),
subWidth(width),
subHeight(height)
{
    unsigned int vertices[] {
        width, 0,
        0, 0,
        0, height,
        height, height
    };
    vao.setVertexData(vertices, sizeof(vertices));

    constexpr unsigned char indices[] {
        0, 1, 2,
        0, 2, 3
    };
    elementBuffer.setData(indices, sizeof(indices));
}

void Image::render(const int x, const int y) const {
    render(x, y, subWidth, subHeight);
}

void Image::render(const int x, const int y,
const int width, const int height) const {
    vao.bind();
    program.use();
    
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    texture.bind();

    elementBuffer.bind();

    glVertexAttribPointer(0, // location
 	2, // 2 elents per coord
 	GL_INT,
 	GL_FALSE,
 	0, // stride
 	nullptr);
    
    glVertexAttribPointer(1,
    2,
    GL_UNSIGNED_BYTE,
    GL_FALSE,
    0, // stride
    nullptr);

    program.uniform1i("textureSampler", 0);
    program.uniform1i("screenSize", WIDTH, HEIGHT);
    program.uniform1i("subCoords", subX, subY);
    program.uniform2i("subSize", subWidth, subHeight);
    program.uniform2i("objPos", x, y);
    program.uniform2i("size", width, height);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);

    glDisable(GL_TEXTURE_2D);
}

Image &Animation::getCurrentImage() {
    return frames[frame];
}

Image &Animation::operator[](int frame) {
    return frames[frame];
}

void Animation::addFrame(const unsigned int length, const std::string path) {
    frames.push_back(Image(path));
    frameLengths.push_back(length);
}
void Animation::addFrame(const unsigned int length, const std::string path,
const unsigned int width, const unsigned int height) {
    frames.push_back(Image(path, width, height));
    frameLengths.push_back(length);
}
void Animation::addFrame(const unsigned int length, const std::string path,
const unsigned int x, const unsigned int y,
const unsigned int width, const unsigned int height) {
    frames.push_back(Image(path, x, y, width, height));
    frameLengths.push_back(length);
}

void Animation::render(const int x, const int y) const {
    frames[frame].render(x, y);
}

void Animation::render(const int x, const int y, const int width, const int height) const {
    frames[frame].render(x, y, width, height);
}

void Animation::tick() {
    // subFrame = (subFrame + 1) % frameLengths[frame];
    // If the subframe is 0
    if (!(subFrame = ((subFrame + 1) % frameLengths[frame]))) {
        // Increase the frame number if necessary
        frame = (frame + 1) % frames.size();
    }
}

void Sprite::Sprite(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Cannot open image file " << path << std::endl;
    }

    for (std::string line; getline(file, path);) {
        std::istringstream tokenStream(line);
        char type;
        tokenStream >> type;

        Animation* currAnimation = nullptr;

        switch (type) {
            case 'a':
                std::string name;
                tokenStream >> name;

                if (!currAnimation) {
                    // set global current animation to the first
                    currentAnimation = name;
                }

                // Creates a new animation
                // Refers to the old animation if it exists
                currAnimation = animations[name];
                break;
            case 'i':
                unsigned int length = 1;
                tokenStream >> length;

                std::string path;
                tokenStream >> path;

                // Create image of just length and path
                if (tokenStream.eof()) {
                    currAnimation.addFrame(length, path);
                    break;
                }

                // Extracts width/height or x/y
                unsigned int t0 = 1;
                unsigned int t1 = 1;
                tokenStream >> t0;
                tokenStream >> t1;
                if (tokenStream.eof()) {
                    currAnimation.addFrame(length, path, t0, t1);
                    break;
                }
                
                // Extract width and height
                unsigned int t2 = 1;
                unsigned int t3 = 1;
                tokenStream >> t2;
                tokenStream >> t3;
                currAnimation.addFrame(length, path, t0, t1, t2, t3);
                break;
        }
    }
}
