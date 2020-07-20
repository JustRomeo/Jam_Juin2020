/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** HUD
*/

#include "HUD.hpp"

HUD::HUD() {
    for (int i = 1; i < 4; i ++)
        battery.push_back(std::make_shared<Battery>(i, 3));
    for (int i = 0; i < 3; i ++) {
        heart.push_back(std::make_shared<ImageSFML>("resources/Images/Hud/heart.png"));
        heart[i]->setScale(sf::Vector2f(0.25, 0.25));
    }
    weapon_type = 1;
}

HUD::~HUD() {}

void HUD::display(std::shared_ptr<sf::RenderWindow> window, int weapon_type, int life) {
    int x = 800;

    battery[weapon_type - 1]->reloadBattery();
    battery[weapon_type - 1]->display(window);
    for (int i = 0; i < life; i ++) {
        heart[i]->setPosition(sf::Vector2f(window->getView().getCenter().x - x,
            window->getView().getCenter().y + 370));
        window->draw(heart[i]->getSprite());
        x+= 50;
    }
}

void HUD::incWeaponType() {
    weapon_type ++;
    if (weapon_type > 3)
        weapon_type = 1;
}

void HUD::incMun(int batteryNb) {battery[batteryNb]->incMaxMun();}
int HUD::getMunBattery() {return (battery[weapon_type -1]->getMun());}
int HUD::decBatteryMun() {return (battery[weapon_type -1]->decMun());}
void HUD::batteryChanneling() {battery[weapon_type - 1]->channeling();}