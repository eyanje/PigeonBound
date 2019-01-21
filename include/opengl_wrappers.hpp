#ifndef OPENGL_WRAPPERS_HPP
#define OPENGL_WRAPPERS_HPP

#include <map>
#include <set>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>

namespace glw {

class Buffer {
    private:
        GLuint id;
        GLenum target;
        // C++ void*
        std::vector<unsigned char> data;
    public:
        Buffer(const GLenum target);
        Buffer(const GLenum target, const void *data, const unsigned int size);
        Buffer(const Buffer &buffer);
        Buffer(Buffer &&buffer) noexcept;
        ~Buffer();
        void bind() const;
        GLuint getId() const;
        void *getData();
        void setData(const void *data, const unsigned int size);
};

class VAO {
    private:
        GLuint id;
        Buffer vbo;
    public:
        VAO();
        VAO(const VAO &vao);
        VAO(VAO &&vao) noexcept;
        ~VAO();
        GLuint getId() const;
        void setVertexData(const void *data, const unsigned int size);
        void bind() const;
};

class Texture {
    private:
        GLuint id;
        int width;
        int height;
        int bytesPerPixel;
    public:
        Texture(const std::string path);
        Texture(const void *data, int width, int height, int bytesPerPixel);
        Texture(const Texture &texture);
        Texture(Texture &&texture) noexcept;
        ~Texture();
        GLuint getId() const;

        int getWidth() const;
        int getHeight() const;
        int getBytesPerPixel() const;
        void bind() const;
};

class Shader {
    private:
        GLuint id;
        const std::string path;
        const GLenum shaderType;
    public:
        Shader(const std::string path, GLenum shaderType);
        Shader(const Shader &shader);
        Shader(Shader &&shader) noexcept;
        ~Shader();
        GLuint getId() const;

        bool operator<(const Shader &shader) const;
};

class Program {
    private:
        GLuint id;
        std::set<Shader *> shaders;
        std::map<std::string, GLint> locations;
    public:
        Program();
        Program(std::string vertexShaderPath, std::string fragmentShaderPath);
        Program(const Program &program);
        Program(Program &&program) noexcept;
        ~Program();
        void attachShader(Shader &shader);
        void linkProgram();
        void use() const;

        GLuint getUniformLocation(const std::string name) noexcept;
        GLuint getUniformLocation(const std::string name) const;
        void uniform1i(const std::string location, const int v0) const;
        void uniform2i(const std::string location, const int v0, const int v1) const;
        void uniform3i(const std::string location, const int v0, const int v1, const int v2) const;
        void uniform4i(const std::string location, const int v0, const int v1, const int v2, const int v3) const;
};

}

#endif