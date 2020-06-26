#include <ostream>
#include <iostream>
#include "Block.hpp"

using namespace std;

Block::Block(int X, int Y, int heigh, int width) {
    pos = sf::Vector2f(X, Y);
    size = sf::Vector2f(heigh, width);
}
Block::~Block() {}

void Block::setTexture(string filepath) {
    if (!_texture->loadFromFile(filepath))
        cout << "Loading Ressource Failed" << endl;
    _sprite.setTexture(*_texture);
}

sf::Vector2f Block::getPosition(void) {return pos;}
sf::Texture *Block::getTexture(void) {return _texture;}
sf::Sprite Block::getSprite(void) const {return (_sprite);}
void Block::setPosition(sf::Vector2f pos) {_sprite.setPosition(pos);}
