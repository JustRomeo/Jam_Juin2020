#include "Death.hpp"

DeathMenu::DeathMenu() {}
DeathMenu::~DeathMenu() {}


enum TypeCHOICE {QUIT = -1, PLAY = 0, REPLAY = 1, BACK = 2};
int DeathMenu::Menu(sf::RenderWindow &window) {
    sf::Event event;
    ImageSFML back("resources/Buttons/back.jpg");
    ImageSFML quit("resources/Buttons/quit.png");
    ImageSFML background("resources/Images/DeathWallpaper.jpg");

    window.setView(window.getDefaultView());
    back.setPosition(sf::Vector2f(800, 450));
    background.setScale(sf::Vector2f((float)1920 / 1100, (float)1080 / 700));
    quit.setPosition(sf::Vector2f(800, 575));

    back.setScale(sf::Vector2f(0.75, 1.20));

    window.setFramerateLimit(20);
    while (window.isOpen()) {
        window.clear();
        window.draw(background.getSprite());

        window.draw(back.getSprite());
        window.draw(quit.getSprite());

        window.display();
        while (window.pollEvent(event)) {
            if (quit.isClicked(event))
                return QUIT;
            else if (back.isClicked(event))
                return BACK;
        }
    }
    back.~ImageSFML();
    background.~ImageSFML();
    return false;
}