#include "MainMenu.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"
#include "Exception.hpp"
#include "Multiplayer.hpp"
#include "EventHandler.hpp"

MainMenu::MainMenu() {}
MainMenu::~MainMenu() {}

static void control_panel(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;
    ImageSFML panel("resources/Images/Menu/Controltext.png");

    while (window->isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;
        window->draw(panel.getSprite());
        window->display();
    }
}

static void form_panel(shared_ptr<sf::RenderWindow> window) {
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

bool MainMenu::Menu(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;
    ImageSFML *play;
    ImageSFML *quit;
    ImageSFML *bugs;
    ImageSFML *ctrl;
    ImageSFML *multi;
    ImageSFML *cursor;
    ImageSFML *background;

    try {
        play = new ImageSFML("resources/Buttons/play.png");
        quit = new ImageSFML("resources/Buttons/quit.png");
        bugs = new ImageSFML("resources/Buttons/Bugs.png");
        ctrl = new ImageSFML("resources/Buttons/Controls.png");
        multi = new ImageSFML("resources/Buttons/multiplayer.png");
        background = new ImageSFML("resources/Images/Game/wallpaper.jpg");
        cursor = new ImageSFML("resources/Images/Game/cursor.png");

        play->setPosition(sf::Vector2f(800, 300));
        multi->setPosition(sf::Vector2f(800, 410));
        ctrl->setPosition(sf::Vector2f(800, 520));
        bugs->setPosition(sf::Vector2f(800, 630));
        quit->setPosition(sf::Vector2f(800, 740));
        window->setFramerateLimit(20);
        cursor->setScale(sf::Vector2f(2.4, 2.4));
    } catch(Exception &e) {
        throw Exception("Error in MainMenu initialisation: " + *e.what());
    }

    while (window->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 110));
        window->clear();

        window->draw(background->getSprite());
        window->draw(play->getSprite());
        window->draw(multi->getSprite());
        window->draw(ctrl->getSprite());
        window->draw(bugs->getSprite());
        window->draw(quit->getSprite());
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
    play->~ImageSFML();
    quit->~ImageSFML();
    background->~ImageSFML();
    return false;
}