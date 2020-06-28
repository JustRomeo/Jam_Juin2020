/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** MunPlus
*/

#ifndef MUNPLUS_HPP_
#define MUNPLUS_HPP_

#include "../include/LibGraphics.hpp"
#include "Exception.hpp"

class MunPlus {
    public:
        MunPlus(int type, int x, int y);
        ~MunPlus();
        void display(std::shared_ptr<sf::RenderWindow> window);
        sf::FloatRect getMunShape();
        int getType() {
            return (type);
        }

    protected:
    private:
        sf::RectangleShape munShape;
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        int mun;
        int type;
        int max_mun;
};

#endif /* !MUNPLUS_HPP_ */
