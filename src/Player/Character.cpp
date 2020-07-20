/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Character
*/

#include "Character.hpp"

Character::Character() {
    jump_sound = new MusicSFML();
    coli_sound = new MusicSFML();
    shot_sound = new MusicSFML();

    jump_sound->load("resources/Sounds/sounds/Jump.ogg");
    coli_sound->load("resources/Sounds/sounds/Colision.ogg");
    _lifes = 3;
    textureFight = std::make_shared<sf::Texture>();
    texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile("./resources/character/adventurer-Sheet.png") == false)
        throw(Exception("resources load failed"));
    if (textureFight->loadFromFile("./resources/character/adventurer-bow-Sheet.png") == false)
        throw(Exception("resources load failed"));
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
    sprite.setScale(sf::Vector2f(3.f, 3.f));
    sprite.setPosition(sf::Vector2f(200.f, 1102.f - (32.f * 3)));
    move_Y = 45;
    notMove_Y = 6;
    move_Xmax = 315;
    shootRectPos = 0;
    channelRectPos = 0;
    weapon_type = 1;
    invulnerability = 0;
    is_shooting = false;
    is_moving = false;
    is_falling = false;
    is_jumping = false;
    is_switching = false;
    is_channeling = false;
    move_clock.restart();
    anim_clock.restart();
    switch_clock.restart();
    hud = std::make_shared<HUD>();
    createAnimRec();
}

Character::~Character() {}

void Character::createAnimRec() {
    shootRect.push_back(sf::IntRect(12, 8, 35, 35));
    shootRect.push_back(sf::IntRect(62, 8, 28, 30));
    shootRect.push_back(sf::IntRect(114, 8, 29, 29));
    shootRect.push_back(sf::IntRect(162, 8, 34, 30));
    shootRect.push_back(sf::IntRect(12, 46, 30, 29));
    shootRect.push_back(sf::IntRect(64, 46, 26, 29));
    shootRect.push_back(sf::IntRect(113, 46, 35, 35));
    shootRect.push_back(sf::IntRect(159, 46, 40, 35));
    shootRect.push_back(sf::IntRect(12, 82, 34, 30));

    channelingRect.push_back(sf::IntRect(7, 236, 28, 22));
    channelingRect.push_back(sf::IntRect(56, 238, 29, 20));
    channelingRect.push_back(sf::IntRect(115, 222, 34, 36));
    channelingRect.push_back(sf::IntRect(165, 222, 27, 36));
    channelingRect.push_back(sf::IntRect(215, 225, 19, 33));
    channelingRect.push_back(sf::IntRect(59, 265, 39, 30));
    channelingRect.push_back(sf::IntRect(101, 273, 34, 22));
    channelingRect.push_back(sf::IntRect(152, 272, 32, 23));

    channelingTime.push_back(0.2);
    channelingTime.push_back(0.3);
    channelingTime.push_back(0.2);
    channelingTime.push_back(0.2);
    channelingTime.push_back(0.1);
    channelingTime.push_back(0.1);
    channelingTime.push_back(0.3);
    channelingTime.push_back(0.3);
}

int Character::getTimeDiff(float diff) {
    sf::Time time;
    float seconds = 0;

    time = anim_clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > diff) {
        anim_clock.restart();
        return (1);
    }
    return (0);
}

int Character::getTimeMove(float diff) {
    sf::Time time;
    float seconds = 0;

    time = move_clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > diff) {
        move_clock.restart();
        return (1);
    }
    return (0);
}

int Character::getTimeSwitch(float diff) {
    sf::Time time;
    float seconds = 0;

    time = switch_clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > diff) {
        switch_clock.restart();
        return (1);
    }
    return (0);
}

void Character::shootAnimation() {
    if (getTimeDiff(0.06) == 1) {
        shootRectPos++;
        if (shootRectPos > 8) {
            is_shooting = false;
            shootRectPos = 0;
            sprite.setTexture(*texture);
            sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
        } else
            sprite.setTextureRect(shootRect[shootRectPos]);
    }
}

void Character::switchAnimation() {
    sf::IntRect rect;

    if (getTimeSwitch(0.2) == 1) {
        rect = sprite.getTextureRect();
        rect.left += 50;
        if (rect.left > 110) {
            is_switching = false;
            sprite.setTexture(*texture);
            sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
        } else
            sprite.setTextureRect(rect);
    }
}

