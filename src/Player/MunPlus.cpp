/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** MunPlus
*/

#include "MunPlus.hpp"

MunPlus::MunPlus(int _type, int x, int y)
{
    munShape.setSize(sf::Vector2f(30, 60));
    munShape.setOutlineColor(sf::Color::Black);
    if (_type == 1)
        munShape.setFillColor(sf::Color::Yellow);
    if (_type == 2)
        munShape.setFillColor(sf::Color::Blue);
    if (_type == 3)
        munShape.setFillColor(sf::Color::Magenta);
    munShape.setOutlineThickness(2);
    munShape.setPosition(x, y);
    type = _type;
}

MunPlus::~MunPlus()
{
}

void MunPlus::display(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(munShape);
}

sf::FloatRect MunPlus::getMunShape()
{
    return (munShape.getGlobalBounds());
}