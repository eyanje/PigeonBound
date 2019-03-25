#include "ui.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <initializer_list>
#include <map>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "defines.h"
#include "sprite.hpp"

std::vector<GLfloat> CharBitmap::uvs({ 1, 0, 0, 0, 0, 1, 1, 1 });
std::vector<GLubyte> CharBitmap::elements({ 0, 1, 2, 0, 2, 3 });

CharBitmap::CharBitmap(FT_GlyphSlot &glyph)
: glyph(glyph),
xOffset(std::round(glyph->metrics.horiBearingX / 64.0)),
yOffset(-std::round(glyph->metrics.horiBearingY / 64.0)),
width(std::round(glyph->metrics.width / 64.0)),
height(std::round(glyph->metrics.height / 64.0)),
horiAdvance(std::round(glyph->metrics.horiAdvance / 64.0)),
texture(glyph->bitmap.buffer, width, height, 1),
uvBuffer(GL_ARRAY_BUFFER, 
    uvs.data(),
    sizeof(GLfloat) * uvs.size()
),
elementBuffer(GL_ELEMENT_ARRAY_BUFFER, 
    elements.data(),
    sizeof(GLubyte) * elements.size()
),
program("shaders/basic.vert", "shaders/text.frag") {
    const GLuint verts[] {
        getWidth(), 0,
        0, 0,
        0, getHeight(),
        getWidth(), getHeight()
    };
    vao.setVertexData(verts, sizeof(verts));
}

CharBitmap::CharBitmap(const CharBitmap &charBitmap)
: glyph(charBitmap.glyph),
xOffset(charBitmap.xOffset),
yOffset(charBitmap.yOffset),
width(charBitmap.width),
height(charBitmap.height),
horiAdvance(charBitmap.horiAdvance),
vao(charBitmap.vao),
texture(charBitmap.texture),
uvBuffer(charBitmap.uvBuffer),
elementBuffer(charBitmap.elementBuffer),
program(charBitmap.program)
{

}

CharBitmap::CharBitmap(CharBitmap&& charBitmap) noexcept
: glyph(charBitmap.glyph),
xOffset(charBitmap.xOffset),
yOffset(charBitmap.yOffset),
width(charBitmap.width),
height(charBitmap.height),
horiAdvance(charBitmap.horiAdvance),
vao(std::move(charBitmap.vao)),
texture(std::move(charBitmap.texture)),
uvBuffer(std::move(charBitmap.uvBuffer)),
elementBuffer(std::move(charBitmap.elementBuffer)),
program(std::move(charBitmap.program)) {
    charBitmap.glyph = nullptr;

    charBitmap.xOffset = 0;
    charBitmap.yOffset = 0;
    charBitmap.width = 0;
    charBitmap.height = 0;
    charBitmap.horiAdvance = 0;
}

CharBitmap::~CharBitmap() {
    std::cout << "Deleted CharBitmap" << std::endl;
}

void CharBitmap::render(const int x, const int y) const {
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
    program.uniform2i("subCoords", 0, 0);
    program.uniform2i("subSize", width, height);
    program.uniform2i("objPos",
        x + xOffset,
        y + yOffset);
    program.uniform2i("size", width, height);
    program.uniform4i("textColor", 128, 0, 0, 255);

    while (error = glGetError()) {
        std::cerr << "Error passing all image uniforms " << error << std::endl;
    }

    elementBuffer.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);

    while (error = glGetError()) {
        std::cerr << "Error drawing elements " << error << std::endl;
    }

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

int CharBitmap::getXOffset() const {
    return xOffset;
}

int CharBitmap::getYOffset() const {
    return yOffset;
}

int CharBitmap::getWidth() const {
    return width;
}

int CharBitmap::getHeight() const {
    return height;
}

int CharBitmap::getHoriAdvance() const {
    return horiAdvance;
}

FT_Library FontFace::library;

FontFace::FontFace(const std::string path, const int size)
: size(size) {
    std::cout << "Loading font at " << path << std::endl;

    FT_Error error;

    error = FT_New_Face(library,
    path.c_str(),
    0,
    &face);
    if (error) {
        std::cerr << "Error loading font face at " << path << std::endl;
    }

    error = FT_Set_Char_Size(
    face,
    0, // char_width in 1/64th of points
    size << 6, // char_height in 1/64th of points
    64, 64); // Resolution
    if (error) {
        std::cerr << "Error loading font face at " << path << std::endl;
    }
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (char c = ' '; c < 127; ++c) {
        error = FT_Load_Glyph(face, FT_Get_Char_Index(face, c), FT_LOAD_DEFAULT | FT_LOAD_RENDER);
        if (error) {
            std::cout << "Error loading glyph at " << path << std::endl;
        }
        error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
        if (error) {
            std::cout << "Error rendering glyph at " << path << std::endl;
        }

        const auto glyphWidth = face->glyph->metrics.width;
        const auto glyphHeight = face->glyph->metrics.height;

        if (glyphWidth % 64) {
            std::cerr << "Glyph width is not a whole pixel! Instead " << glyphWidth/64.0 << std::endl;
        }
        if (glyphHeight % 64) {
            std::cerr << "Glyph height is not a whole pixel! Instead " << glyphHeight/64.0 << std::endl;
        }

        bitmaps.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(c), 
            std::forward_as_tuple(face->glyph)
        );
    } // TODO make different shaders for different input values

    std::cout << "Loaded font at " << path << std::endl;

}

FontFace::FontFace(const FontFace &fontFace)
: face(fontFace.face),
bitmaps(fontFace.bitmaps),
size(fontFace.size) {
}

FontFace::FontFace(FontFace &&fontFace)
: face(fontFace.face),
bitmaps(std::move(fontFace.bitmaps)),
size(fontFace.size) {
    fontFace.face = nullptr;
    fontFace.size = 0;
}

void FontFace::init() {
    FT_Init_FreeType(&library);
}

void FontFace::render(const char c, const int x, const int y) const {
    bitmaps.at(c).render(x, y);
}

std::map<std::string, FontFace> Text::faces;

Text::Text(const std::string text, const std::string font)
: text(text),
font(font) {
    if (faces.find(font) == faces.end()) {
        faces.emplace(font, FontFace(font));
    }
}

std::string Text::getText() const {
    return text;
}

void Text::setText(const std::string text) {
    this->text = text;
}

void Text::renderChar(const char c, const int x, const int y) const {
    faces.at(font).render(c, x, y);
}

void Text::render(const int x, const int y, const int width) const {    
    int xLoc = x;
    int yLoc = y - faces.at(font).size;
    //renderChar('a', x, y);
    for (unsigned int i = 0; i < text.size(); ++i) {
        char c = text[i];
        renderChar(c, xLoc, yLoc);
        xLoc += (faces.at(font).bitmaps.at(c).getHoriAdvance());

        // Check to see if the line should break
        if (c == ' ') {
            // Represents the left x value of the char at j
            int nextX = xLoc;
            // Represents the width of the last character
            int nextWidth = (faces.at(font).bitmaps.at(c).getWidth());
            for (unsigned int j = i + 1; j < text.size() && text[j] != ' '; ++j) {
                char futureC = text[j];
                nextX += (faces.at(font).bitmaps.at(futureC).getHoriAdvance());
                nextWidth = faces.at(font).bitmaps.at(futureC).getWidth();
            }
            // If the right side of the next word is off the edge
            if (nextX + nextWidth > x + width) {
                xLoc = x;
                yLoc += faces.at(font).size;
            }
        }
    }
}
