#include "sprite.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <SDL_opengl.h>

#include "defines.h"

Image::Image(const std::string path)
: subX(0), subY(0),
uvBuffer(GL_ARRAY_BUFFER),
elementBuffer(GL_ELEMENT_ARRAY_BUFFER),
program("shaders/basic.vert", "shaders/basic.frag"),
texture(path),
subWidth(texture.getWidth()),
subHeight(texture.getHeight())
{
    unsigned int vertices[] {
        static_cast<unsigned int>(texture.getWidth()), 0,
        0, 0,
        0, static_cast<unsigned int>(texture.getHeight()),
        static_cast<unsigned int>(texture.getWidth()), static_cast<unsigned int>(texture.getHeight())
    };
    vao.setVertexData(vertices, sizeof(vertices));

    constexpr float uvs[] {
        1, 0,
        0, 0,
        0, 1,
        1, 1
    };
    uvBuffer.setData(uvs, sizeof(uvs));

    constexpr unsigned char indices[] {
        0, 1, 2,
        0, 2, 3
    };
    elementBuffer.setData(indices, sizeof(indices));

}

Image::Image(const std::string path, const unsigned int width, const unsigned int height)
: subX(0), subY(0),
uvBuffer(GL_ARRAY_BUFFER),
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

    constexpr float uvs[] {
        1, 0,
        0, 0,
        0, 1,
        1, 1
    };
    uvBuffer.setData(uvs, sizeof(uvs));

    constexpr unsigned char indices[] {
        0, 1, 2,
        0, 2, 3
    };
    elementBuffer.setData(indices, sizeof(indices));
}

Image::Image(const std::string path,
const unsigned int xOffset, const unsigned int yOffset,
const unsigned int width, const unsigned int height)
: subX(xOffset), subY(yOffset),
uvBuffer(GL_ARRAY_BUFFER),
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

    constexpr float uvs[] {
        1, 0,
        0, 0,
        0, 1,
        1, 1
    };
    uvBuffer.setData(uvs, sizeof(uvs));

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

    GLenum error;
    
    while (error = glGetError()) {
        std::cerr << "Error before rendering image " << error << std::endl;
    }
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    program.use();
    vao.bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, // location
 	2, // 2 elements per coord
 	GL_UNSIGNED_INT,
 	GL_FALSE,
 	0, // stride
 	nullptr);

    while (error = glGetError()) {
        std::cerr << "Error passing vertex attrib pointers " << error << std::endl;
    }
    
    uvBuffer.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, // location of uvs
    2,
    GL_FLOAT,
    GL_FALSE,
    0, // stride
    nullptr);
    while (error = glGetError()) {
        std::cerr << "Error passing uv attrib pointers " << error << std::endl;
    }
    
    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    program.uniform1i("textureSampler", 0);
    program.uniform2i("screenSize", WIDTH, HEIGHT);
    program.uniform2i("subCoords", subX, subY);
    program.uniform2i("subSize", subWidth, subHeight);
    program.uniform2i("objPos", x, y);
    program.uniform2i("size", width, height);

    while (error = glGetError()) {
        std::cerr << "Error passing all image uniforms " << error << std::endl;
    }

    elementBuffer.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);

    while (error = glGetError()) {
        std::cerr << "Error drawing elements " << error << std::endl;
    }

    // Don't know why but this throws 1280
    // glDisable(GL_TEXTURE_2D);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    while (error = glGetError()) {
        std::cerr << "Error unbinding " << error << std::endl;
    }
}

Image &Animation::getCurrentImage() {
    return frames.at(frame);
}

Image &Animation::operator[](const int frame) {
    return frames[frame];
}

void Animation::addFrame(const unsigned int length, const std::string path) {
    frames.emplace_back(path);
    frameLengths.push_back(length);
}

void Animation::addFrame(const unsigned int length, const std::string path,
const unsigned int width, const unsigned int height) {
    frames.emplace_back(path, width, height);
    frameLengths.push_back(length);
}
void Animation::addFrame(const unsigned int length, const std::string path,
const unsigned int x, const unsigned int y,
const unsigned int width, const unsigned int height) {
    frames.emplace_back(path, x, y, width, height);
    frameLengths.push_back(length);
}

void Animation::render(const int x, const int y) const {
    frames.at(frame).render(x, y);
}

void Animation::render(const int x, const int y, const int width, const int height) const {
    frames.at(frame).render(x, y, width, height);
}

void Animation::tick() {
    // subFrame = (subFrame + 1) % frameLengths[frame];
    // If the subframe is 0
    if (!(subFrame = ((subFrame + 1) % frameLengths.at(frame)))) {
        // Increase the frame number if necessary
        frame = (frame + 1) % frames.size();
    }
}

Sprite::Sprite(const std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Cannot open image file " << path << std::endl;
    }

    Animation* currAnimation_p = nullptr;
    for (std::string line; std::getline(file, line);) {
        std::istringstream tokenStream(line);
        char type;
        tokenStream >> type;

        switch (type) {
            case 'a': {
                    std::string name;
                    tokenStream >> name;

                    if (!currAnimation_p) {
                        // set global current animation to the first
                        currentAnimation = name;
                    }

                    // Creates a new animation
                    // Refers to the old animation if it exists
                    currAnimation_p = &(animations[name]);

                    if (!currAnimation_p) {
                        std::cout << "Could not set currAnimation_p to " << name << std::endl; 
                    }
                    break;
            }
            case 'i': {
                if (!currAnimation_p) {
                    std::cerr << "In line " << line << std::endl;
                    std::cerr << "Image inserted before animation!" << std::endl;
                    break;
                }

                unsigned int length = 1;
                tokenStream >> length;

                std::string path;
                tokenStream >> path;

                // Create image of just length and path
                if (tokenStream.eof()) {
                    currAnimation_p->addFrame(length, path);
                    break;
                }

                // Extracts width/height or x/y
                unsigned int t0 = 1;
                unsigned int t1 = 1;
                tokenStream >> t0;
                tokenStream >> t1;
                if (tokenStream.eof()) {
                    currAnimation_p->addFrame(length, path, t0, t1);
                    break;
                }
                
                // Extract width and height
                unsigned int t2 = 1;
                unsigned int t3 = 1;
                tokenStream >> t2;
                tokenStream >> t3;
                currAnimation_p->addFrame(length, path, t0, t1, t2, t3);
                break;
            }
        }
    }
}

void Sprite::render(const int x, const int y) const {
    if (animations.find(currentAnimation) == animations.end()) {
        std::cerr << "Animation " << currentAnimation << " not found" << std::endl;
        std::cerr << "Animation list: ";
        for (auto pair : animations) {
            std::cout << pair.first << " ";
        }
        std::cout << std::endl;
    } else {
        animations.at(currentAnimation).render(x, y);
    }
}

void Sprite::render(const int x, const int y, const int width, const int height) const {
    if (animations.find(currentAnimation) == animations.end()) {
        std::cerr << "Animation " << currentAnimation << " not found" << std::endl;
        std::cerr << "Animation list: ";
        for (auto pair : animations) {
            std::cout << pair.first << " ";
        }
        std::cout << std::endl;
    } else {
        animations.at(currentAnimation).render(x, y, width, height);
    }
}

void Sprite::tick() {
    if (animations.find(currentAnimation) == animations.end()) {
        std::cerr << "Animation " << currentAnimation << " not found" << std::endl;
        std::cerr << "Animation list: ";
        for (auto pair : animations) {
            std::cout << pair.first << " ";
        }
        std::cout << std::endl;
    } else {
        animations.at(currentAnimation).tick();
    }
}
