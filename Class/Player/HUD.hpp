/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** HUD
*/

#ifndef HUD_HPP_
#define HUD_HPP_

#include "ImageSFML.hpp"
#include "Battery.hpp"
#include <memory>

using namespace std;
class HUD {
    public:
        HUD();
        ~HUD();

        int getMunBattery();
        int decBatteryMun();
        void incWeaponType();
        void batteryChanneling();
        void incMun(int batteryNb);
        void displaySprintBar(shared_ptr<sf::RenderWindow> window, int sprintBar);
        void display(shared_ptr<sf::RenderWindow> window, int weapon_type, int life);

    protected:
    private:
        int nbHeart;
        int weapon_type;
        vector<shared_ptr<ImageSFML>> heart;
        vector<shared_ptr<Battery>> battery;
};

#endif
