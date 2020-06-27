/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sprite
*/

#include "Exception.hpp"
#include "Sprite.hpp"

Sprite::Sprite(char const *path)
{
    texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile(path) == false)
        throw (Exception("resources load failed"));
    sprite.setTexture(*texture);
    load_failed = false;
}

Sprite::~Sprite()
{
}

void Sprite::destroyTexture()
{
}

void Sprite::setTexture(std::string filepath)
{
    if (texture->loadFromFile(filepath) == false)
        throw (Exception("resources load failed"));
    sprite.setTexture(*texture);
}

void Sprite::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

bool Sprite::getLoadFailed() const
{
    return (load_failed);
}

sf::Sprite Sprite::getSprite() const
{
    return (sprite);
}