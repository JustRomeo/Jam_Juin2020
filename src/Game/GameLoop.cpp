/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Gameloop
*/

#include "Door.hpp"
#include "Death.hpp"
#include "System.hpp"
#include "MapMenu.hpp"
#include "GameLoop.hpp"
#include "MainMenu.hpp"
#include "MusicSFML.hpp"
#include "MapUpdater.hpp"
#include "Multiplayer.hpp"
#include "Cinematique.hpp"
#include "InputControler.hpp"


enum CHOICE {QUIT = 0, REPLAY = 1, RETURN = -1};
GameLoop::GameLoop() {
    try {
        auto image = sf::Image{};
        if (!image.loadFromFile("resources/Images/Icon/icon.png"))
            throw Exception("Loading Ressource Failed");
        perso = make_shared<Character>();
        perso2 = make_shared<Character>();
        gameMusic = make_shared<GameMusic>();
        echapMenu = make_shared<EchapMenu>(_sound);
        view = make_shared<sf::View>(sf::FloatRect(0, 0, 1920, 1080));
        background = make_shared<Sprite>("resources/Images/Game/space.png");
        font = make_shared<ImageSFML>("resources/Images/Game/sprite_font.png");
        window = make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SoundWaves");
        window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

        _players = 1;
        _sound = true;
        _remote = Controler::KeyBoard;
        RemoteControler = make_shared<ManetteSFML>();

        window->setView(*view);
        window->setFramerateLimit(60);
    } catch (bad_alloc &e) {
        throw Exception("Can't initiate window and view\n");
    }
}
GameLoop::~GameLoop() {}

void GameLoop::EnnemiGeneration(vector<string> map) {
    size_t row = 0;

    Bar->load(window, "Generation   des   Ennemis");
    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++) {
            if (map[i][j] == 'E') {
                Bar->load(window, "Generation   des   Ennemis   Walkers(" + to_string(row) + ")");
                Ennemilist.push_back(make_shared<Ennemi>(Ennemi(j * 157, i * 157)));
                row += 1;
            } else if (map[i][j] == 'R') {
                Bar->load(window, "Generation   des   Ennemis   Runners(" + to_string(row) + ")");
                Runnerlist.push_back(make_shared<Runner>(Runner(j * 157, i * 157)));
                row += 1;
            }
        }
}

void GameLoop::reloadPerso(shared_ptr<sf::Texture> texture) {
    perso = make_shared<Character>(texture);
}

int GameLoop::menu() {
    int res = -1;
    size_t value;
    vector<string> map;

    window->setMouseCursorVisible(true);
    gameMusic->playMainMusic();
    try {
        while (res == -1) {
            if (!MainMenu().Menu(window, *this))
                return QUIT;
            Bar = make_shared<LoadingBar>(1500, 25, 22);
            value = MapMenu().choice(*this);
            Bar->load(window, "Je fais un test");

            if (value != RETURN) {
                map = System().openfile("maps/.map" + to_string(value));
                Bar->load(window);
                reset_map();
                Bar->load(window);
                EnnemiGeneration(map);
                Bar->load(window);
                PlusGeneration(map);
                Bar->load(window);
                MapGeneration(map);
                Bar->load(window);
                MapUpdater().setPlayerPosition(map, perso);
                Bar->load(window);
                if (_players > 1) {
                    Bar->load(window, "Placement   du   second   joueur   sur   la   map.");
                    MapUpdater().setSecondPlayerPosition(map, perso2);
                }
                Bar->load(window);
                ItemsGeneration(map);
                Bar->load(window);
                return gameLoop();
            }
        }
    } catch (Exception &e) {
        cout << e.what() << endl;
    }
    return (QUIT);
}

void GameLoop::reset_map(void) {
    Bar->load(window, "Nettoyage   de   la   map");
    mapSFML.clear();
    Bar->load(window, "Nettoyage   des   boosters");
    PlusList.clear();
    Bar->load(window, "Nettoyage   des   items");
    Itemslist.clear();
    Bar->load(window, "Nettoyage   des   ennemis");
    Ennemilist.clear();
    Bar->load(window, "Nettoyage   des   projectiles");
    projectile.clear();
}

