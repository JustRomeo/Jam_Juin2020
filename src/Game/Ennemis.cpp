#include "Ennemis.hpp"

Ennemi::Ennemi(int X, int Y) {
    left = true;
    moving = false;
    move_clock.restart();
    _pos = sf::Vector2f(X, Y);
    _texture = new sf::Texture;
    try {
        this->setTexture("resources/Images/robot.png");
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
    this->_sprite.setPosition(_pos);
    this->_sprite.setScale(sf::Vector2f(2, 2));
    _size = this->getSize();

}
Ennemi::~Ennemi() {}

void Ennemi::setTexture(string filepath) {
    if (!_texture->loadFromFile(filepath))
        throw (Exception("Loading Ressource Failed"));
    _sprite.setTexture(*_texture);
}

void Ennemi::move(vector<shared_ptr<Block>> mapSFML) {
    if (!this->isColisionned(mapSFML) && this->left);
    else if (this->isColisionned(mapSFML) && this->left)
        this->left = false;
    else if (!this->isColisionned(mapSFML) && !this->left);
    else if (this->isColisionned(mapSFML) && !this->left)
        this->left = true;
    if (left)
        goLeft();
    else
        goRight();
}

bool Ennemi::isColisionned(vector<shared_ptr<Block>> mapSFML)
{
    sf::FloatRect g;
    sf::FloatRect charact = _sprite.getGlobalBounds();

    for (size_t i = 0; i < mapSFML.size() - 1; i ++) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if (charact.intersects(g))
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
        return (1);
    }
    return (0);
}

void Ennemi::goLeft(void) {
    if (_sprite.getScale().x < 0) {
        this->_sprite.setScale(sf::Vector2f(2, 2));
        this->movePosition(-95, 0);
    } if (getTimeDiff(0.06) == 1) {
        _anim ++;
        if (_anim > 5) {
            _anim = 0;
            _sprite.setTextureRect(sf::IntRect(315, 10, 45, 80));
        } else {
            _sprite.setTextureRect(sf::IntRect(315 + (_anim * 48), 10, 45, 80));
        }
    }
    this->movePosition(-10, 0);
}

void Ennemi::goRight(void) {
    if (_sprite.getScale().x > 0) {
        this->_sprite.setScale(sf::Vector2f(-2, 2));
        this->movePosition(95, 0);
    } if (getTimeDiff(0.06) == 1) {
        _anim ++;
        if (_anim > 5) {
            _anim = 0;
            _sprite.setTextureRect(sf::IntRect(315, 10, 45, 80));
        } else {
            _sprite.setTextureRect(sf::IntRect(315 + (_anim * 48), 10, 45, 80));
        }
    }
    this->movePosition(10, 0);
}

void Ennemi::movePosition(int x, int y) {
    _pos = sf::Vector2f(_pos.x + x, _pos.y + y);
    _sprite.setPosition(_pos);
}

void Ennemi::movePosition(sf::Vector2f pos) {
    _pos = sf::Vector2f(_pos.x + pos.x, _pos.y + pos.y);
    _sprite.setPosition(_pos);
}

void Ennemi::setPosition(sf::Vector2f pos) {
    _pos = pos;
    _sprite.setPosition(_pos);
}

void Ennemi::setPosition(int x, int y) {
    _pos = sf::Vector2f(x, y);
    _sprite.setPosition(_pos);
}

sf::Vector2f Ennemi::getPosition(void) {return _pos;}
sf::Vector2f Ennemi::getSize(void) const {return _size;}
sf::Texture *Ennemi::getTexture(void) {return _texture;}
sf::Sprite Ennemi::getSprite(void) const {return (_sprite);}
