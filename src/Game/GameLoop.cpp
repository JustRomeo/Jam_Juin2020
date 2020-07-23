/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GameLoop
*/

#include "Door.hpp"
#include "Echap.hpp"
#include "Death.hpp"
#include "System.hpp"
#include "GameLoop.hpp"
#include "MainMenu.hpp"
#include "MusicSFML.hpp"
#include "Multiplayer.hpp"

GameLoop::GameLoop() {
    try {
        gameMusic = make_shared<GameMusic>();
        window = make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SoundWaves");
        window->setFramerateLimit(60);
        auto image = sf::Image{};
        if (!image.loadFromFile("resources/Images/Icon/icon.png"))
            throw Exception("Loading Ressource Failed");
        window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
        view = make_shared<sf::View>(sf::FloatRect(0, 0, 1920, 1080));
        background = make_shared<Sprite>("resources/Images/Game/space.png");
        perso = make_shared<Character>();
        font = make_shared<ImageSFML>("resources/Images/Game/sprite_font.png");
        window->setView(*view);
    } catch (bad_alloc &e) {
        throw Exception("can't initiate window and view\n");
    }
}
GameLoop::~GameLoop() {}

void GameLoop::EnnemiGeneration(vector<string> map) {
    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++)
            if (map[i][j] == 'E')
                Ennemilist.push_back(make_shared<Ennemi>(Ennemi(j * 157, i * 157)));
}

void GameLoop::ItemsGeneration(vector<string> map) {
    size_t row = 0;
    vector<string> items = System().openfile("./maps/.item1");

    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++)
            if (map[i][j] == '+') {
                string name = System().strtowordarray(items[row], "|")[0];

                cout << "Generate: " << row << "° item > " << name << " | x:" << j << " y:" << i << endl;
                Itemslist.push_back(make_shared<Lootable>(Lootable(Lootable::TYPE::Object, name, j * 157, i * 157)));
                row += 1;
            }
}

void GameLoop::PlusGeneration(vector<string> map) {
    for (size_t i = 0; i < map.size(); i ++) {
        for (size_t j = 0; j < map[i].length(); j ++) {
            if (map[i][j] == '1')
                PlusList.push_back(make_shared<MunPlus>(1, j * 157 + 50, i * 157 + 60));
            else if (map[i][j] == '2')
                PlusList.push_back(make_shared<MunPlus>(2, j * 157 + 50, i * 157 + 60));
            else if (map[i][j] == '3')
                PlusList.push_back(make_shared<MunPlus>(3, j * 157 + 50, i * 157 + 60));
        }
    }
}

void GameLoop::MapGeneration(vector<string> _map) {
    for (size_t i = 0; i < _map.size(); i ++) {
        for (size_t j = 0; j < _map[i].length(); j ++) {
            switch(_map[i][j]) {
                case '+': break;
                case '#': mapSFML.push_back(make_shared<Block>(Block(j * 157, i * 157, 157))); break;
                case ' ': break;
                case 'o': break;
                case '1': break;
                case '2': break;
                case '3': break;
                case 'B': mapSFML.push_back(make_shared<Block>(Block(j * 157, i * 157, 157, Block::Type::BLUE))); break;
                case 'E': break;
                case 'P': break;
                case 'U': mapSFML.push_back(make_shared<Block>(Block(j * 157, i * 157, 157, Block::Type::PURPLE))); break;
                case 'Y': mapSFML.push_back(make_shared<Block>(Block(j * 157, i * 157, 157, Block::Type::YELLOW))); break;
                default:  throw (Exception("Unknown Symbol in File: Abort")); break;
            }
        }
    }
    door = make_shared<Door>(_map);
}


int GameLoop::checkOpen() {return window->isOpen();}
void GameLoop::clear() {window->clear(sf::Color::White);}
shared_ptr<sf::RenderWindow> GameLoop::getWindow(void) {return this->window;}

void GameLoop::checkDestruction(vector<shared_ptr<Block>> &mapSFML) {
    int res = -1;

    for (size_t i = 0; i < projectile.size(); i ++) {
        res = -1;
        res = projectile[i]->checkDestruction(mapSFML);
        if (res == 0)
            projectile.erase(projectile.begin() + i);
    }
}

