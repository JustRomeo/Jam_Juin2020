#include "WindowLib.hpp"

WindowLib::WindowLib() {}
WindowLib::~WindowLib() {}

void WindowLib::drawSprites(shared_ptr<sf::RenderWindow> window, vector<ImageSFML> sprites) {
    for (size_t i = 0; i < sprites.size(); i ++)
        window->draw(sprites[i].getSprite());
}
