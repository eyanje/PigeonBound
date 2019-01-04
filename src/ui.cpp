#include "ui.hpp"

#include <map>
#include <string>
#include <vector>

#include "sprite.hpp"

FT_Library FontFace::library;

FontFace::FontFace(std::string path)  {
    FT_New_Face(library,
    path.c_str(),
    0,
    &face);

    FT_Set_Char_Size(
    face,
    0, // char_width in 1/64th of points
    16*64,   // char_height in 1/64th of points
    300, 300); // Resolution
}

void FontFace::init() {
    FT_Init_FreeType(&library);
}

std::map<std::string, FontFace> Text::faces;

Text::Text(const std::string text, const std::string font)
: text(text),
font(font) {
    if (faces.find(font) == faces.end()) {
        faces.emplace(font, FontFace(font));
    }
}

void Text::renderChar(const char c, const int x, const int y) {
    FT_Load_Glyph(faces.at(font).face, c, FT_LOAD_DEFAULT | FT_LOAD_RENDER);
    FT_Render_Glyph(faces.at(font).face->glyph, FT_RENDER_MODE_NORMAL);

}

void Text::render(const int x, const int y, const int width) {    
    int xLoc = x;
    int yLoc = y;
    for (char c : text) {
        renderChar(c, xLoc, yLoc);
        xLoc += (faces.at(font).face->glyph->advance.x >> 6);
        if (xLoc + (faces.at(font).face->glyph->advance.x >> 6) > x + width && width) {
            yLoc += (faces.at(font).face->glyph->advance.y >> 6);
            xLoc = x;
        }
    }
}
