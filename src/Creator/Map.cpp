/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** MapCreator File
*/

#include <time.h>
#include <stdio.h>

#include "Map.hpp"
#include "System.hpp"
#include "TextSFML.hpp"
#include "Exception.hpp"

MapCreator::MapCreator(size_t width, size_t heigh) {
    block_row = 0;
    _width = width;
    _heigh = heigh;
    makeMapBounds();
    isPersoPlaced = false;
    view = make_shared<sf::View>(sf::FloatRect(0, 0, 1920, 1080));
}

MapCreator::~MapCreator() {}

void MapCreator::makeMapBounds(void) {
    for (size_t i = 0; i < 3; i ++) {
        string line = "###";
        for (size_t j = 0; j < _width; j ++)
            line += "#";
        line += "###";
        _map.push_back(line);
        for (size_t j = 0; j < line.size(); j ++) {
            _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/blockCobble.png"));
            _mapimg[_mapimg.size() - 1]->setPosition(sf::Vector2f(j * 157, i * 157));
            _mapimg[_mapimg.size() - 1]->setScale(sf::Vector2f(0.5, 0.5));
        }
    } for (size_t i = 0; i < _heigh; i ++) {
        string line = "###";
        for (size_t j = 0; j < _width; j ++)
            line += " ";
        line += "###";
        _map.push_back(line);
        for (size_t j = 0; j < line.size(); j ++) {
            if (line[j] == '#') {
                _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/blockCobble.png"));
                _mapimg[_mapimg.size() - 1]->setPosition(sf::Vector2f(j * 157, i * 157));
                _mapimg[_mapimg.size() - 1]->setScale(sf::Vector2f(0.5, 0.5));
            }
        }
    } for (size_t i = 0; i < 3; i ++) {
        string line = "###";
        for (size_t j = 0; j < _width; j ++)
            line += "#";
        line += "###";
        _map.push_back(line);
        for (size_t j = 0; j < line.size(); j ++) {
            _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/blockCobble.png"));
            _mapimg[_mapimg.size() - 1]->setPosition(sf::Vector2f(j * 157, _mapimg.size() * 157));
            _mapimg[_mapimg.size() - 1]->setScale(sf::Vector2f(0.5, 0.5));
        }
    }
}

