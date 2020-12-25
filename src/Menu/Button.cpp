/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Button
*/

#include "Button.hpp"

Button::Button(sf::Vector2f _pos, sf::Vector2f _size): pos(_pos), size(_size) {
    button.setPosition(_pos);
    button.setSize(_size);
}
Button::~Button() {}

void Button::setText(string fontPath, string _text, int _size, const sf::Color textColor) {
    sf::Vector2f textPos;

    if (!font.loadFromFile(fontPath))
        throw Exception("can't load button text font \n");
    text.setFont(font);
    text.setString(_text);
    text.setCharacterSize(_size);
    textPos.x = (pos.x + (button.getSize().x / 2)) - ((_text.length() / 4) * _size);
    textPos.y = pos.y + 5;
    text.setPosition(textPos);
    text.setFillColor(textColor);
}

void Button::setColor(sf::Color buttonColor, sf::Color boundColor, float boundSize) {
    button.setFillColor(buttonColor);
    button.setOutlineThickness(boundSize);
    button.setOutlineColor(boundColor);
}

void Button::drawButton(shared_ptr<sf::RenderWindow> window) {
    sf::Vector2i cursorPos = sf::Mouse::getPosition();

    cursorPos.y -= 50;
    if (button.getGlobalBounds().contains(sf::Vector2f(cursorPos))) {
        button.setOutlineColor(sf::Color::White);
        button.setFillColor(sf::Color::Black);
        text.setFillColor(sf::Color::White);
    } else {
        button.setOutlineColor(sf::Color::Black);
        button.setFillColor(sf::Color::White);
        text.setFillColor(sf::Color::Black);
    }
    window->draw(button);
    window->draw(text);
}

int Button::isClicked(sf::Event event) {
    sf::Vector2i cursorPos = sf::Mouse::getPosition();

    cursorPos.y -= 50;
    if (event.type == sf::Event::MouseButtonPressed)
        if (button.getGlobalBounds().contains(sf::Vector2f(cursorPos)))
            return true;
    return false;
}
