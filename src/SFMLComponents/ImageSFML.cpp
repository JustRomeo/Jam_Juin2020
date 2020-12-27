#include <iostream>

#include "Exception.hpp"
#include "ImageSFML.hpp"

using namespace std;
ImageSFML::ImageSFML(string path) {
    try {
        _width = 0;
        _heigh = 0;
        _pos = sf::Vector2f(0, 0);
        _texture = make_shared<sf::Texture>();

        isButton = false;
        if (!_texture->loadFromFile(path))
            throw Exception("Loading Ressource Failed");
        _sprite.setTexture(*_texture);
        _width = _sprite.getTexture()->getSize().x;
        _heigh = _sprite.getTexture()->getSize().y;
    } catch (Exception &e) {
        cout << "Texture: " << *e.what() << endl;
    }
}
ImageSFML::ImageSFML() {}
ImageSFML::~ImageSFML() {}
ImageSFML &ImageSFML::operator=(const ImageSFML &to_cmp) {
    _width = to_cmp._width;
    _heigh = to_cmp._heigh;
    _pos = to_cmp._pos;
    _sprite = to_cmp._sprite;
    _texture = to_cmp._texture;
    _sprite.setTexture(*_texture);
    _width = _sprite.getTexture()->getSize().x;
    _heigh = _sprite.getTexture()->getSize().y;
    return (*this);
}

void ImageSFML::loadAsButton(sf::Texture visual, sf::Texture click) {
    texture_mouseon = make_shared<sf::Texture>(visual);
    texture_clicked = make_shared<sf::Texture>(click);

    isButton = true;
}

void ImageSFML::loadAsButton(string visual, string click) {
    texture_mouseon = make_shared<sf::Texture>();
    texture_clicked = make_shared<sf::Texture>();

    if (!texture_mouseon->loadFromFile(visual.c_str()))
        throw Exception("Visual initialisation mouse movement failed");
    if (!texture_clicked->loadFromFile(click.c_str()))
        throw Exception("Visual initialisation click failed");
    isButton = true;
}

void ImageSFML::update(sf::Event event) {
    if (!isButton)
        return;
    try {
        if (isMouseOnImage())
            setSprite(*texture_mouseon);
        else if (isClicked(event))
            setSprite(*texture_clicked);
        else
            setSprite(*_texture);
    } catch (Exception &e) {
        cout << "Texture: " << *e.what() << endl;
    }
}

bool ImageSFML::isClicked(sf::Event event) {
    sf::Vector2i mouse(sf::Mouse::getPosition());

    mouse.y -= 65;
    if (event.type == sf::Event::MouseButtonPressed)
        if ((mouse.y > _pos.y && mouse.y < _pos.y + _heigh) && (mouse.x > _pos.x && mouse.x < _pos.x + _width))
            return true;
    return false;
}

bool ImageSFML::isClickedinView(sf::Event event, sf::View view) {
    sf::Vector2i mouse(sf::Mouse::getPosition());
    sf::Vector2i _view(view.getCenter().x - (1920 / 2), view.getCenter().y - (1080 / 2));

    mouse.y -= 65;
    if (event.type == sf::Event::MouseButtonPressed)
        if ((mouse.y + _view.y > _pos.y && mouse.y + _view.y < _pos.y + _heigh) && (mouse.x + _view.x > _pos.x && mouse.x + _view.x < _pos.x + _width))
            return true;
    return false;
}

void ImageSFML::setTexture(string path) {
    if (!_texture->loadFromFile(path))
        throw Exception("Loading Ressource Failed");
    _sprite.setTexture(*_texture);
}


void ImageSFML::setPosition(sf::Vector2f pos) {
    _pos = pos;
    _sprite.setPosition(pos);
}

bool ImageSFML::isMouseOnImage(void) const {
    sf::Vector2i mouse(sf::Mouse::getPosition());

    mouse.y -= 65;
    if ((mouse.y > _pos.y && mouse.y < _pos.y + _heigh) && (mouse.x > _pos.x && mouse.x < _pos.x + _width))
        return true;
    return false;
}

sf::Sprite ImageSFML::getSprite(void) {return (_sprite);}
void ImageSFML::setSprite(sf::Sprite newone) {_sprite = newone;}
void ImageSFML::setRotate(float angle) {_sprite.setRotation(angle);}
void ImageSFML::setScale(sf::Vector2f size) {_sprite.setScale(size);}
shared_ptr<sf::Texture> ImageSFML::getTexture(void) {return this->_texture;}
void ImageSFML::setSprite(sf::Texture newtexture) {_sprite.setTexture(newtexture);}
