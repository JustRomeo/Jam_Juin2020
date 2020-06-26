/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace arcade {
    class Sprite {
        public:
            Sprite();
            ~Sprite();
            void destroyTexture();
            void setTexture(std::string filepath);
            void setPosition(sf::Vector2f pos);
            bool getLoadFailed() const;
            sf::Sprite getSprite() const;

        protected:
        private:
            sf::Texture *_texture;
            sf::Sprite _sprite;
            bool _load_failed;
    };
}

#endif /* !SPRITE_HPP_ */
