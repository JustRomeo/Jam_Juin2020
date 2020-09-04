#include "BugsScreen.hpp"

BugsScreen::BugsScreen() {}
BugsScreen::~BugsScreen() {}

void BugsScreen::form_panel(shared_ptr<sf::RenderWindow> window) {
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

        for (size_t i = 0; i < texts.size(); i ++) {
            texts[i]->setString(fields[i]);
            window->draw(texts[i]->getData());
        }
        window->display();
    }
}