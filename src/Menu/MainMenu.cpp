/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

MainMenu::MainMenu()
{
    try {
        play = std::make_shared<Button>(sf::Vector2f(800, 300), sf::Vector2f(250, 100));
        play->setColor(sf::Color::White, sf::Color::Black, 5);
        play->setText("resources/Buttons/text/Aileron-Black.otf", "play", 75, sf::Color::Black);
        quit = std::make_shared<Button>(sf::Vector2f(800, 740), sf::Vector2f(250, 100));
        quit->setColor(sf::Color::White, sf::Color::Black, 5);
        quit->setText("resources/Buttons/text/Aileron-Black.otf", "quit", 75, sf::Color::Black);
        bugs = std::make_shared<Button>(sf::Vector2f(800, 630), sf::Vector2f(250, 100));
        bugs->setColor(sf::Color::White, sf::Color::Black, 5);
        bugs->setText("resources/Buttons/text/Aileron-Black.otf", "bugs", 75, sf::Color::Black);
        ctrl = std::make_shared<Button>(sf::Vector2f(800, 520), sf::Vector2f(250, 100));
        ctrl->setColor(sf::Color::White, sf::Color::Black, 5);
        ctrl->setText("resources/Buttons/text/Aileron-Black.otf", "ctrl", 75, sf::Color::Black);
        multi = std::make_shared<Button>(sf::Vector2f(800, 410), sf::Vector2f(250, 100));
        multi->setColor(sf::Color::White, sf::Color::Black, 5);
        multi->setText("resources/Buttons/text/Aileron-Black.otf", "multi", 75, sf::Color::Black);
        background = std::make_shared<ImageSFML>("resources/Images/Game/wallpaper.jpg");
        cursor = std::make_shared<ImageSFML>("resources/Images/Game/cursor.png");

        cursor->setScale(sf::Vector2f(2.4, 2.4));
    } catch(Exception &e) {
        throw Exception("Error in MainMenu initialisation: " + *e.what());
    }
}
MainMenu::~MainMenu() {}

static void control_panel(shared_ptr<sf::RenderWindow> window) 
{
    sf::Event event;
    ImageSFML panel("resources/Images/Menu/Controltext.png");

    while (window->isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;
        window->draw(panel.getSprite());
        window->display();
    }
}

static void form_panel(shared_ptr<sf::RenderWindow> window) 
{
    size_t row = 0;
    sf::Event event;
    vector<shared_ptr<TextSfml>> texts;
    vector<string> fields = {"", "", "", "", ""};
    ImageSFML form("resources/Images/Menu/Report_form.png");

    texts.push_back(make_shared<TextSfml>("Name", "resources/character/arial.ttf", sf::Color::White, 0, 0));
    texts.push_back(make_shared<TextSfml>("Objet", "resources/character/arial.ttf", sf::Color::White, 0, 0));
    texts.push_back(make_shared<TextSfml>("La description de mon super probleme de la mort", "resources/character/arial.ttf", sf::Color::White, 0, 0));
    texts.push_back(make_shared<TextSfml>("La Situation dans laquelle j'etais au moment du probleme", "resources/character/arial.ttf", sf::Color::White, 0, 0));
    texts.push_back(make_shared<TextSfml>("autres chose a dire mon khey ?!", "resources/character/arial.ttf", sf::Color::White, 0, 0));

    for (size_t i = 0; i < texts.size(); i ++)
        texts[i]->setSize(32);

    texts[0]->setPosition(sf::Vector2f(150, 30));
    texts[1]->setPosition(sf::Vector2f(160, 97));
    texts[2]->setPosition(sf::Vector2f(75, 210));
    texts[3]->setPosition(sf::Vector2f(75, 450));
    texts[4]->setPosition(sf::Vector2f(75, 785));

    while (window->isOpen()) {
        while (window->pollEvent(event))
            EventHandler().inputEvent(event, fields[row]);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;
        window->draw(form.getSprite());

        for (size_t i = 0; i < texts.size(); i ++)
            texts[i]->setString(fields[i]);
        for (size_t i = 0; i < texts.size(); i ++)
            window->draw(texts[i]->getData());
        window->display();
    }
}

bool MainMenu::Menu(shared_ptr<sf::RenderWindow> window) 
{
    sf::Event event;
    sf::Vector2i cursorPos;

    window->setFramerateLimit(20);
    while (window->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 110));
        window->clear();

        window->draw(background->getSprite());
        play->drawButton(window);
        multi->drawButton(window);
        ctrl->drawButton(window);
        bugs->drawButton(window);
        quit->drawButton(window);
        window->draw(cursor->getSprite());

        window->display();
        while (window->pollEvent(event)) {
            if (play->isClicked(event))
                return true;
            else if (multi->isClicked(event))
                Multi_Screen(window).display();
            else if (bugs->isClicked(event))
                form_panel(window);
            else if (ctrl->isClicked(event))
                control_panel(window);
            else if (quit->isClicked(event))
                return false;
        }
    }
    return false;
}