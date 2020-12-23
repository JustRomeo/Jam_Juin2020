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

using namespace std;
class Battery {
    public:
        Battery(int type, int max_mun);
        ~Battery();

        int getMun();
        int incMun();
        int decMun();
        int getType();
        int getMaxMun();
        void incMaxMun();
        void channeling();
        int reloadBattery();
        int getTimeDiff(float diff);
        void display(shared_ptr<sf::RenderWindow> window, sf::Vector2f pos);

    protected:
    private:
        int mun;
        int type;
        int max_mun;
        sf::Clock reload;
        float reload_time;
        sf::Sprite sprite_b;
        shared_ptr<sf::Texture> texture;
        vector<sf::RectangleShape> munShape;
};

#endif
