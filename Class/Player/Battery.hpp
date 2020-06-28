/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Battery
*/

#ifndef BATTERY_HPP_
#define BATTERY_HPP_

#include "../include/LibGraphics.hpp"
#include "Exception.hpp"

class Battery {
    public:
        Battery(int type);
        ~Battery();
        void display(std::shared_ptr<sf::RenderWindow> window);
        int getMun();
        int incMun();
        int decMun();
        int getType();
        int getTimeDiff(float diff);
        int reloadBattery();

    protected:
    private:
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite_b;
        std::vector<sf::RectangleShape> munShape;
        sf::Clock reload;
        int mun;
        int type;
};

#endif /* !BATTERY_HPP_ */