void GameLoop::ItemsGeneration(vector<string> map) {
    size_t row = 0;
    vector<string> items = System().openfile("./maps/.item1");

    Bar->load(window, "Generation   des   Items");
    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++)
            if (map[i][j] == '+') {
                string name = System().strtowordarray(items[row], "|")[0];

                Bar->load(window, "Generation   des   Items(" + to_string(row) + ")", false);
                Itemslist.push_back(make_shared<Lootable>(Lootable(Lootable::TYPE::Object, name, j * 157, i * 157)));
                row += 1;
            }
}

void GameLoop::PlusGeneration(vector<string> map) {
    size_t row = 0;

    Bar->load(window, "Generation   des   Boosters(" + to_string(row) + ")");
    for (size_t i = 0; i < map.size(); i ++) {
        for (size_t j = 0; j < map[i].length(); j ++) {
            if (map[i][j] == '1' || map[i][j] == '2' || map[i][j] == '3') {
                row ++;
                Bar->load(window, "Generation   des   Boosters(" + to_string(row) + ")", false);
            } switch(map[i][j]) {
                case '1': PlusList.push_back(make_shared<MunPlus>(1, j * 157 + 50, i * 157 + 60)); break;
                case '2': PlusList.push_back(make_shared<MunPlus>(2, j * 157 + 50, i * 157 + 60)); break;
                case '3': PlusList.push_back(make_shared<MunPlus>(3, j * 157 + 50, i * 157 + 60)); break;
                default: continue;
            }
        }
    }
}

void GameLoop::MapGeneration(vector<string> _map) {
    size_t row = 0;

    Bar->load(window, "Generation   de   la   Map");
    for (size_t i = 0; i < _map.size(); i ++) {
        Bar->load(window, "Generation   de   la   Map(" + to_string(row) + "/" + to_string(_map.size() * _map[i].length()) + ")", false);
        for (size_t j = 0; j < _map[i].length(); j ++, row ++) {
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
                case 'R': break;
                case 'S': break;
                case 'U': mapSFML.push_back(make_shared<Block>(Block(j * 157, i * 157, 157, Block::Type::PURPLE))); break;
                case 'Y': mapSFML.push_back(make_shared<Block>(Block(j * 157, i * 157, 157, Block::Type::YELLOW))); break;
                default:  throw (Exception("Unknown Symbol in File: Abort")); break;
            }
        }
    }
    door = make_shared<Door>(_map);
}

void GameLoop::earnXp(shared_ptr<Character> &perso, size_t var) {
    perso->exp += var;
    while (perso->exp >= perso->lvl) {
        perso->exp -= perso->lvl;
        perso->lvl ++;
        perso->_comptree->upgradebyLevel(perso->lvl);
    }
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
                earnXp(perso, 1);
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
        if (Ennemilist[j]->getSprite().getGlobalBounds().contains(swordPoint) && perso->isCac())
            Ennemilist.erase(Ennemilist.begin() + j);
    }
}

void GameLoop::checkDeathRunner(vector<shared_ptr<Runner>> &Runnerlist) {
    int res = -1;
    sf::Sprite persoSprite = perso->getSprite();
    sf::Vector2f swordPoint = persoSprite.getPosition();

    for (size_t i = 0; i < projectile.size(); i ++) {
        res = -1;
        for (size_t j = 0; j < Runnerlist.size() && res != 0 && res != 1; j++) {
            res = projectile[i]->checkKill(Runnerlist[j]);
            if (projectile[i]->getCurrentCapacity() <= 0) {
                if (_sound)
                    gameMusic->startDeathMusic();
                projectile.erase(projectile.begin() + i);
                earnXp(perso, 3);
            } if (res == 1)
                Runnerlist.erase(Runnerlist.begin() + j);
        }
    }
    swordPoint.y += (persoSprite.getTextureRect().height * persoSprite.getScale().y) / 3;
    if (persoSprite.getScale().x > 0)
        swordPoint.x += persoSprite.getTextureRect().width * persoSprite.getScale().x;
    else
        swordPoint.x -= persoSprite.getTextureRect().width * persoSprite.getScale().x * -1;
    for (size_t j = 0; j < Runnerlist.size() && res != 0 && res != 1; j ++) {
        if (Runnerlist[j]->getSprite().getGlobalBounds().contains(swordPoint) && perso->isCac())
            Runnerlist.erase(Runnerlist.begin() + j);
    }
}