void MapCreator::event_handling(shared_ptr<sf::RenderWindow> window, sf::Event event) {
    //Inputs
    if (event.type == sf::Event::MouseWheelMoved) {
        if (event.mouseWheel.delta > 0)
            block_row ++;
        else if (event.mouseWheel.delta < 0)
            block_row --;
        block_row = block_row > 6 ? 0 : block_row;
    } else if (event.type == sf::Event::MouseButtonPressed) {
        switch(block_row) {
            //Blocks
            case 0: _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/blockCobble.png")); break;
            case 1: _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/brokable_blue.png")); break;
            case 2: _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/brokable_purple.png")); break;
            case 3: _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/brokable_yellow.png")); break;

            //Entities
            case 4:
                if (!isPersoPlaced)
                    _mapimg.push_back(make_shared<ImageSFML>("resources/character/adventurer-v1.5-Sheet.png"));
                break;
            case 5: _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Game/robot.jpg")); break;

            //Items & Bonus
            case 6: _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Game/Object/bonus.png")); break;
            default: throw Exception("Create New Bloc Failed: " + to_string(block_row) + " indexe unkown.");
        } if (block_row == 4 && !isPersoPlaced) {
            sf::Sprite newone = _mapimg[_mapimg.size() - 1]->getSprite();

            newone.setTextureRect(sf::IntRect(65, 5, 19, 32));
            newone.setScale(sf::Vector2f(3, 3));
            newone.setPosition(sf::Vector2f(200, 1102 - (32 * 3)));
            _mapimg[_mapimg.size() - 1]->setSprite(newone);
            isPersoPlaced = true;
        } else if (block_row == 4 && isPersoPlaced)
            return;
        else
            _mapimg[_mapimg.size() - 1]->setScale(sf::Vector2f(0.5, 0.5));
        sf::Vector2f blockpos(0, 0);
        blockpos.x = (sf::Mouse::getPosition().x + view->getCenter().x - (window->getSize().x / 2)) - ((sf::Mouse::getPosition().x + (int)view->getCenter().x - (window->getSize().x / 2)) % 157);
        blockpos.y = (sf::Mouse::getPosition().y + view->getCenter().y - (window->getSize().y / 2)) - ((sf::Mouse::getPosition().y + (int)view->getCenter().y - (window->getSize().y / 2)) % 157);
        _mapimg[_mapimg.size() - 1]->setPosition(blockpos);
        switch(block_row) {
            //Blocks
            case 0: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = '#'; break;
            case 1: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = 'B'; break;
            case 2: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = 'U'; break;
            case 3: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = 'Y'; break;

            //Entities
            case 4: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = 'P'; break;
            case 5: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = 'E'; break;

            //Items & Bonus
            case 6: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = '+'; break;
            default: throw Exception("Create New Bloc Failed: " + to_string(block_row) + " indexe unkown.");
        }
    }

    //Views update
    if (sf::Mouse::getPosition().x < 25 && view->getCenter().x > window->getSize().x / 2)
        view->setCenter(view->getCenter().x - 50, view->getCenter().y);
    if (sf::Mouse::getPosition().y < 25 && view->getCenter().y > window->getSize().y / 2)
        view->setCenter(view->getCenter().x, view->getCenter().y - 50);
    if (sf::Mouse::getPosition().x > 1895 && view->getCenter().x < _width * 157)
        view->setCenter(view->getCenter().x + 50, view->getCenter().y);
    if (sf::Mouse::getPosition().y > 1055 && view->getCenter().y < _heigh * 157)
        view->setCenter(view->getCenter().x, view->getCenter().y + 50);
    window->setView(*view);
}

void MapCreator::drawWhichUnderMouse(shared_ptr<sf::RenderWindow> window) {
    shared_ptr<ImageSFML> cursor;

    switch(block_row) {
        //Blocks
        case 0: cursor = make_shared<ImageSFML>("resources/Images/Map/blockCobble.png"); break;
        case 1: cursor = make_shared<ImageSFML>("resources/Images/Map/brokable_blue.png"); break;
        case 2: cursor = make_shared<ImageSFML>("resources/Images/Map/brokable_purple.png"); break;
        case 3: cursor = make_shared<ImageSFML>("resources/Images/Map/brokable_yellow.png"); break;

        //Entities
        case 4: cursor = make_shared<ImageSFML>("resources/character/adventurer-v1.5-Sheet.png"); break;
        case 5: cursor = make_shared<ImageSFML>("resources/Images/Game/robot.jpg"); break;

        //Bonus & Items
        case 6: cursor = make_shared<ImageSFML>("resources/Images/Game/Object/bonus.png"); break;
        default: throw Exception("Cursor Image Failed: " + to_string(block_row) + " indexe unkown.");
    } if (block_row == 4) {
        sf::Sprite newone = cursor->getSprite();

        newone.setTextureRect(sf::IntRect(65, 5, 19, 32));
        newone.setScale(sf::Vector2f(3, 3));
        newone.setPosition(sf::Vector2f(200, 1102 - (32 * 3)));
        cursor->setSprite(newone);
    } else
        cursor->setScale(sf::Vector2f(0.5, 0.5));
    int X = (sf::Mouse::getPosition().x + view->getCenter().x - (window->getSize().x / 2)) - ((sf::Mouse::getPosition().x + (int)view->getCenter().x - (window->getSize().x / 2)) % 157);
    int Y = (sf::Mouse::getPosition().y + view->getCenter().y - (window->getSize().y / 2)) - ((sf::Mouse::getPosition().y + (int)view->getCenter().y - (window->getSize().y / 2)) % 157);
    cursor->setPosition(sf::Vector2f(X, Y));
    window->draw(cursor->getSprite());
}

