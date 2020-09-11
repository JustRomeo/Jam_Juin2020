/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** MainMenu
*/

#include "MainMenu.hpp"
#include "BugsScreen.hpp"
#include "ControlPanel.hpp"

MainMenu::MainMenu() {
    try {
        background = std::make_shared<ImageSFML>("resources/Images/Game/wallpaper.jpg");
        play = std::make_shared<Button>(sf::Vector2f(800, 300), sf::Vector2f(250, 100));
        local = std::make_shared<Button>(sf::Vector2f(800, 410), sf::Vector2f(250, 100));
        multi = std::make_shared<Button>(sf::Vector2f(800, 520), sf::Vector2f(250, 100));
        ctrl = std::make_shared<Button>(sf::Vector2f(800, 630), sf::Vector2f(250, 100));
        bugs = std::make_shared<Button>(sf::Vector2f(800, 740), sf::Vector2f(250, 100));
        quit = std::make_shared<Button>(sf::Vector2f(800, 850), sf::Vector2f(250, 100));
        cursor = std::make_shared<ImageSFML>("resources/Images/Game/cursor.png");

        play->setColor(sf::Color::White, sf::Color::Black, 5);
        local->setColor(sf::Color::White, sf::Color::Black, 5);
        multi->setColor(sf::Color::White, sf::Color::Black, 5);
        ctrl->setColor(sf::Color::White, sf::Color::Black, 5);
        bugs->setColor(sf::Color::White, sf::Color::Black, 5);
        quit->setColor(sf::Color::White, sf::Color::Black, 5);

        play->setText("resources/Buttons/text/Aileron-Black.otf", "play", 75, sf::Color::Black);
        local->setText("resources/Buttons/text/Aileron-Black.otf", "Local", 75, sf::Color::Black);
        multi->setText("resources/Buttons/text/Aileron-Black.otf", "multi", 75, sf::Color::Black);
        ctrl->setText("resources/Buttons/text/Aileron-Black.otf", "ctrl", 75, sf::Color::Black);
        bugs->setText("resources/Buttons/text/Aileron-Black.otf", "bugs", 75, sf::Color::Black);
        quit->setText("resources/Buttons/text/Aileron-Black.otf", "quit", 75, sf::Color::Black);

        cursor->setScale(sf::Vector2f(2.4, 2.4));
    } catch(Exception &e) {
        throw Exception("Error in MainMenu initialisation: " + *e.what());
    }
}
MainMenu::~MainMenu() {}

bool MainMenu::Menu(shared_ptr<sf::RenderWindow> window, GameLoop &game) {
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
            else if (local->isClicked(event)) {
                game.setPlayerNumber(2);
                return true;
            } else if (multi->isClicked(event))
                Multi_Screen(window).display();
            else if (bugs->isClicked(event))
                BugsScreen().form_panel(window);
            else if (ctrl->isClicked(event))
                ControlPanel().control_panel(window);
            else if (quit->isClicked(event) || event.type == sf::Event::Closed)
                return false;
        }
    }
    return false;
}