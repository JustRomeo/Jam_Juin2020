/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GreenProjectile
*/

#include "GreenProjectile.hpp"

GreenProjectile::GreenProjectile(int _orient, sf::Vector2f pos, int desCap): Projectile(desCap)
{
     texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile("./resources/Images/sonor_shockwaves.png") == false)
        throw(Exception("resources load failed"));
    type = IProjectile::CHARGED;
    posRect = 0;
    orient = _orient;
    sprite.setTexture(*texture);

    shootRect.push_back(sf::IntRect(0, 0, 0, 0));
    shootRect.push_back(sf::IntRect(64, 623, 26, 28));
    shootRect.push_back(sf::IntRect(858, 613, 92, 44));
    shootRect.push_back(sf::IntRect(1008, 604, 93, 66));
    shootTime.push_back(0.3);
    shootTime.push_back(0.6);
    shootTime.push_back(0.3);
    shootTime.push_back(0.2);
    shootMove.push_back(sf::Vector2f(0.f, 0.f));
    shootMove.push_back(sf::Vector2f(0.f, 0.f));
    shootMove.push_back(sf::Vector2f(0.f, 0.f));
    if (orient > 0) {
        pos.x += 20;
        pos.y -= 80;
        sprite.setScale(sf::Vector2f(1.5, 1.5));
        shootMove.push_back(sf::Vector2f(30.f, 0.f));
        shootMove.push_back(sf::Vector2f(30.f, 0.f));
    }
    else {
        pos.x -= 20;
        pos.y -= 80;
        sprite.setScale(sf::Vector2f(-1.5, 1.5));
        shootMove.push_back(sf::Vector2f(-30.f, 0.f));
        shootMove.push_back(sf::Vector2f(-30.f, 0.f));
    }
    sprite.setTextureRect(shootRect[posRect]);
    sprite.setPosition(pos);
}

GreenProjectile::~GreenProjectile()
{
}

void GreenProjectile::animation()
{
    sf::Vector2f pos = sprite.getPosition();

    if (getTimeAnim(shootTime[posRect]) == 1) {
            if (posRect < shootRect.size() - 1) {
                posRect++;
                if (posRect == 2) {
                    if (orient > 0)
                        pos.x += 60;
                    if (orient < 0)
                        pos.x -= 60;
                    pos.y += 60;
                    sprite.setPosition(pos);
                }
                if (posRect == 3) {
                    if (orient > 0)
                        pos.x += 60;
                    if (orient < 0)
                        pos.x -= 60;
                    pos.y -= 30;
                    sprite.setPosition(pos);
                }
                sprite.setTextureRect(shootRect[posRect]);
            }
        }
}

void GreenProjectile::movement()
{
    if (getTimeMov(0.05) == 1)
        sprite.move(shootMove[posRect]);
}

void GreenProjectile::display(std::shared_ptr<sf::RenderWindow> window)
{
    animation();
    movement();
    window->draw(sprite);
}

int GreenProjectile::checkDestruction(std::shared_ptr<Block> block)
{
    sf::FloatRect bullet = sprite.getGlobalBounds();
    sf::FloatRect g = block->getSprite().getGlobalBounds();

    if (bullet.intersects(g) == true) {
        if (block->getType() != Block::Type::UNBREAKABLE) {
            destructionCapacity--;
            return (1);
        }
        return (0);
    }
    return (-1);
}

int GreenProjectile::checkKill(std::shared_ptr<Ennemi> ennemi)
{
    sf::FloatRect bullet = sprite.getGlobalBounds();
    sf::FloatRect g = ennemi->getSprite().getGlobalBounds();

    if (bullet.intersects(g) == true) {
        destructionCapacity--;
        return (1);
    }
    return (-1);
}