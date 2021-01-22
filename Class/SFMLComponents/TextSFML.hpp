#ifndef _TEXTSFML_
#define _TEXTSFML_

#include <SFML/Graphics.hpp>

using namespace std;
class TextSfml {
    public:
        TextSfml(string value = "", string font = "", sf::Color color = sf::Color::White, int x = 0, int y = 0);
        ~TextSfml();

        void setSize(size_t size);
        size_t getSize(void) const;
        sf::Text getData(void) const;
        sf::Font getFont(void) const;
        void setColor(sf::Color color);
        sf::Color getColor(void) const;
        void setString(string str);
        void setPosition(sf::Vector2f pos);
        sf::Vector2f getPosition(void) const;
        void update(string value, sf::Color color);

    private:
        sf::Text _data;
        sf::Font _font;
        sf::Vector2f _pos;
        sf::Color _TextColor;
};

#endif