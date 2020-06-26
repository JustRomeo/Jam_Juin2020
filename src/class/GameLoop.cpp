/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GameLoop
*/

#include "GameLoop.hpp"

GameLoop::GameLoop() {
    try {
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "graphical interface");
        window->setFramerateLimit(40);
        view = std::make_shared<sf::View>(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
        window->setView(*view);
        background = std::make_shared<Sprite>("resources/Images/space.png");
    } catch (std::bad_alloc &e) {
        throw (Exception("can't initiate window and view\n"));
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
    window->display();
    window->draw(background->getSprite());
}

int GameLoop::checkOpen()
{
    return (window->isOpen());
}

int GameLoop::getEvent()
{
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.key.code == sf::Keyboard::Key::Z)
            view->move(sf::Vector2f(0.f, -10.f));
        if (event.key.code == sf::Keyboard::Key::Q)
            view->move(sf::Vector2f(-10.f, 0.f));
        if (event.key.code == sf::Keyboard::Key::S)
            view->move(sf::Vector2f(0.f, 10.f));
        if (event.key.code == sf::Keyboard::Key::D)
            view->move(sf::Vector2f(10.f, 0.f));
        window->setView(*view);
        if (event.type == sf::Event::Closed) {
            window->close();
            return (-1);
        }
    }
    return (0);
}

#include "MainMenu.hpp"
int GameLoop::gameLoop(vector<shared_ptr<Block>> mapSFML)
{
    if (!MainMenu().Menu(*window))
        return 0;
    while (window->isOpen()) {
        size_t i = 0;

        getEvent();
        for (; i < mapSFML.size(); i ++)
            window->draw(mapSFML[i]->getSprite());
        display();
        clear();
    }
    return (0);
}