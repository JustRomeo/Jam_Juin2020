#ifndef __IMAGE__
#define __IMAGE__

#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
class ImageSFML {
    public:
        ImageSFML(string filepath);
        ImageSFML();
        ~ImageSFML();
        ImageSFML &operator=(const ImageSFML &to_cmp);

        void setRotate(float);
        void setTexture(string);
        void destroyTexture(void);
        bool isClicked(sf::Event);
        void setScale(sf::Vector2f);
        sf::Sprite getSprite() const;
        void setPosition(sf::Vector2f);
        shared_ptr<sf::Texture> getTexture(void);
        bool isClickedinView(sf::Event event, sf::View view);

    private:
        size_t _width;
        size_t _heigh;
        sf::Vector2f _pos;
        sf::Sprite _sprite;
        shared_ptr<sf::Texture> _texture;
};

#endif
