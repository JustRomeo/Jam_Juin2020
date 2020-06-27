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
        ~ImageSFML();

        void destroyTexture();
        sf::Sprite getSprite() const;
        bool isClicked(sf::Event event);
        void setTexture(string filepath);
        void setScale(sf::Vector2f size);
        void setPosition(sf::Vector2f pos);

    private:
        size_t _width;
        size_t _heigh;
        sf::Vector2f _pos;
        sf::Sprite _sprite;
        sf::Texture *_texture;
};

#endif