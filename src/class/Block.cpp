#include <ostream>
#include <iostream>
#include "Block.hpp"
#include "Exception.hpp"

using namespace std;

Block::Block(int X, int Y, size_t size) {
    _size = size;
    _texture = new sf::Texture;
    pos = sf::Vector2f(X, Y);
    try {
        this->setTexture("resources/Images/blockCobble.png");
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
    this->_sprite.setPosition(pos);
    this->_sprite.setScale(sf::Vector2f(0.5, 0.5));
}
Block::~Block() {}

void Block::setTexture(string filepath) {
    if (!_texture->loadFromFile(filepath))
        throw (Exception("Loading Ressource Failed"));
    _sprite.setTexture(*_texture);
}

size_t Block::getSize(void) const {return _size;}
sf::Vector2f Block::getPosition(void) {return pos;}
sf::Texture *Block::getTexture(void) {return _texture;}
sf::Sprite Block::getSprite(void) const {return (_sprite);}
void Block::setPosition(sf::Vector2f pos) {_sprite.setPosition(pos);}