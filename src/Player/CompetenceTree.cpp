#include "CompetenceTree.hpp"

CompetenceTree::CompetenceTree() {
    pts = 0;
    _spdshot = 0.06;
    _db_jump = false;
    _killshiel = false;
    _spdreload = 0.2;
    _speed = sf::Vector2f(0, 0);
    _lifeproj = sf::Vector2f(0, 0);
}
CompetenceTree::~CompetenceTree() {}

void CompetenceTree::upgradebyLevel(size_t lvl) {
    switch(lvl) {
        case 3: _speed.x += 3; _speed.y += 1; _spdshot = 0.04; _spdreload = 0.150; break;
        case 5: _speed.x += 3; _spdreload = 0.125; break;
        case 7: _speed.x += 3; _speed.y += 1; _spdshot = 0.02; _spdreload = 0.100; break;
        case 10: _speed.x += 3; _spdreload = 0.75; break;
        case 12: _speed.x += 3; _speed.y += 1; _spdshot = 0.01; _spdreload = 0.50; break;
        default: break;
    }
}

void CompetenceTree::competenceChoice(shared_ptr<ImageSFML> &image, size_t &pts, bool &spell) {
    pts -= 1;
    spell = true;
    image->setTexture("resources/Images/Hud/blue_heart.png");
}

void CompetenceTree::ChooseMenu(shared_ptr<sf::RenderWindow> window, shared_ptr<sf::View> view) {
    sf::Event event;
    string rpath = "resources/Images/Hud/heart.png";
    string bpath = "resources/Images/Hud/blue_heart.png";

    shared_ptr<ImageSFML> comp_1 = make_shared<ImageSFML>(_db_jump ? bpath : rpath);
    shared_ptr<ImageSFML> comp_2 = make_shared<ImageSFML>(_killshiel ? bpath : rpath);
    shared_ptr<TextSfml> comp_1_txt = make_shared<TextSfml>("Double Saut", "resources/Buttons/text/Aileron-BlackItalic.otf", sf::Color::Black, 1750 / 4, 800);
    shared_ptr<TextSfml> comp_2_txt = make_shared<TextSfml>("Kill Chield", "resources/Buttons/text/Aileron-BlackItalic.otf", sf::Color::Black, 1750 / 4 * 3, 800);
    shared_ptr<ImageSFML> background = make_shared<ImageSFML>("resources/Images/Menu/background_competence_tree.jpg");

    view->setCenter(sf::Vector2f(990, 540));
    window->setView(*view);

    background->setPosition(sf::Vector2f(0, -100));
    background->setScale(sf::Vector2f(2, 2));
    comp_1->setPosition(sf::Vector2f(1750 / 4, 540));
    comp_2->setPosition(sf::Vector2f(1750 / 4 * 3, 540));
    
    window->setFramerateLimit(20);
    window->setMouseCursorVisible(true);
    while (window->isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return;
        while (window->pollEvent(event)) {
            if (comp_1->isClickedinView(event, *view) && pts > 0)
                competenceChoice(comp_1, pts, _db_jump);
            else if (comp_2->isClickedinView(event, *view) && pts > 0)
                competenceChoice(comp_2, pts, _killshiel);
        }
        window->clear();
        window->draw(background->getSprite());
        window->draw(comp_1->getSprite());
        window->draw(comp_2->getSprite());
        window->draw(comp_1_txt->getData());
        window->draw(comp_2_txt->getData());
        window->display();
    }
    return;
}

size_t CompetenceTree::getPoints(void) {return pts;}
void CompetenceTree::setPoints(size_t news) {pts = news;}
bool CompetenceTree::getDoubleJump(void) const {return _db_jump;}
bool CompetenceTree::getKillShield(void) const {return _killshiel;}