/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Ennemis File
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Ennemis.hpp"

static int _number = 0;
Ennemi::Ennemi(int X, int Y) {
    srand(time(NULL));
    int rdom_type = rand() % 4;
    switch (rdom_type) {
        case 0: _type = Type::Blue; break;
        case 1: _type = Type::Green; break;
        case 2: _type = Type::Orange; break;
        case 3: _type = Type::Purple; break;
        default: throw Exception("Unkown number for create ennemi type:" + to_string(rdom_type));
    }

    left = true;
    is_falling = false;
    move_clock.restart();
    _pos = sf::Vector2f(X, Y);
    _sprite = make_shared<sf::Sprite>();
    _texture = make_shared<sf::Texture>();
    gravity = sf::Vector2f(0, 0);
    try {
        switch (_type) {
            case 0: setTexture("resources/Images/Game/robot_blue.png"); break;
            case 1: setTexture("resources/Images/Game/robot_green.png"); break;
            case 2: setTexture("resources/Images/Game/robot_orange.png"); break;
            case 3: setTexture("resources/Images/Game/robot_purple.png"); break;
            default: throw Exception("Unkown number for create ennemi type:" + to_string(rdom_type));
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
    _sprite->setPosition(_pos);
    _sprite->setScale(sf::Vector2f(2, 2));
    _sprite->setTextureRect(sf::IntRect(71, 16, 44, 62));
    _size = getSize();
    _anim = 0;
}
Ennemi::~Ennemi() {}

void Ennemi::setTexture(string filepath) {
    if (!_texture->loadFromFile(filepath))
        throw (Exception("Loading Ressource Failed"));
    _sprite->setTexture(*_texture);
}

bool Ennemi::isFalllingStop(std::vector<std::shared_ptr<Block>> mapSFML) {
    int y = 0;
    sf::FloatRect ColisionArea;
    sf::FloatRect entite = _sprite->getGlobalBounds();
    sf::Vector2f charact_xm = _sprite->getPosition();
    sf::Vector2f charact_mx = _sprite->getPosition();

    charact_xm.y += (_sprite->getTextureRect().height * 2) + 30;
    charact_mx.y += (_sprite->getTextureRect().height * 2) + 30;
    if (_sprite->getScale().x > 0) {
        charact_mx.x += (_sprite->getTextureRect().width * 2) - 15;
        charact_xm.x += 15;
    } else {
        charact_mx.x -= (_sprite->getTextureRect().width * 2) - 15;
        charact_xm.x -= 15;
    }
    for (size_t i = 0; i < mapSFML.size() - 1; i ++) {
        ColisionArea = mapSFML[i]->getSprite().getGlobalBounds();
        if (entite.intersects(ColisionArea) && _sprite->getPosition().y < mapSFML[i]->getSprite().getPosition().y ||
            (entite.contains(charact_mx)  || entite.contains(charact_xm))) {
            _sprite->setTextureRect(sf::IntRect(315, 20, 44, 58));
            y = mapSFML[i]->getSprite().getPosition().y - (_sprite->getTextureRect().height * 2);
            _sprite->setPosition(_sprite->getPosition().x, y);
            _pos = _sprite->getPosition();
            return true;
        }
    }
    return false;
}

void Ennemi::move(vector<shared_ptr<Block>> mapSFML)
{
    if (this->isColisionned(mapSFML) && this->left)
        this->left = false;
    else if (this->isColisionned(mapSFML) && !this->left)
        this->left = true;
    if (this->checkFall(mapSFML) || is_falling)  {
        if (isFalllingStop(mapSFML)) {
            is_falling = false;
            gravity.y = 0;
        } else if (getTimeDiff(0.07) == 1)
            this->movePosition(left ? -2 : 2, gravity.y += 2);
    } else if (left)
        goLeft();
    else
        goRight();
}

bool Ennemi::checkFall(std::vector<std::shared_ptr<Block>> mapSFML) {
    sf::FloatRect ColisionArea;
    sf::Vector2f entite = _sprite->getPosition();
    sf::Vector2f charact_xm = _sprite->getPosition();
    sf::Vector2f charact_mx = _sprite->getPosition();

    entite.y += (_sprite->getTextureRect().height * 2) + 30;
    charact_xm.y += (_sprite->getTextureRect().height * 2) + 30;
    charact_mx.y += (_sprite->getTextureRect().height * 2) + 30;
    if (_sprite->getScale().x > 0) {
        entite.x += (_sprite->getTextureRect().width * 2) / 2;
        charact_mx.x += (_sprite->getTextureRect().width * 2);
    } else {
        entite.x -= (_sprite->getTextureRect().width * 2) / 2;
        charact_mx.x -= (_sprite->getTextureRect().width * 2);
    }
    for (size_t i = 0; i < mapSFML.size(); i ++) {
        ColisionArea = mapSFML[i]->getSprite().getGlobalBounds();
        if (ColisionArea.contains(entite) || ColisionArea.contains(charact_xm) || ColisionArea.contains(charact_mx))
            return false;
    } if (!is_falling) {
        is_falling = true;
        _sprite->setTextureRect(sf::IntRect(72, 20, 44, 60));
        gravity = sf::Vector2f(0, 0);
    }
    return true;
}

bool Ennemi::isColisionned(vector<shared_ptr<Block>> mapSFML) {
    sf::FloatRect ColisionArea;
    sf::FloatRect entite = _sprite->getGlobalBounds();

    for (size_t i = 0; i < mapSFML.size() - 1; i ++) {
        ColisionArea = mapSFML[i]->getSprite().getGlobalBounds();
        if (entite.intersects(ColisionArea))
            return true;
    }
    return false;
}

int Ennemi::getTimeDiff(float diff) {
    sf::Time time;
    float seconds = 0;

    time = move_clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > diff) {
        move_clock.restart();
        return 1;
    }
    return 0;
}

void Ennemi::goLeft(void) {
    if (_sprite->getScale().x < 0) {
        this->_sprite->setScale(sf::Vector2f(2, 2));
        this->movePosition(-95, 0);
    } if (getTimeDiff(0.06) == 1) {
        _anim ++;
        if (_anim > 5) {
            _anim = 0;
            _sprite->setTextureRect(sf::IntRect(315, 20, 44, 58));
        } else
            _sprite->setTextureRect(sf::IntRect(315 + (_anim * 48), 20, 44, 58));
    }
    this->movePosition(-10, 0);
}

void Ennemi::goRight(void) {
    if (_sprite->getScale().x > 0) {
        this->_sprite->setScale(sf::Vector2f(-2, 2));
        this->movePosition(95, 0);
    } if (getTimeDiff(0.06) == 1) {
        _anim ++;
        if (_anim > 5) {
            _anim = 0;
            _sprite->setTextureRect(sf::IntRect(315, 20, 44, 58));
        } else
            _sprite->setTextureRect(sf::IntRect(315 + (_anim * 48), 20, 44, 58));
    }
    this->movePosition(10, 0);
}

void Ennemi::movePosition(int x, int y) {
    _pos = sf::Vector2f(_pos.x + x, _pos.y + y);
    _sprite->setPosition(_pos);
}

void Ennemi::movePosition(sf::Vector2f pos) {
    _pos = sf::Vector2f(_pos.x + pos.x, _pos.y + pos.y);
    _sprite->setPosition(_pos);
}

void Ennemi::setPosition(sf::Vector2f pos) {
    _pos = pos;
    _sprite->setPosition(_pos);
}

void Ennemi::setPosition(int x, int y) {
    _pos = sf::Vector2f(x, y);
    _sprite->setPosition(_pos);
}

int Ennemi::getType(void) const {return _type;}
sf::Vector2f Ennemi::getSize(void) const {return _size;}
void Ennemi::setType(Type newtype) {this->_type = newtype;}
sf::Vector2f Ennemi::getPosition(void) const {return _pos;}
sf::Sprite Ennemi::getSprite(void) const {return *_sprite;}
sf::Texture Ennemi::getTexture(void) const {return *_texture;}
