#include <ostream>
#include <iostream>
#include "Block.hpp"
#include "Exception.hpp"

using namespace std;

Block::Block(int X, int Y, size_t size, Block::Type type) {
    _type = type;
    _size = size;
    _texture = std::make_shared<sf::Texture>();
    pos = sf::Vector2f(X, Y);
    try {
        switch(_type) {
            case Block::Type::BLUE:   this->setTexture("resources/Images/brokable_blue.png"); break;
            case Block::Type::PURPLE: this->setTexture("resources/Images/brokable_purple.png"); break;
            case Block::Type::YELLOW: this->setTexture("resources/Images/brokable_yellow.png"); break;
            default:                  this->setTexture("resources/Images/blockCobble.png"); break;
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
    this->_sprite.setPosition(pos);
    this->_sprite.setScale(sf::Vector2f(0.5, 0.5));
}
Block::~Block() 
{
    //delete(_texture);
}

void Block::setTexture(string filepath) {
    if (!_texture->loadFromFile(filepath))
        throw (Exception("Loading Ressource Failed"));
    _sprite.setTexture(*_texture);
}
Block::Type Block::getType() const {return _type;}
size_t Block::getSize(void) const {return _size;}
sf::Vector2f Block::getPosition(void) {return pos;}
//std::shared_ptr<sf::Texture> Block::getTexture(void) {return _texture;}
sf::Sprite Block::getSprite(void) const {return (_sprite);}
void Block::setPosition(sf::Vector2f pos) {_sprite.setPosition(pos);}
