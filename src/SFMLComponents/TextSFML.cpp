#include <iostream>
#include "TextSFML.hpp"
#include "Exception.hpp"

using namespace std;
TextSfml::TextSfml(std::string value, std::string font, sf::Color color, int x, int y) {
    if (!_font.loadFromFile(font))
        throw Exception("Loading Ressource Failed");
    _TextColor = color;
    _data.setFont(_font);
    _data.setString(value.c_str());
    _data.setFillColor(_TextColor);
    _data.setCharacterSize(20);
    _data.setPosition(sf::Vector2f(x, y));
}
TextSfml::~TextSfml() {}

void TextSfml::setColor(sf::Color color = sf::Color::White) {
    _TextColor = color;
    _data.setFillColor(_TextColor);
}

void TextSfml::update(std::string value, sf::Color color = sf::Color::White) {
    _TextColor = color;
    _data.setString(value.c_str());
    _data.setFillColor(_TextColor);
}

void TextSfml::setPosition(sf::Vector2f pos) {
    _pos = pos;
    _data.setPosition(pos);
}

sf::Text TextSfml::getData(void) const {return _data;}
sf::Font TextSfml::getFont(void) const {return _font;}
sf::Color TextSfml::getColor(void) const {return _TextColor;}
sf::Vector2f TextSfml::getPosition(void) const {return _pos;}
void TextSfml::setSize(size_t size) {_data.setCharacterSize(size);}
size_t TextSfml::getSize(void) const {return _data.getCharacterSize();}
void TextSfml::setString(std::string str = "Error") {_data.setString(str);}
