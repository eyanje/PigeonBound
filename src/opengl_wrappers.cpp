#include "opengl_wrappers.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <SDL_opengl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

glw::Buffer::Buffer(const GLenum target)
: target(target) {
    glGenBuffers(1, &id);
    glBindBuffer(target, id);
    glBindBuffer(target, 0);

    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error creating buffer " << error << std::endl;
    }
}

glw::Buffer::Buffer(const glw::Buffer &buffer)
: target(buffer.target),
data(buffer.data) {
    glGenBuffers(1, &id);
    glBindBuffer(target, id);
    glBufferData(target, data.size(), data.data(), GL_STATIC_DRAW);
    glBindBuffer(target, 0);
}

glw::Buffer::Buffer(glw::Buffer &&buffer) 
: target(buffer.target),
id(buffer.id),
data(buffer.data) {
    buffer.id = 0;
}

glw::Buffer::~Buffer() {
    if (glIsBuffer(id)) {
        glDeleteBuffers(1, &id);
        
        GLenum error = glGetError();
        if (error) {
            do {
                std::cerr << "Error deleting buffer " << error << std::endl;
            } while (error = glGetError());
        } else {
            std::cout << "Deleted buffer at " << id << std::endl;
        }
    }
}

void glw::Buffer::bind() const {
    glBindBuffer(target, id);
    
    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error binding buffer " << error << std::endl;
    }
}

GLuint glw::Buffer::getId() const {
    return id;
}

void glw::Buffer::setData(const void *data, const unsigned int size) {
    this->data.resize(size);
    std::memcpy(this->data.data(), data, size);

    glBindBuffer(target, id);
    glBufferData(target, size, data, GL_STATIC_DRAW);
    glBindBuffer(target, 0);

    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error setting data " << error << std::endl;
    }
}

void *glw::Buffer::getData() {
    return data.data();
}

glw::VAO::VAO()
: vbo(GL_ARRAY_BUFFER) {
    glGenVertexArrays(1, &id);

    glBindVertexArray(id);
    vbo.bind();
    glBindVertexArray(0);

    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Erorr creating vao " << error << std::endl;
    }
}

glw::VAO::VAO(const glw::VAO &vao)
: vbo(vao.vbo) {
    glGenVertexArrays(1, &id);
    
    glBindVertexArray(id);
    vbo.bind();
    glBindVertexArray(0);

    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Erorr copying vao " << error << std::endl;
    }
}

glw::VAO::VAO(glw::VAO &&vao)
: id(vao.id),
vbo(std::move(vao.vbo)) {
    vao.id = 0;
    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Erorr moving vao " << error << std::endl;
    }
}

glw::VAO::~VAO() {
    if (glIsVertexArray(id)) {
        glDeleteVertexArrays(1, &id);

        GLenum error = glGetError();
        if (error) {
            do {
                std::cerr << "Error deleting VAO " << error << std::endl;
            } while (error = glGetError());
        } else {
            std::cout << "Deleted VAO at " << id << std::endl;
        }
    }
}

GLuint glw::VAO::getId() const {
    return id;
}

void glw::VAO::setVertexData(const void *data, const unsigned int size) {
    vbo.setData(data, size);
}

void glw::VAO::bind() const {
    glBindVertexArray(id);
    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error binding VAO " << id << " " << error << std::endl;
        if (glIsVertexArray(id)) {
            std::cerr << "VAO is valid" << std::endl;
        } else {
            std::cerr << "VAO is invalid" << std::endl;
        }
    }

    vbo.bind();
}

glw::Texture::Texture(const std::string path) {
    std::cout << "Loading texture at " << path << std::endl;

    glGenTextures(1, &id);

    stbi_uc *imgData = stbi_load(path.c_str(), &width, &height, &bytesPerPixel, 4);
    if (!imgData) {
        std::cerr << "Could not load image " << path << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D,
    0, // level
    GL_RGBA, // internal format
    width, height,
    0, // border
    GL_RGBA, //format
    GL_UNSIGNED_BYTE,
    imgData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(imgData);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error loading texture at " << path << " " << error << std::endl;
    }
}

glw::Texture::~Texture() {

    if (glIsTexture(id)) {
        glDeleteTextures(1, &id);

        GLenum error = glGetError();
        if (error) {
            do {
                std::cerr << "Error deleting texture " << id << std::endl;
            } while (error = glGetError());
        } else {
            std::cout << "Deleted texture at " << id << std::endl;
        }
    }
}

glw::Texture::Texture(const glw::Texture &texture) {

}

glw::Texture::Texture(glw::Texture &&texture)
: id(texture.id) {
    texture.id = 0;
}

GLuint glw::Texture::getId() const {
    return id;
}

int glw::Texture::getWidth() const {
    return width;
}

int glw::Texture::getHeight() const {
    return height;
}

int glw::Texture::getBytesPerPixel() const {
    return bytesPerPixel;
}

void glw::Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);

    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error binding texture " << id << " " << error << std::endl;
    }
}

glw::Shader::Shader(const std::string path, GLenum shaderType)
: id(glCreateShader(shaderType)),
shaderType(shaderType) {
    std::ifstream fileStream(path);
    if (!fileStream.is_open()) {
        std::cerr << "Could not open shader " << path << std::endl;
    }

    std::ostringstream fileSStream;
    fileSStream << fileStream.rdbuf();

    std::string source = fileSStream.str();

    const GLchar *sourceChrArr = source.c_str();
    glShaderSource(id,
    1, // count
    &sourceChrArr,
    nullptr // Length, null if the string is null-terminated
    );

    glCompileShader(id);

    GLint compileStatus;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
    if(!compileStatus)
    {
        GLint maxLength = 0;
    	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> infoLogVector(maxLength);
        glGetShaderInfoLog(id, maxLength, nullptr, &infoLogVector[0]);
        std::string infoLog(infoLogVector.begin(), infoLogVector.end());
        std::cerr << "Error compiling shader at " << path << " " << infoLog << std::endl;

        glDeleteShader(id);
    }

    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error creating shader at " << path << " " << error << std::endl;
    }
}

