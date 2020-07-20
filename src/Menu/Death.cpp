#include "Death.hpp"

DeathMenu::DeathMenu() {
    _music = new MusicSFML();
}
DeathMenu::~DeathMenu() {
    _music->~MusicSFML();
}


enum TypeCHOICE {QUIT = -1, PLAY = 0, REPLAY = 1, BACK = 2};
int DeathMenu::Menu(sf::RenderWindow &window) {
    sf::Event event;
    ImageSFML back("resources/Buttons/back.jpg");
    ImageSFML quit("resources/Buttons/quit.png");
    ImageSFML background("resources/Images/Game/DeathWallpaper.jpg");
    ImageSFML cursor("resources/Images/Game/cursor.png");

    window.setMouseCursorVisible(false);
    cursor.setScale(sf::Vector2f(2.4, 2.4));
    _music->load("resources/Sounds/End.ogg");
    _music->setLoop(true);
    _music->start();
    window.setView(window.getDefaultView());
    back.setPosition(sf::Vector2f(800, 450));
    background.setScale(sf::Vector2f((float)1920 / 1100, (float)1080 / 700));
    quit.setPosition(sf::Vector2f(800, 575));

    back.setScale(sf::Vector2f(0.75, 1.20));

    window.setFramerateLimit(20);
    while (window.isOpen()) {
        cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 130));
        window.clear();
        window.draw(background.getSprite());

        window.draw(back.getSprite());
        window.draw(quit.getSprite());
        window.draw(cursor.getSprite());

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