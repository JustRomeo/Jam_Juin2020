/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Runner File
*/

#include "Runner.hpp"

Runner::Runner(int X, int Y) {
    left = true;
    is_falling = false;

    _anim = 0;
    _size = getSize();
    _pos = sf::Vector2f(X, Y);
    gravity = sf::Vector2f(0, 0);
    _sprite = make_shared<sf::Sprite>();
    _texture = make_shared<sf::Texture>();

    setTexture("resources/Images/Game/runner.gif");

    _sprite->setPosition(_pos);
    _sprite->setScale(sf::Vector2f(2, 2));
    _sprite->setTextureRect(sf::IntRect(71, 16, 44, 62));

    move_clock.restart();
}

Runner::~Runner() {}

void Runner::setTexture(string filepath) {
    if (!_texture->loadFromFile(filepath))
        throw (Exception("Loading Ressource Failed"));
    _sprite->setTexture(*_texture);
}

bool Runner::isFalllingStop(std::vector<std::shared_ptr<Block>> mapSFML) {
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

int abs(int one, int two) {return (one - two) * (one - two > 0 ? 1 : -1);}

void Runner::move(vector<shared_ptr<Block>> mapSFML, shared_ptr<Character> player) {
    bool near = (abs(player->getSprite().getPosition().y, this->_pos.y) < 15 ? true : false);

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
    } else if (near && player->getSprite().getPosition().x < this->_pos.x)
        left = true;
    else if (near && player->getSprite().getPosition().x > this->_pos.x)
        left = false;
    else if (left)
        goLeft();
    else
        goRight();
}

bool Runner::checkFall(std::vector<std::shared_ptr<Block>> mapSFML) {
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
        _sprite->setTextureRect(sf::IntRect(0, 0, 55, 58));
        gravity = sf::Vector2f(0, 0);
    }
    return true;
}

bool Runner::isColisionned(vector<shared_ptr<Block>> mapSFML) {
    sf::FloatRect ColisionArea;
    sf::FloatRect entite = _sprite->getGlobalBounds();

    for (size_t i = 0; i < mapSFML.size() - 1; i ++) {
        ColisionArea = mapSFML[i]->getSprite().getGlobalBounds();
        if (entite.intersects(ColisionArea))
            return true;
    }
    return false;
}

int Runner::getTimeDiff(float diff) {
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

void Runner::goLeft(void) {
    if (_sprite->getScale().x < 0) {
        this->_sprite->setScale(sf::Vector2f(2, 2));
        this->movePosition(-95, 0);
    } if (getTimeDiff(0.06) == 1) {
        _anim ++;
        if (_anim > 5) {
            _anim = 0;
            _sprite->setTextureRect(sf::IntRect(0, 0, 45, 50));
        } else
            _sprite->setTextureRect(sf::IntRect(0 + (_anim * 48), 0, 45, 50));
    }
    this->movePosition(-10, 0);
}

void Runner::goRight(void) {
    if (_sprite->getScale().x > 0) {
        this->_sprite->setScale(sf::Vector2f(-2, 2));
        this->movePosition(95, 0);
    } if (getTimeDiff(0.06) == 1) {
        _anim ++;
        if (_anim > 5) {
            _anim = 0;
            _sprite->setTextureRect(sf::IntRect(245, 0, 45, 50));
        } else
            _sprite->setTextureRect(sf::IntRect(245 + (_anim * 48), 0, 45, 50));
    }
    this->movePosition(10, 0);
}

void Runner::movePosition(int x, int y) {
    _pos = sf::Vector2f(_pos.x + x, _pos.y + y);
    _sprite->setPosition(_pos);
}

void Runner::movePosition(sf::Vector2f pos) {
    _pos = sf::Vector2f(_pos.x + pos.x, _pos.y + pos.y);
    _sprite->setPosition(_pos);
}

void Runner::setPosition(sf::Vector2f pos) {
    _pos = pos;
    _sprite->setPosition(_pos);
}

void Runner::setPosition(int x, int y) {
    _pos = sf::Vector2f(x, y);
    _sprite->setPosition(_pos);
}

sf::Vector2f Runner::getSize(void) const {return _size;}
sf::Vector2f Runner::getPosition(void) const {return _pos;}
sf::Sprite Runner::getSprite(void) const {return (*_sprite);}
sf::Texture Runner::getTexture(void) const {return *_texture;}