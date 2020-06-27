/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GameLoop
*/

#include "Door.hpp"
#include "GameLoop.hpp"
#include "MainMenu.hpp"

GameLoop::GameLoop()
{
    try {
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "graphical interface");
        window->setFramerateLimit(60);
        view = std::make_shared<sf::View>(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
        window->setView(*view);
        background = std::make_shared<Sprite>("resources/Images/space.png");
        perso = std::make_shared<Character>();
    } catch (std::bad_alloc &e) {
        throw(Exception("can't initiate window and view\n"));
    }
}

GameLoop::~GameLoop()
{
}

void GameLoop::clear()
{
    window->clear(sf::Color::White);
}

void GameLoop::display()
{
    perso->display(window);
    window->display();
}

int GameLoop::checkOpen()
{
    return (window->isOpen());
}

int GameLoop::getEvent()
{
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            return (-1);
        }
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && perso->isShooting() == false) {
        view->move(sf::Vector2f(0.f, -10.f));
        window->setView(*view);
        return (1);
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && perso->isShooting() == false) {
        view->move(sf::Vector2f(-10.f, 0.f));
        perso->moveLeft();
        window->setView(*view);
        return (1);
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && perso->isShooting() == false) {
        view->move(sf::Vector2f(0.f, 10.f));
        window->setView(*view);
        return (1);
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& perso->isShooting() == false) {
        view->move(sf::Vector2f(10.f, 0.f));
        perso->moveRigth();
        window->setView(*view);
        return (1);
    } if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        perso->shoot();
        return (1);
    }
    window->setView(*view);
    if (perso->isShooting() == false)
        perso->restartPos();
    return (0);
}

int GameLoop::gameLoop(vector<shared_ptr<Block>> mapSFML, Door door)
{
    if (!MainMenu().Menu(*window))
        return 0;
    while (window->isOpen()) {
        door.doorOpen();
        getEvent();
        for (size_t i = 0; i < mapSFML.size(); i ++)
            window->draw(mapSFML[i]->getSprite());
        window->draw(door.getSprite());
        display();
        clear();
    }
    return (0);
}