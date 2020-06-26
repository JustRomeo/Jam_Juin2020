/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "memory"

class Sprite
{
public:
    Sprite(char const *path);
    ~Sprite();
    void destroyTexture();
    void setTexture(std::string filepath);
    void setPosition(sf::Vector2f pos);
    bool getLoadFailed() const;
    sf::Sprite getSprite() const;

protected:
private:
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    bool load_failed;
};

#endif /* !SPRITE_HPP_ */
