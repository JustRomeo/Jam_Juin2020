/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Training
*/

#include "Map.hpp"
#include "Training.hpp"

Training::Training() {
    try {
        load = std::make_shared<Button>(sf::Vector2f(800, 520), sf::Vector2f(250, 100));
        quit = std::make_shared<Button>(sf::Vector2f(800, 740), sf::Vector2f(250, 100));
        create = std::make_shared<Button>(sf::Vector2f(800, 300), sf::Vector2f(250, 100));

        load->setColor(sf::Color::White, sf::Color::Black, 5);
        quit->setColor(sf::Color::White, sf::Color::Black, 5);
        create->setColor(sf::Color::White, sf::Color::Black, 5);

        load->setText("resources/Buttons/text/Aileron-Black.otf", "Load", 75, sf::Color::Black);
        quit->setText("resources/Buttons/text/Aileron-Black.otf", "Quit", 75, sf::Color::Black);
        create->setText("resources/Buttons/text/Aileron-Black.otf", "Create", 75, sf::Color::Black);
    } catch(Exception &e) {
        throw Exception("Error in Training initialisation: " + *e.what());
    }
}

Training::~Training() {}

void Training::Menu(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;

    window->setFramerateLimit(20);
    while (window->isOpen()) {
        window->clear(sf::Color::Black);

        create->drawButton(window);
        load->drawButton(window);
        quit->drawButton(window);

        window->display();
        while (window->pollEvent(event)) {
            if (create->isClicked(event)) {
                MapCreator _creator(50, 50);
                _creator.creator(window);
            } else if (load->isClicked(event))
                return;
            else if (quit->isClicked(event) || event.type == sf::Event::Closed)
                return;
        }
    }
}

