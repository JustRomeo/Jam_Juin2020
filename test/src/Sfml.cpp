/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sfml
*/

#include "Exception.hpp"
#include "Sfml.hpp"

Sfml::Sfml()
{
    _background.setTexture("resources/space.png");
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "graphical interface");
    _window->setFramerateLimit(40);
    view = new sf::View(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
    _window->setView(*view);
}

Sfml::~Sfml()
{
    delete(_window);
}

void Sfml::Clear()
{
    _window->clear(sf::Color::White);
}

void Sfml::Refresh()
{
    _window->clear(sf::Color::White);
}

int Sfml::manageEventMenu()
{
    sf::Event event;

    while (_window->pollEvent(event)) {
        if (event.key.code == sf::Keyboard::Key::Z)
            view->move(sf::Vector2f(0.f, -10.f));
        if (event.key.code == sf::Keyboard::Key::Q)
            view->move(sf::Vector2f(-10.f, 0.f));
        if (event.key.code == sf::Keyboard::Key::S)
            view->move(sf::Vector2f(0.f, 10.f));
        if (event.key.code == sf::Keyboard::Key::D)
            view->move(sf::Vector2f(10.f, 0.f));
        _window->setView(*view);
        // if (event.type == sf::Event::MouseButtonReleased)
        //     return (checkButtonClicked(sf::Mouse::getPosition()));
        // if (event.type == sf::Event::KeyReleased)
        //     updatePlayerName(event);
        if (event.type == sf::Event::Closed) {
            _window->close();
            return (arcade::Input::QUIT);
        }
    }
    return (0);
}

void Sfml::drawAndDisplayWindow()
{
    _window->draw(_background.getSprite());
    _window->display();
}


int Sfml::menu(std::vector<std::string> gameLib_path)
{
    int nb_lib = 0;
    int button_clicked = 0;

    while (_window->isOpen()) {
        drawAndDisplayWindow();
        Clear();
        button_clicked = manageEventMenu();
    }
    return (0);
}