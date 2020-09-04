#include "Echap.hpp"
#include <iostream>


EchapMenu::EchapMenu(bool &sound_on)
{
    play = std::make_shared<Button>(sf::Vector2f(800, 325), sf::Vector2f(250, 100));
    back = std::make_shared<Button>(sf::Vector2f(800, 575), sf::Vector2f(250, 100));
    quit = std::make_shared<Button>(sf::Vector2f(800, 700), sf::Vector2f(250, 100));
    cursor = std::make_shared<ImageSFML>("resources/Images/Game/cursor.png");
    background = std::make_shared<ImageSFML>("resources/Images/Game/Menu_options.png");
    if (sound_on)
        sound = std::make_shared<ImageSFML>("resources/Images/Menu/sound.png");
    else
        sound = std::make_shared<ImageSFML>("resources/Images/Menu/sound_off.png");
    play->setColor(sf::Color::White, sf::Color::Black, 5);
    play->setText("resources/Buttons/text/Aileron-Black.otf", "play", 75, sf::Color::Black);
    quit->setColor(sf::Color::White, sf::Color::Black, 5);
    quit->setText("resources/Buttons/text/Aileron-Black.otf", "quit", 75, sf::Color::Black);
    back->setColor(sf::Color::White, sf::Color::Black, 5);
    back->setText("resources/Buttons/text/Aileron-Black.otf", "back", 75, sf::Color::Black);
    cursor->setScale(sf::Vector2f(2.4, 2.4));
    sound->setScale(sf::Vector2f(0.25, 0.25));
    sound->setPosition(sf::Vector2f(50, 50));
    soundOn = sound_on;
}
EchapMenu::~EchapMenu()
{
}

enum CHOICE {QUIT = -1, PLAY = 0, REPLAY = 1, BACK = 2};
int EchapMenu::Menu(std::shared_ptr<sf::RenderWindow> window)
{
    sf::Event event;

    window->setMouseCursorVisible(false);
    window->setFramerateLimit(20);
    window->setView(window->getDefaultView());
    while (window->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 130));
        window->clear();
        window->draw(background->getSprite());
        play->drawButton(window);
        back->drawButton(window);
        quit->drawButton(window);
        window->draw(sound->getSprite());
        window->draw(cursor->getSprite());
        window->display();
        while (window->pollEvent(event)) {
            if (quit->isClicked(event))
                return QUIT;
            else if (play->isClicked(event))
                return PLAY;
            else if (sound->isClicked(event)) {
                soundOn = !soundOn;
                sound->setTexture(soundOn ? "resources/Images/Menu/sound.png" : "resources/Images/Menu/sound_off.png");
            } else if (back->isClicked(event))
                return BACK;
        }
    }
    return false;
}