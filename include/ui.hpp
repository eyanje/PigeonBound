#ifndef UI_HPP
#define UI_HPP

#include <map>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "sprite.hpp"

struct FontFace {
    static FT_Library library;
    FT_Face face;
    std::map<char, Image> images;

    FontFace(std::string path);
    
    static void init();
};

class Text {
    private:
        static std::map<std::string, FontFace> faces;
        std::string text;
        std::string font;
        void renderChar(const char c, const int x, const int y);
    public:
        Text(const std::string text, const std::string font = "default.ttf");
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