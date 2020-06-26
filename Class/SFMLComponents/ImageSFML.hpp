#ifndef __IMAGE__
#define __IMAGE__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
class ImageSFML {
    public:
        ImageSFML(string filepath);
        ~ImageSFML() {}

        bool isClicked(sf::Event event);
        void destroyTexture();
        void setTexture(string filepath);
        sf::Sprite getSprite() const {return (_sprite);}
        void setPosition(sf::Vector2f pos) {_sprite.setPosition(pos);}

    private:
        sf::Sprite _sprite;
        sf::Texture *_texture;
};

#endif