void Character::channelingAnimation() {
    if (getTimeDiff(channelingTime[channelRectPos]) == 1) {
        channelRectPos ++;
        if (channelRectPos > 7) {
            is_channeling = false;
            channelRectPos = 0;
            sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
            sprite.setPosition(oldPose);
        } else {
            if (channelRectPos == 2)
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 47);
            if (channelRectPos == 4)
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 7);
            if (channelRectPos == 5)
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 7);
            if (channelRectPos == 6)
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 25);
            if (channelRectPos <= 7)
                sprite.setTextureRect(channelingRect[channelRectPos]);
        }
    }
}

void Character::jumpAnimation(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML) {
    sf::IntRect rect = sprite.getTextureRect();
    sf::View view = window->getView();

    if (getTimeDiff(0.07) == 1) {
        if (rect.left < 165) {
            rect.left += 50;
            sprite.setTextureRect(rect);
        }
        move.y += 1;
        if (move.y > 0) {
            is_jumping = false;
            sprite.setTextureRect(sf::IntRect(215, 77, 25, 36));
            is_falling = true;
        } else if (not_colision(mapSFML) == 1) {
            sprite.move(move);
            view.move(move);
        } else {
            move.y = 0;
            view.setCenter(sprite.getPosition());
            is_jumping = false;
            is_falling = true;
        }
        window->setView(view);
    }
}

void Character::fallingAnimation(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML) {
    sf::IntRect rect = sprite.getTextureRect();
    sf::Vector2f pos = sprite.getPosition();
    sf::View view = window->getView();

    if (getTimeDiff(0.07) == 1) {
        if (rect.top == 77) {
            rect.left += 50;
            if (rect.left > 315) {
                rect.top = 112;
                rect.left = 15;
            }
            sprite.setTextureRect(rect);
        } if (rect.top == 112) {
            if (rect.left < 115)
                rect.left += 50;
            sprite.setTextureRect(rect);
        }
        move.y += 2;
        sprite.move(move);
        view.move(move);
        if (collisionFall(mapSFML) == 0) {
            is_falling = false;
            view.setCenter(sprite.getPosition());
            sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
        }
        window->setView(view);
    }
}

void Character::display(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML) {
    if (is_shooting)
        shootAnimation();
    if (is_jumping)
        jumpAnimation(window, mapSFML);
    if (is_falling)
        fallingAnimation(window, mapSFML);
    if (is_channeling == true)
        channelingAnimation();
    if (is_switching == true)
        switchAnimation();
    hud->display(window, weapon_type, _lifes);
    window->draw(sprite);
}

void Character::jump() {
    if (is_jumping == false && is_falling == false) {
        is_jumping = true;
        jump_sound->start();
        sprite.setTextureRect(sf::IntRect(65, 79, 21, 31));
        move = sf::Vector2f(0.f, -20.f);
    }
}

void Character::fall() {
    if (is_falling == false) {
        is_falling = true;
        sprite.setTextureRect(sf::IntRect(215, 78, 25, 28));
        move = sf::Vector2f(0.f, 0.f);
    }
}

void Character::shoot() {
    sf::IntRect rect = sprite.getTextureRect();
    int toTurn = 0;

    switch (getWeapon()) {
        case 1:
            shot_sound->load("resources/Sounds/sounds/shot1.ogg");
            shot_sound->start();
            break;
        case 2:
            shot_sound->load("resources/Sounds/sounds/shot2.ogg");
            shot_sound->start();
            break;
        case 3:
            shot_sound->load("resources/Sounds/sounds/shot3.ogg");
            shot_sound->start();
            break;
        case 4:
            shot_sound->load("resources/Sounds/sounds/channelingShot.ogg");
            shot_sound->start();
            break;
    } if (is_shooting != true && is_jumping == false && is_falling == false) {
        is_shooting = true;
        if (sprite.getScale().x < 0)
            toTurn = 1;
        sprite.setTexture(*textureFight);
        if (toTurn == 0)
            sprite.setScale(sf::Vector2f(3.f, 3.f));
        else
            sprite.setScale(sf::Vector2f(-3.f, 3.f));
        sprite.setTextureRect(shootRect[shootRectPos]);
    }
}

