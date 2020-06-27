#include "Ennemis.hpp"

Ennemi::Ennemi(int X, int Y) {
    moving = false;
    move_clock.restart();
    _pos = sf::Vector2f(X, Y);
    _texture = new sf::Texture;
    try {
        this->setTexture("resources/Images/robot.jpg");
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
    this->_sprite.setPosition(_pos);
    this->_sprite.setScale(sf::Vector2f(1, 1));
    _size = this->getSize();
}
Ennemi::~Ennemi() {}

void Ennemi::setTexture(string filepath) {
    if (!_texture->loadFromFile(filepath))
        throw (Exception("Loading Ressource Failed"));
    _sprite.setTexture(*_texture);
}

sf::Texture *_texture;
sf::Vector2f Ennemi::getPosition(void) {return _pos;}
sf::Vector2f Ennemi::getSize(void) const {return _size;}
sf::Texture *Ennemi::getTexture(void) {return _texture;}
sf::Sprite Ennemi::getSprite(void) const {return (_sprite);}
