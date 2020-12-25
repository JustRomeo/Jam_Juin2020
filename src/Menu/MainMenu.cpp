/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** MainMenu
*/

#include "MainMenu.hpp"
#include "Training.hpp"
#include "BugsScreen.hpp"
#include "ControlPanel.hpp"

MainMenu::MainMenu() {
    try {
        remote = make_shared<ManetteSFML>();
        bugs = make_shared<ImageSFML>("resources/Buttons/Bugs.png");
        tuto = make_shared<ImageSFML>("resources/Buttons/Tuto.png");
        cursor = make_shared<ImageSFML>("resources/Images/Game/cursor.png");
        background = make_shared<ImageSFML>("resources/Images/Game/wallpaper.jpg");
        manette_cursor = make_shared<ImageSFML>("resources/Buttons/manette_cursor.jpg");

        play = make_shared<Button>(sf::Vector2f(800, 200), sf::Vector2f(250, 100));
        ctrl = make_shared<Button>(sf::Vector2f(800, 650), sf::Vector2f(250, 100));
        quit = make_shared<Button>(sf::Vector2f(800, 800), sf::Vector2f(250, 100));
        local = make_shared<Button>(sf::Vector2f(800, 350), sf::Vector2f(250, 100));
        multi = make_shared<Button>(sf::Vector2f(800, 500), sf::Vector2f(250, 100));

        play->setColor(sf::Color::White, sf::Color::Black, 5);
        ctrl->setColor(sf::Color::White, sf::Color::Black, 5);
        quit->setColor(sf::Color::White, sf::Color::Black, 5);
        local->setColor(sf::Color::White, sf::Color::Black, 5);
        multi->setColor(sf::Color::White, sf::Color::Black, 5);

        play->setText("resources/Buttons/text/Aileron-Black.otf", "Play", 75, sf::Color::Black);
        ctrl->setText("resources/Buttons/text/Aileron-Black.otf", "Ctrl", 75, sf::Color::Black);
        quit->setText("resources/Buttons/text/Aileron-Black.otf", "Quit", 75, sf::Color::Black);
        multi->setText("resources/Buttons/text/Aileron-Black.otf", "Multi", 75, sf::Color::Black);
        local->setText("resources/Buttons/text/Aileron-Black.otf", "Local", 75, sf::Color::Black);

        manette_cursor->setRotate(-90);
        bugs->setScale(sf::Vector2f(0.25, 0.25));
        tuto->setScale(sf::Vector2f(0.25, 0.25));
        cursor->setScale(sf::Vector2f(2.4, 2.4));
        background->setScale(sf::Vector2f(1.6, 1.6));
        manette_cursor->setScale(sf::Vector2f(0.05, 0.05));

        bugs->setPosition(sf::Vector2f(25, 50));
        tuto->setPosition(sf::Vector2f(25, 200));
        manette_cursor->setPosition(sf::Vector2f(650, 300));

        _remote_row = 0;
        isRemoteUsed = false;
    } catch(Exception &e) {
        throw Exception("Error in MainMenu initialisation: " + *e.what());
    }
}
MainMenu::~MainMenu() {}

void MainMenu::remoteChoice(shared_ptr<sf::RenderWindow> window) {
    if (isRemoteUsed) {
        manette_cursor->setPosition(sf::Vector2f(650, 300 + _remote_row * 150));
        window->draw(manette_cursor->getSprite());
    } else
        window->draw(cursor->getSprite());
}

void drawButtons(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Button>> buttons) {
    for (size_t i = 0; i < buttons.size(); i ++)
        buttons[i]->drawButton(window);
}

void drawImages(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<ImageSFML>> images) {
    for (size_t i = 0; i < images.size(); i ++)
        window->draw(images[i]->getSprite());
}

bool MainMenu::Menu(shared_ptr<sf::RenderWindow> window, GameLoop &game) {
    sf::Event event;
    sf::Vector2i cursorPos;
    sf::Vector2i last = sf::Mouse::getPosition();

    window->setFramerateLimit(20);
    while (window->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 110));
        window->clear();

        drawImages(window, {background, bugs, tuto});
        drawButtons(window, {play, local, multi, ctrl, quit});

        remoteChoice(window);
        window->display();
        while (window->pollEvent(event)) {
            if (sf::Mouse::getPosition().x != last.x || sf::Mouse::getPosition().y != last.y)
                isRemoteUsed = false;
            if (remote->getJoysDirection() != ManetteSFML::Nothing)
                isRemoteUsed = true;
            if (play->isClicked(event))
                return true;
            else if (local->isClicked(event)) {
                game.setPlayerNumber(2);
                return true;
            } else if (multi->isClicked(event))
                Multi_Screen(window).display();
            else if (tuto->isClicked(event))
                Training().Menu(window);
            else if (bugs->isClicked(event))
                BugsScreen().form_panel(window);
            else if (ctrl->isClicked(event))
                ControlPanel().control_panel(window);
            else if (quit->isClicked(event) || event.type == sf::Event::Closed)
                return false;
            last = sf::Mouse::getPosition();
        }
    }
    return false;
}