/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Echap Menu File
*/

#include <iostream>

#include "Echap.hpp"
#include "System.hpp"
#include "GameLoop.hpp"
#include "WindowLib.hpp"

EchapMenu::EchapMenu() {
    GameLoop::Controler controler_on = GameLoop::Controler::KeyBoard;

    soundlvl = 50;

    rectbase = make_shared<sf::RectangleShape>();
    rectcolo = make_shared<sf::RectangleShape>();
    rectload = make_shared<sf::RectangleShape>();
    cursor = make_shared<ImageSFML>("resources/Images/Game/cursor.png");
    larrow = make_shared<ImageSFML>("resources/Images/Menu/arrowHUD.png");
    rarrow = make_shared<ImageSFML>("resources/Images/Menu/arrowHUD.png");
    play = make_shared<Button>(sf::Vector2f(800, 325), sf::Vector2f(250, 100));
    back = make_shared<Button>(sf::Vector2f(800, 575), sf::Vector2f(250, 100));
    quit = make_shared<Button>(sf::Vector2f(800, 700), sf::Vector2f(250, 100));
    background = make_shared<ImageSFML>("resources/Images/Game/Menu_options.png");
    controler = make_shared<ImageSFML>(controler_on == GameLoop::Controler::KeyBoard ? "resources/Images/Menu/Control.png" : "resources/Images/Menu/mannette.png");
    if (soundlvl != 0)
        sound = make_shared<ImageSFML>("resources/Images/Menu/sound.png");
    else
        sound = make_shared<ImageSFML>("resources/Images/Menu/sound_off.png");

    play->setColor(sf::Color::White, sf::Color::Black, 5);
    back->setColor(sf::Color::White, sf::Color::Black, 5);
    quit->setColor(sf::Color::White, sf::Color::Black, 5);

    play->setText("resources/Buttons/text/Aileron-Black.otf", "play", 75, sf::Color::Black);
    back->setText("resources/Buttons/text/Aileron-Black.otf", "back", 75, sf::Color::Black);
    quit->setText("resources/Buttons/text/Aileron-Black.otf", "quit", 75, sf::Color::Black);

    cursor->setScale(sf::Vector2f(2.4, 2.4));
    sound->setScale(sf::Vector2f(0.125, 0.125));

    rectbase->setFillColor(sf::Color::White);
    rectcolo->setFillColor(sf::Color::Black);
    rectload->setFillColor(sf::Color::Green);

    rectbase->setSize(sf::Vector2f(200, 20));
    rectcolo->setSize(sf::Vector2f(198, 18));
    rectload->setSize(sf::Vector2f(100, 20));
    
    sound->setPosition(sf::Vector2f(750, 50));
    rectbase->setPosition(sf::Vector2f(845, 75));
    rectcolo->setPosition(sf::Vector2f(846, 76));
    rectload->setPosition(sf::Vector2f(845, 75));
    rarrow->setPosition(sf::Vector2f(1750, 750));
    larrow->setPosition(sf::Vector2f(1200, 875));
    controler->setPosition(controler_on == GameLoop::Controler::KeyBoard ? sf::Vector2f(1325, 750) : sf::Vector2f(1350, 700));

    rarrow->setRotate(90);
    larrow->setRotate(-90);

    rarrow->setScale(sf::Vector2f(0.25, 0.25));
    larrow->setScale(sf::Vector2f(0.25, 0.25));
    controler->setScale(controler_on == GameLoop::Controler::KeyBoard ? sf::Vector2f(0.3, 0.3) : sf::Vector2f(1, 1));
}
EchapMenu::~EchapMenu() {}

void EchapMenu::updateSong(sf::Event event) {
    sf::Vector2i _mouse = sf::Mouse::getPosition();

    _mouse.y -= 65;
    if (event.type == sf::Event::MouseButtonPressed && (_mouse.x < 845 + 200 && _mouse.x > 845) && (_mouse.y < 75 + 20 && _mouse.y > 75)) {
        rectload->setSize(sf::Vector2f(_mouse.x - 845, 20));
        soundlvl = (_mouse.x - 845) / 2;
        cout << "Set Volume to " << soundlvl << endl;
    } if (sound->isClicked(event)) {
        soundlvl = soundlvl > 0 ? 0 : 50;
        if (soundlvl == 0)
            sound = make_shared<ImageSFML>("resources/Images/Menu/sound_off.png");
        else
            sound = make_shared<ImageSFML>("resources/Images/Menu/sound.png");
        sound->setScale(sf::Vector2f(0.125, 0.125));
        sound->setPosition(sf::Vector2f(50, 50));
    }
}

void EchapMenu::dispEchapMenu(shared_ptr<sf::RenderWindow> window) {
    cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 130));
    window->clear();
    window->draw(background->getSprite());
    play->drawButton(window);
    back->drawButton(window);
    quit->drawButton(window);
    window->draw(sound->getSprite());
    window->draw(larrow->getSprite());
    window->draw(rarrow->getSprite());
    window->draw(controler->getSprite());
    window->draw(*rectbase);
    window->draw(*rectcolo);
    window->draw(*rectload);
    window->draw(cursor->getSprite());
    window->display();
}

enum CHOICE {QUIT = -1, PLAY = 0, REPLAY = 1, BACK = 2};
int EchapMenu::Menu(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;
    sf::Joystick joys;
    bool connected = sf::Joystick::isConnected(0);
    size_t buttons = sf::Joystick::getButtonCount(0);
    GameLoop::Controler controler_on = GameLoop::Controler::KeyBoard;

    if (connected) {
        bool hasX = sf::Joystick::hasAxis(0, sf::Joystick::X);
        bool hasY = sf::Joystick::hasAxis(0, sf::Joystick::Y);

        if (!hasX || !hasY)
            throw Exception("Error: Disfunction Mannette");
        float positionX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float positionY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    }

    window->setView(window->getDefaultView());
    window->setMouseCursorVisible(false);
    window->setFramerateLimit(60);

    while (window->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 130));
        dispEchapMenu(window);

        while (window->pollEvent(event)) {
            updateSong(event);
            if (quit->isClicked(event)) {
                // System().createFile("save", _map);
                return QUIT;
            } else if (play->isClicked(event))
                return PLAY;
            else if (larrow->isClicked(event) || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)) {
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

size_t EchapMenu::getSoundLvl(void) const {return soundlvl;}
