#include "opengl_wrappers.hpp"

#include <sstream>

#include <stb_image.h>

glw::Buffer::Buffer(const GLenum target)
: target(target) {
    glGenBuffers(1, &id);
    glBindBuffer(target, id);
    glBindBuffer(target, 0);
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
    std::memcpy(this->data.data, data, size);

    glBindBuffer(target, id);
    glBufferData(target, size, data, GL_STATIC_DRAW);
    glBindBuffer(target, 0);
}

void *glw::Buffer::getData() {
    return data.data();
}

glw::VAO::VAO()
: vbo(GL_ARRAY_BUFFER) {
    glGenVertexArrays(id);
}

glw::VAO::~VAO() {
    glDeleteVertexArrays(id);
}

GLuint glw::VAO::getId() const {
    return id;
}

void glw::VAO::setVertexData(const void *data, const unsigned int size) {
    vbo.setData(data, size);
}

void glw::VAO::bind() const {
    glBindVertexArrays(id);
    vbo.bind();
}

glw::Texture::Texture(const std::string path) {
    glGenTextures(1, &id);

    const void* imgData = stbi_load(path, &width, &height, bytesPerPixel, 4);
    if (!imgData) {
        std::cerr << "Could not load image " << path << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, id);

    glTextureData(GL_TEXTURE_2D,
    0, // level
    GL_RGBA, // internal format
    width, height,
    0, // border
    GL_RGBA, //format
    GL_UNSIGNED_BYTE,
    data);

    stb_image_free(img_data);
}

glw::Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

GLuint glw::Texture::getId() const {
    return id;
}

unsigned int glw::Texture::getWidth() const {
    return width;
}

unsigned int glw::Texture::getHeight() const {
    return height;
}

unsigned int glw::Texture::getBytesPerPixel() const {
    return bytesPerPixel;
}

void glw::Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}

glw::Shader::Shader(const std::string path, GLenum shaderType)
: id(glCreateShader(shaderType)) {
    std::ifstream fileStream(path);
    if (!fileStream.is_open()) {
        std::cerr << "Could not open shader " << path << std::endl;
    }

    std::istringstream fileSStream;
    fileSStream << fileStream.rdbuf();

    std::string source = fileSStream.str();

    GLchar *sourceChrArr = source.c_str();
    glShaderSource(id,
    1, // count
    &sourceChrArr,
    nullptr // Length, null if the string is null-terminated
    );

    glCompileShader(id);

    GLenum compileStatus;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
    if(!compileStatus)
    {
        GLint maxLength = 0;
    	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> infoLogVector;
        glGetShaderInfoLog(vertex, maxLength, NULL, &infoLogVector[0]);
        std::string infoLog(infoLogVector.begin(), infoLogVector.end());
        std::cout << "Error compiling shader at " << path << " " << infoLog << std::endl;

        glDeleteShader(id);
    }
}

glw::Shader::~Shader() {
    glDeleteShader(shader);
}

GLuint glw::Shader::getId() const {
    return id;
}

glw::Program::Program()
: id(glCreateProgram()) {
}

glw::Program::Program(std::string vertexShaderPath, std::string fragmentShaderPath)
: id(glCreateProgram()) {
    attachShader(vertexShaderPath);
    attachShader(fragmentShaderPath);
}

glw::Program::~Program() {
    for (const Shader& s : shaders) {
        glDetachShader(id, s.getId());
    }
    shaders.clear();

    glDeleteProgram(program);
}

void glw::Program::attachShader(const Shader &shader) {
    glAttachShader(program.getId());
    shaders.insert(shader);
}

void glw::Program::linkProgram() const {
    glLinkProgram(id);
    
    for (const Shader& s : shaders) {
        glDetachShader(id, s.getId());
    }
    shaders.clear();
}

void glw::Program::use() {
    glUseProgram(id);
}

GLuint glw::Program::getUniformLocation(std::string name) {
    auto cachedLocation = locations.find(name);
    if (cachedLocation == locations.end()) {
        GLint location = glGetUniformLocation(id, name);
        locations[name] = location;
        return location;
    } else {
        return *cachedLocation;
    }
}

void glw::Program::uniform1i(std::string location, int v0) {
    GLuint currProgram = 0;
    glGetIntegeri_v(GL_CURRENT_PROGRAM, &currProgram);
    if (id == currProgram) {
        std::cerr << "In uniform1i " << location << " " << v0 << ":" << std::endl;
        std::cerr << "Current program is not bound!" << std::endl;
        std::cout << "Binding current program..." << std::endl;
        use();
    }

    glUniform1i(getUniformLocation(location), v0);
}

void glw::Program::uniform2i(std::string location, int v0, int v1) {
    GLuint currProgram = 0;
    glGetIntegeri_v(GL_CURRENT_PROGRAM, &currProgram);
    if (id == currProgram) {
        std::cerr << "In uniform1i " << location << " " << v0 << " " << v1 << ":" << std::endl;
        std::cerr << "Current program is not bound!" << std::endl;
        std::cout << "Binding current program..." << std::endl;
        use();
    }

    glUniform1i(getUniformLocation(location), v0, v1);
}
