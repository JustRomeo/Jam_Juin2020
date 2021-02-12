#include "Lootable.hpp"
#include "Exception.hpp"

Lootable::Lootable(TYPE type, string name, size_t x, size_t y, string path) {
    _type = type;
    _pos = sf::Vector2f(x, y);
    _objet = make_shared<Objet>(name, 0);
    if (path == "")
        _image = make_shared<ImageSFML>("resources/Images/Game/Object/bonus.png");
    else
        _image = make_shared<ImageSFML>(path);

    _image->setPosition(sf::Vector2f(x + 60, y + 60));
    _image->setScale(sf::Vector2f(0.1, 0.1));
}
Lootable::~Lootable() {}

shared_ptr<Objet> Lootable::getObject(void) const {
    if (_type != Object)
        throw Exception("Not the good lootable type.");
    return _objet;
}

void Lootable::setPosition(sf::Vector2f pos) {_pos = pos;}
void Lootable::setFilepath(string path) {_filepath = path;}
string Lootable::getFilepath(void) const {return _filepath;}
sf::Vector2f Lootable::getPosition(void) const {return _pos;}
shared_ptr<ImageSFML> Lootable::getImage(void) const {return _image;}
void Lootable::setPosition(float x, float y) {_pos = sf::Vector2f(x, y);}