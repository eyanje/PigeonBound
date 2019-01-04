#ifndef UI_HPP
#define UI_HPP

#include <map>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "sprite.hpp"

struct FontFace {
    FT_Face face;
    std::map<char, Image> images;

    FontFace(std::string path) {
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
};

class Text {
    private:
        static FT_Library library;
        static std::map<std::string, FontFace> faces;
        std::string text;
        std::string font;
        void renderChar(const char c, const int x, const int y);
    public:
        Text(const std::string text, const std::string font = "default.ttf");
        static void init();
        void render(const int x, const int y, int width);
};

class TextBox {
    private:
        std::vector<Text> lines;
        Sprite background;
        int width, height;

        int selection;
    public:
        TextBox(std::vector<std::string> text);
        void render(const int x, const int y);
};

#endif