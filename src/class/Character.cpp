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
    sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
    sprite.setScale(sf::Vector2f(3.f, 3.f));
    sprite.setPosition(sf::Vector2f(200.f, 1102.f - (32.f * 3)));
    move_Y = 45;
    notMove_Y = 6;
    move_Xmax = 315;
    shootRectPos = 0;
    is_shooting = false;
    is_moving = false;
    is_falling = false;
    is_jumping = false;
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

void Character::jumpAnimation(std::shared_ptr<sf::RenderWindow> window,
    std::vector<std::shared_ptr<Block>> mapSFML)
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
        if (not_colision(mapSFML) == 1) {
            sprite.move(move);
            view.move(move);
        }
        else {
            move.y = 0;
            is_jumping = false;
            sprite.setTextureRect(sf::IntRect(215, 77, 25, 36));
            is_falling = true;
        }
        window->setView(view);
    }
}

void Character::fallingAnimation(std::shared_ptr<sf::RenderWindow> window,
    std::vector<std::shared_ptr<Block>> mapSFML)
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
        move.y += 2;
        sprite.move(move);
        if (collisionFall(mapSFML) == 0) {
            is_falling = false;
            sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
        }
        view.move(move);
        window->setView(view);
    }
}

void Character::display(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML)
{
    sf::Vector2f charact = sprite.getPosition();

    charact.y += (sprite.getTextureRect().height * 3) + 30;
    if (sprite.getScale().x > 0)
        charact.x += (sprite.getTextureRect().width * 3) / 2;
    else
        charact.x -= (sprite.getTextureRect().width * 3) / 2;
    sf::CircleShape Circle = sf::CircleShape(1);
    Circle.setPosition(charact);
    if (is_shooting == true)
        shootAnimation();
    if (is_jumping == true)
        jumpAnimation(window, mapSFML);
    if (is_falling == true)
        fallingAnimation(window, mapSFML);
    window->draw(sprite);
    window->draw(Circle);
}

void Character::jump()
{
    if (is_jumping == false && is_falling == false) {
        is_jumping = true;
        sprite.setTextureRect(sf::IntRect(65, 79, 21, 31));
        move = sf::Vector2f(0.f, -20.f);
    }
}

void Character::fall()
{
    if (is_falling == false) {
        is_falling = true;
        sprite.setTextureRect(sf::IntRect(215, 78, 25, 28));
        move = sf::Vector2f(0.f, 0.f);
    }
}

void Character::moveLeft(std::shared_ptr<sf::RenderWindow> window,
    std::vector<std::shared_ptr<Block>> mapSFML)
{
    sf::IntRect rect = sprite.getTextureRect();
    sf::View view= window->getView();

    is_moving = true;
    if (is_jumping == false && is_falling == false && checkFall(mapSFML) == 1)
        return;
    if (is_jumping == false && is_falling == false) {
        if (sprite.getScale().x > 0) {
            sf::Vector2f pos = sprite.getPosition();
            pos.x += 55.f;
            sprite.setPosition(pos);
            sprite.setScale(-3, 3);
        }
        if (rect.top != move_Y)
            sprite.setTextureRect(sf::IntRect(65, 45, 22, 28));
        else {
            if (getTimeDiff(0.03) == 1) {
                if (rect.left >= 265)
                    rect.left = 65;
                else
                    rect.left += 50;
                sprite.setTextureRect(rect);
            }
        }
        if (not_colision(mapSFML) == 1) {
            sprite.move(sf::Vector2f(-10.f, 0.f));
            view.move(sf::Vector2f(-10.f, 0.f));
            window->setView(view);
        }
    }
    else {
        if (sprite.getScale().x > 0) {
            sf::Vector2f pos = sprite.getPosition();
            pos.x += 55.f;
            sprite.setPosition(pos);
            sprite.setScale(-3, 3);
        }
        if (not_colision(mapSFML) == 1) {
            sprite.move(sf::Vector2f(-5.f, 0.f));
            view.move(sf::Vector2f(-5.f, 0.f));
            window->setView(view);
        }
    }
}

void Character::moveRigth(std::shared_ptr<sf::RenderWindow> window,
    std::vector<std::shared_ptr<Block>> mapSFML)
{
    sf::IntRect rect = sprite.getTextureRect();
    sf::View view= window->getView();

    is_moving = true;
    if (is_jumping == false && is_falling == false && checkFall(mapSFML) == 1)
        return;
    if (is_jumping == false && is_falling == false) {
        if (sprite.getScale().x < 0) {
            sf::Vector2f pos = sprite.getPosition();
            pos.x -= 55.f;
            sprite.setPosition(pos);
            sprite.setScale(3, 3);
        }
        if (rect.top != move_Y)
            sprite.setTextureRect(sf::IntRect(65, 45, 22, 28));
        else {
            if (getTimeDiff(0.03) == 1) {
                if (rect.left >= 315)
                    rect.left = 65;
                else
                    rect.left += 50;
                sprite.setTextureRect(rect);
            }
        }
        if (not_colision(mapSFML) == 1) {
            sprite.move(sf::Vector2f(10.f, 0.f));
            view.move(sf::Vector2f(10.f, 0.f));
            window->setView(view);
        }
    }
    else {
        if (sprite.getScale().x < 0) {
            sf::Vector2f pos = sprite.getPosition();
            pos.x -= 55.f;
            sprite.setPosition(pos);
            sprite.setScale(3, 3);
        }
        if (not_colision(mapSFML) == 1) {
            sprite.move(sf::Vector2f(5.f, 0.f));
            view.move(sf::Vector2f(5.f, 0.f));
            window->setView(view);
        }
    }
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

int Character::not_colision(std::vector<std::shared_ptr<Block>> mapSFML)
{
    int i = 0;
    sf::FloatRect charact = sprite.getGlobalBounds();
    sf::FloatRect g;

    while (i < mapSFML.size() - 1) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if (charact.intersects(g) == true)
            return (0);
        i++;
    }
    return (1);
}

int Character::collisionFall(std::vector<std::shared_ptr<Block>> mapSFML)
{
    int i = 0;
    int y = 0;
    sf::FloatRect charact = sprite.getGlobalBounds();
    sf::FloatRect g;

    while (i < mapSFML.size() - 1) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if (charact.intersects(g) == true && sprite.getPosition().y < mapSFML[i]->getSprite().getPosition().y) {
            y = mapSFML[i]->getSprite().getPosition().y - (32.f * 3);
            sprite.setPosition(sprite.getPosition().x, y);
            return (0);
        }
        i++;
    }
    return (1);
}

int Character::checkFall(std::vector<std::shared_ptr<Block>> mapSFML)
{
    int i = 0;
    int y = 0;
    sf::Vector2f charact = sprite.getPosition();
    sf::FloatRect g;

    charact.y += (sprite.getTextureRect().height * 3) + 30;
    if (sprite.getScale().x > 0)
        charact.x += (sprite.getTextureRect().width * 3) / 2;
    else
        charact.x -= (sprite.getTextureRect().width * 3) / 2;
    while (i < mapSFML.size()) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if (g.contains(charact) == true) {
            return (0);
        }
        i++;
    }
    fall();
    return (1);
}

sf::Sprite Character::getSprite()
{
    return (sprite);
}

void Character::restartPos()
{
    sprite.setTextureRect(sf::IntRect(65, 6, 19, 30));
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