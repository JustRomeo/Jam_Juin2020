#include "Paths.hpp"
#include "System.hpp"
#include "MapMenu.hpp"

MapMenu::MapMenu() {}
MapMenu::~MapMenu() {}

size_t MapMenu::choice(GameLoop game) {
    sf::Event event;
    vector<string> maps;
    shared_ptr<ImageSFML> cursor;
    shared_ptr<ImageSFML> background;

    try {
        cursor = make_shared<ImageSFML>("resources/Images/Game/cursor.png");
        background = make_shared<ImageSFML>("resources/Images/Game/wallpaper.jpg");

        Paths().fillPathList(maps, "maps/");
        // cout << "After Fill" << endl;
        // for (size_t i = 0; i < maps.size(); i ++)
        //     cout << maps[i] << endl;
        // exit(0);
        maps = getOnlyMaps(maps);
        loadImages(maps);
        loadTexts(maps);
        cursor->setScale(sf::Vector2f(2.4, 2.4));
        background->setScale(sf::Vector2f(1.6, 1.6));
    } catch (Exception &e) {
        throw Exception("Initialisation failed: " + *e.what());
    } while (game.getWindow()->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 110));
        game.getWindow()->draw(background->getSprite());
        for(size_t i = 0; i < maps.size(); i ++)
            button[i]->drawButton(game.getWindow());
        go_back_button->drawButton(game.getWindow());
        while (game.getWindow()->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game.getWindow()->close();
            for(size_t i = 0; i < button.size(); i ++) {
                if (button[i]->isClicked(event))
                    return i + 1;
                if (go_back_button->isClicked(event))
                    return -1;
            }
        }
        game.getWindow()->draw(cursor->getSprite());
        game.getWindow()->display();
    }
    return 0;
}

vector<string> MapMenu::getOnlyMaps(vector<string> files) {
    vector<string> maps;

    for (size_t i = 0; i < files.size(); i ++)
        if (files[i].find(".map") != string::npos)
            maps.push_back(files[i]);
    return maps;
}

void MapMenu::loadTexts(vector<string> maps) {
    go_back_button->setText("resources/character/arial.ttf", "Back", 35, sf::Color::Black);
    for (size_t i = 0; i < maps.size(); i ++)
        button[i]->setText("resources/character/arial.ttf", maps[i].replace(maps[i].find(".m"), 2, "M") , 35, sf::Color::Black);
}

void MapMenu::loadImages(vector<string> maps) {

    for (size_t i = 0; i < maps.size(); i ++) {
        button.push_back(make_shared<Button>(sf::Vector2f(800, 300 + 110 * i), sf::Vector2f(250, 100)));
        button[i]->setColor(sf::Color::White, sf::Color::Black, 5);
    }
    go_back_button = make_shared<Button>(sf::Vector2f(100, 700), sf::Vector2f(250, 100));
    go_back_button->setColor(sf::Color::White, sf::Color::Black, 5);
}
