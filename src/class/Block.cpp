#include <ostream>
#include <iostream>
#include "Block.hpp"

using namespace std;

Block::Block() {}
Block::~Block() {}

void Block::setTexture(string path) {
    if (!_texture->loadFromFile(path))
        cout << "Loading Ressource Failed" << endl;
    _sprite.setTexture(*_texture);
}

sf::Vector2f Block::getPosition(void) {return pos;}
sf::Texture *Block::getTexture(void) {return _texture;}
sf::Sprite Block::getSprite() const {return (_sprite);}
void Block::setPosition(sf::Vector2f pos) {_sprite.setPosition(pos);}