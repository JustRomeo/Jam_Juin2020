#include "../include/LibGraphics.hpp"

class Block {
    public:
        Block();
        ~Block();

        sf::Sprite getSprite() const;
        sf::Texture *getTexture(void);
        sf::Vector2f getPosition(void);
        void setTexture(std::string filepath);
        void setPosition(sf::Vector2f pos);

    private:
        sf::Vector2f pos;
        sf::Sprite _sprite;
        sf::Texture *_texture;
};