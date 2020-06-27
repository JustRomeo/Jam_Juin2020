/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Character
*/

#include "Character.hpp"

Character::Character()
{
    textureFight = std::make_shared<sf::Texture>();
    texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile("./resources/character/adventurer-Sheet.png") == false)
        throw(Exception("resources load failed"));
    if (textureFight->loadFromFile("./resources/character/adventurer-bow-Sheet.png") == false)
        throw(Exception("resources load failed"));
    sprite.setTexture(*texture);
    sprite.setPosition(sf::Vector2f(40.f, 400.f));
    sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
    sprite.setScale(sf::Vector2f(3.f, 3.f));
    move_Y = 43;
    notMove_Y = 5;
    move_Xmax = 315;
    shootRectPos = 0;
    is_shooting = false;
    is_moving = false;
    is_falling = false;
    move_clock.restart();
    shootRect.push_back(sf::IntRect(12, 8, 35, 35));
    shootRect.push_back(sf::IntRect(62, 8, 28, 30));
    shootRect.push_back(sf::IntRect(114, 8, 29, 29));
    shootRect.push_back(sf::IntRect(162, 8, 34, 30));
    shootRect.push_back(sf::IntRect(12, 46, 30, 29));
    shootRect.push_back(sf::IntRect(64, 46, 26, 29));
    shootRect.push_back(sf::IntRect(113, 46, 35, 35));
    shootRect.push_back(sf::IntRect(159, 46, 40, 35));
    shootRect.push_back(sf::IntRect(12, 82, 34, 30));
}

Character::~Character()
{
}

int Character::getTimeDiff(float diff)
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

void Character::shootAnimation()
{
    if (getTimeDiff(0.06) == 1)
    {
        shootRectPos++;
        if (shootRectPos > 8) {
            is_shooting = false;
            shootRectPos = 0;
            sprite.setTexture(*texture);
            sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
        }
        else
            sprite.setTextureRect(shootRect[shootRectPos]);
    }
}

void Character::jumpAnimation(std::shared_ptr<sf::RenderWindow> window)
{
    sf::IntRect rect = sprite.getTextureRect();
    sf::View view = window->getView();

    if (getTimeDiff(0.07) == 1) {
        if (rect.left < 165) {
            rect.left += 50;
            sprite.setTextureRect(rect);
        }
        move.y += 1;
        if (move.y > 0) {
            is_jumping = false;
            sprite.setTextureRect(sf::IntRect(215, 77, 25, 36));
            is_falling = true;
        }
        view.move(move);
        window->setView(view);
        sprite.move(move);
    }
}

void Character::fallingAnimation(std::shared_ptr<sf::RenderWindow> window)
{
    sf::IntRect rect = sprite.getTextureRect();
    sf::Vector2f pos = sprite.getPosition();
    sf::View view = window->getView();

    if (getTimeDiff(0.07) == 1) {
        if (rect.top == 77) {
            rect.left += 50;
            if (rect.left > 315) {
                rect.top = 112;
                rect.left = 15;
            }
            sprite.setTextureRect(rect);
        }
        if (rect.top == 112) {
            if (rect.left < 115)
                rect.left += 50;
            sprite.setTextureRect(rect);
        }
        move.y += 1;
        if (pos.y + move.y > 400) {
            is_falling = false;
            move.y = 400 - pos.y - 1;
        }
        view.move(move);
        window->setView(view);
        sprite.move(move);
    }
}

void Character::display(std::shared_ptr<sf::RenderWindow> window)
{
    if (is_shooting == true)
        shootAnimation();
    if (is_jumping == true)
        jumpAnimation(window);
    if (is_falling == true)
        fallingAnimation(window);
    window->draw(sprite);
}

void Character::jump()
{
    if (is_jumping == false) {
        is_jumping = true;
        sprite.setTextureRect(sf::IntRect(65, 78, 25, 32));
        move = sf::Vector2f(0.f, -15.f);
    }
}

void Character::fall()
{
    if (is_falling == false) {
        is_falling = true;
        sprite.setTextureRect(sf::IntRect(215, 78, 25, 28));
        move = sf::Vector2f(0.f, 15.f);
    }
}

void Character::moveLeft()
{
    sf::IntRect rect = sprite.getTextureRect();

    is_moving = true;
    if (is_jumping == false && is_falling == false) {
        if (sprite.getScale().x > 0) {
            sf::Vector2f pos = sprite.getPosition();
            pos.x += 69.f;
            sprite.setPosition(pos);
            sprite.setScale(-3, 3);
        }
        if (rect.top != move_Y)
            sprite.setTextureRect(sf::IntRect(65, 43, 22, 32));
        else {
            if (getTimeDiff(0.03) == 1) {
                if (rect.left >= 265)
                    rect.left = 65;
                else
                    rect.left += 50;
                sprite.setTextureRect(rect);
            }
        }
        sprite.move(sf::Vector2f(-10.f, 0.f));
    }
    else
        sprite.move(sf::Vector2f(-3.f, 0.f));
}

void Character::moveRigth()
{
    sf::IntRect rect = sprite.getTextureRect();

    is_moving = true;
    if (is_jumping == false && is_falling == false) {
        if (sprite.getScale().x < 0) {
            sf::Vector2f pos = sprite.getPosition();
            pos.x -= 69.f;
            sprite.setPosition(pos);
            sprite.setScale(3, 3);
        }
        if (rect.top != move_Y)
            sprite.setTextureRect(sf::IntRect(65, 43, 23, 32));
        else {
            if (getTimeDiff(0.03) == 1) {
                if (rect.left >= 315)
                    rect.left = 65;
                else
                    rect.left += 50;
                sprite.setTextureRect(rect);
            }
        }
        sprite.move(sf::Vector2f(10.f, 0.f));
    }
    else
        sprite.move(sf::Vector2f(3.f, 0.f));
}

void Character::shoot()
{
    sf::IntRect rect = sprite.getTextureRect();
    int toTurn = 0;

    if (is_shooting != true && is_jumping == false && is_falling == false) {
        is_shooting = true;
        if (sprite.getScale().x < 0)
            toTurn = 1;
        sprite.setTexture(*textureFight);
        if (toTurn == 0)
            sprite.setScale(sf::Vector2f(3.f, 3.f));
        else
            sprite.setScale(sf::Vector2f(-3.f, 3.f));
        sprite.setTextureRect(shootRect[shootRectPos]);
    }
}

void Character::restartPos()
{
    sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
}

int Character::isShooting()
{
    return (is_shooting);
}

bool Character::isJumping()
{
    return (is_jumping);
}

bool Character::isFalling()
{
    return (is_falling);
}

bool Character::getMoving()
{
    return (is_moving);
}

void Character::setMoving(bool status)
{
    is_moving = status;
}