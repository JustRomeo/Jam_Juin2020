/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Loading Bar File
*/

#include "Exception.hpp"
#include "LoadingBar.hpp"

LoadingBar::LoadingBar() {
    _max = 0;
    _row = 0;
    _total_width = 0;
    _rectangle = make_shared<sf::RectangleShape>(sf::Vector2f(200, 25));
    _text = make_shared<TextSfml>("", "resources/Buttons/text/Aileron-Heavy.otf", sf::Color::White, 200, 850);
    _rectangle->setFillColor(sf::Color::Green);
    _rectangle->setPosition(sf::Vector2f(200, 900));
}
LoadingBar::LoadingBar(size_t total_width, size_t heigh, size_t max) {
    _row = 0;
    if (max < 0)
        throw Exception("Cannot set a loading Max count in negative number or digits");
    _max = max;
    if (total_width < 0)
        throw Exception("Cannot set a LoadingBar max width in negative number or digits");
    _total_width = total_width;
    _rectangle = make_shared<sf::RectangleShape>(sf::Vector2f(total_width / max, heigh));
    _text = make_shared<TextSfml>("Test", "resources/Buttons/text/Aileron-Heavy.otf", sf::Color::White, 200, 850);
    _rectangle->setFillColor(sf::Color::Green);
    _rectangle->setPosition(sf::Vector2f(200, 900));
    _isText = true;
}
LoadingBar::~LoadingBar() {}

void LoadingBar::load(shared_ptr<sf::RenderWindow> window, string text, bool inc) {
    if (_row == _max && inc)
        return;
    if (inc)
        _row += 1;
    _rectangle->setSize(sf::Vector2f(_total_width / _max * _row, 25));

    if (text != "")
        _text->setString(text);
    window->clear();
    window->draw(*_rectangle);
    if (_isText)
        window->draw(_text->getData());
    window->display();
}

void LoadingBar::setMax(size_t max) {
    if (max < 0)
        throw Exception("Cannot set a loading Max count in negative number or digits");
    _max = max;
}

void LoadingBar::setRow(size_t row) {
    if (row < 0)
        throw Exception("Cannot set a loading row in negative number or digits");
    _row = row;
}

void LoadingBar::isText(bool text) {_isText = text;}
size_t LoadingBar::getRow(void) const {return _row;}
size_t LoadingBar::getMax(void) const {return _max;}
bool LoadingBar::isText(void) const {return _isText;}
size_t LoadingBar::getTotalWidth(void) const {return _total_width;}
shared_ptr<TextSfml> LoadingBar::getText(void) const {return _text;}
void LoadingBar::setTotalWidth(size_t total) {_total_width = total;}
shared_ptr<sf::RectangleShape> LoadingBar::getRectangle(void) const {return _rectangle;}
void LoadingBar::setRectangle(shared_ptr<sf::RectangleShape> newrect) {_rectangle = _rectangle;}