void MapCreator::creator(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;
    sf::Vector2i cursorPos;
    size_t _count = 0;

    srand(time(NULL));
    save = make_shared<ImageSFML>("resources/Buttons/Save.png");
    leave = make_shared<ImageSFML>("resources/Buttons/leave.png");
    more = make_shared<ImageSFML>("resources/Images/Menu/more.png");
    less = make_shared<ImageSFML>("resources/Images/Menu/less.png");
    _back = make_shared<ImageSFML>("resources/Buttons/creator_back.png");
    shared_ptr<TextSfml> countText = make_shared<TextSfml>(to_string(_count), "resources/Buttons/text/Aileron-BlackItalic.otf", sf::Color::White, 1250, 350);

    _back->setPosition(sf::Vector2f(0, 0));
    save->setPosition(sf::Vector2f(25, 100));
    leave->setPosition(sf::Vector2f(25, 150));
    less->setPosition(sf::Vector2f(1800, 500));
    more->setPosition(sf::Vector2f(1800, 600));
    countText->setPosition(sf::Vector2f(1800, 560));
    
    more->setScale(sf::Vector2f(0.5, 0.5));
    _back->setScale(sf::Vector2f(0.5, 0.5));
    leave->setScale(sf::Vector2f(0.5, 0.5));
    save->setScale(sf::Vector2f(0.25, 0.25));
    less->setScale(sf::Vector2f(0.075, 0.080));

    view->setCenter(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
    window->setView(*view);
    window->setFramerateLimit(20);
    while (window->isOpen()) {
        window->clear(sf::Color::Black);
        view->setSize(window->getSize().x, window->getSize().y);
        _back->setPosition(sf::Vector2f(view->getCenter().x - window->getSize().x / 2, view->getCenter().y - window->getSize().y / 2));
        window->draw(_back->getSprite());

        while (window->pollEvent(event)) {
            if (save->isClickedinView(event, *view)) {
                view->setCenter(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
                window->setView(*view);
                vector<string> tosave;
                tosave.push_back("<i>level=" + to_string(_count * 2));
                for (size_t i = 0; i < _map.size(); i ++)
                    tosave.push_back(_map[i]);
                System().createFile("/maps/.map" + to_string(rand()), tosave);
                return;
            } else if (leave->isClickedinView(event, *view)) {
                view->setCenter(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
                window->setView(*view);
                return;
            } else if (more->isClickedinView(event, *view)) {
                _count += 1;
                countText->setString(to_string(_count));
            } else if (less->isClickedinView(event, *view) && _count > 0) {
                _count -= 1;
                countText->setString(to_string(_count));
            }
            event_handling(window, event);
        }
        save->setPosition(sf::Vector2f(30 + view->getCenter().x - (window->getSize().x / 2), 100 + view->getCenter().y - (window->getSize().y / 2)));
        leave->setPosition(sf::Vector2f(25 + view->getCenter().x - (window->getSize().x / 2), 300 + view->getCenter().y - (window->getSize().y / 2)));
        less->setPosition(sf::Vector2f(1800 + view->getCenter().x - (window->getSize().x / 2), 500 + view->getCenter().y - (window->getSize().y / 2)));
        more->setPosition(sf::Vector2f(1800 + view->getCenter().x - (window->getSize().x / 2), 600 + view->getCenter().y - (window->getSize().y / 2)));
        countText->setPosition(sf::Vector2f(1825 + view->getCenter().x - (window->getSize().x / 2), 560 + view->getCenter().y - (window->getSize().y / 2)));

        for (size_t i = 0; i < _mapimg.size(); i ++)
            window->draw(_mapimg[i]->getSprite());
        drawWhichUnderMouse(window);
        window->draw(save->getSprite());
        window->draw(more->getSprite());
        window->draw(countText->getData());
        window->draw(less->getSprite());
        window->draw(leave->getSprite());
        window->display();
    }
    view->setCenter(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
    window->setView(*view);
    return;
}

void MapCreator::addChar(char c, size_t x, size_t y) {_map[x + 3][y + 3] = c;}