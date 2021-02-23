/*
** EPITECH PROJECT, 2020
** Soundwaves
** File description:
** Input Controler
*/

#include "InputControler.hpp"

InputControler::InputControler() {
    _remote = false;
    remote = make_shared<ManetteSFML>();

    KeyJump = ' ';
    KeySprint = 'r';
    KeySwitching = 'f';
    KeyTree = 'y';

    _remote = remote->isConnected();
}
InputControler::~InputControler() {}

bool InputControler::isJumping(sf::Event event) const {
    if (_remote && remote->getButtonsClicked() == ManetteSFML::Button::Croix)
        return true;
    if (event.key.code == KeyJump || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return true;
    return false;
}

bool InputControler::isShooting(sf::Event event) const {
    if (_remote && remote->getButtonsClicked() == ManetteSFML::Button::Carre)
        return true;
    return false;
}

bool InputControler::isSwitching(sf::Event event) const {
    if (_remote && remote->getButtonsClicked() == ManetteSFML::Button::Triangle)
        return true;
    if (event.key.code == KeySwitching)
        return true;
    return false;
}

bool InputControler::isSprinting(sf::Event event) const {
    if (_remote && remote->getButtonsClicked() == ManetteSFML::Button::Rond)
        return true;
    if (event.key.code == KeySprint)
        return true;
    return false;
}

bool InputControler::isLeft(sf::Event event) const {
    if (_remote && remote->getJoysDirection() == ManetteSFML::Gauche)
        return true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return true;
    return false;
}

bool InputControler::isRight(sf::Event event) const {
    if (_remote && remote->getJoysDirection() == ManetteSFML::Droite)
        return true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return true;
    return false;
}

bool InputControler::isTreeMenu(sf::Event event) const {
    if (_remote && remote->getButtonsClicked() == ManetteSFML::Button::Rond)
        return true;
    if (event.key.code == KeyTree)
        return true;
    return false;
}

void InputControler::setJumpKey(int key) {KeyJump = key;}
int InputControler::getJumpKey(void) const {return KeyJump;}
void InputControler::setTreeKey(int key) {KeyTree = key;}
int InputControler::getTreeKey(void) const {return KeyTree;}
void InputControler::setSprintKey(int key) {KeySprint = key;}
void InputControler::setSwitchKey(int key) {KeySwitching = key;}
int InputControler::getSprintKey(void) const {return KeySprint;}
int InputControler::getSwitchKey(void) const {return KeySwitching;}
