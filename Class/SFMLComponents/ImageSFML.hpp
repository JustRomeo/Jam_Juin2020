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
        sf::Sprite getSprite();
        void setTexture(string);
        void destroyTexture(void);
        bool isClicked(sf::Event);
        void setScale(sf::Vector2f);
        void update(sf::Event event);
        void setPosition(sf::Vector2f);
        bool isMouseOnImage(void) const;
        void setSprite(sf::Sprite newone);
        void setSprite(sf::Texture newtexture);
        shared_ptr<sf::Texture> getTexture(void);
        void loadAsButton(string visual, string click);
        bool isClickedinView(sf::Event event, sf::View view);
        void loadAsButton(sf::Texture visual, sf::Texture click);

    private:
        bool isButton;
        size_t _width;
        size_t _heigh;
        sf::Vector2f _pos;
        sf::Sprite _sprite;
        shared_ptr<sf::Texture> texture_mouseon;
        shared_ptr<sf::Texture> texture_clicked;
        shared_ptr<sf::Texture> _texture;
};

#endif
