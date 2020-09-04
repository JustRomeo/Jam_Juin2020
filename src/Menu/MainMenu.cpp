/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** MainMenu
*/

#include "MainMenu.hpp"
#include "BugsScreen.hpp"
#include "ControlPanel.hpp"

MainMenu::MainMenu() {
    try {
        play = std::make_shared<Button>(sf::Vector2f(800, 300), sf::Vector2f(250, 100));
        play->setColor(sf::Color::White, sf::Color::Black, 5);
        play->setText("resources/Buttons/text/Aileron-Black.otf", "play", 75, sf::Color::Black);
        quit = std::make_shared<Button>(sf::Vector2f(800, 850), sf::Vector2f(250, 100));
        quit->setColor(sf::Color::White, sf::Color::Black, 5);
        quit->setText("resources/Buttons/text/Aileron-Black.otf", "quit", 75, sf::Color::Black);
        bugs = std::make_shared<Button>(sf::Vector2f(800, 740), sf::Vector2f(250, 100));
        bugs->setColor(sf::Color::White, sf::Color::Black, 5);
        bugs->setText("resources/Buttons/text/Aileron-Black.otf", "bugs", 75, sf::Color::Black);
        ctrl = std::make_shared<Button>(sf::Vector2f(800, 630), sf::Vector2f(250, 100));
        ctrl->setColor(sf::Color::White, sf::Color::Black, 5);
        ctrl->setText("resources/Buttons/text/Aileron-Black.otf", "ctrl", 75, sf::Color::Black);
        multi = std::make_shared<Button>(sf::Vector2f(800, 520), sf::Vector2f(250, 100));
        multi->setColor(sf::Color::White, sf::Color::Black, 5);
        multi->setText("resources/Buttons/text/Aileron-Black.otf", "multi", 75, sf::Color::Black);
        local = std::make_shared<Button>(sf::Vector2f(800, 410), sf::Vector2f(250, 100));
        local->setColor(sf::Color::White, sf::Color::Black, 5);
        local->setText("resources/Buttons/text/Aileron-Black.otf", "Local", 75, sf::Color::Black);
        background = std::make_shared<ImageSFML>("resources/Images/Game/wallpaper.jpg");
        cursor = std::make_shared<ImageSFML>("resources/Images/Game/cursor.png");

        cursor->setScale(sf::Vector2f(2.4, 2.4));
    } catch(Exception &e) {
        throw Exception("Error in MainMenu initialisation: " + *e.what());
    }
}
MainMenu::~MainMenu() {}

bool MainMenu::Menu(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;
    sf::Vector2i cursorPos;

    window->setFramerateLimit(20);
    while (window->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 110));
        window->clear();

        window->draw(background->getSprite());
        play->drawButton(window);
        multi->drawButton(window);
        local->drawButton(window);
        ctrl->drawButton(window);
        bugs->drawButton(window);
        quit->drawButton(window);
        window->draw(cursor->getSprite());

        window->display();
        while (window->pollEvent(event)) {
            if (play->isClicked(event))
                return true;
            else if (multi->isClicked(event))
                Multi_Screen(window).display();
            else if (bugs->isClicked(event))
                BugsScreen().form_panel(window);
            else if (ctrl->isClicked(event))
                ControlPanel().control_panel(window);
            else if (quit->isClicked(event))
                return false;
        }
    }
    return false;
}