/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Battery
*/

#include "Battery.hpp"

Battery::Battery(int _type, int _max_mun)
{
    int x = 150;
    int y = 980;
    type = _type;
    mun = _max_mun;
    max_mun = _max_mun;
    reload_time = 5;
    for (int i = 0; i < 5; i++) {
        munShape.push_back(sf::RectangleShape(sf::Vector2f(20, 40)));
        munShape[i].setOutlineColor(sf::Color::Black);
        if (_type == 1)
            munShape[i].setFillColor(sf::Color::Yellow);
        if (_type == 2)
            munShape[i].setFillColor(sf::Color::Blue);
        if (_type == 3)
            munShape[i].setFillColor(sf::Color::Magenta);
        if (_type == 4) {
            munShape[i].setFillColor(sf::Color::Green);
            reload_time = 10;
        }
        munShape[i].setOutlineThickness(2);
        munShape[i].setPosition(x, y);
        x += 20;
    }
}

Battery::~Battery()
{
}

int Battery::getTimeDiff(float diff)
{
    sf::Time time;
    float seconds = 0;

    time = reload.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > diff) {
        reload.restart();
        return (1);
    }
    return (0);
}

void Battery::display(std::shared_ptr<sf::RenderWindow> window, sf::Vector2f pos)
{
    sf::View view = window->getView();
    sf::RectangleShape emptyMun = sf::RectangleShape(sf::Vector2f(20, 40));
    int x = 20;

    emptyMun.setOutlineColor(sf::Color::Black);
    emptyMun.setFillColor(sf::Color::White);
    emptyMun.setOutlineThickness(2);
    for (int i = 0; i < mun; i++) {
        munShape[i].setPosition(pos.x + x, pos.y);
        window->draw(munShape[i]);
        x+= 20;
    }
    if (mun < max_mun) {
        for (int i = mun; i < max_mun; i++) {
            emptyMun.setPosition(pos.x + x, pos.y);
            window->draw(emptyMun);
            x+= 20;
        }
    }
}

int Battery::getMun()
{
    return (mun);
}
int Battery::incMun()
{
    if (mun < max_mun) {
        mun++;
        return (1);
    }
    return (0);
}

int Battery::decMun()
{
    if (mun > 0) {
        reload.restart();
        mun--;
        return (1);
    }
    return (0);
}

int Battery::getType()
{
    return (type);
}

int Battery::reloadBattery()
{
    if (getTimeDiff(reload_time) == 1) {
        return (incMun());
    }
    return (0);
}

void Battery::channeling()
{
    mun = 0;
}

int Battery::getMaxMun()
{
    return (max_mun);
}

void Battery::incMaxMun()
{
    max_mun++;
}