void Character::incWeapon() {
    int toTurn = 0;

    if (is_switching == false && is_jumping == false && is_falling == false
        && is_channeling == false && is_shooting == false) {
        is_switching = true;
        hud->incWeaponType();
        weapon_type++;
        if (weapon_type > 3)
            weapon_type = 1;
        if (sprite.getScale().x < 0)
            toTurn = 1;
        sprite.setTexture(*textureFight);
        if (toTurn == 0)
            sprite.setScale(sf::Vector2f(3.f, 3.f));
        else
            sprite.setScale(sf::Vector2f(-3.f, 3.f));
        switch_clock.restart();
        sprite.setTextureRect(sf::IntRect(10, 8, 40, 29));
    }
}

void Character::moveLeft(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML) {
    sf::IntRect rect = sprite.getTextureRect();
    sf::View view= window->getView();

    is_moving = true;
    if (is_jumping == false && is_falling == false && checkFall(mapSFML) == 1)
        return;
    if (is_jumping == false && is_falling == false) {
        if (sprite.getScale().x > 0) {
            sf::Vector2f pos = sprite.getPosition();
            pos.x += 55.f;
            sprite.setPosition(pos);
            sprite.setScale(-3, 3);
        } if (rect.top != move_Y)
            sprite.setTextureRect(sf::IntRect(65, 45, 22, 28));
        else {
            if (getTimeDiff(0.03) == 1) {
                if (rect.left >= 265)
                    rect.left = 65;
                else
                    rect.left += 50;
                sprite.setTextureRect(rect);
            }
        } if (not_colision(mapSFML) == 1 && getTimeMove(0.01)) {
            sprite.move(sf::Vector2f(-10.f, 0.f));
            view.move(sf::Vector2f(-10.f, 0.f));
            window->setView(view);
        }
    } else {
        if (sprite.getScale().x > 0) {
            sf::Vector2f pos = sprite.getPosition();
            pos.x += 55.f;
            sprite.setPosition(pos);
            sprite.setScale(-3, 3);
        } if (not_colision(mapSFML) == 1 && getTimeMove(0.01)) {
            sprite.move(sf::Vector2f(-5.f, 0.f));
            view.move(sf::Vector2f(-5.f, 0.f));
            window->setView(view);
        }
    }
}

void Character::moveRigth(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML) {
    sf::IntRect rect = sprite.getTextureRect();
    sf::View view= window->getView();

    is_moving = true;
    if (is_jumping == false && is_falling == false && checkFall(mapSFML) == 1)
        return;
    if (is_jumping == false && is_falling == false) {
        if (sprite.getScale().x < 0) {
            sf::Vector2f pos = sprite.getPosition();
            pos.x -= 55.f;
            sprite.setPosition(pos);
            sprite.setScale(3, 3);
        } if (rect.top != move_Y)
            sprite.setTextureRect(sf::IntRect(65, 45, 22, 28));
        else {
            if (getTimeDiff(0.03) == 1) {
                if (rect.left >= 315)
                    rect.left = 65;
                else
                    rect.left += 50;
                sprite.setTextureRect(rect);
            }
        } if (not_colision(mapSFML) == 1 && getTimeMove(0.01)) {
            sprite.move(sf::Vector2f(10.f, 0.f));
            view.move(sf::Vector2f(10.f, 0.f));
            window->setView(view);
        }
    } else {
        if (sprite.getScale().x < 0) {
            sf::Vector2f pos = sprite.getPosition();
            pos.x -= 55.f;
            sprite.setPosition(pos);
            sprite.setScale(3, 3);
        } if (not_colision(mapSFML) == 1 && getTimeMove(0.01)) {
            sprite.move(sf::Vector2f(5.f, 0.f));
            view.move(sf::Vector2f(5.f, 0.f));
            window->setView(view);
        }
    }
}

void Character::channeling() {
    if (is_jumping == false && is_falling == false && is_shooting == false && is_channeling == false) {
        shot_sound->load("resources/Sounds/channelingShot.ogg");
        shot_sound->start();
        is_channeling = true;
        oldPose = sprite.getPosition();
        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 30);
        sprite.setTextureRect(channelingRect[channelRectPos]);
    }
}

sf::Vector2f Character::getSpriteMid() {
    sf::Vector2f charact = sprite.getPosition();

    charact.y += (sprite.getTextureRect().height * 3) + 30;
    if (sprite.getScale().x > 0)
        charact.x += (sprite.getTextureRect().width * 3) / 2;
    else
        charact.x -= (sprite.getTextureRect().width * 3) / 2;
    return (charact);
}

