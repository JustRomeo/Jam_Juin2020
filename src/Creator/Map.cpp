/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** MapCreator
*/

#include "Map.hpp"
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

void MapCreator::event_handling(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;

    while (window->pollEvent(event)) {
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
            blockpos.x = sf::Mouse::getPosition().x - (sf::Mouse::getPosition().x % 157);
            blockpos.y = sf::Mouse::getPosition().y - (sf::Mouse::getPosition().y % 157);
            _mapimg[_mapimg.size() - 1]->setScale(sf::Vector2f(0.5, 0.5));
            _mapimg[_mapimg.size() - 1]->setPosition(blockpos);
            switch(block_row) {
                case 0: _map[sf::Mouse::getPosition().x / 157][sf::Mouse::getPosition().y / 157] = '#'; break;
                case 1: _map[sf::Mouse::getPosition().x / 157][sf::Mouse::getPosition().y / 157] = 'B'; break;
                case 2: _map[sf::Mouse::getPosition().x / 157][sf::Mouse::getPosition().y / 157] = 'U'; break;
                case 3: _map[sf::Mouse::getPosition().x / 157][sf::Mouse::getPosition().y / 157] = 'Y'; break;
                default: throw Exception("Create New Bloc Failed: " + to_string(block_row) + " indexe unkown.");
            }
        }
        if (sf::Mouse::getPosition().x < 25)
            view->setCenter(view->getCenter().x - 5, view->getCenter().y);
        if (sf::Mouse::getPosition().y < 25)
            view->setCenter(view->getCenter().x, view->getCenter().y - 5);
        if (sf::Mouse::getPosition().x > 1895)
            view->setCenter(view->getCenter().x + 5, view->getCenter().y);
        if (sf::Mouse::getPosition().y > 1055)
            view->setCenter(view->getCenter().x, view->getCenter().y + 5);
    }
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
    cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - (sf::Mouse::getPosition().x % 157), sf::Mouse::getPosition().y - (sf::Mouse::getPosition().y % 157)));
    window->draw(cursor->getSprite());
}

void MapCreator::creator(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;
    sf::Vector2i cursorPos;

    view->setCenter(sf::Vector2f(1920 / 2, 1080 / 2));
    window->setView(*view);
    window->setFramerateLimit(20);
    while (window->isOpen()) {
        window->clear(sf::Color::Black);

        event_handling(window);
        for (size_t i = 0; i < _mapimg.size(); i ++)
            window->draw(_mapimg[i]->getSprite());
        drawWhichUnderMouse(window);
        window->display();
    }
}

void MapCreator::addChar(char c, size_t x, size_t y) {_map[x + 3][y + 3] = c;}