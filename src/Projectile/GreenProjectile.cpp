/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** GreenProjectile
*/

#include "GreenProjectile.hpp"

GreenProjectile::GreenProjectile(int _orient, sf::Vector2f pos, int desCap): Projectile(desCap)
{
     texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile("./resources/Images/Game/sonor_shockwaves.png") == false)
        throw(Exception("resources load failed"));
    type = IProjectile::Purple;
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

int GreenProjectile::checkDestruction(vector<shared_ptr<Block>> &mapSFML)
{
    sf::FloatRect bullet = sprite.getGlobalBounds();
    sf::FloatRect g;
    sf::FloatRect r;
    sf::CircleShape explosionRange;
    sf::Vector2f rangePosition;
    int j = 0;

    for (int i = 0; i < mapSFML.size(); i ++) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if (bullet.intersects(g)) {
            rangePosition.y = sprite.getPosition().y - 80;
            if (mapSFML[i]->getSprite().getPosition().x - sprite.getPosition().x > 0)
                rangePosition.x = sprite.getPosition().x;
            else
                rangePosition.x = sprite.getPosition().x - 200;
            explosionRange.setPosition(rangePosition);
            explosionRange.setRadius(120.f);
            while (j < mapSFML.size()) {
                r = mapSFML[j]->getSprite().getGlobalBounds();
                if (r.intersects(explosionRange.getGlobalBounds()) && mapSFML[j]->getType() != Block::Type::UNBREAKABLE) {
                    mapSFML.erase(mapSFML.begin() + j);
                    j = 0;
                }
                j ++;
            }
            return (0);
        }
    }
    return (-1);
}

int GreenProjectile::checkKill(std::shared_ptr<Ennemi> ennemi) {
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

int GreenProjectile::checkKill(std::shared_ptr<Runner> ennemi) {
    sf::FloatRect bullet = sprite.getGlobalBounds();
    sf::FloatRect g = ennemi->getSprite().getGlobalBounds();

    if (bullet.intersects(g)) {
        destructionCapacity --;
        return 1;
    }
    return -1;
}
