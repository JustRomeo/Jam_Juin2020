#include "Echap.hpp"

EchapMenu::EchapMenu() {}
EchapMenu::~EchapMenu() {}

int EchapMenu::Menu(sf::RenderWindow &window) {
    sf::Event event;
    ImageSFML play("resources/Buttons/play.png");
    ImageSFML replay("resources/Buttons/replay.jpg");
    ImageSFML back("resources/Buttons/back.jpg");
    ImageSFML quit("resources/Buttons/quit.png");
    ImageSFML background("resources/Images/wallpaper.jpg");

    window.setView(window.getDefaultView());
    play.setPosition(sf::Vector2f(800, 400));
    replay.setPosition(sf::Vector2f(800, 525));
    back.setPosition(sf::Vector2f(800, 650));
    quit.setPosition(sf::Vector2f(800, 775));

    replay.setScale(sf::Vector2f(0.75, 1.20));
    back.setScale(sf::Vector2f(0.75, 1.20));

    window.setFramerateLimit(20);
    while (window.isOpen()) {
        window.clear();
        window.draw(background.getSprite());

        window.draw(play.getSprite());
        window.draw(replay.getSprite());
        window.draw(back.getSprite());
        window.draw(quit.getSprite());

        window.display();
        while (window.pollEvent(event)) {
            if (quit.isClicked(event))
                return -1;
            else if (play.isClicked(event))
                return 0;
            else if (replay.isClicked(event))
                return 1;
            else if (back.isClicked(event))
                return 2;
        }
    }
    play.~ImageSFML();
    back.~ImageSFML();
    background.~ImageSFML();
    return false;
}