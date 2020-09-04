#include <iostream>

#include "Echap.hpp"
#include "GameLoop.hpp"
#include "WindowLib.hpp"

EchapMenu::EchapMenu(bool &sound_on)
{
    GameLoop::Controler controler_on = GameLoop::Controler::KeyBoard;

    soundOn = sound_on;

    play = std::make_shared<Button>(sf::Vector2f(800, 325), sf::Vector2f(250, 100));
    back = std::make_shared<Button>(sf::Vector2f(800, 575), sf::Vector2f(250, 100));
    quit = std::make_shared<Button>(sf::Vector2f(800, 700), sf::Vector2f(250, 100));

    larrow = make_shared<ImageSFML>("resources/Images/Menu/arrowHUD.png");
    rarrow = make_shared<ImageSFML>("resources/Images/Menu/arrowHUD.png");

    controler = make_shared<ImageSFML>(controler_on == GameLoop::Controler::KeyBoard ? "resources/Images/Menu/Control.png" : "resources/Images/Menu/mannette.png");
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

    rarrow->setPosition(sf::Vector2f(1750, 750));
    larrow->setPosition(sf::Vector2f(1200, 875));
    controler->setPosition(controler_on == GameLoop::Controler::KeyBoard ? sf::Vector2f(1325, 750) : sf::Vector2f(1350, 700));

    rarrow->setRotate(90);
    larrow->setRotate(-90);

    rarrow->setScale(sf::Vector2f(0.25, 0.25));
    larrow->setScale(sf::Vector2f(0.25, 0.25));
    controler->setScale(controler_on == GameLoop::Controler::KeyBoard ? sf::Vector2f(0.3, 0.3) : sf::Vector2f(1, 1));
}
EchapMenu::~EchapMenu()
{
}

void EchapMenu::dispEchapMenu(std::shared_ptr<sf::RenderWindow> window)
{
    cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 130));
    window->clear();
    window->draw(background->getSprite());
    play->drawButton(window);
    back->drawButton(window);
    quit->drawButton(window);
    window->draw(sound->getSprite());
    window->draw(cursor->getSprite());
    window->draw(larrow->getSprite());
    window->draw(rarrow->getSprite());
    window->draw(controler->getSprite());
    window->display();
}

enum CHOICE {QUIT = -1, PLAY = 0, REPLAY = 1, BACK = 2};
int EchapMenu::Menu(std::shared_ptr<sf::RenderWindow> window)
{
    sf::Event event;
    sf::Joystick joys;
    bool connected = sf::Joystick::isConnected(0);
    size_t buttons = sf::Joystick::getButtonCount(0);
    GameLoop::Controler controler_on = GameLoop::Controler::KeyBoard;

    cout << (connected ? "A Joy's connected and support " : "No Joy's connected") << (connected ? to_string(buttons) : "") << (connected ? " buttons" : "") << endl;
    if (connected) {
        bool hasX = sf::Joystick::hasAxis(0, sf::Joystick::X);
        bool hasY = sf::Joystick::hasAxis(0, sf::Joystick::Y);

        if (!hasX || !hasY)
            throw Exception("Error: Disfunction Mannette");
        float positionX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float positionY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        cout << "Position X:" << positionX << " | Y:" << positionY << endl;
    }

    // Is button #2 pressed on joystick #0?
    // bool pressed = sf::Joystick::isButtonPressed(0, 2);

    window->setView(window->getDefaultView());
    window->setMouseCursorVisible(false);
    window->setFramerateLimit(60);

    while (window->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 130));
        dispEchapMenu(window);
        while (window->pollEvent(event)) {
            if (quit->isClicked(event))
                return QUIT;
            else if (play->isClicked(event))
                return PLAY;
            else if (sound->isClicked(event)) {
                soundOn = !soundOn;
                sound->setTexture(soundOn ? "resources/Images/Menu/sound.png" : "resources/Images/Menu/sound_off.png");
            } else if (larrow->isClicked(event) || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)) {
                switch (controler_on) {
                    case GameLoop::Controler::KeyBoard: controler_on = GameLoop::Controler::RemoteXBOX; break;
                    case GameLoop::Controler::RemoteXBOX: controler_on = GameLoop::Controler::RemotePS; break;
                    case GameLoop::Controler::RemotePS: controler_on = GameLoop::Controler::KeyBoard; break;
                    default: continue;
                    controler->setTexture(controler_on == GameLoop::Controler::KeyBoard ? "resources/Images/Menu/Control.png" : "resources/Images/Menu/mannette.png");
                    controler->setPosition(controler_on == GameLoop::Controler::KeyBoard ? sf::Vector2f(1325, 750) : sf::Vector2f(1350, 700));
                    controler->setScale(controler_on == GameLoop::Controler::KeyBoard ? sf::Vector2f(0.3, 0.3) : sf::Vector2f(1, 1));
                }
            } else if (rarrow->isClicked(event) || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right)) {
                switch (controler_on) {
                    case GameLoop::Controler::KeyBoard: controler_on = GameLoop::Controler::RemotePS; break;
                    case GameLoop::Controler::RemotePS: controler_on = GameLoop::Controler::RemoteXBOX; break;
                    case GameLoop::Controler::RemoteXBOX: controler_on = GameLoop::Controler::KeyBoard; break;
                    default: continue;
                }
                controler->setTexture(controler_on == GameLoop::Controler::KeyBoard ? "resources/Images/Menu/Control.png" : "resources/Images/Menu/mannette.png");
                controler->setPosition(controler_on == GameLoop::Controler::KeyBoard ? sf::Vector2f(1325, 750) : sf::Vector2f(1350, 700));
                controler->setScale(controler_on == GameLoop::Controler::KeyBoard ? sf::Vector2f(0.3, 0.3) : sf::Vector2f(1, 1));
            } else if (back->isClicked(event))
                return BACK;
        }
    }
    return false;
}