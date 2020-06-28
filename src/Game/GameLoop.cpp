/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GameLoop
*/

#include "Door.hpp"
#include "Echap.hpp"
#include "Death.hpp"
#include "GameLoop.hpp"
#include "MainMenu.hpp"
#include "MusicSFML.hpp"

GameLoop::GameLoop()
{
    try {
        death_ennemi = new MusicSFML();
        death_ennemi->load("resources/Sounds/death.ogg");
        death_ennemi->setVolume(50);
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SoundWaves");
        window->setFramerateLimit(60);
        auto image = sf::Image {};
        if (!image.loadFromFile("resources/Images/icon.jpg"))
            throw Exception("Loading Ressource Failed");
        window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
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
    death_ennemi->~MusicSFML();
}

shared_ptr<sf::RenderWindow> GameLoop::getWindow(void) {
    return this->window;
}

void GameLoop::clear()
{
    window->clear(sf::Color::White);
}

void GameLoop::display()
{
    for (int i = 0; i < projectile.size(); i ++)
        projectile[i]->display(window);
    window->display();
}

int GameLoop::checkOpen()
{
    return window->isOpen();
}

void GameLoop::checkDestruction(vector<shared_ptr<Block>> &mapSFML)
{
    int res = -1;

    for (int i = 0; i < projectile.size(); i++) {
        res = -1;
        for (int j = 0; j < mapSFML.size() && res != 0 && res != 1; j++) {
            res = projectile[i]->checkDestruction(mapSFML[j]);
            if (res == 0 || projectile[i]->getCurrentCapacity() <= 0)
                projectile.erase(projectile.begin() + i);
            if (res == 1)
                mapSFML.erase(mapSFML.begin() + j);
        }
    }
}

void GameLoop::checkDeathEnemy(vector<shared_ptr<Ennemi>> &Ennemilist)
{
    int res = -1;

    for (size_t i = 0; i < projectile.size(); i++) {
        res = -1;
        for (size_t j = 0; j < Ennemilist.size() && res != 0 && res != 1; j++) {
            res = projectile[i]->checkKill(Ennemilist[j]);
            if (projectile[i]->getCurrentCapacity() <= 0) {
                death_ennemi->start();
                projectile.erase(projectile.begin() + i);
            } if (res == 1)
                Ennemilist.erase(Ennemilist.begin() + j);
        }
    }
}

int GameLoop::getEvent(std::vector<std::shared_ptr<Block>> mapSFML) {
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            return (-1);
        } if (event.type == sf::Event::MouseButtonReleased &&
            perso->isShooting() == false && perso->isJumping() == false && perso->isFalling() == false && perso->isChanneling() == false && perso->isSwitching() == false) {
            perso->shoot();
            if (perso->getSprite().getScale().x > 0 && perso->getMunBattery() == 1) {
                if (perso->getWeapon() == 1)
                    projectile.push_back(std::make_shared<Projectile>(1, 1, perso->getSprite().getPosition(), 1));
                if (perso->getWeapon() == 2)
                    projectile.push_back(std::make_shared<Projectile>(2, 1, perso->getSprite().getPosition(), 1));
                if (perso->getWeapon() == 3)
                    projectile.push_back(std::make_shared<Projectile>(3, 1, perso->getSprite().getPosition(), 1));
            } else if (perso->getSprite().getScale().x < 0 && perso->getMunBattery() == 1) {
                if (perso->getWeapon() == 1)
                    projectile.push_back(std::make_shared<Projectile>(1, -1, perso->getSprite().getPosition(), 1));
                if (perso->getWeapon() == 2)
                    projectile.push_back(std::make_shared<Projectile>(2, -1, perso->getSprite().getPosition(), 1));
                if (perso->getWeapon() == 3)
                    projectile.push_back(std::make_shared<Projectile>(3, -1, perso->getSprite().getPosition(), 1));
            }
            return (3);
        } if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F) {
            perso->incWeapon();
            return (3);
        } if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R && !perso->isShooting() && !perso->isJumping() && !perso->isFalling() && !perso->isSwitching()) {
            perso->channeling();
            if (perso->getSprite().getScale().x > 0)
                projectile.push_back(std::make_shared<Projectile>(4, 1, perso->getSprite().getPosition(), perso->getMun()));
            if (perso->getSprite().getScale().x < 0)
                projectile.push_back(std::make_shared<Projectile>(4, -1, perso->getSprite().getPosition(), perso->getMun()));
            perso->channelBat();
            return (3);
        }
    } if (!perso->isShooting() && !perso->isChanneling()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            perso->jump();
            return (3);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            perso->moveLeft(window, mapSFML);
            return (3);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return (3);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            perso->moveRigth(window, mapSFML);
            return (3);
        }
    } if (perso->isShooting() == false && perso->isJumping() == false && perso->isFalling() == false && perso->isChanneling() == false && perso->isSwitching() == false) {
        perso->restartPos();
        window->setView(window->getView());
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        switch (EchapMenu().Menu(*window)) {
            case -1: return -1; // Quit
            case 0:  return 0;  // resume
            case 1:  return 1;  // replay
            case 2:  return 2;  // back
            default: throw (Exception("Error: Menu Failed: Abort"));  // Error
        }
        return 1;
    }
    return 0;
}

