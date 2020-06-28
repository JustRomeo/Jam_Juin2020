#include "MainMenu.hpp"
#include "ImageSFML.hpp"
#include "Exception.hpp"

MainMenu::MainMenu() {

}
MainMenu::~MainMenu() {

}

bool MainMenu::Menu(sf::RenderWindow &window) {
    sf::Event event;
    ImageSFML play("resources/Buttons/play.png");
    ImageSFML quit("resources/Buttons/quit.png");
    ImageSFML background("resources/Images/wallpaper.jpg");
    ImageSFML cursor("resources/Images/cursor.png");

    // window.setMouseCursorVisible(false);
    play.setPosition(sf::Vector2f(800, 400));
    quit.setPosition(sf::Vector2f(800, 525));
    window.setFramerateLimit(20);
    cursor.setScale(sf::Vector2f(2.4, 2.4));
    while (window.isOpen()) {
        cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 110));
        window.clear();
        window.draw(background.getSprite());
        window.draw(play.getSprite());
        window.draw(quit.getSprite());
        window.draw(cursor.getSprite());
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