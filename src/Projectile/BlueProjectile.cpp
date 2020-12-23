/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** BlueProjectile
*/

#include "BlueProjectile.hpp"

BlueProjectile::BlueProjectile(int _orient, sf::Vector2f pos, int desCap): Projectile(desCap)
{
    texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile("./resources/Images/Game/sonor_shockwaves.png"))
        throw(Exception("resources load failed"));
    type = IProjectile::Blue;
    move_clock.restart();
    anim_clock.restart();
    posRect = 0;
    orient = _orient;
    sprite.setTexture(*texture);

    shootRect.push_back(sf::IntRect(110, 462, 49, 44));
    shootRect.push_back(sf::IntRect(286, 456, 112, 61));
    shootRect.push_back(sf::IntRect(286, 453, 22, 42));
    shootRect.push_back(sf::IntRect(694, 450, 89, 64));
    shootTime.push_back(0.3);
    shootTime.push_back(0.2);
    shootTime.push_back(0.2);
    shootTime.push_back(0.4);
    shootMove.push_back(sf::Vector2f(0.f, 0.f));
    shootMove.push_back(sf::Vector2f(0.f, 0.f));
    shootMove.push_back(sf::Vector2f(0.f, 0.f));
    if (orient > 0) {
        pos.x += 20;
        pos.y -= 12;
        sprite.setScale(sf::Vector2f(1.5, 1.5));
        shootMove.push_back(sf::Vector2f(30.f, 0.f));
    } else {
        pos.x -= 20;
        pos.y -= 10;
        sprite.setScale(sf::Vector2f(-1.5, 1.5));
        shootMove.push_back(sf::Vector2f(-30.f, 0.f));
    }
    sprite.setTextureRect(shootRect[posRect]);
    sprite.setPosition(pos);
}

BlueProjectile::~BlueProjectile()
{
}

void BlueProjectile::animation()
{
    sf::Vector2f pos = sprite.getPosition();

    if (getTimeAnim(shootTime[posRect]) == 1) {
        if (posRect < shootRect.size() - 1) {
            posRect++;
            sprite.setTextureRect(shootRect[posRect]);
        }
    }
}

void BlueProjectile::movement()
{
    if (getTimeMov(0.05) == 1)
        sprite.move(shootMove[posRect]);
}

void BlueProjectile::display(std::shared_ptr<sf::RenderWindow> window)
{
    animation();
    movement();
    window->draw(sprite);
}

int BlueProjectile::checkDestruction(vector<shared_ptr<Block>> &mapSFML)
{
    sf::FloatRect bullet = sprite.getGlobalBounds();
    sf::FloatRect g = mapSFML[0]->getSprite().getGlobalBounds();

    for (int i = 0; i < mapSFML.size(); i++) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if (bullet.intersects(g) == true) {
            if (mapSFML[i]->getType() == Block::Type::BLUE) {
                mapSFML.erase(mapSFML.begin() + i);
                return (0);
            }
            return (0);
        }
    }
    return (-1);
}

int BlueProjectile::checkKill(std::shared_ptr<Ennemi> ennemi) {
    sf::FloatRect bullet = sprite.getGlobalBounds();
    sf::FloatRect g = ennemi->getSprite().getGlobalBounds();

    if (this->type != ennemi->getType())
        return -1;
    if (bullet.intersects(g)) {
        destructionCapacity --;
        return 1;
    }
    return -1;
}