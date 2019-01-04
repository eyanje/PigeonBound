#include "ui.hpp"

#include <map>
#include <string>
#include <vector>

#include "sprite.hpp"

FT_Library Text::library;
std::map<std::string, FontFace> Text::faces;

void Text::init() {
    FT_Init_FreeType(&library);
}

Text::Text(const std::string text, const std::string font)
: text(text),
font(font) {
    if (faces.find(font) == faces.end()) {
        faces.emplace(font, FontFace(font));
    }
}

void Text::renderChar(const char c, const int x, const int y) {
    FT_Load_Glyph(faces[font].face, c, FT_LOAD_DEFAULT | FT_LOAD_RENDER);
    FT_Render_Glyph(faces[font].face->glyph, FT_RENDER_MODE_NORMAL);

}

void Text::render(const int x, const int y, const int width) {    
    int xLoc = x;
    int yLoc = y;
    for (char c : text) {
        renderChar(c, xLoc, yLoc);
        xLoc += (faces[font].face->glyph->advance.x >> 6);
        if (xLoc + (faces[font].face->glyph->advance.x >> 6) > x + width && width) {
            yLoc += (faces[font].face->glyph->advance.y >> 6);
            xLoc = x;
        }
    }
}
