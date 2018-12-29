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
    std::cout << "Creating buffer" << std::endl;
    std::cout << (void *)glGenBuffers << std::endl;
    glGenBuffers(1, &id);
    glBindBuffer(target, id);
    glBindBuffer(target, 0);
    std::cout << "Created buffer" << std::endl;
}

glw::Buffer::~Buffer() {
    glDeleteBuffers(1, &id);
}

void glw::Buffer::bind() const {
    glBindBuffer(target, id);
}

GLuint glw::Buffer::getId() const {
    return id;
}

void glw::Buffer::setData(const void *data, const unsigned int size) {
    std::cout << "Begin" << std::endl;
    this->data.resize(size);
    std::memcpy(this->data.data(), data, size);

    glBindBuffer(target, id);
    glBufferData(target, size, data, GL_STATIC_DRAW);
    glBindBuffer(target, 0);
    std::cout << "End setData" << std::endl;
}

void *glw::Buffer::getData() {
    return data.data();
}

glw::VAO::VAO()
: vbo(GL_ARRAY_BUFFER) {
    glGenVertexArrays(1, &id);
}

glw::VAO::~VAO() {
    glDeleteVertexArrays(1, &id);
}

GLuint glw::VAO::getId() const {
    return id;
}

void glw::VAO::setVertexData(const void *data, const unsigned int size) {
    vbo.setData(data, size);
}

void glw::VAO::bind() const {
    glBindVertexArray(id);
    vbo.bind();
}

glw::Texture::Texture(const std::string path) {
    std::cout << "Loading texture at " << path << std::endl;

    glGenTextures(1, &id);

    void* imgData = stbi_load(path.c_str(), &width, &height, &bytesPerPixel, 4);
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

    stbi_image_free(imgData);

    std::cout << "Loaded texture" << std::endl;
}

glw::Texture::~Texture() {
    glDeleteTextures(1, &id);
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
}

glw::Shader::Shader(const std::string path, GLenum shaderType)
: id(glCreateShader(shaderType)) {
    std::cout << "Creating shader at " << path << std::endl;

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
        std::cout << "Error compiling shader at " << path << " " << infoLog << std::endl;

        glDeleteShader(id);
    }

    std::cout << "Created shader" << std::endl;
}

glw::Shader::~Shader() {
    glDeleteShader(id);
}

GLuint glw::Shader::getId() const {
    return id;
}

bool glw::Shader::operator<(const Shader &shader) const {
    return id < shader.id;
}

glw::Program::Program()
: id(glCreateProgram()) {
    std::cout << "Created empty program" << std::endl;
}

glw::Program::Program(std::string vertexShaderPath, std::string fragmentShaderPath)
: id(glCreateProgram()) {
    std::cout << "Creating program" << std::endl;

    use();

    attachShader(vertexShaderPath, GL_VERTEX_SHADER);
    attachShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    linkProgram();

    std::cout << "Finished creating program" << std::endl;
}

glw::Program::~Program() {
    for (const Shader& s : shaders) {
        glDetachShader(id, s.getId());
    }
    shaders.clear();

    glDeleteProgram(id);
}

void glw::Program::attachShader(const Shader &shader) {
    glAttachShader(id, shader.getId());
    shaders.insert(shader);
}

void glw::Program::attachShader(const std::string path, const GLenum shaderType) {
    attachShader(Shader(path, shaderType));
}

void glw::Program::linkProgram() {
    glLinkProgram(id);
    
    for (const Shader& s : shaders) {
        glDetachShader(id, s.getId());
    }
    shaders.clear();
}

void glw::Program::use() const {
    glUseProgram(id);
}

GLuint glw::Program::getUniformLocation(const std::string name) {
    auto cachedLocation = locations.find(name);
    if (cachedLocation == locations.end()) {
        GLint location = glGetUniformLocation(id, name.c_str());
        // Cache the location
        locations[name] = location;
        return location;
    } else {
        return (*cachedLocation).second;
    }
}

GLuint glw::Program::getUniformLocation(const std::string name) const {
    return glGetUniformLocation(id, name.c_str());
}

void glw::Program::uniform1i(const std::string location, const int v0) const {
    GLint currProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
    if (id == currProgram) {
        std::cerr << "In uniform1i " << location << " " << v0 << ":" << std::endl;
        std::cerr << "Current program is not bound!" << std::endl;
        std::cout << "Binding current program..." << std::endl;
        use();
    }

    glUniform1i(getUniformLocation(location), v0);
}

void glw::Program::uniform2i(const std::string location, const int v0, const int v1) const {
    GLint currProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
    if (id == currProgram) {
        std::cerr << "In uniform1i " << location << " " << v0 << " " << v1 << ":" << std::endl;
        std::cerr << "Current program is not bound!" << std::endl;
        std::cout << "Binding current program..." << std::endl;
        use();
    }

    glUniform2i(getUniformLocation(location), v0, v1);
}
