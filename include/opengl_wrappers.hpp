#ifndef OPENGL_WRAPPERS_HPP
#define OPENGL_WRAPPERS_HPP

#include <map>
#include <set>
#include <vector>

#include <GL/glew.h>

namespace glw {

class Buffer {
    private:
        GLuint id;
        GLenum target;
        // C++ void*
        std::vector<char> data;
    public:
        Buffer(const GLenum target);
        void bind() const;
        GLuint getId() const;
        void *getData();
        void setData(void *data, unsigned int size);
};

class VAO {
    private:
        GLuint id;
        Buffer vbo;
    public:
        VAO();
        ~VAO();
        GLuint getId() const;
        void setVertexData(const void *data, const unsigned int size);
        void bind() const;
};

class Texture {
    private:
        GLuint id;
        unsigned int width;
        unsigned int height;
        unsigned int bytesPerPixel;
    public:
        Texture(const std::string path);
        ~Texture();
        GLuint getId() const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;
        unsigned int getBytesPerPixel() const;
        void bind() const;
};

class Shader {
    private:
        GLuint id;
    public:
        Shader(const std::string path);
        ~Shader();
        GLuint getId() const;
};

class Program {
    private:
        GLuint id;
        std::set<Shader> shaders;
        std::map<std::string, GLint> locations;
    public:
        Program();
        Program(std::string vertexShaderPath, std::string fragmentShaderPath);
        Program::~Program();
        void attachShader(const Shader &shader);
        void linkProgram();
        void use();

        GLuint getUniformLocation(std::string name);
        void uniform1i(std::string location, int v0);
        void uniform2i(std::string location, int v0, int v1);
};

}

#endif