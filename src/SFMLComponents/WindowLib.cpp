#include "WindowLib.hpp"

WindowLib::WindowLib() {}
WindowLib::~WindowLib() {}

void WindowLib::drawSprites(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<ImageSFML>> sprites) {
    for (size_t i = 0; i < sprites.size(); i ++)
        window->draw(sprites[i]->getSprite());
}
