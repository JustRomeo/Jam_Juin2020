#include "TextSFML.hpp"
#include <iostream>

using namespace std;
TextSfml::TextSfml(std::string value, std::string font, sf::Color color, int x, int y) {
    sf::Vector2f pos;

    pos.x = x;
    pos.y = y;
    _font.loadFromFile(font);

    _TextColor = color;
    _data.setFont(_font);
    _data.setCharacterSize(20);
    _data.setString(value.c_str());
    _data.setFillColor(_TextColor);
    _data.setPosition(pos);
}

TextSfml::~TextSfml() {}

void TextSfml::setString(std::string str = "Error") {_data.setString(str);}

void TextSfml::setColor(sf::Color color = sf::Color::White) {
    _TextColor = color;
    _data.setFillColor(_TextColor);
}

void TextSfml::update(std::string value, sf::Color color = sf::Color::White) {
    _TextColor = color;
    _data.setString(value.c_str());
    _data.setFillColor(_TextColor);
}