glw::Shader::~Shader() {
    if (glIsShader(id)) {
        glDeleteShader(id);

        GLenum error = glGetError();
        if (error) {
            do {
                std::cerr << "Error deleting shader " << id << " " << error << std::endl;
            } while (error = glGetError());
        } else {
            std::cout << "Deleted shader " << id << std::endl;
        }
    }
}

GLuint glw::Shader::getId() const {
    return id;
}

bool glw::Shader::operator<(const Shader &shader) const {
    return id < shader.id;
}

glw::Program::Program()
: id(glCreateProgram()) {
    std::cout << "Created empty program " << id << std::endl;
}

glw::Program::Program(std::string vertexShaderPath, std::string fragmentShaderPath)
: id(glCreateProgram()) {
    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error creating program " << id << " " << error << std::endl;
    }

    Shader vertex(vertexShaderPath, GL_VERTEX_SHADER);
    attachShader(vertex);
    Shader fragment(fragmentShaderPath, GL_FRAGMENT_SHADER);
    attachShader(fragment);

    linkProgram();

    error = glGetError();
    if (error) {
        do {
            std::cerr << "Error creating whole program " << id << " " << error << std::endl;
        } while (error = glGetError());
    } else {
        std::cout << "Successfully created program " << id << std::endl;
    }
}

glw::Program::Program(const glw::Program &program)
: id(program.id) {

}

glw::Program::Program(glw::Program &&program)
: id(program.id),
shaders(std::move(program.shaders)) {
    program.id = 0;
}

glw::Program::~Program() {
    for (const Shader  *s : shaders) {
        glDetachShader(id, s->getId());
        
        GLenum error;
        while (error = glGetError()) {
            std::cerr << "Error detaching shader " << s->getId() << " " << error << std::endl;
        }
    }
    shaders.clear();

    glDeleteProgram(id);

    GLenum error = glGetError();
    if (error) {
        do {
            std::cerr << "Error deleting program " << id << " " << error << std::endl;
        } while (error = glGetError());
    } else {
        std::cout << "Deleted program " << id << std::endl;
    }
}

void glw::Program::attachShader(Shader &shader) {
    glAttachShader(id, shader.getId());
    shaders.insert(&shader);

    GLenum error = glGetError();
    if (error) {
        do {
            std::cerr << "Error attaching shader " << shader.getId() << " " << error << std::endl;
        } while (error = glGetError());
    } else {
        std::cout << "Attached shader " << shader.getId() << " to program " << id << std::endl;
    }
}

void glw::Program::linkProgram() {

    glLinkProgram(id);
    
    GLenum error = glGetError();
    if (error) {
        do {
            std::cerr << "Error linking program " << id << " " << error << std::endl;
        } while (error = glGetError());
    } else {
        std::cout << "Linked program " << id << std::endl;
    }

    for (const Shader *s : shaders) {
        glDetachShader(id, s->getId());
        while (error = glGetError()) {
            std::cerr << "Error detaching shader " << s->getId() << " " << error << std::endl;
        }
    }
    shaders.clear();

    while (error = glGetError()) {
        std::cerr << "Error clearing shaders " << error << std::endl;
    }
}

void glw::Program::use() const {
    glUseProgram(id);

    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error using program " << id << " " << error << std::endl;
        if (glIsProgram(id)) {
            std::cerr << "Program is valid" << std::endl;
        } else {
            std::cerr << "Program is invalid" << std::endl;
        }
    }
}

GLuint glw::Program::getUniformLocation(const std::string name) {
    auto cachedLocation = locations.find(name);
    if (cachedLocation == locations.end()) {
        GLint location = glGetUniformLocation(id, name.c_str());
        // Cache the location
        locations[name] = location;
        return location;
    } else {
        return cachedLocation->second;
    }
}

GLuint glw::Program::getUniformLocation(const std::string name) const {
    const auto cachedLocation = locations.find(name);
    if (cachedLocation != locations.cend()) {
        return cachedLocation->second;
    }
    return glGetUniformLocation(id, name.c_str());
}

void glw::Program::uniform1i(const std::string location, const int v0) const {
    GLint currProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
    if (id != currProgram) {
        std::cerr << "In uniform1i " << location << " " << v0 << ":" << std::endl;
        std::cerr << "Current program " << id << " is not bound! Instead " << currProgram << std::endl;
        std::cout << "Binding current program..." << std::endl;
        use();
    }

    glUniform1i(getUniformLocation(location), v0);

    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error uniform1i " << location << " " << v0 << " " << error << std::endl;
    }
}

void glw::Program::uniform2i(const std::string location, const int v0, const int v1) const {
    GLint currProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
    if (id != static_cast<GLuint>(currProgram)) {
        std::cerr << "In uniform2i " << location << " " << v0 << " " << v1 << ":" << std::endl;
        std::cerr << "Current program " << id << " is not bound! Instead " << currProgram << std::endl;
        std::cout << "Binding current program..." << std::endl;
        use();
    }

    glUniform2i(getUniformLocation(location), v0, v1);

    GLenum error;
    while (error = glGetError()) {
        std::cerr << "Error uniform2i " << location << " " << v0 << " " << v1 << " " << error << std::endl;
    }
}
