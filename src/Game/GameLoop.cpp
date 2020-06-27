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
    for (int i = 0; i < projectile.size(); i++) {
        projectile[i]->display(window);
    }
    window->display();
}

int GameLoop::checkOpen()
{
    return (window->isOpen());
}

int GameLoop::getEvent(std::vector<std::shared_ptr<Block>> mapSFML)
{
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            return (-1);
        }
        if (event.type == sf::Event::MouseButtonReleased && 
            perso->isShooting() == false && perso->isJumping() == false && perso->isFalling() == false && perso->isChanneling() == false) {
            perso->shoot();
            if (perso->getSprite().getScale().x > 0)
                projectile.push_back(std::make_shared<Projectile>(3, 1, perso->getSprite().getPosition()));
            else
                projectile.push_back(std::make_shared<Projectile>(3, -1, perso->getSprite().getPosition()));
            return (1);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && perso->isShooting() == false && perso->isChanneling() == false) {
        perso->jump();
        return (1);
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && perso->isShooting() == false && perso->isChanneling() == false) {
        perso->moveLeft(window, mapSFML);
        return (1);
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && perso->isShooting() == false && perso->isChanneling() == false) {
        return (1);
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& perso->isShooting() == false && perso->isChanneling() == false) {
        perso->moveRigth(window, mapSFML);
        return (1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && perso->isShooting() == false 
        && perso->isJumping() == false && perso->isFalling() == false ) {
        perso->channeling();
        return (1);
    }
    if (perso->isShooting() == false && perso->isJumping() == false && perso->isFalling() == false && perso->isChanneling() == false) {
        perso->restartPos();
        window->setView(window->getView());
    }
    return (0);
}

int GameLoop::gameLoop(vector<shared_ptr<Block>> mapSFML, Door door, vector<shared_ptr<Ennemi>> Ennemilist)
{
    size_t loop = 0;

    // if (!MainMenu().Menu(*window))
    //    return 0;
    window->setFramerateLimit(40);
    view->setCenter(perso->getSprite().getPosition());
    window->setView(*view);
    while (window->isOpen()) {
        //door.doorOpen();
        for (size_t i = 0; i < mapSFML.size(); i ++)
            window->draw(mapSFML[i]->getSprite());
        for (size_t i = 0; i < Ennemilist.size(); i ++)
            window->draw(Ennemilist[i]->getSprite());
        if (loop < 300)
            Ennemilist[0]->goLeft();
        else
            Ennemilist[0]->goRight();
        if (loop > 600)
            loop = 0;
        perso->display(window, mapSFML);
        window->draw(door.getSprite());
        display();
        clear();
        getEvent(mapSFML);
        loop ++;
    }
    return (0);
}