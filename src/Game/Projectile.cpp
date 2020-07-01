/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Projectile
*/

#include "Projectile.hpp"

Projectile::Projectile(int _type, int _orient, sf::Vector2f pos, int desCap)
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
    if (_type == 4)
        type = Type::CHARGED;
    move_clock.restart();
    anim_clock.restart();
    posRect = 0;
    orient = _orient;
    destructionCapacity = desCap;
    sprite.setTexture(*texture);
    if (_type == 1)
        createProject1(orient, type, pos);
    if (_type == 2)
        createProject2(orient, type, pos);
    if (_type == 3)
        createProject3(orient, type, pos);
    if (_type == 4)
        createProject4(orient, type, pos);
}

Projectile::~Projectile()
{
}

void Projectile::createProject1(int orient, int type, sf::Vector2f pos)
{
    shootRect1.push_back(sf::IntRect(166, 212, 42, 42));
    shootRect1.push_back(sf::IntRect(960, 212, 22, 42));

    shoot1Time.push_back(0.4);
    shoot1Time.push_back(0.5);

    shoot1Move.push_back(sf::Vector2f(0.f, 0.f));
    if (orient > 0) {
        if (type == 1) {
            pos.x += 40;
            pos.y += 7;
        }
        sprite.setScale(sf::Vector2f(1.5, 1.5));
        shoot1Move.push_back(sf::Vector2f(30.f, 0.f));
    }
    else {
        if (type == 1) {
            pos.x -= 40;
            pos.y += 7;
        }
        sprite.setScale(sf::Vector2f(-1.5, 1.5));
        shoot1Move.push_back(sf::Vector2f(-30.f, 0.f));
    }
    sprite.setTextureRect(shootRect1[posRect]);
    sprite.setPosition(pos);
}

void Projectile::createProject2(int orient, int type, sf::Vector2f pos)
{
    shootRect2.push_back(sf::IntRect(110, 462, 49, 44));
    shootRect2.push_back(sf::IntRect(286, 456, 112, 61));
    shootRect2.push_back(sf::IntRect(286, 453, 22, 42));
    shootRect2.push_back(sf::IntRect(694, 450, 89, 64));

    shoot2Time.push_back(0.3);
    shoot2Time.push_back(0.2);
    shoot2Time.push_back(0.2);
    shoot2Time.push_back(0.4);

    shoot2Move.push_back(sf::Vector2f(0.f, 0.f));
    shoot2Move.push_back(sf::Vector2f(0.f, 0.f));
    shoot2Move.push_back(sf::Vector2f(0.f, 0.f));
    if (orient > 0) {
        if (type == 2) {
            pos.x += 20;
            pos.y -= 12;
        }
        sprite.setScale(sf::Vector2f(1.5, 1.5));
        shoot2Move.push_back(sf::Vector2f(30.f, 0.f));
    }
    else {
        if (type == 2) {
            pos.x -= 20;
            pos.y -= 10;
        }
        sprite.setScale(sf::Vector2f(-1.5, 1.5));
        shoot2Move.push_back(sf::Vector2f(-30.f, 0.f));
    }
    sprite.setTextureRect(shootRect2[posRect]);
    sprite.setPosition(pos);
}
void Projectile::createProject3(int orient, int type, sf::Vector2f pos)
{
    shootRect3.push_back(sf::IntRect(164, 310, 44, 49));
    shootRect3.push_back(sf::IntRect(362, 310, 117, 65));
    shootRect3.push_back(sf::IntRect(760, 310, 95, 42));

    shoot3Time.push_back(0.3);
    shoot3Time.push_back(0.2);
    shoot3Time.push_back(0.2);

    shoot3Move.push_back(sf::Vector2f(0.f, 0.f));
    shoot3Move.push_back(sf::Vector2f(0.f, 0.f));
    if (orient > 0) {
        if (type == 3) {
            pos.x += 20;
            pos.y -= 6;
        }
        sprite.setScale(sf::Vector2f(1.5, 1.5));
        shoot3Move.push_back(sf::Vector2f(30.f, 0.f));
    }
    else {
        if (type == 3) {
            pos.x += 20;
            pos.y -= 6;
        }
        sprite.setScale(sf::Vector2f(-1.5, 1.5));
        shoot3Move.push_back(sf::Vector2f(-30.f, 0.f));
    }
    sprite.setTextureRect(shootRect3[posRect]);
    sprite.setPosition(pos);
}

void Projectile::createProject4(int orient, int type, sf::Vector2f pos)
{
    shootRect4.push_back(sf::IntRect(0, 0, 0, 0));
    shootRect4.push_back(sf::IntRect(64, 623, 26, 28));
    shootRect4.push_back(sf::IntRect(858, 613, 92, 44));
    shootRect4.push_back(sf::IntRect(1008, 604, 93, 66));

    shoot4Time.push_back(0.3);
    shoot4Time.push_back(0.6);
    shoot4Time.push_back(0.3);
    shoot4Time.push_back(0.2);

    shoot4Move.push_back(sf::Vector2f(0.f, 0.f));
    shoot4Move.push_back(sf::Vector2f(0.f, 0.f));
    shoot4Move.push_back(sf::Vector2f(0.f, 0.f));
    if (orient > 0) {
        if (type == 4) {
            pos.x += 20;
            pos.y -= 80;
        }
        sprite.setScale(sf::Vector2f(1.5, 1.5));
        shoot4Move.push_back(sf::Vector2f(30.f, 0.f));
        shoot4Move.push_back(sf::Vector2f(30.f, 0.f));
    }
    else {
        if (type == 4) {
            pos.x -= 20;
            pos.y -= 80;
        }
        sprite.setScale(sf::Vector2f(-1.5, 1.5));
        shoot4Move.push_back(sf::Vector2f(-30.f, 0.f));
        shoot4Move.push_back(sf::Vector2f(-30.f, 0.f));
    }
    sprite.setTextureRect(shootRect4[posRect]);
    sprite.setPosition(pos);
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
    sf::Vector2f pos = sprite.getPosition();

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
    if (type == CHARGED && posRect < shoot4Time.size()) {
        if (getTimeAnim(shoot4Time[posRect]) == 1) {
            if (posRect < shootRect4.size() - 1) {
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
                sprite.setTextureRect(shootRect4[posRect]);
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
        if (type == CHARGED)
            sprite.move(shoot4Move[posRect]);
    }
}

void Projectile::display(std::shared_ptr<sf::RenderWindow> window)
{
    animation();
    movement();
    window->draw(sprite);
}

int Projectile::getCurrentCapacity()
{
    return (destructionCapacity);
}

int Projectile::checkDestruction(std::shared_ptr<Block> block)
{
    sf::FloatRect bullet = sprite.getGlobalBounds();
    sf::FloatRect g = block->getSprite().getGlobalBounds();

    if (bullet.intersects(g) == true) {
        if ((type == Type::YELLOW && block->getType() == Block::Type::YELLOW)
        || (type == Type::BLUE && block->getType() == Block::Type::BLUE)
        || (type == Type::PURPLE && block->getType() == Block::Type::PURPLE)
        || (type == Type::CHARGED && block->getType() != Block::Type::UNBREAKABLE)) {
            destructionCapacity--;
            return (1);
        }
        return (0);
    }
    return (-1);
}

int Projectile::checkKill(std::shared_ptr<Ennemi> ennemi)
{
    sf::FloatRect bullet = sprite.getGlobalBounds();
    sf::FloatRect g = ennemi->getSprite().getGlobalBounds();

    if (bullet.intersects(g) == true) {
        destructionCapacity--;
        return (1);
    }
    return (-1);
}