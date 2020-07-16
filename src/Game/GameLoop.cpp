/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GameLoop
*/

#include "Door.hpp"
#include "Echap.hpp"
#include "Death.hpp"
#include "GameLoop.hpp"
#include "MainMenu.hpp"
#include "MusicSFML.hpp"

GameLoop::GameLoop()
{
    try {
        gameMusic = std::make_shared<GameMusic>();
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SoundWaves");
        window->setFramerateLimit(60);
        auto image = sf::Image {};
        if (!image.loadFromFile("resources/Images/icon.png"))
            throw Exception("Loading Ressource Failed");
        window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
        view = std::make_shared<sf::View>(sf::FloatRect(0, 0, 1920, 1080));
        background = std::make_shared<Sprite>("resources/Images/space.png");
        perso = std::make_shared<Character>();
        font = std::make_shared<ImageSFML>("resources/Images/sprite_font.png");
        window->setView(*view);
    } catch (std::bad_alloc &e) {
        throw(Exception("can't initiate window and view\n"));
    }
}

GameLoop::~GameLoop()
{
}


void GameLoop::EnnemiGeneration(vector<string> map)
{
    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++)
            if (map[i][j] == 'E')
                Ennemilist.push_back(make_shared<Ennemi>(Ennemi(j * 157, i * 157)));
}

void GameLoop::PlusGeneration(vector<string> map)
{
    for (size_t i = 0; i < map.size(); i ++) {
        for (size_t j = 0; j < map[i].length(); j ++) {
            if (map[i][j] == '1')
                PlusList.push_back(make_shared<MunPlus>(1, j * 157 + 50, i * 157 + 60));
            if (map[i][j] == '2')
                PlusList.push_back(make_shared<MunPlus>(2, j * 157 + 50, i * 157 + 60));
            if (map[i][j] == '3')
                PlusList.push_back(make_shared<MunPlus>(3, j * 157 + 50, i * 157 + 60));
        }
    }
}

void GameLoop::MapGeneration(vector<string> _map)
{
    for (size_t i = 0; i < _map.size(); i ++) {
        for (size_t j = 0; j < _map[i].length(); j ++) {
            if (_map[i][j] == '#')
                mapSFML.push_back(make_shared<Block>(Block(j * 157, i * 157, 157)));
            else if (_map[i][j] == ' ');
            else if (_map[i][j] == 'E');
            else if (_map[i][j] == 'o');
            else if (_map[i][j] == '1');
            else if (_map[i][j] == '2');
            else if (_map[i][j] == '3');
            else if (_map[i][j] == 'P');
            else if (_map[i][j] == 'Y')
                mapSFML.push_back(make_shared<Block>(Block(j * 157, i * 157, 157, Block::Type::YELLOW)));
            else if (_map[i][j] == 'U')
                mapSFML.push_back(make_shared<Block>(Block(j * 157, i * 157, 157, Block::Type::PURPLE)));
            else if (_map[i][j] == 'B')
                mapSFML.push_back(make_shared<Block>(Block(j * 157, i * 157, 157, Block::Type::BLUE)));
            else
                throw (Exception("Unknown Symbol in File: Abort"));
        }
    }
}


shared_ptr<sf::RenderWindow> GameLoop::getWindow(void) 
{
    return this->window;
}

void GameLoop::clear()
{
    window->clear(sf::Color::White);
}

int GameLoop::checkOpen()
{
    return window->isOpen();
}

void GameLoop::checkDestruction(vector<shared_ptr<Block>> &mapSFML)
{
    int res = -1;

    for (int i = 0; i < projectile.size(); i++) {
        res = -1;
        res = projectile[i]->checkDestruction(mapSFML);
        if (res == 0)
            projectile.erase(projectile.begin() + i);
    }
}

void GameLoop::checkDeathEnemy(vector<shared_ptr<Ennemi>> &Ennemilist)
{
    int res = -1;
    sf::Sprite persoSprite = perso->getSprite();
    sf::Vector2f swordPoint = persoSprite.getPosition();

    for (size_t i = 0; i < projectile.size(); i++) {
        res = -1;
        for (size_t j = 0; j < Ennemilist.size() && res != 0 && res != 1; j++) {
            res = projectile[i]->checkKill(Ennemilist[j]);
            if (projectile[i]->getCurrentCapacity() <= 0) {
                gameMusic->startDeathMusic();
                projectile.erase(projectile.begin() + i);
            }
            if (res == 1)
                Ennemilist.erase(Ennemilist.begin() + j);
        }
    }
    swordPoint.y += (persoSprite.getTextureRect().height * persoSprite.getScale().y) / 3;
    if (persoSprite.getScale().x > 0)
        swordPoint.x += persoSprite.getTextureRect().width * persoSprite.getScale().x;
    else
        swordPoint.x -= persoSprite.getTextureRect().width * persoSprite.getScale().x * -1;
    for (size_t j = 0; j < Ennemilist.size() && res != 0 && res != 1; j++) {
        if (Ennemilist[j]->getSprite().getGlobalBounds().contains(swordPoint) == true 
            && perso->isCac() == true)
            Ennemilist.erase(Ennemilist.begin() + j);
    }
}

