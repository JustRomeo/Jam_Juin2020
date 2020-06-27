#include "MainMenu.hpp"
#include "ImageSFML.hpp"

MainMenu::MainMenu() {}
MainMenu::~MainMenu() {}

bool MainMenu::Menu(sf::RenderWindow &window) {
    sf::Event event;
    ImageSFML play("resources/Buttons/play.png");
    ImageSFML back("resources/Buttons/back.jpg");
    ImageSFML background("resources/Images/wallpaper.jpg");

    play.setPosition(sf::Vector2f(800, 400));
    back.setPosition(sf::Vector2f(800, 525));
    back.setScale(sf::Vector2f(0.75, 1.20));
    window.setFramerateLimit(20);
    while (window.isOpen()) {
        window.clear();
        window.draw(background.getSprite());
        window.draw(play.getSprite());
        window.draw(back.getSprite());
        window.display();
        while (window.pollEvent(event)) {
            if (play.isClicked(event))
                return true;
            else if (back.isClicked(event))
                return false;
        }
    }
    play.~ImageSFML();
    back.~ImageSFML();
    background.~ImageSFML();
    return false;
}