int GameLoop::movementEvent(sf::Event event) {
    if (!perso->isShooting() && !perso->isChanneling() && !perso->isSwitching()) {
        if (InputControler().isSprinting())
            perso->sprint();
        else
            perso->stopSprint();
        if (InputControler().isJumping()) {
            perso->jump();
            return (3);
        } if (InputControler().isLeft()) {
            perso->moveLeft(window, mapSFML);
            return (3);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return (3);
        if (InputControler().isRight()) {
            perso->moveRigth(window, mapSFML);
            return (3);
        }
    }
    return 0;
}

int GameLoop::SecondmovementEvent(sf::Event event) {
    if (!perso2->isShooting() && !perso2->isChanneling() && !perso2->isSwitching()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            perso2->sprint();
        else
            perso2->stopSprint();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            perso2->jump();
            return (3);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            perso2->moveLeft(window, mapSFML);
            return (3);
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            return (3);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            perso2->moveRigth(window, mapSFML);
            return (3);
        }
    }
    return 0;
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

int GameLoop::SecondshootEvent() {
    if (perso2->getWeapon() == 4)
        perso2->channeling();
    else
        perso2->shoot();
    if (perso2->getSprite().getScale().x > 0 && perso2->getMunBattery() == 1)
        projectile.push_back(projFactory.createComponent(perso2->getWeapon(), 1, perso2->getSprite().getPosition(), 1));
    else if (perso2->getSprite().getScale().x < 0 && perso2->getMunBattery() == 1)
        projectile.push_back(projFactory.createComponent(perso2->getWeapon(), -1, perso2->getSprite().getPosition(), 1));
    return (3);
}

int GameLoop::switchWeaponEvent() {
    perso->incWeapon();
    if (!_sound)
        return 3;
    gameMusic->pause_music(perso->getWeapon());
    gameMusic->switch_music(perso->getWeapon());
    return (3);
}

enum GameIssue {Quit = -1, resume = 0, replay = 1, back = 2};
int GameLoop::getEvent(vector<shared_ptr<Block>> mapSFML) {
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            return (-1);
        } if (perso->isActionPossible()) {
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left || InputControler().isShooting())
                return (shootEvent());
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Right || InputControler().isShooting()) {
                perso->hook(window);
                return (3);
            }
        } if (InputControler().isSwitching())
            return (switchWeaponEvent());
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) {
            perso->cacAttack();
            return (3);
        }
    } if (movementEvent(event) == 3)
        return (3);
    if (_players > 1 && SecondmovementEvent(event) == 3)
        return (3);
    if (perso->isActionPossible()) {
        perso->restartPos();
        window->setView(window->getView());
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window->setMouseCursorVisible(true);
        switch (echapMenu->Menu(window)) {
            case -1: return Quit;
            case 0:  return resume;
            case 1:  return replay;
            case 2:  return back;
            default: throw (Exception("Error: Menu Failed: Abort"));
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
    MapUpdater().RunnerUpdate(*window, Runnerlist, mapSFML, perso);
    if (_players > 1) {
        MapUpdater().RunnerUpdate(*window, Runnerlist, mapSFML, perso2);
        MapUpdater().EnnemiUpdate(*window, Ennemilist, mapSFML, perso2);
    }
    window->draw(door->getSprite());
    perso->display(window, mapSFML);
    if (_players > 1)
        perso2->display(window, mapSFML);
    for (size_t i = 0; i < projectile.size(); i ++)
        projectile[i]->display(window);
    for (size_t i = 0; i < Itemslist.size(); i ++)
        window->draw(Itemslist[i]->getImage()->getSprite());
    window->display();
}

int GameLoop::gameLoop() {
    if (!Cinematique().Intro(window, perso))
        return QUIT;
    gameMusic->stopMainMusic();
    window->setFramerateLimit(40);
    view->setCenter(perso->getSprite().getPosition());
    window->setView(*view);
    font->setScale(sf::Vector2f(3, 3.5));
    window->setMouseCursorVisible(false);
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
        if (_players > 1)
            perso2->invulnerability = perso2->invulnerability > 0 ? perso2->invulnerability - 1 : perso2->invulnerability;
        MapUpdater().checkDestruction(mapSFML, projectile);
        checkDeathEnemy(Ennemilist);
        checkDeathRunner(Runnerlist);
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
void GameLoop::setPlayerNumber(int nbr) {_players = nbr;}
void GameLoop::clear() {window->clear(sf::Color::White);}
shared_ptr<Character> GameLoop::getCharacter(void) const {return perso;}
shared_ptr<sf::RenderWindow> GameLoop::getWindow(void) {return this->window;}
shared_ptr<Character> GameLoop::getSecondCharacter(void) const {return perso2;}
