/*
** EPITECH PROJECT, 2020
** SFML
** File description:
** Manette SFML Cpp
*/

#include "ManetteSFML.hpp"

ManetteSFML::ManetteSFML() {
    _sensybility = 80;
    _isCo = _joys.isConnected(0);
}
ManetteSFML::~ManetteSFML() {}

bool ManetteSFML::isConnected(void) {
    if (!_isCo)
        howManyConnected();
    return _isCo;
}

size_t ManetteSFML::howManyConnected(void) {
    size_t i = 0;

    for (size_t i = 0; _joys.isConnected(i); i ++);
    _isCo = (i > 0 ? true : false);
    return i;
}

bool ManetteSFML::isClicked(ManetteSFML::Button button) {
    if (_joys.isButtonPressed(0, 0) && button == Croix)
        return true;
    else if (_joys.isButtonPressed(0, 1) && button == Rond)
        return true;
    else if (_joys.isButtonPressed(0, 2) && button == Carre)
        return true;
    else if (_joys.isButtonPressed(0, 3) && button == Triangle)
        return true;
    return false;
}

ManetteSFML::Button ManetteSFML::getButtonsClicked(void) {
    if (_joys.isButtonPressed(0, 0))
        return Croix;
    else if (_joys.isButtonPressed(0, 1))
        return Rond;
    else if (_joys.isButtonPressed(0, 2))
        return Carre;
    else if (_joys.isButtonPressed(0, 3))
        return Triangle;
    return Nada;
}

ManetteSFML::Direction ManetteSFML::getJoysDirection(void) {
    sf::Vector2f Axis = getAxis();

    if (Axis.x > _sensybility && Axis.y > _sensybility)
        return DroiteBas;
    else if (Axis.x > _sensybility && Axis.y < (int)(-1 * _sensybility))
        return DroiteHaut;
    else if (Axis.x < (int)(-1 * _sensybility) > _sensybility && Axis.y > _sensybility)
        return GaucheBas;
    else if (Axis.x < (int)(-1 * _sensybility) > _sensybility && Axis.y < (int)(-1 * _sensybility))
        return GaucheHaut;
    else if (Axis.x > _sensybility)
        return Droite;
    else if (Axis.x < (int)(-1 * _sensybility))
        return Gauche;
    else if (Axis.y > _sensybility)
        return Bas;
    else if (Axis.y < (int)(-1 * _sensybility))
        return Haut;
    return Nothing;
}

size_t ManetteSFML::getSensibility(void) const {return _sensybility;}
void ManetteSFML::setSensibility(size_t sensy) {_sensybility = sensy;}
sf::Vector2f ManetteSFML::getAxis(void) {return (sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y)));}
