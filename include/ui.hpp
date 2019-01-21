#ifndef UI_HPP
#define UI_HPP

#include <map>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "opengl_wrappers.hpp"
#include "sprite.hpp"

class CharBitmap {
    private:
        static std::vector<GLfloat> uvs;
        static std::vector<GLubyte> elements;

        FT_GlyphSlot &glyph;

        int xOffset;
        int yOffset;
        int width;
        int height;
        
        int horiAdvance;

        glw::VAO vao;

        glw::Texture texture;
        
        glw::Buffer uvBuffer;
        glw::Buffer elementBuffer;
        glw::Program program;

    public:
        CharBitmap(FT_GlyphSlot &glyph);
        CharBitmap(const CharBitmap &charBitmap);
        CharBitmap(CharBitmap &&charBitmap) noexcept;
        ~CharBitmap();

        int getXOffset() const;
        int getYOffset() const;
        int getWidth() const;
        int getHeight() const;
        int getHoriAdvance() const;

        void render(const int x, const int y) const;
};

struct FontFace {
    static FT_Library library;
    FT_Face face;
    std::map<char, CharBitmap> bitmaps;
    int size;

    FontFace(const std::string path, const int size = 16);
    FontFace(const FontFace &fontFace);
    FontFace(FontFace &&fontFace);
    
    static void init();

    void render(const char c, const int x, const int y) const;
};

class Text {
    private:
        static std::map<std::string, FontFace> faces;
        std::string text;
        std::string font;
        void renderChar(const char c, const int x, const int y) const;
    public:
        Text(const std::string text, const std::string font = "default.ttf");
        std::string getText() const;
        void setText(const std::string text);
        void render(const int x, const int y, int width) const;
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