int Character::not_colision(std::vector<std::shared_ptr<Block>> mapSFML) {
    int i = 0;
    sf::FloatRect charact = sprite.getGlobalBounds();
    sf::FloatRect g;

    while (i < mapSFML.size() - 1) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if (charact.intersects(g)) {
            coli_sound->start();
            return (0);
        }
        i++;
    }
    return (1);
}

int Character::collisionFall(std::vector<std::shared_ptr<Block>> mapSFML) {
    int i = 0;
    int y = 0;
    sf::FloatRect charact = sprite.getGlobalBounds();
    sf::FloatRect g;
    sf::Vector2f sp = getSpriteMid();
    sf::Vector2f charact_xm = sprite.getPosition();
    sf::Vector2f charact_mx = sprite.getPosition();

    charact_xm.y += (sprite.getTextureRect().height * 3) + 30;
    charact_mx.y += (sprite.getTextureRect().height * 3) + 30;
    if (sprite.getScale().x > 0) {
        charact_mx.x += (sprite.getTextureRect().width * 3) - 15;
        charact_xm.x += 15;
    } else {
        charact_mx.x -= (sprite.getTextureRect().width * 3) - 15;
        charact_xm.x -= 15;
    }
    while (i < mapSFML.size() - 1) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if ((charact.intersects(g) == true && sprite.getPosition().y < mapSFML[i]->getSprite().getPosition().y &&
            sp.x > mapSFML[i]->getSprite().getPosition().x &&
            sp.x < mapSFML[i]->getSprite().getPosition().x + (mapSFML[i]->getSprite().getTextureRect().width * 0.5)) ||
            g.contains(charact_mx) == true  || g.contains(charact_xm) == true) {
            y = mapSFML[i]->getSprite().getPosition().y - (32.f * 3);
            sprite.setPosition(sprite.getPosition().x, y);
            return (0);
        }
        i ++;
    }
    return (1);
}

int Character::checkFall(std::vector<std::shared_ptr<Block>> mapSFML) {
    int i = 0;
    int y = 0;
    sf::Vector2f charact = sprite.getPosition();
    sf::Vector2f charact_xm = sprite.getPosition();
    sf::Vector2f charact_mx = sprite.getPosition();
    sf::FloatRect g;

    charact.y += (sprite.getTextureRect().height * 3) + 30;
    charact_xm.y += (sprite.getTextureRect().height * 3) + 30;
    charact_mx.y += (sprite.getTextureRect().height * 3) + 30;
    if (sprite.getScale().x > 0) {
        charact.x += (sprite.getTextureRect().width * 3) / 2;
        charact_mx.x += (sprite.getTextureRect().width * 3);
    } else {
        charact.x -= (sprite.getTextureRect().width * 3) / 2;
        charact_mx.x -= (sprite.getTextureRect().width * 3);
    }
    while (i < mapSFML.size()) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if (g.contains(charact) == true || g.contains(charact_xm) == true ||
            g.contains(charact_mx) == true) {
            return (0);
        }
        i ++;
    }
    fall();
    return (1);
}

sf::Sprite Character::getSprite() {return (sprite);}

int Character::getWeapon() {return (weapon_type);}

void Character::checkCollMunPlus(vector<shared_ptr<MunPlus>> &PlusList) {
    sf::FloatRect rect;

    for (int i = 0; i < PlusList.size(); i++) {
        rect = PlusList[i]->getMunShape();
        if (rect.intersects(sprite.getGlobalBounds()) == true) {
            hud->incMun(PlusList[i]->getType() - 1);
            PlusList.erase(PlusList.begin() + i);
        }
    }
}

void Character::restartPos() {sprite.setTextureRect(sf::IntRect(65, 6, 19, 30));}
bool Character::isShooting() {return (is_shooting);}
bool Character::isJumping() {return (is_jumping);}
bool Character::isFalling() {return (is_falling);}
bool Character::getMoving() {return (is_moving);}
bool Character::isChanneling() {return (is_channeling);}

bool Character::isSwitching() {return (is_switching);}

bool Character::isActionPossible(){
    if (is_jumping == false && is_falling == false && is_channeling == false && is_switching == false && is_shooting == false)
        return (true);
    return (false);
}

void Character::setMoving(bool status) {is_moving = status;}
int Character::getMunBattery() {return (hud->decBatteryMun());}
int Character::getMun() {return (hud->getMunBattery());}

int Character::channelBat()
{
    hud->batteryChanneling();
    return (0);
}

void Character::setSpritePosition(int x, int y) {sprite.setPosition(x, y);}