int GameLoop::movementEvent(sf::Event event)
{
    if (!perso->isShooting() && !perso->isChanneling() && !perso->isSwitching()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            perso->jump();
            return (3);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            perso->moveLeft(window, mapSFML);
            return (3);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return (3);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            perso->moveRigth(window, mapSFML);
            return (3);
        }
    }
    return (0);
}

int GameLoop::shootEvent()
{
    if (perso->getWeapon() == 4)
        perso->channeling();
    else
        perso->shoot();
    if (perso->getSprite().getScale().x > 0 && perso->getMunBattery() == 1)
        projectile.push_back(projFactory.createComponent(perso->getWeapon(), 1, perso->getSprite().getPosition(), 1));
    else if (perso->getSprite().getScale().x < 0 && perso->getMunBattery() == 1)
        projectile.push_back(projFactory.createComponent(perso->getWeapon(), -1, perso->getSprite().getPosition(), 1));
    return (3);
}

int GameLoop::switchWeaponEvent()
{
    gameMusic->pause_music(perso->getWeapon());
    perso->incWeapon();
    gameMusic->switch_music(perso->getWeapon());
    return (3);
}

int GameLoop::getEvent(std::vector<std::shared_ptr<Block>> mapSFML) {
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            return (-1);
        }
        if (event.type == sf::Event::MouseButtonReleased && perso->isActionPossible())
            return (shootEvent());
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F)
            return (switchWeaponEvent());
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) {
            perso->cacAttack();
            return (3);
        }
    }
    if (movementEvent(event) == 3)
        return (3);
    if (perso->isActionPossible()) {
        perso->restartPos();
        window->setView(window->getView());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window->setMouseCursorVisible(true);
        switch (EchapMenu().Menu(*window)) {
            case -1: return -1; // Quit
            case 0:  return 0;  // resume
            case 1:  return 1;  // replay
            case 2:  return 2;  // back
            default: throw (Exception("Error: Menu Failed: Abort"));  // Error
        }
        return 1;
    }
    return 0;
}

static void EnnemiUpdate(sf::RenderWindow &window, vector<shared_ptr<Ennemi>> &Ennemilist, vector<shared_ptr<Block>> mapSFML, shared_ptr<Character> &perso) {
    for (size_t i = 0; i < Ennemilist.size(); i ++) {
            window.draw(Ennemilist[i]->getSprite());
            Ennemilist[i]->move(mapSFML);
            if (perso->invulnerability < 1 && sf::IntRect(perso->getSprite().getGlobalBounds()).intersects(sf::IntRect(Ennemilist[i]->getSprite().getGlobalBounds()))) {
                perso->_lifes --;
                perso->invulnerability += 60;
            }
        }
}

static void BlockUpdate(sf::RenderWindow &window, vector<shared_ptr<Block>> mapSFML) {
    for (size_t i = 0; i < mapSFML.size(); i++)
            window.draw(mapSFML[i]->getSprite());
}

static int getTimeDiff(float diff, sf::Clock &clock)
{
    sf::Time time;
    float seconds = 0;

    time = clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > diff) {
        clock.restart();
        return (1);
    }
    return (0);
}

int GameLoop::fondue()
{
    sf::RectangleShape fade = sf::RectangleShape(sf::Vector2f(1920, 1080));
    sf::Event event;
    int quit = 0;
    sf::Clock clock = sf::Clock();
    sf::Font font;
    sf::Color c1(255, 255, 255, 255);
    sf::Color c2(255, 255, 255, 0);
    sf::Color c3(255, 255, 255, 0);
    sf::Color c4(255, 255, 255, 0);

    clock.restart();
    if (font.loadFromFile("./resources/character/arial.ttf") == false)
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
    while (window->isOpen() == true && quit != 1 || (c1.a != 255 && c2.a != 255 && c3.a != 255 && c4.a != 255)) {
        window->draw(fade);
        window->draw(text);
        window->draw(text2);
        window->draw(text3);
        window->draw(text4);
        if (c1.a == 255 && c2.a != 255) {
            if (getTimeDiff(0.01, clock) == 1)
                c2.a++;
            text2.setFillColor(c2);
        }
        if (c1.a == 255 && c2.a == 255 && c3.a != 255) {
            if (getTimeDiff(0.01, clock) == 1)
                c3.a++;
            text3.setFillColor(c3);
        }
        else if (c1.a == 255 && c2.a == 255 && c3.a == 255 && c4.a != 255) {
            if (getTimeDiff(0.01, clock) == 1)
                c4.a++;
            text4.setFillColor(c4);
        }
        if (c2.a == 255 && c3.a == 255 && c4.a == 255)
            break;
       //display();
       clear();
       while (window->pollEvent(event)) {
           if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S) {
            perso->incWeapon();
            return (true);
        }
       }
    }
    return (true);
}

