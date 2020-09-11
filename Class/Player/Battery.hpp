/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Battery
*/

#ifndef BATTERY_HPP_
#define BATTERY_HPP_

#include "../include/LibGraphics.hpp"
#include "Exception.hpp"

class Battery {
    public:
        Battery(int type, int max_mun);
        ~Battery();
        void display(std::shared_ptr<sf::RenderWindow> window, sf::Vector2f pos);
        int getMun();
        int incMun();
        int decMun();
        int getType();
        int getTimeDiff(float diff);
        int reloadBattery();
        int getMaxMun();
        void incMaxMun();
        void channeling();
    protected:
    private:
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite_b;
        std::vector<sf::RectangleShape> munShape;
        sf::Clock reload;
        int mun;
        int type;
        int max_mun;
        float reload_time;
};

#endif /* !BATTERY_HPP_ */
