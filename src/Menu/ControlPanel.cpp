#include "ControlPanel.hpp"

ControlPanel::ControlPanel() {}
ControlPanel::~ControlPanel() {}

void ControlPanel::control_panel(shared_ptr<sf::RenderWindow> window) {
    sf::Event event;
    ImageSFML panel("resources/Images/Menu/Controltext.png");

    while (window->isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;
        window->draw(panel.getSprite());
        window->display();
    }
}