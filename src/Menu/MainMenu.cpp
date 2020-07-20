#include "MainMenu.hpp"
#include "ImageSFML.hpp"
#include "Exception.hpp"
#include "Multiplayer.hpp"

MainMenu::MainMenu() {

}
MainMenu::~MainMenu() {

}

bool MainMenu::Menu(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;
    ImageSFML *play;
    ImageSFML *quit;
    ImageSFML *multi;
    ImageSFML *cursor;
    ImageSFML *background;

    try {
        play = new ImageSFML("resources/Buttons/play.png");
        quit = new ImageSFML("resources/Buttons/quit.png");
        multi = new ImageSFML("resources/Buttons/multiplayer.png");
        background = new ImageSFML("resources/Images/Game/wallpaper.jpg");
        cursor = new ImageSFML("resources/Images/Game/cursor.png");

        play->setPosition(sf::Vector2f(800, 400));
        multi->setPosition(sf::Vector2f(800, 535));
        quit->setPosition(sf::Vector2f(800, 650));
        window->setFramerateLimit(20);
        cursor->setScale(sf::Vector2f(2.4, 2.4));
    } catch(Exception &e) {
        throw Exception("Error in MainMenu initialisation: " + *e.what());
    }

    while (window->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 110));
        window->clear();

        window->draw(background->getSprite());
        window->draw(play->getSprite());
        window->draw(multi->getSprite());
        window->draw(quit->getSprite());
        window->draw(cursor->getSprite());

        window->display();
        while (window->pollEvent(event)) {
            if (play->isClicked(event))
                return true;
            else if (multi->isClicked(event))
                Multi_Screen(window).display();
            else if (quit->isClicked(event))
                return false;
        }
    }
    play->~ImageSFML();
    quit->~ImageSFML();
    background->~ImageSFML();
    return false;
}