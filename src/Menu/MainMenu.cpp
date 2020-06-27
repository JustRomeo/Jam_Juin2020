#include "MainMenu.hpp"
#include "ImageSFML.hpp"

MainMenu::MainMenu() {}
MainMenu::~MainMenu() {}

bool MainMenu::Menu(sf::RenderWindow &window) {
    sf::Event event;
    ImageSFML play("resources/Buttons/play.png");
    ImageSFML quit("resources/Buttons/quit.png");
    ImageSFML background("resources/Images/wallpaper.jpg");

    play.setPosition(sf::Vector2f(800, 400));
    quit.setPosition(sf::Vector2f(800, 525));
    window.setFramerateLimit(20);
    while (window.isOpen()) {
        window.clear();
        window.draw(background.getSprite());
        window.draw(play.getSprite());
        window.draw(quit.getSprite());
        window.display();
        while (window.pollEvent(event)) {
            if (play.isClicked(event))
                return true;
            else if (quit.isClicked(event))
                return false;
        }
    }
    play.~ImageSFML();
    quit.~ImageSFML();
    background.~ImageSFML();
    return false;
}