int GameLoop::endScreen()
{
    sf::RectangleShape fade = sf::RectangleShape(sf::Vector2f(1920, 1080));
    sf::Event event;
    int quit = 0;
    sf::Clock clock = sf::Clock();
    sf::Font font;
    sf::Color c1(255, 255, 255, 255);
    sf::Color c2(255, 255, 255, 0);
    sf::Color c3(255, 255, 255, 0);
    sf::Color c4(255, 255, 255, 0);

    gameMusic->endAllMusic();
    gameMusic->startEndMusic();
    window->setView(window->getDefaultView());
    clock.restart();
    if (!font.loadFromFile("./resources/character/arial.ttf"))
        return (false);
    fade.setFillColor(sf::Color::Black);
    sf::Text text("Bravo Aventurier!\n", font);
    sf::Text text2("Apres avoir traverse de nombreuse epreuve vous etes finalement sortis tu temple.\n                                            En vie et avec la relique.\n", font);
    sf::Text text3("Vous rentrez chez vous avec et grace a son pouvoir vous devenez une personne riche et influente.\n", font);
    sf::Text text4("FIN\n", font);
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
    text3.setPosition(sf::Vector2f(305, 350));

    text4.setCharacterSize(30);
    text4.setStyle(sf::Text::Bold);
    text4.setFillColor(c4);
    text4.setPosition(sf::Vector2f(930, 500));
    while (window->isOpen() == true && quit != 1 || (c1.a != 255 && c2.a != 255 && c3.a != 255 && c4.a != 255)) {
        window->draw(fade);
        window->draw(text);
        window->draw(text2);
        window->draw(text3);
        window->draw(text4);
        if (c1.a == 255 && c2.a != 255) {
            if (getTimeDiff(0.01, clock) == 1)
                c2.a++;
            text2.setFillColor(c2);
        }
        if (c1.a == 255 && c2.a == 255 && c3.a != 255) {
            if (getTimeDiff(0.01, clock) == 1)
                c3.a++;
            text3.setFillColor(c3);
        }
        else if (c1.a == 255 && c2.a == 255 && c3.a == 255 && c4.a != 255) {
            if (getTimeDiff(0.01, clock) == 1)
                c4.a++;
            text4.setFillColor(c4);
        }
        if (c2.a == 255 && c3.a == 255 && c4.a == 255)
            break;
        //display();
        clear();
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S) {
                gameMusic->endEndMusic();
                return (true);
            }
       }
    }
    return (true);
}

void GameLoop::setPlayerPosition(vector<string> map) {
    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++)
            if (map[i][j] == 'P')
                perso->setSpritePosition(j * 157, i * 157 + 60);
}

void GameLoop::display(Door door_s)
{
    font->setPosition(sf::Vector2f(window->getView().getCenter().x - 960, window->getView().getCenter().y - 550));
    window->draw(font->getSprite());
    for (int i = 0; i < PlusList.size(); i++)
        PlusList[i]->display(window);
    BlockUpdate(*window, mapSFML);
    EnnemiUpdate(*window, Ennemilist, mapSFML, perso);
    window->draw(door_s.getSprite());
    perso->display(window, mapSFML);
    for (int i = 0; i < projectile.size(); i ++)
        projectile[i]->display(window);
    window->display();
}

enum CHOICE {QUIT = 0, REPLAY = 1};
int GameLoop::gameLoop(Door door) {
    size_t loop = 0;
    int is_end = 0;
    Door door_s = door;

    window->setMouseCursorVisible(false);
    gameMusic->playMainMusic();
    // if (!MainMenu().Menu(*window))
    //    return QUIT;
    // if (!fondue())
    //     return QUIT;
    gameMusic->stopMainMusic();
    window->setFramerateLimit(40);
    view->setCenter(perso->getSprite().getPosition());
    window->setView(*view);
    font->setScale(sf::Vector2f(3, 3.5));
    while (window->isOpen()) {
        door_s.doorOpen(perso->getSprite());
        perso->invulnerability = perso->invulnerability > 0 ? perso->invulnerability - 1 : perso->invulnerability;
        checkDestruction(mapSFML);
        checkDeathEnemy(Ennemilist);
        display(door);
        clear();
        perso->checkCollMunPlus(PlusList);
        if (perso->_lifes < 1) {
            gameMusic->startDeathMusic();
            window->setMouseCursorVisible(true);
            switch(DeathMenu().Menu(*window)) {
                case -1: window->close(); break;
                case 2: return REPLAY;
            }
        } try {
            switch(getEvent(mapSFML)) {
                case -1: window->close(); break;
                case 0:
                    view->setCenter(perso->getSprite().getPosition());
                    window->setView(*view);
                    break;
                case 2: return REPLAY;
                case 3: continue; break;
            }
            window->setMouseCursorVisible(false);
        } catch (Exception &e) {
            throw e;
        }
    }
    if (is_end == 1)
        endScreen();
    return QUIT;
}