#include "Cinematique.hpp"

Cinematique::Cinematique() {}
Cinematique::~Cinematique() {}

static bool getTimeDiff(float diff, sf::Clock &clock) {
    sf::Time time;
    float seconds = 0;

    time = clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000;
    if (seconds > diff) {
        clock.restart();
        return false;
    }
    return true;
}

int Cinematique::Intro(shared_ptr<sf::RenderWindow> window, shared_ptr<Character> &perso) {
    sf::View view;
    sf::RectangleShape fade = sf::RectangleShape(sf::Vector2f(1920, 1080));
    sf::Event event;
    int quit = 0;
    sf::Clock clock = sf::Clock();
    sf::Font font;
    sf::Color c1(255, 255, 255, 255);
    sf::Color c2(255, 255, 255, 0);
    sf::Color c3(255, 255, 255, 0);
    sf::Color c4(255, 255, 255, 0);

    view.setSize(1920, 1080);
    view.setCenter(960, 540);
    window->setView(view);
    clock.restart();
    if (!font.loadFromFile("./resources/character/police.ttf"))
        return (false);
    fade.setFillColor(sf::Color::Black);
    sf::Text text("Aventurier!\n", font);
    sf::Text text2("Apres avoir trouve dans une temple une ancienne relique aux pouvoir mysterieux.\n                          Emettant des sons d'une puissance inouie.\nVous decidez de rentrez avec, afin d'en exploiter l'immmense potentiel.\n", font);
    sf::Text text3("               Malheureusement de grande puissance convoite aussi cet artefact.\nEt on deploye tous les moyens en leur possession pour vous tuer et recuperer la relique.\n", font);
    sf::Text text4("Vous devrez donc vous echapper du temple et survivre au different danger qui se dresseront sur votre chemin.\n                                  Grace a vos competences d'aventurier et au pouvoir de la relique.\n", font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(c1);
    text.setPosition(sf::Vector2f(845, 50));

    text2.setCharacterSize(30);
    text2.setStyle(sf::Text::Bold);
    text2.setFillColor(c2);
    text2.setPosition(sf::Vector2f(400, 150));

    text3.setCharacterSize(30);
    text3.setStyle(sf::Text::Bold);
    text3.setFillColor(c3);
    text3.setPosition(sf::Vector2f(375, 350));

    text4.setCharacterSize(30);
    text4.setStyle(sf::Text::Bold);
    text4.setFillColor(c4);
    text4.setPosition(sf::Vector2f(200, 500));
    while (window->isOpen() && quit != 1 || (c1.a != 255 && c2.a != 255 && c3.a != 255 && c4.a != 255)) {
        window->draw(fade);
        window->draw(text);
        window->draw(text2);
        window->draw(text3);
        window->draw(text4);
        window->display();
        if (c1.a == 255 && c2.a != 255) {
            if (getTimeDiff(0.01, clock))
                c2.a ++;
            text2.setFillColor(c2);
        } if (c1.a == 255 && c2.a == 255 && c3.a != 255) {
            if (getTimeDiff(0.01, clock))
                c3.a ++;
            text3.setFillColor(c3);
        } else if (c1.a == 255 && c2.a == 255 && c3.a == 255 && c4.a != 255) {
            if (getTimeDiff(0.01, clock))
                c4.a ++;
            text4.setFillColor(c4);
        } if (c2.a == 255 && c3.a == 255 && c4.a == 255)
            break;
        window->clear(sf::Color::White);
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S) {
                perso->incWeapon();
                return (true);
            }
       }
    }
    return (true);
}