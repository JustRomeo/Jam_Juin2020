/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Window
*/

#include "Window.hpp"


Window::Window()
{
    try
    {
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "graphical interface");
        window->setFramerateLimit(40);
        view = std::make_shared<sf::View>(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
        window->setView(*view);
        background = std::make_shared<Sprite>("resources/space.png");
    }
    catch (std::bad_alloc &e) {
        throw (Exception("can't initiate window and view\n"));
    }
}

Window::~Window()
{
}

void Window::clear()
{
    window->clear(sf::Color::White);
}

void Window::display()
{
    window->draw(background->getSprite());
    window->display();
}

int Window::checkOpen()
{
    return (window->isOpen());
}