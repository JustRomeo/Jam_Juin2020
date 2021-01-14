#include "InputControler.hpp"

InputControler::InputControler() {
    _remote = false;
    remote = make_shared<ManetteSFML>();
    _remote = remote->isConnected();
}
InputControler::~InputControler() {}

bool InputControler::isJumping(void) const {
    if (_remote && remote->getButtonsClicked() == ManetteSFML::Button::Croix)
        return true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return true;
    return false;
}

bool InputControler::isShooting(void) const {
    if (_remote && remote->getButtonsClicked() == ManetteSFML::Button::Carre)
        return true;
    return false;
}

bool InputControler::isSwitching(void) const {
    if (_remote && remote->getButtonsClicked() == ManetteSFML::Button::Triangle)
        return true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        return true;
    return false;
}

bool InputControler::isSprinting(void) const {
    if (_remote && remote->getButtonsClicked() == ManetteSFML::Button::Rond)
        return true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        return true;
    return false;
}

bool InputControler::isLeft(void) const {
    if (_remote && remote->getJoysDirection() == ManetteSFML::Gauche)
        return true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return true;
    return false;
}

bool InputControler::isRight(void) const {
    if (_remote && remote->getJoysDirection() == ManetteSFML::Droite)
        return true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return true;
    return false;
}
