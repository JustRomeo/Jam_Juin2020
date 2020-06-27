/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Projectile
*/

#include "Projectile.hpp"

Projectile::Projectile(int _type, int orient, sf::Vector2f pos)
{
    texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile("./resources/Images/sonor_shockwaves.png") == false)
        throw(Exception("resources load failed"));
    if (_type == 1)
        type = YELLOW;
    if (_type == 2)
        type = Type::BLUE;
    if (_type == 3)
        type = Type::PURPLE;
    move_clock.restart();
    anim_clock.restart();
    shootRect1.push_back(sf::IntRect(166, 212, 42, 42));
    shootRect1.push_back(sf::IntRect(960, 212, 22, 42));

    shootRect2.push_back(sf::IntRect(110, 462, 49, 44));
    shootRect2.push_back(sf::IntRect(286, 456, 112, 61));
    shootRect2.push_back(sf::IntRect(286, 453, 22, 42));
    shootRect2.push_back(sf::IntRect(694, 450, 89, 64));

    shootRect3.push_back(sf::IntRect(164, 310, 44, 49));
    shootRect3.push_back(sf::IntRect(362, 310, 117, 65));
    shootRect3.push_back(sf::IntRect(760, 310, 95, 42));
    posRect = 0;
    sprite.setTexture(*texture);
    if (_type == 1)
        sprite.setTextureRect(shootRect1[posRect]);
    if (_type == 2)
        sprite.setTextureRect(shootRect2[posRect]);
    if (_type == 3)
        sprite.setTextureRect(shootRect3[posRect]);
    shoot1Time.push_back(0.4);
    shoot1Time.push_back(0.5);

    shoot2Time.push_back(0.3);
    shoot2Time.push_back(0.2);
    shoot2Time.push_back(0.2);
    shoot2Time.push_back(0.4);

    shoot3Time.push_back(0.3);
    shoot3Time.push_back(0.2);
    shoot3Time.push_back(0.2);

    shoot1Move.push_back(sf::Vector2f(0.f, 0.f));

    shoot2Move.push_back(sf::Vector2f(0.f, 0.f));
    shoot2Move.push_back(sf::Vector2f(0.f, 0.f));
    shoot2Move.push_back(sf::Vector2f(0.f, 0.f));
    shoot3Move.push_back(sf::Vector2f(0.f, 0.f));
    shoot3Move.push_back(sf::Vector2f(0.f, 0.f));
    if (orient > 0) {
        shoot1Move.push_back(sf::Vector2f(20.f, 0.f));
        shoot2Move.push_back(sf::Vector2f(20.f, 0.f));
        shoot3Move.push_back(sf::Vector2f(20.f, 0.f));
        sprite.setScale(sf::Vector2f(1.5, 1.5));
        if (type == 1) {
            pos.x += 40;
            pos.y += 7;
        }
        if (type == 2) {
            pos.x += 20;
            pos.y -= 12;
        }
        if (type == 3) {
            pos.x += 20;
            pos.y -= 6;
        }
    }
    else {
        shoot1Move.push_back(sf::Vector2f(-20.f, 0.f));
        shoot2Move.push_back(sf::Vector2f(-20.f, 0.f));
        shoot3Move.push_back(sf::Vector2f(-20.f, 0.f));
        sprite.setScale(sf::Vector2f(-1.5, 1.5));
        if (type == 1) {
            pos.x -= 40;
            //pos.y += 12;
        }
        if (type == 2) {
            pos.x -= 20;
            pos.y -= 10;
        }
        if (type == 3) {
            pos.x -= 20;
            pos.y -= 6;
        }
    }
    sprite.setPosition(pos);
}

Projectile::~Projectile()
{
}

int Projectile::getTimeAnim(float diff)
{
    sf::Time time;
    float seconds = 0;

    time = anim_clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > diff) {
        anim_clock.restart();
        return (1);
    }
    return (0);
}

int Projectile::getTimeMov(float diff)
{
    sf::Time time;
    float seconds = 0;

    time = move_clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > diff) {
        move_clock.restart();
        return (1);
    }
    return (0);
}

void Projectile::animation()
{
    if (type == BLUE && posRect < shoot2Time.size()) {
        if (getTimeAnim(shoot2Time[posRect]) == 1) {
            if (posRect < shootRect2.size() - 1) {
                posRect++;
                sprite.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y);
                sprite.setTextureRect(shootRect2[posRect]);
            }
        }
    }
    if (type == YELLOW && posRect < shoot1Time.size()) {
        if (getTimeAnim(shoot1Time[posRect]) == 1) {
            if (posRect < shootRect1.size() - 1) {
                posRect++;
                sprite.setTextureRect(shootRect1[posRect]);
            }
        }
    }
    if (type == PURPLE && posRect < shoot3Time.size()) {
        if (getTimeAnim(shoot3Time[posRect]) == 1) {
            if (posRect < shootRect3.size() - 1) {
                posRect++;
                sprite.setPosition(sprite.getPosition().x + 4, sprite.getPosition().y);
                sprite.setTextureRect(shootRect3[posRect]);
            }
        }
    }
}

void Projectile::movement()
{
    if (getTimeMov(0.05) == 1) {
        if (type == YELLOW)
            sprite.move(shoot1Move[posRect]);
        if (type == BLUE)
            sprite.move(shoot2Move[posRect]);
        if (type == PURPLE)
            sprite.move(shoot3Move[posRect]);
    }
}

void Projectile::display(std::shared_ptr<sf::RenderWindow> window)
{
    animation();
    movement();
    window->draw(sprite);
}