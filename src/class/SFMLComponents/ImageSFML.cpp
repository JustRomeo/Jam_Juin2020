#include <iostream>
#include "ImageSFML.hpp"

using namespace std;

ImageSFML::ImageSFML(string path)
{
    _width = 0;
    _heigh = 0;
    _pos = sf::Vector2f(0, 0);
    _texture = new sf::Texture;

    if (!_texture->loadFromFile(path))
        cout << "Loading Ressource Failed" << endl;
    _sprite.setTexture(*_texture);
    _width = _sprite.getTexture()->getSize().x;
    _heigh = _sprite.getTexture()->getSize().y;
}

bool ImageSFML::isClicked(sf::Event event) {
    sf::Vector2i mouse(sf::Mouse::getPosition());

    mouse.y -= 65;
    if (event.type == sf::Event::MouseButtonPressed)
        if ((mouse.y > _pos.y && mouse.y < _pos.y + _heigh) && (mouse.x > _pos.x && mouse.x < _pos.x + _width))
            return true;
    return false;
}

void ImageSFML::setTexture(string path)
{
    if (!_texture->loadFromFile(path))
        cout << "Loading Ressource Failed" << endl;
    _sprite.setTexture(*_texture);
}

void ImageSFML::setScale(sf::Vector2f size) {
    _sprite.setScale(size);
}
void ImageSFML::setPosition(sf::Vector2f pos) {
    _pos = pos;
    _sprite.setPosition(pos);
}

sf::Sprite ImageSFML::getSprite(void) const {return (_sprite);}