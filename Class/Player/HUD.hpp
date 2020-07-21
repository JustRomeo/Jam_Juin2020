/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** HUD
*/

#ifndef HUD_HPP_
#define HUD_HPP_

#include "ImageSFML.hpp"
#include "Battery.hpp"
#include <memory>



class HUD {
    public:
        HUD();
        ~HUD();
        void display(std::shared_ptr<sf::RenderWindow> window, int weapon_type, int life);
        int getMunBattery();
        int decBatteryMun();
        void batteryChanneling();
        void incMun(int batteryNb);
        void incWeaponType();
        void displaySprintBar(std::shared_ptr<sf::RenderWindow> window, int sprintBar);

    protected:
    private:
        int nbHeart;
        int weapon_type;
        std::vector<std::shared_ptr<ImageSFML>> heart;
        std::vector<std::shared_ptr<Battery>> battery;
};

#endif /* !HUD_HPP_ */
