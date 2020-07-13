/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** OrangeProjectile
*/

#include "OrangeProjectile.hpp"

OrangeProjectile::OrangeProjectile(int _orient, sf::Vector2f pos, int desCap): Projectile(desCap)
{
    texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile("./resources/Images/sonor_shockwaves.png") == false)
        throw(Exception("resources load failed"));
    type = IProjectile::YELLOW;
    // move_clock.restart();
    // anim_clock.restart();
    posRect = 0;
    orient = _orient;
    sprite.setTexture(*texture);

    shootRect.push_back(sf::IntRect(166, 212, 42, 42));
    shootRect.push_back(sf::IntRect(960, 212, 22, 42));
    shootTime.push_back(0.4);
    shootTime.push_back(0.5);
    shootMove.push_back(sf::Vector2f(0.f, 0.f));
    if (orient > 0) {
        pos.x += 40;
        pos.y += 7;
        sprite.setScale(sf::Vector2f(1.5, 1.5));
        shootMove.push_back(sf::Vector2f(30.f, 0.f));
    }
    else {
        pos.x -= 40;
        pos.y += 7;
        sprite.setScale(sf::Vector2f(-1.5, 1.5));
        shootMove.push_back(sf::Vector2f(-30.f, 0.f));
    }
    sprite.setTextureRect(shootRect[posRect]);
    sprite.setPosition(pos);
}

OrangeProjectile::~OrangeProjectile()
{
}

void OrangeProjectile::animation()
{
    sf::Vector2f pos = sprite.getPosition();

    if (getTimeAnim(shootTime[posRect]) == 1) {
        if (posRect < shootRect.size() - 1) {
            posRect++;
            sprite.setTextureRect(shootRect[posRect]);
        }
    }
}

void OrangeProjectile::movement()
{
    if (getTimeMov(0.05) == 1)
        sprite.move(shootMove[posRect]);
}

void OrangeProjectile::display(std::shared_ptr<sf::RenderWindow> window)
{
    animation();
    movement();
    window->draw(sprite);
}

int OrangeProjectile::checkDestruction(std::shared_ptr<Block> block)
{
    sf::FloatRect bullet = sprite.getGlobalBounds();
    sf::FloatRect g = block->getSprite().getGlobalBounds();

    if (bullet.intersects(g) == true) {
        if (block->getType() == Block::Type::YELLOW) {
            destructionCapacity--;
            return (1);
        }
        return (0);
    }
    return (-1);
}

int OrangeProjectile::checkKill(std::shared_ptr<Ennemi> ennemi)
{
    sf::FloatRect bullet = sprite.getGlobalBounds();
    sf::FloatRect g = ennemi->getSprite().getGlobalBounds();

    if (bullet.intersects(g) == true) {
        destructionCapacity--;
        return (1);
    }
    return (-1);
}