#ifndef __RECTTEXTSFML__
#define __RECTTEXTSFML__

#include <iostream>
#include "TextSFML.hpp"
#include "RectSFML.hpp"

using namespace std;
class TextRectSFML {
    public:
        TextRectSFML(sf::Vector2i pos = sf::Vector2i(50, 50), sf::Vector2i size = sf::Vector2i(50, 200), string str = "", sf::Color Color = sf::Color::Black);
        ~TextRectSFML();

        void update(string str);

        void Rectupdate(sf::Color Color);

        void Textupdate(string font);
        void Textupdate(sf::Color Color);

        void draw(sf::RenderWindow &window);

    private:
        string str;
        TextSfml Text;
        RectSFML Rect;
};

#endif