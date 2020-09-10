#include "ImageSFML.hpp"
#include "Exception.hpp"
#include "Connection.hpp"
#include "Multiplayer.hpp"

Multi_Screen::Multi_Screen(shared_ptr<sf::RenderWindow> window) {
    _host = true;
    _connected = false;

    if (window == 0)
        _window = make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SoundWaves: Multiplayer");
    else
        _window = window;
}

Multi_Screen::~Multi_Screen() {}

void Multi_Screen::display(void) {
    sf::Event event;
    shared_ptr<ImageSFML> cursor;
    shared_ptr<ImageSFML> houseSFML;
    shared_ptr<ImageSFML> inviteSFML;

    try {
        cursor = make_shared<ImageSFML>("./resources/Images/Game/cursor.png");
        houseSFML = make_shared<ImageSFML>("./resources/Images/Multiplayer/house.png");
        inviteSFML = make_shared<ImageSFML>("./resources/Images/Multiplayer/incoming.jpg");

        houseSFML->setPosition(sf::Vector2f(0, 0));
        inviteSFML->setPosition(sf::Vector2f(900, 0));

        houseSFML->setScale(sf::Vector2f(4, 4));
        cursor->setScale(sf::Vector2f(2.4, 2.4));
        inviteSFML->setScale(sf::Vector2f(2, 2));
    } catch (Exception &e) {
        throw ("Error:\n\t -> SFML Image(s) in Multiplayer screen\n\t -> " + *e.what());
    }

    _window->setFramerateLimit(45);
    while (_window->isOpen()) {
        try {
            cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 110));

            _window->draw(inviteSFML->getSprite());
            _window->draw(houseSFML->getSprite());
            _window->draw(cursor->getSprite());

            _window->display();
            while (_window->pollEvent(event))
                if (event.type == sf::Event::Closed)
                    _window->close();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    return;
        } catch (Exception &e) {
            _window->close();
        }
    }
}