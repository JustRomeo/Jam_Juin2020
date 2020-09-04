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
#include "MapMenu.hpp"
#include "GameLoop.hpp"
#include "MainMenu.hpp"
#include "MusicSFML.hpp"
#include "MapUpdater.hpp"
#include "Multiplayer.hpp"
#include "Cinematique.hpp"

enum CHOICE {QUIT = 0, REPLAY = 1, RETURN = -1};

GameLoop::GameLoop() {
    try {
        _sound = true;
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

void GameLoop::EnnemiGeneration(vector<string> map)
{
    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++)
            if (map[i][j] == 'E')
                Ennemilist.push_back(make_shared<Ennemi>(Ennemi(j * 157, i * 157)));
}

int GameLoop::menu()
{
    int res = -1;
    vector<string> map;
    size_t value;

    window->setMouseCursorVisible(true);
    gameMusic->playMainMusic();
    try {
        while (res == -1) {
            if (!MainMenu().Menu(window))
                return QUIT;
            value = MapMenu().choice(*this);
            if (value != RETURN) {
                map = System().openfile("maps/.map" + to_string(value));
                reset_map();
                EnnemiGeneration(map);
                PlusGeneration(map);
                MapGeneration(map);
                MapUpdater().setPlayerPosition(map, perso);
                ItemsGeneration(map);
                return (gameLoop());
            }
        }
    } catch (Exception &e) {
        cout << e.what() << endl;
    }
    return (QUIT);
}

void GameLoop::reset_map(void) {
    mapSFML.clear();
    PlusList.clear();
    Itemslist.clear();
    Ennemilist.clear();
    projectile.clear();
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
            switch(map[i][j]) {
                case '1': PlusList.push_back(make_shared<MunPlus>(1, j * 157 + 50, i * 157 + 60)); break;
                case '2': PlusList.push_back(make_shared<MunPlus>(2, j * 157 + 50, i * 157 + 60)); break;
                case '3': PlusList.push_back(make_shared<MunPlus>(3, j * 157 + 50, i * 157 + 60)); break;
                default: continue;
            }
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

void GameLoop::checkDeathEnemy(vector<shared_ptr<Ennemi>> &Ennemilist) {
    int res = -1;
    sf::Sprite persoSprite = perso->getSprite();
    sf::Vector2f swordPoint = persoSprite.getPosition();

    for (size_t i = 0; i < projectile.size(); i ++) {
        res = -1;
        for (size_t j = 0; j < Ennemilist.size() && res != 0 && res != 1; j++) {
            res = projectile[i]->checkKill(Ennemilist[j]);
            if (projectile[i]->getCurrentCapacity() <= 0) {
                if (_sound)
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

int GameLoop::movementEvent(sf::Event event)
{
    if (!perso->isShooting() && !perso->isChanneling() && !perso->isSwitching()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            perso->sprint();
        else
            perso->stopSprint();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            perso->jump();
            return (3);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            perso->moveLeft(window, mapSFML);
            return (3);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return (3);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
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
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left &&  perso->isActionPossible())
            return (shootEvent());
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Right && perso->isActionPossible()) {
            perso->hook(window);
            return (3);
        }
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
        switch (EchapMenu().Menu(*window, _sound)) {
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

void GameLoop::display() {
    font->setPosition(sf::Vector2f(window->getView().getCenter().x - 960, window->getView().getCenter().y - 550));
    window->draw(font->getSprite());
    for (size_t i = 0; i < PlusList.size(); i ++)
        PlusList[i]->display(window);
    MapUpdater().BlockUpdate(*window, mapSFML);
    MapUpdater().EnnemiUpdate(*window, Ennemilist, mapSFML, perso);
    window->draw(door->getSprite());
    perso->display(window, mapSFML);
    for (size_t i = 0; i < projectile.size(); i ++)
        projectile[i]->display(window);
    for (size_t i = 0; i < Itemslist.size(); i ++)
        window->draw(Itemslist[i]->getImage()->getSprite());
    window->display();
}

int GameLoop::gameLoop()
{
    size_t loop = 0;

    if (!Cinematique().Intro(window, perso))
        return QUIT;
    gameMusic->stopMainMusic();
    window->setFramerateLimit(40);
    view->setCenter(perso->getSprite().getPosition());
    window->setView(*view);
    font->setScale(sf::Vector2f(3, 3.5));
    window->setMouseCursorVisible(true);
    while (window->isOpen()) {
        for (size_t i = 0; i < Itemslist.size(); i ++)
            if (sf::IntRect(perso->getSprite().getGlobalBounds()).intersects(sf::IntRect(Itemslist[i]->getImage()->getSprite().getGlobalBounds()))) {
                perso->addValue(Itemslist[i]->getObject());
                Itemslist.erase(Itemslist.begin() + i);

                for (size_t i = 0; i < perso->getItems().size(); i ++)
                    cout << perso->getItems()[i]->getName() << endl;
            }
        this->door->doorOpen(perso->getSprite());
        perso->invulnerability = perso->invulnerability > 0 ? perso->invulnerability - 1 : perso->invulnerability;
        MapUpdater().checkDestruction(mapSFML, projectile);
        checkDeathEnemy(Ennemilist);
        display();
        clear();
        perso->checkCollMunPlus(PlusList);
        if (perso->_lifes < 1) {
            if (_sound)
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
        } catch (Exception &e) {
            throw Exception("Error in map event: " + *e.what());
        } if (!_sound)
            gameMusic->endAllMusic();
    }
    return QUIT;
}

int GameLoop::checkOpen() {return window->isOpen();}
void GameLoop::clear() {window->clear(sf::Color::White);}
shared_ptr<Character> GameLoop::getCharacter(void) const {return perso;}
shared_ptr<sf::RenderWindow> GameLoop::getWindow(void) {return this->window;}
