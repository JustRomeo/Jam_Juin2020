/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** HUD
*/

#include "HUD.hpp"

HUD::HUD() {
    for (size_t i = 1; i < 5; i ++)
        battery.push_back(std::make_shared<Battery>(i, 3));
    for (size_t i = 0; i < 3; i ++) {
        heart.push_back(std::make_shared<ImageSFML>("resources/Images/Hud/heart.png"));
        heart[i]->setScale(sf::Vector2f(0.25, 0.25));
    }
    weapon_type = 1;
}
HUD::~HUD() {}

void HUD::display(std::shared_ptr<sf::RenderWindow> window, int weapon_type, int life, size_t lvl) {
    int x = 800;
    int x1 = 20;
    sf::Font font;
    sf::Text text1;
    sf::Text text2;
    sf::Text lvltxt;
    sf::RectangleShape hudBack = sf::RectangleShape(sf::Vector2f(500, 200));

    if (font.loadFromFile("./resources/character/arial.ttf") == false)
        throw(Exception("can't load police.ttf"));

    text2.setFont(font);
    text2.setString("Next:");
    text2.setCharacterSize(30);
    text2.setStyle(sf::Text::Bold);
    text2.setPosition(window->getView().getCenter().x - 700 + x1, window->getView().getCenter().y + 450);

    text1.setFont(font);
    text1.setString("Ammo:");
    text1.setCharacterSize(30);
    text1.setStyle(sf::Text::Bold);
    text1.setPosition(window->getView().getCenter().x - 915 + x1, window->getView().getCenter().y + 450);

    lvltxt.setFont(font);
    lvltxt.setString("lvl: " + to_string(lvl));
    lvltxt.setCharacterSize(30);
    lvltxt.setStyle(sf::Text::Bold);
    lvltxt.setPosition(window->getView().getCenter().x - 915 + x1, window->getView().getCenter().y + 325);

    hudBack.setFillColor(sf::Color::Black);
    hudBack.setPosition(window->getView().getCenter().x - 935 + x1, window->getView().getCenter().y + 300);
    window->draw(hudBack);
    window->draw(text1);
    window->draw(text2);
    window->draw(lvltxt);

    battery[weapon_type - 1]->reloadBattery();
    battery[weapon_type - 1]->display(window, {window->getView().getCenter().x - 800, window->getView().getCenter().y + 450});

    if (weapon_type < 4)
        battery[weapon_type]->display(window, {window->getView().getCenter().x - 600, window->getView().getCenter().y + 450});
    else
        battery[0]->display(window, {window->getView().getCenter().x - 600, window->getView().getCenter().y + 450});
    sf::Vector2f viewpos = window->getView().getCenter();
    for (size_t i = 0; i < life; i ++) {
        heart[i]->setPosition(sf::Vector2f(viewpos.x - x + 100, viewpos.y + 310));
        window->draw(heart[i]->getSprite());
        x += 50;
    }
}

void HUD::displaySprintBar(std::shared_ptr<sf::RenderWindow> window, int sprintBar) {
    shared_ptr<sf::RectangleShape> back = make_shared<sf::RectangleShape>();
    shared_ptr<sf::RectangleShape> front = make_shared<sf::RectangleShape>();

    back->setSize({210, 50});
    back->setFillColor(sf::Color::White);
    back->setPosition(window->getView().getCenter().x - 890, window->getView().getCenter().y + 380);
    back->setOutlineColor(sf::Color::Magenta);
    front->setSize(sf::Vector2f(sprintBar * 200 / 100, 45));
    front->setFillColor(sf::Color::Yellow);
    front->setPosition(window->getView().getCenter().x - 885, window->getView().getCenter().y + 382);
    window->draw(*back);
    window->draw(*front);
}

void HUD::incWeaponType() {
    weapon_type ++;
    if (weapon_type > 4)
        weapon_type = 1;
}

void HUD::incMun(int batteryNb) {battery[batteryNb]->incMaxMun();}
int HUD::getMunBattery() {return (battery[weapon_type -1]->getMun());}
int HUD::decBatteryMun() {return (battery[weapon_type - 1]->decMun());}
void HUD::batteryChanneling() {battery[weapon_type - 1]->channeling();}
