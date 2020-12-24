/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** MapCreator
*/

#include <time.h>
#include <stdio.h>

#include "Map.hpp"
#include "System.hpp"
#include "Exception.hpp"

MapCreator::MapCreator(size_t width, size_t heigh) {
    block_row = 0;
    _width = width;
    _heigh = heigh;
    makeMapBounds();
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
        block_row = block_row > 3 ? 0 : block_row;
    } else if (event.type == sf::Event::MouseButtonPressed) {
        switch(block_row) {
            case 0: _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/blockCobble.png")); break;
            case 1: _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/brokable_blue.png")); break;
            case 2: _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/brokable_purple.png")); break;
            case 3: _mapimg.push_back(make_shared<ImageSFML>("resources/Images/Map/brokable_yellow.png")); break;
            default: throw Exception("Create New Bloc Failed: " + to_string(block_row) + " indexe unkown.");
        }
        sf::Vector2f blockpos(0, 0);
        blockpos.x = (sf::Mouse::getPosition().x + view->getCenter().x - (1920 / 2)) - ((sf::Mouse::getPosition().x + (int)view->getCenter().x - (1920 / 2)) % 157);
        blockpos.y = (sf::Mouse::getPosition().y + view->getCenter().y - (1080 / 2)) - ((sf::Mouse::getPosition().y + (int)view->getCenter().y - (1080 / 2)) % 157);
        _mapimg[_mapimg.size() - 1]->setScale(sf::Vector2f(0.5, 0.5));
        _mapimg[_mapimg.size() - 1]->setPosition(blockpos);
        switch(block_row) {
            case 0: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = '#'; break;
            case 1: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = 'B'; break;
            case 2: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = 'U'; break;
            case 3: _map[sf::Mouse::getPosition().y / 157][sf::Mouse::getPosition().x / 157] = 'Y'; break;
            default: throw Exception("Create New Bloc Failed: " + to_string(block_row) + " indexe unkown.");
        }
    }

    //Views update
    if (sf::Mouse::getPosition().x < 25 && view->getCenter().x > 1920 / 2)
        view->setCenter(view->getCenter().x - 50, view->getCenter().y);
    if (sf::Mouse::getPosition().y < 25 && view->getCenter().y > 1080 / 2)
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
        case 0: cursor = make_shared<ImageSFML>("resources/Images/Map/blockCobble.png"); break;
        case 1: cursor = make_shared<ImageSFML>("resources/Images/Map/brokable_blue.png"); break;
        case 2: cursor = make_shared<ImageSFML>("resources/Images/Map/brokable_purple.png"); break;
        case 3: cursor = make_shared<ImageSFML>("resources/Images/Map/brokable_yellow.png"); break;
        default: throw Exception("Cursor Image Failed: " + to_string(block_row) + " indexe unkown.");
    }
    cursor->setScale(sf::Vector2f(0.5, 0.5));
    int X = (sf::Mouse::getPosition().x + view->getCenter().x - (1920 / 2)) - ((sf::Mouse::getPosition().x + (int)view->getCenter().x - (1920 / 2)) % 157);
    int Y = (sf::Mouse::getPosition().y + view->getCenter().y - (1080 / 2)) - ((sf::Mouse::getPosition().y + (int)view->getCenter().y - (1080 / 2)) % 157);
    cursor->setPosition(sf::Vector2f(X, Y));
    window->draw(cursor->getSprite());
}

void MapCreator::creator(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;
    sf::Vector2i cursorPos;

    srand(time(NULL));
    save = make_shared<ImageSFML>("resources/Buttons/Save.png");
    leave = make_shared<ImageSFML>("resources/Buttons/leave.png");

    save->setPosition(sf::Vector2f(25, 100));
    leave->setPosition(sf::Vector2f(25, 150));
    save->setScale(sf::Vector2f(0.25, 0.25));
    leave->setScale(sf::Vector2f(0.5, 0.5));

    view->setCenter(sf::Vector2f(1920 / 2, 1080 / 2));
    window->setView(*view);
    window->setFramerateLimit(20);
    while (window->isOpen()) {
        window->clear(sf::Color::Black);

        while (window->pollEvent(event)) {
            if (save->isClickedinView(event, *view)) {
                System().createFile("/maps/.map_" + to_string(rand()), _map);
                view->setCenter(0, 0);
                return;
            } else if (leave->isClickedinView(event, *view)) {
                view->setCenter(0, 0);
                return;
            }
            event_handling(window, event);
        }
        save->setPosition(sf::Vector2f(30 + view->getCenter().x - 1920 / 2, 100 + view->getCenter().y - 1080 / 2));
        leave->setPosition(sf::Vector2f(25 + view->getCenter().x - 1920 / 2, 300 + view->getCenter().y - 1080 / 2));
        for (size_t i = 0; i < _mapimg.size(); i ++)
            window->draw(_mapimg[i]->getSprite());
        drawWhichUnderMouse(window);
        window->draw(save->getSprite());
        window->draw(leave->getSprite());
        window->display();
    }
}

void MapCreator::addChar(char c, size_t x, size_t y) {_map[x + 3][y + 3] = c;}