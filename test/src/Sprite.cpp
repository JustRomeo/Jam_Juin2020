/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sprite
*/

#include "Exception.hpp"
#include "Sprite.hpp"

arcade::Sprite::Sprite()
{
    _texture = new sf::Texture;
    _load_failed = false;
}

arcade::Sprite::~Sprite()
{
}

void arcade::Sprite::destroyTexture()
{
    delete(_texture);
}

void arcade::Sprite::setTexture(std::string filepath)
{
    if (_texture->loadFromFile(filepath) == false)
        throw (Exception("resources load failed"));
    _sprite.setTexture(*_texture);
}

void arcade::Sprite::setPosition(sf::Vector2f pos)
{
    _sprite.setPosition(pos);
}

bool arcade::Sprite::getLoadFailed() const
{
    return (_load_failed);
}

sf::Sprite arcade::Sprite::getSprite() const
{
    return (_sprite);
}