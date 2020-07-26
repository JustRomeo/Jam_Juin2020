#include "Paths.hpp"
#include "System.hpp"
#include "MapMenu.hpp"

MapMenu::MapMenu() {}
MapMenu::~MapMenu() {}

size_t MapMenu::choice(GameLoop game) {
    sf::Event event;
    vector<string> maps;
    ImageSFML *cursor;
    ImageSFML *background;
    vector<shared_ptr<TextSfml>> texts;
    vector<shared_ptr<ImageSFML>> images;

    try {
        cursor = new ImageSFML("resources/Images/Game/cursor.png");
        background = new ImageSFML("resources/Images/Game/wallpaper.jpg");

        game.reset_map();
        Paths().fillPathList(maps, "maps/");
        maps = getOnlyMaps(maps);
        texts = loadTexts(maps);
        images = loadImages(maps);
        cursor->setScale(sf::Vector2f(2.4, 2.4));
    } catch (Exception &e) {
        throw Exception("Initialisation failed: " + *e.what());
    }
    while (game.getWindow()->isOpen()) {
        cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition().x - 75, sf::Mouse::getPosition().y - 110));
        game.getWindow()->draw(background->getSprite());
        for(size_t i = 0; i < maps.size(); i ++) {
            game.getWindow()->draw(images[i]->getSprite());
            game.getWindow()->draw(texts[i]->getData());
        } while (game.getWindow()->pollEvent(event)) {
            for(size_t i = 0; i < images.size(); i ++)
                if (images[i]->isClicked(event))
                    return i;
        }
        game.getWindow()->draw(cursor->getSprite());
        game.getWindow()->display();
    }
    return 0;
}

vector<string> MapMenu::getOnlyMaps(vector<string> files) {
    vector<string> maps;
    vector<TextSfml> texts;
    vector<ImageSFML> images;

    for (size_t i = 0; i < files.size(); i ++)
        if (files[i].find(".map") != string::npos)
            maps.push_back(files[i]);
    return maps;
}

vector<shared_ptr<TextSfml>> MapMenu::loadTexts(vector<string> maps) {
    vector<shared_ptr<TextSfml>> texts;

    for (size_t i = 0; i < maps.size(); i ++) {
        texts.push_back(make_shared<TextSfml>(maps[i], "resources/character/arial.ttf", sf::Color::Black, 0, 0));
        texts[i]->setSize(35);
        texts[i]->setPosition(sf::Vector2f(900, 330 + 110 * i));
    }
    return texts;
}

vector<shared_ptr<ImageSFML>> MapMenu::loadImages(vector<string> maps) {
    vector<shared_ptr<ImageSFML>> images;

    for (size_t i = 0; i < maps.size(); i ++) {
        images.push_back(make_shared<ImageSFML>("resources/Buttons/empty.png"));
        images[i]->setPosition(sf::Vector2f(800, 300 + 110 * i));
    }
    return images;
}