static void EnnemiUpdate(sf::RenderWindow &window, vector<shared_ptr<Ennemi>> &Ennemilist, vector<shared_ptr<Block>> mapSFML, shared_ptr<Character> &perso) {
    for (size_t i = 0; i < Ennemilist.size(); i ++) {
            window.draw(Ennemilist[i]->getSprite());
            Ennemilist[i]->move(mapSFML);
            if (perso->invulnerability < 1 && sf::IntRect(perso->getSprite().getGlobalBounds()).intersects(sf::IntRect(Ennemilist[i]->getSprite().getGlobalBounds()))) {
                perso->_lifes --;
                perso->invulnerability += 60;
            }
        }
}

static void drawHearts(sf::RenderWindow &window, shared_ptr<Character> &perso) {
    ImageSFML heart3("resources/Images/heart.png");
    ImageSFML heart2("resources/Images/heart.png");
    ImageSFML heart1("resources/Images/heart.png");

    // window.getView().getCenter().x - 935, view.getCenter().y + 370

    heart3.setScale(sf::Vector2f(0.25, 0.25));
    heart2.setScale(sf::Vector2f(0.25, 0.25));
    heart1.setScale(sf::Vector2f(0.25, 0.25));
    heart3.setPosition(sf::Vector2f(window.getView().getCenter().x - 800, window.getView().getCenter().y + 370));
    heart2.setPosition(sf::Vector2f(window.getView().getCenter().x - 850, window.getView().getCenter().y + 370));
    heart1.setPosition(sf::Vector2f(window.getView().getCenter().x - 900, window.getView().getCenter().y + 370));
    switch (perso->_lifes) {
        case 3: window.draw(heart3.getSprite());
        case 2: window.draw(heart2.getSprite());
        case 1: window.draw(heart1.getSprite());
    }
}

static void BlockUpdate(sf::RenderWindow &window, vector<shared_ptr<Block>> mapSFML) {
    for (size_t i = 0; i < mapSFML.size(); i++)
            window.draw(mapSFML[i]->getSprite());
}

enum CHOICE {QUIT = 0, REPLAY = 1};
int GameLoop::gameLoop(vector<shared_ptr<Block>> mapSFML, Door door, vector<shared_ptr<Ennemi>> Ennemilist) {
    size_t loop = 0;
    Door door_s = door;
    vector<shared_ptr<Block>> mapSFML_s = mapSFML;
    vector<shared_ptr<Ennemi>> Ennemilist_s = Ennemilist;

    // if (!MainMenu().Menu(*window))
    //    return QUIT;
    window->setFramerateLimit(40);
    view->setCenter(perso->getSprite().getPosition());
    window->setView(*view);
    while (window->isOpen()) {
        BlockUpdate(*window, mapSFML);
        EnnemiUpdate(*window, Ennemilist, mapSFML, perso);
        perso->invulnerability = perso->invulnerability > 0 ? perso->invulnerability - 1 : perso->invulnerability;
        window->draw(door.getSprite());
        perso->display(window, mapSFML);
        drawHearts(*window, perso);
        if (sf::IntRect(perso->getSprite().getGlobalBounds()).intersects(sf::IntRect(door.getSprite().getGlobalBounds()))) {
            door.setOpening(true);
            door.doorOpen();
        }
        display();
        clear();
        checkDestruction(mapSFML);
        checkDeathEnemy(Ennemilist);
        if (perso->_lifes < 0) {
            switch(DeathMenu().Menu(*window)) {
                case -1: window->close(); break;
                case 2: return REPLAY;
            }
        } try {
            switch(getEvent(mapSFML)) {
                case -1: window->close(); break;
                case 0:
                    view->setCenter(perso->getSprite().getPosition());
                    window->setView(*view);
                    break;
                case 2: return REPLAY;
                case 3: continue; break;
            }
        } catch (Exception &e) {
            throw e;
        }
    }
    return QUIT;
}