void GameLoop::checkDeathEnemy(vector<shared_ptr<Ennemi>> &Ennemilist) {
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
            } if (res == 1)
                Ennemilist.erase(Ennemilist.begin() + j);
        }
    }
    swordPoint.y += (persoSprite.getTextureRect().height * persoSprite.getScale().y) / 3;
    if (persoSprite.getScale().x > 0)
        swordPoint.x += persoSprite.getTextureRect().width * persoSprite.getScale().x;
    else
        swordPoint.x -= persoSprite.getTextureRect().width * persoSprite.getScale().x * -1;
    for (size_t j = 0; j < Ennemilist.size() && res != 0 && res != 1; j ++) {
        if (Ennemilist[j]->getSprite().getGlobalBounds().contains(swordPoint)
            && perso->isCac())
            Ennemilist.erase(Ennemilist.begin() + j);
    }
}

int GameLoop::movementEvent(sf::Event event) {
    if (!perso->isShooting() && !perso->isChanneling() && !perso->isSwitching()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            perso->sprint();
        else
            perso->stopSprint();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            perso->jump();
            return (3);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            perso->moveLeft(window, mapSFML);
            return (3);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return (3);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            perso->moveRigth(window, mapSFML);
            return (3);
        }
    }
    return (0);
}

int GameLoop::shootEvent() {
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

int GameLoop::switchWeaponEvent() {
    gameMusic->pause_music(perso->getWeapon());
    perso->incWeapon();
    gameMusic->switch_music(perso->getWeapon());
    return (3);
}

int GameLoop::getEvent(vector<shared_ptr<Block>> mapSFML) {
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            return (-1);
        } if (event.type == sf::Event::MouseButtonReleased && perso->isActionPossible())
            return (shootEvent());
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F)
            return (switchWeaponEvent());
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) {
            perso->cacAttack();
            return (3);
        }
    } if (movementEvent(event) == 3)
        return (3);
    if (perso->isActionPossible()) {
        perso->restartPos();
        window->setView(window->getView());
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
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

static int getTimeDiff(float diff, sf::Clock &clock) {
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

int GameLoop::endScreen() {
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
    while (window->isOpen() && quit != 1 || (c1.a != 255 && c2.a != 255 && c3.a != 255 && c4.a != 255)) {
        window->draw(fade);
        window->draw(text);
        window->draw(text2);
        window->draw(text3);
        window->draw(text4);
        window->display();
        if (c1.a == 255 && c2.a != 255) {
            if (getTimeDiff(0.01, clock) == 1)
                c2.a ++;
            text2.setFillColor(c2);
        } if (c1.a == 255 && c2.a == 255 && c3.a != 255) {
            if (getTimeDiff(0.01, clock) == 1)
                c3.a ++;
            text3.setFillColor(c3);
        } else if (c1.a == 255 && c2.a == 255 && c3.a == 255 && c4.a != 255) {
            if (getTimeDiff(0.01, clock) == 1)
                c4.a ++;
            text4.setFillColor(c4);
        } if (c2.a == 255 && c3.a == 255 && c4.a == 255)
            break;
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

void GameLoop::display() {
    font->setPosition(sf::Vector2f(window->getView().getCenter().x - 960, window->getView().getCenter().y - 550));
    window->draw(font->getSprite());
    for (int i = 0; i < PlusList.size(); i++)
        PlusList[i]->display(window);
    BlockUpdate(*window, mapSFML);
    EnnemiUpdate(*window, Ennemilist, mapSFML, perso);
    window->draw(door->getSprite());
    perso->display(window, mapSFML);
    for (size_t i = 0; i < projectile.size(); i ++)
        projectile[i]->display(window);
    for (size_t i = 0; i < Itemslist.size(); i ++)
        window->draw(Itemslist[i]->getImage()->getSprite());
    window->display();
}

#include "Cinematique.hpp"
enum CHOICE {QUIT = 0, REPLAY = 1};
int GameLoop::gameLoop(Door door) {
    size_t loop = 0;
    //this->door = door;
    //Door door_s = door;

    window->setMouseCursorVisible(false);
    gameMusic->playMainMusic();
    if (!MainMenu().Menu(window) || !Cinematique().Intro(window, perso))
        return QUIT;
    gameMusic->stopMainMusic();
    window->setFramerateLimit(40);
    view->setCenter(perso->getSprite().getPosition());
    window->setView(*view);
    font->setScale(sf::Vector2f(3, 3.5));
    while (window->isOpen()) {
        this->door->doorOpen(perso->getSprite());
        perso->invulnerability = perso->invulnerability > 0 ? perso->invulnerability - 1 : perso->invulnerability;
        checkDestruction(mapSFML);
        checkDeathEnemy(Ennemilist);
        display();
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
            throw Exception("Error in map event: " + *e.what());
        }
    }
    return QUIT;
}