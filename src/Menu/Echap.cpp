#include "Echap.hpp"

EchapMenu::EchapMenu() {}
EchapMenu::~EchapMenu() {}

enum CHOICE {QUIT = -1, PLAY = 0, REPLAY = 1, BACK = 2};
int EchapMenu::Menu(sf::RenderWindow &window) {
    sf::Event event;
    ImageSFML play("resources/Buttons/play.png");
    ImageSFML back("resources/Buttons/back.jpg");
    ImageSFML quit("resources/Buttons/quit.png");
    ImageSFML background("resources/Images/Menu_options.png");
    ImageSFML cursor("resources/Images/cursor.png");

    window.setView(window.getDefaultView());
    play.setPosition(sf::Vector2f(800, 325));
    back.setPosition(sf::Vector2f(800, 575));
    quit.setPosition(sf::Vector2f(800, 700));
    cursor.setScale(sf::Vector2f(2.4, 2.4));
    back.setScale(sf::Vector2f(0.75, 1.20));

    window.setMouseCursorVisible(false);
    window.setFramerateLimit(20);
    while (window.isOpen()) {
        cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 130));
        window.clear();
        window.draw(background.getSprite());
        window.draw(play.getSprite());
        window.draw(back.getSprite());
        window.draw(quit.getSprite());
        window.draw(cursor.getSprite());
        window.display();
        while (window.pollEvent(event)) {
            if (quit.isClicked(event))
                return QUIT;
            else if (play.isClicked(event))
                return PLAY;
            else if (back.isClicked(event))
                return BACK;
        }
    }
    play.~ImageSFML();
    back.~ImageSFML();
    background.~ImageSFML();
    return false;
}