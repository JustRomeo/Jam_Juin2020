/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** MunPlus
*/

#include "MunPlus.hpp"

MunPlus::MunPlus(int _type, int x, int y) {
    munShape.setSize(sf::Vector2f(30, 60));
    munShape.setOutlineColor(sf::Color::Black);
    switch(_type) {
        case 1: munShape.setFillColor(sf::Color::Yellow); break;
        case 2: munShape.setFillColor(sf::Color::Blue); break;
        case 3: munShape.setFillColor(sf::Color::Magenta); break;
        default: throw Exception("Error: Munition unkown color");
    }
    munShape.setOutlineThickness(2);
    munShape.setPosition(x, y);
    type = _type;
}

MunPlus::~MunPlus() {}

int MunPlus::getType() const {return (type);}
sf::FloatRect MunPlus::getMunShape() {return (munShape.getGlobalBounds());}
void MunPlus::display(std::shared_ptr<sf::RenderWindow> window) {window->draw(munShape);}
