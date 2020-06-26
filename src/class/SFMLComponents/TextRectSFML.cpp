#include <iostream>
#include "TextRectSFML.hpp"

using namespace std;
TextRectSFML::TextRectSFML(sf::Vector2i pos, sf::Vector2i size, string mastring, sf::Color Color) {
    sf::Color TextColor = sf::Color::Black;

    this->str = mastring;
    if (Color == sf::Color::Black)
        TextColor = sf::Color::White;
    Rect = RectSFML(pos.x, pos.y, size.x, size.y, Color);
    Text = TextSfml(this->str, "InterfaceCPP/ressources/TextFont/2MASS.otf", TextColor, pos.x, pos.y);
}

TextRectSFML::~TextRectSFML() {}

void TextRectSFML::draw(sf::RenderWindow &window) {
    TextSfml BG(this->str, "InterfaceCPP/ressources/TextFont/2MASS.otf", sf::Color::Black, Rect._pos.x + 10, Rect._pos.y + 5);

    window.draw(this->Rect._shape);
    window.draw(BG._data);
}

void TextRectSFML::update(string mastring) {this->str = mastring;}
void TextRectSFML::Textupdate(string font) {this->Text._font.loadFromFile(font);}
void TextRectSFML::Rectupdate(sf::Color Color) {this->Rect._Color = Color;}
void TextRectSFML::Textupdate(sf::Color Color) {this->Text.setColor(Color);}