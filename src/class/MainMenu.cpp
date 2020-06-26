#include "MainMenu.hpp"
#include "ImageSFML.hpp"

MainMenu::MainMenu() {}
MainMenu::~MainMenu() {}

bool MainMenu::Menu(sf::RenderWindow &window) {
    int oui = 0;
    sf::Event event;
    ImageSFML play("resources/Buttons/play.png");
    ImageSFML back("resources/Images/wallpaper.jpg");

    play.setPosition(sf::Vector2f(800, 400));
    window.setFramerateLimit(10);
    while (window.isOpen()) {
        window.clear();
        window.draw(back.getSprite());
        window.draw(play.getSprite());
        window.display();
        while (window.pollEvent(event))
            if (play.isClicked(event))
                return true;
        oui ++;
        if (oui > 60)
            break;
    }
    return false;
}