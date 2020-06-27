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
        background = std::make_shared<Sprite>("resources/Images/space.png");
        perso = std::make_shared<Character>();
        window->setView(*view);
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
    window->display();
}

int GameLoop::checkOpen()
{
    return window->isOpen();
}

#include "Echap.hpp"
int GameLoop::getEvent(std::vector<std::shared_ptr<Block>> mapSFML) {
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return -1;
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && perso->isShooting() == false) {
        perso->jump();
        return 0;
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && perso->isShooting() == false) {
        perso->moveLeft(window, mapSFML);
        return 0;
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && perso->isShooting() == false) {
        return 0;
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& perso->isShooting() == false) {
        perso->moveRigth(window, mapSFML);
        return 0;
    } if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        perso->shoot();
        return 0;
    } if (perso->isShooting() == false && perso->isJumping() == false && perso->isFalling() == false) {
        perso->restartPos();
        window->setView(window->getView());
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        switch (EchapMenu().Menu(*window)) {
            case -1: return -1; // Quit
            case 0:  return 0;  // resume
            case 1:  return 1;  // replay
            case 2:  return 2;  // back
            default: throw (Exception("Error: Menu Failed: Abort"));  // nothing
        }
        return 1;
    }
    return 0;
}

enum CHOICE {QUIT = 0, REPLAY = 1};
int GameLoop::gameLoop(vector<shared_ptr<Block>> mapSFML, Door door, vector<shared_ptr<Ennemi>> Ennemilist) {
    if (!MainMenu().Menu(*window))
       return QUIT;
    window->setFramerateLimit(40);
    view->setCenter(perso->getSprite().getPosition());
    window->setView(*view);
    while (window->isOpen()) {
        for (size_t i = 0; i < mapSFML.size(); i ++)
            window->draw(mapSFML[i]->getSprite());
        for (size_t i = 0; i < Ennemilist.size(); i ++) {
            window->draw(Ennemilist[i]->getSprite());
            Ennemilist[i]->move(mapSFML);
        }
        perso->display(window, mapSFML);
        window->draw(door.getSprite());
        display();
        clear();
        try {
            switch(getEvent(mapSFML)) {
                case -1: window->close(); break;
                case 0:  continue;        break;
                case 2:  return REPLAY;   break;
            }
        } catch (Exception &e) {
            throw e;
        }
    }
    return QUIT;
}