#include <iostream>

#include "Echap.hpp"
#include "GameLoop.hpp"
#include "WindowLib.hpp"

EchapMenu::EchapMenu() {}
EchapMenu::~EchapMenu() {}

enum CHOICE {QUIT = -1, PLAY = 0, REPLAY = 1, BACK = 2};
int EchapMenu::Menu(shared_ptr<sf::RenderWindow> window, bool &sound_on) {
    sf::Joystick joys;
    GameLoop::Controler controler_on = GameLoop::Controler::KeyBoard;

    sf::Event event;
    shared_ptr<ImageSFML> play = make_shared<ImageSFML>("resources/Buttons/play.png");
    shared_ptr<ImageSFML> back = make_shared<ImageSFML>("resources/Buttons/back.jpg");
    shared_ptr<ImageSFML> quit = make_shared<ImageSFML>("resources/Buttons/quit.png");
    shared_ptr<ImageSFML> cursor = make_shared<ImageSFML>("resources/Images/Game/cursor.png");
    shared_ptr<ImageSFML> background = make_shared<ImageSFML>("resources/Images/Game/Menu_options.png");
    shared_ptr<ImageSFML> sound = make_shared<ImageSFML>(sound_on ? "resources/Images/Menu/sound.png" : "resources/Images/Menu/sound_off.png");
    shared_ptr<ImageSFML> larrow = make_shared<ImageSFML>("resources/Images/Menu/arrowHUD.png");
    shared_ptr<ImageSFML> rarrow = make_shared<ImageSFML>("resources/Images/Menu/arrowHUD.png");
    shared_ptr<ImageSFML> controler = make_shared<ImageSFML>(controler_on == GameLoop::Controler::KeyBoard ? "resources/Images/Menu/Control.png" : "resources/Images/Menu/mannette.png");

    bool connected = sf::Joystick::isConnected(0);
    size_t buttons = sf::Joystick::getButtonCount(0);

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

    sound->setPosition(sf::Vector2f(50, 50));
    play->setPosition(sf::Vector2f(800, 325));
    back->setPosition(sf::Vector2f(800, 575));
    quit->setPosition(sf::Vector2f(800, 700));
    rarrow->setPosition(sf::Vector2f(1750, 750));
    larrow->setPosition(sf::Vector2f(1200, 875));
    controler->setPosition(controler_on == GameLoop::Controler::KeyBoard ? sf::Vector2f(1325, 750) : sf::Vector2f(1350, 700));

    cursor->setScale(sf::Vector2f(2.4, 2.4));
    back->setScale(sf::Vector2f(0.75, 1.20));
    sound->setScale(sf::Vector2f(0.25, 0.25));
    rarrow->setScale(sf::Vector2f(0.25, 0.25));
    larrow->setScale(sf::Vector2f(0.25, 0.25));
    controler->setScale(controler_on == GameLoop::Controler::KeyBoard ? sf::Vector2f(0.3, 0.3) : sf::Vector2f(1, 1));

    rarrow->setRotate(90);
    larrow->setRotate(-90);

    window->setMouseCursorVisible(false);
    window->setFramerateLimit(60);
    while (window->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 130));
        window->clear();
        WindowLib().drawSprites(window, {background, play, back, quit, sound, rarrow, larrow, controler, cursor});
        window->display();
        while (window->pollEvent(event)) {
            if (quit->isClicked(event))
                return QUIT;
            else if (play->isClicked(event))
                return PLAY;
            else if (sound->isClicked(event)) {
                sound_on = !sound_on;
                sound->setTexture(sound_on ? "resources/Images/Menu/sound.png" : "resources/Images/Menu/sound_off.png");
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