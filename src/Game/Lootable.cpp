#include "Lootable.hpp"
#include "Exception.hpp"

Lootable::Lootable(shared_ptr<Lootable> &loot) {
    life = loot->getLife();
    _name = loot->getName();
    speed = loot->getSpeed();

    _type = loot->getType();
    _pos = loot->getPosition();
    _objet = make_shared<Objet>(_name, 0);

    _filepath = loot->getFilepath();
    if (_filepath == "")
        _image = make_shared<ImageSFML>("resources/Images/Game/Object/bonus.png");
    else
        _image = make_shared<ImageSFML>(_filepath);

    _image->setPosition(sf::Vector2f(_pos.x + 60, _pos.y + 60));
    _image->setScale(sf::Vector2f(0.1, 0.1));
}

Lootable::Lootable(TYPE type, string name, size_t x, size_t y, string path) {
    life = 0;
    speed = 0;

    _name = name;
    _type = type;
    _filepath = path;
    _pos = sf::Vector2f(x, y);
    _objet = make_shared<Objet>(_name, 0);
    if (path == "")
        _image = make_shared<ImageSFML>("resources/Images/Game/Object/bonus.png");
    else
        _image = make_shared<ImageSFML>(path);

    _image->setPosition(sf::Vector2f(x + 60, y + 60));
    _image->setScale(sf::Vector2f(0.1, 0.1));
}
Lootable::~Lootable() {}

Lootable &Lootable::operator=(Lootable &loot) {
    life = loot.getLife();
    _name = loot.getName();
    speed = loot.getSpeed();

    _type = loot.getType();
    _pos = loot.getPosition();
    _objet = make_shared<Objet>(_name, 0);

    _filepath = loot.getFilepath();
    if (_filepath == "")
        _image = make_shared<ImageSFML>("resources/Images/Game/Object/bonus.png");
    else
        _image = make_shared<ImageSFML>(_filepath);

    _image->setPosition(sf::Vector2f(_pos.x + 60, _pos.y + 60));
    _image->setScale(sf::Vector2f(0.1, 0.1));
    return *this;
}

shared_ptr<Objet> Lootable::getObject(void) const {
    if (_type != Object)
        throw Exception("Not the good lootable type.");
    return _objet;
}

size_t Lootable::getLife(void) const {return life;}
string Lootable::getName(void) const {return _name;}
void Lootable::setLife(size_t value) {life = value;}
void Lootable::setName(string value) {_name = value;}
size_t Lootable::getSpeed(void) const {return speed;}
void Lootable::setSpeed(size_t value) {speed = value;}
void Lootable::setFilepath(string path) {_filepath = path;}
Lootable::TYPE Lootable::getType(void) const {return _type;}
string Lootable::getFilepath(void) const {return _filepath;}
sf::Vector2f Lootable::getPosition(void) const {return _pos;}
void Lootable::setPosition(sf::Vector2f value) {_pos = value;}
void Lootable::setType(Lootable::TYPE newone) {_type = newone;}
shared_ptr<Objet> Lootable::getObjet(void) const {return _objet;}
void Lootable::setObjet(shared_ptr<Objet> value) {_objet = value;}
shared_ptr<ImageSFML> Lootable::getImage(void) const {return _image;}
void Lootable::setPosition(float x, float y) {_pos = sf::Vector2f(x, y);}