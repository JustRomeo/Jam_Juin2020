#include "Door.hpp"

Door::Door(int X, int Y) {
    alreadyopen = false;
    _anim = 0;
    _opening = false;
    move_clock.restart();
    _texture = new sf::Texture;
    pos = sf::Vector2f(X, Y);
    try {
        this->setTexture("resources/Images/Door.png");
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
    this->_sprite.setPosition(pos);
    this->_sprite.setScale(sf::Vector2f(1, 1));
    _size = this->getSize();
}
Door::Door(vector<string> map) {
    alreadyopen = false;
    _texture = new sf::Texture;
    pos = sf::Vector2f(0, 0);
    _anim = 0;
    try {
        this->setTexture("resources/Images/Door.png");
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
    this->setPosition(map);
    this->_sprite.setScale(sf::Vector2f((float) 157 / 260, (float)157 / 375));
    _size = this->getSize();
}
Door::~Door() {}

void Door::setTexture(string filepath) {
    if (!_texture->loadFromFile(filepath))
        throw (Exception("Loading Ressource Failed"));
    _sprite.setTexture(*_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, 260, 375));
}

void Door::setPosition(vector<string> map) {
    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++)
            if (map[i][j] == 'o')
                this->setPosition(sf::Vector2f(j * 157, i * 157));
}

void Door::doorOpen(void) {
    if (!_opening)
        return;
    if (getTimeDiff(0.3) == 1 && _anim < 5) {
        _anim ++;
        _sprite.setTextureRect(sf::IntRect(_anim * 267, 0, 267, 375));
        _sprite.setScale(sf::Vector2f((float) 157 / 260, (float)157 / 375));
    }
}

int Door::getTimeDiff(float diff) {
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

void Door::setPosition(sf::Vector2f pos) {
    this->pos = pos;
    _sprite.setPosition(this->pos);
}

int Door::getAnim() {return _anim;}
size_t Door::getSize(void) const {return _size;}
void Door::setOpening(bool var) {_opening = var;}
sf::Vector2f Door::getPosition(void) {return pos;}
sf::Texture *Door::getTexture(void) {return _texture;}
sf::Sprite Door::getSprite(void) const {return (_sprite);}
