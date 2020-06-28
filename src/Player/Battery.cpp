/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Battery
*/

#include "Battery.hpp"

Battery::Battery(int _type)
{
    int x = 150;
    int y = 980;
    type = _type;
    mun = 5;
    for (int i = 0; i < 5; i++) {
        munShape.push_back(sf::RectangleShape(sf::Vector2f(20, 40)));
        munShape[i].setOutlineColor(sf::Color::Black);
        if (_type == 1)
            munShape[i].setFillColor(sf::Color::Yellow);
        if (_type == 2)
            munShape[i].setFillColor(sf::Color::Blue);
        if (_type == 3)
            munShape[i].setFillColor(sf::Color::Magenta);
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

void Battery::display(std::shared_ptr<sf::RenderWindow> window)
{
    sf::View view = window->getView();
    sf::RectangleShape hudBack = sf::RectangleShape(sf::Vector2f(250, 150));
    sf::RectangleShape emptyMun = sf::RectangleShape(sf::Vector2f(20, 40));
    int x = 20;

    emptyMun.setOutlineColor(sf::Color::Black);
    emptyMun.setFillColor(sf::Color::White);
    hudBack.setFillColor(sf::Color::Black);
    emptyMun.setOutlineThickness(2);
    hudBack.setPosition(view.getCenter().x - 935 + x, view.getCenter().y + 370);
    window->draw(hudBack);
    for (int i = 0; i < mun; i++) {
        munShape[i].setPosition(view.getCenter().x - 900 + x, view.getCenter().y + 450);
        window->draw(munShape[i]);
        x+= 20;
    }
    if (mun < 5) {
        for (int i = mun; i < 5; i++) {
            emptyMun.setPosition(view.getCenter().x - 900 + x, view.getCenter().y + 450);
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
    if (mun < 5) {
        mun++;
        return (1);
    }
    return (0);
}

int Battery::decMun()
{
    if (mun > 0) {
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
    if (getTimeDiff(5) == 1) {
        return (incMun());
    }
    return (0);
}

void Battery::channeling()
{
    mun = 0;
}