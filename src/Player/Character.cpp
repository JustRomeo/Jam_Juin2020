/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Character
*/

#include "Character.hpp"

static bool isDoubleJump = false;
Character::Character(shared_ptr<sf::Texture> theone) {
    jump_sound = make_unique<MusicSFML>();
    coli_sound = make_unique<MusicSFML>();
    shot_sound1 = make_unique<MusicSFML>();
    shot_sound2 = make_unique<MusicSFML>();
    shot_sound3 = make_unique<MusicSFML>();
    shot_sound4 = make_unique<MusicSFML>();
    _comptree = make_shared<CompetenceTree>();

    try {
        jump_sound->load("resources/Sounds/sounds/Jump.ogg");
        coli_sound->load("resources/Sounds/sounds/Colision.ogg");
        _lifes = 3;
        texture = theone == nullptr ? make_shared<sf::Texture>() : make_shared<sf::Texture>(*theone);
        textureFight = make_shared<sf::Texture>();
        shot_sound1->load("resources/Sounds/sounds/shot1.ogg");
        shot_sound2->load("resources/Sounds/sounds/shot2.ogg");
        shot_sound3->load("resources/Sounds/sounds/shot3.ogg");
        shot_sound4->load("resources/Sounds/sounds/channelingShot.ogg");
        if (theone == nullptr)
            if (!texture->loadFromFile("./resources/character/adventurer-v1.5-Sheet.png"))
                throw(Exception("resources load failed"));
        if (!textureFight->loadFromFile("./resources/character/adventurer-bow-Sheet.png"))
            throw(Exception("resources load failed"));
    } catch (Exception &e) {
        cout << e.what() << endl;
    }
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
    sprite.setScale(sf::Vector2f(3, 3));
    sprite.setPosition(sf::Vector2f(200, 1102 - (32 * 3)));

    lvl = 1;
    exp = 0;
    move_Y = 43;
    notMove_Y = 6;
    cacRectPos = 0;
    weapon_type = 1;
    sprintBar = 100;
    move_Xmax = 315;
    shootRectPos = 0;
    channelRectPos = 0;
    jumpCacRectPos = 0;
    invulnerability = 0;

    is_cac = false;
    is_hooked = false;
    is_moving = false;
    is_jumping = false;
    is_falling = false;
    is_hooking = false;
    is_shooting = false;
    is_switching = false;
    is_sprinting = false;
    is_channeling = false;

    cac_clock.restartClock();
    move_clock.restartClock();
    anim_clock.restartClock();
    switch_clock.restartClock();
    sprint_clock.restartClock();

    hud = make_shared<HUD>();
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

    cacAttackRect.push_back(sf::IntRect(313, 230, 20, 28));
    cacAttackRect.push_back(sf::IntRect(303, 272, 47, 23));
    cacAttackRect.push_back(sf::IntRect(4, 313, 30, 19));

    jumpCacAttackRect.push_back(sf::IntRect(303, 485, 46, 30));
    jumpCacAttackRect.push_back(sf::IntRect(6, 521, 28, 30));
    jumpCacAttackRect.push_back(sf::IntRect(55, 520, 27, 31));
}

void Character::moveChar(shared_ptr<sf::RenderWindow> window, int orient) {
    sf::Vector2f move;
    sf::View view = window->getView();

    is_sprinting ? move = sf::Vector2f((20 + _comptree->_speed.x) * orient, 0) : move = sf::Vector2f((10 + _comptree->_speed.x) * orient, 0);
    if (is_sprinting)
        sprintBar > 0 ? sprintBar -- : is_sprinting = false;
    if (is_jumping || is_falling)
        is_sprinting ? move = sf::Vector2f((10 + _comptree->_speed.x) * orient, 0) : move = sf::Vector2f((5 + (_comptree->_speed.x / 2)) * orient, 0);
    else
        is_sprinting ? move = sf::Vector2f((20 + _comptree->_speed.x) * orient, 0) : move;
    view.move(move);
    sprite.move(move);
    window->setView(view);
}

void Character::moveLeft(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML) {
    float timeAnim;
    sf::View view = window->getView();
    sf::IntRect rect = sprite.getTextureRect();

    is_sprinting ? timeAnim = 0.005 : timeAnim = 0.01;
    is_moving = true;
    if (!is_jumping && !is_falling && checkFall(mapSFML) == 1)
        return;
    if (sprite.getScale().x > 0) {
        sf::Vector2f pos = sprite.getPosition();
        pos.x += 55;
        sprite.setPosition(pos);
        sprite.setScale(-3, 3);
    } if (!is_jumping && !is_falling) {
        rect.top != move_Y ? sprite.setTextureRect(sf::IntRect(65, 43, 22, 30)) : spriteAnimation();
        if (not_colision(mapSFML) == 1 && move_clock.getTimeDiff(timeAnim))
            sprite.getScale().x > 0 ? moveChar(window, 1) : moveChar(window, -1);
    } else
        if (not_colision(mapSFML) == 1 && move_clock.getTimeDiff(0.01))
            sprite.getScale().x > 0 ? moveChar(window, 1) : moveChar(window, -1);
    if (not_colision(mapSFML) == 0)
        unblockCharacter(mapSFML);
}

void Character::moveRigth(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML) {
    float timeAnim;
    sf::View view = window->getView();
    sf::IntRect rect = sprite.getTextureRect();

    is_sprinting ? timeAnim = 0.005 : timeAnim = 0.01;
    is_moving = true;
    if (!is_jumping && !is_falling && checkFall(mapSFML) == 1)
        return;
    if (sprite.getScale().x < 0) {
        sf::Vector2f pos = sprite.getPosition();
        pos.x -= 55;
        sprite.setPosition(pos);
        sprite.setScale(3, 3);
    } if (!is_jumping && !is_falling) {
        rect.top != move_Y ? sprite.setTextureRect(sf::IntRect(65, 43, 22, 30)) : spriteAnimation();
        if (not_colision(mapSFML) == 1 && move_clock.getTimeDiff(timeAnim))
            sprite.getScale().x > 0 ? moveChar(window, 1) : moveChar(window, -1);
    } else
        if (not_colision(mapSFML) == 1 && move_clock.getTimeDiff(0.01))
            sprite.getScale().x > 0 ? moveChar(window, 1) : moveChar(window, -1);
    if (not_colision(mapSFML) == 0)
        unblockCharacter(mapSFML);
}

void Character::jumpAnimation(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML) {
    sf::IntRect rect = sprite.getTextureRect();
    sf::View view = window->getView();

    if (anim_clock.getTimeDiff(0.07) == 1) {
        if (rect.left < 165 && !is_cac) {
            rect.left += 50;
            sprite.setTextureRect(rect);
        }
        move.y += 1;
        if (move.y > 0) {
            is_jumping = false;
            isDoubleJump = false;
            sprite.setTextureRect(sf::IntRect(215, 77, 25, 31));
            is_falling = true;
        } else if (not_colision(mapSFML) == 1) {
            sprite.move(move);
            view.move(move);
        } else {
            move.y = 0;
            sprite.setTextureRect(sf::IntRect(215, 77, 25, 36));
            view.setCenter(sprite.getPosition());
            is_jumping = false;
            isDoubleJump = false;
            is_falling = true;
        }
        window->setView(view);
    }
}

void Character::fallingAnimation(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML) {
    sf::IntRect rect = sprite.getTextureRect();
    sf::Vector2f pos = sprite.getPosition();
    sf::View view = window->getView();

    if (anim_clock.getTimeDiff(0.07) == 1) {
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
            is_cac = false;
            view.setCenter(sprite.getPosition());
            sprite.setTextureRect(sf::IntRect(65, 6, 18, 30));
        }
        window->setView(view);
    }
}

void Character::channelingAnimation() {
    if (move_clock.getTimeDiff(channelingTime[channelRectPos]) == 1) {
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

void Character::cacAnimation() {
    if (cac_clock.getTimeDiff(0.3) == 1) {
        cacRectPos ++;
        jumpCacRectPos ++;
        if (cacRectPos > 2 || jumpCacRectPos > 2) {
            is_cac = false;
            cacRectPos = 0;
            jumpCacRectPos = 0;
            if (!is_jumping && !is_falling) {
                sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 30);
            } else if (is_falling)
                sprite.setTextureRect(sf::IntRect(215, 78, 25, 28));
            else if (is_jumping)
                sprite.setTextureRect(sf::IntRect(65, 79, 21, 31));
        } else {
            if (!is_jumping && !is_falling)
                sprite.setTextureRect(cacAttackRect[cacRectPos]);
            else
                sprite.setTextureRect(jumpCacAttackRect[jumpCacRectPos]);
        }
    }
}

void Character::shootAnimation() {
    if (move_clock.getTimeDiff(_comptree->_spdshot) == 1) {
        shootRectPos ++;
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

    if (switch_clock.getTimeDiff(_comptree->_spdreload) == 1) {
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

void Character::hookShoot(vector<shared_ptr<Block>> mapSFML) {
    for (size_t i = 0; i < mapSFML.size(); i++) {
        if (mapSFML[i]->getSprite().getGlobalBounds().contains(hookEnd)) {
            is_hooked = true;
            is_hooking = false;
            return;
        }
    } if (move_clock.getTimeDiff(0.1) == 1) {
        hookEnd.x += hookVec.x;
        hookEnd.y += hookVec.y;
    }
}

void Character::hookAnimation(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML) {
    sf::Vertex line[2];

    hookBeg.y = sprite.getPosition().y + 40;
    if (sprite.getScale().x > 0)
        hookBeg.x = sprite.getPosition().x + 30;
    else
        hookBeg.x = sprite.getPosition().x - 30;
    line[0].position = hookBeg;
    line[0].color  = sf::Color::Red;
    line[1].position = hookEnd;
    line[1].color = sf::Color::Red;

    window->draw(line, 2, sf::Lines);
    if (is_hooking && !is_hooked)
        hookShoot(mapSFML);
}

void Character::display(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML) {
    if (is_shooting)
        shootAnimation();
    if (is_jumping)
        jumpAnimation(window, mapSFML);
    if (is_falling)
        fallingAnimation(window, mapSFML);
    if (is_channeling)
        channelingAnimation();
    if (is_switching)
        switchAnimation();
    if (is_cac)
        cacAnimation();
    if (is_hooking || is_hooked)
        hookAnimation(window, mapSFML);
    hud->display(window, weapon_type, _lifes, lvl);
    hud->displaySprintBar(window, sprintBar);
    if (sprint_clock.getTimeDiff(0.1))
        sprintBar < 100 ? sprintBar++: sprintBar+=0;
    window->draw(sprite);
}

void Character::hook(shared_ptr<sf::RenderWindow> window) {
    sf::Vector2i cursor;

    if (!is_jumping && !is_falling && !is_shooting && !is_channeling) {
        is_hooking = true;
        hookBeg.y = sprite.getPosition().y + 40;
        if (sprite.getScale().x > 0)
            hookBeg.x = sprite.getPosition().x + 30;
        else
            hookBeg.x = sprite.getPosition().x - 30;

        sf::Vector2i pixelPos = sf::Mouse().getPosition(*window);
        sf::Vector2f cursor = window->mapPixelToCoords(pixelPos);

        hookVec.x = cursor.x - hookBeg.x;
        hookVec.y = cursor.y - hookBeg.y;
        if (hookVec.x > 0 && hookVec.y > 0) {
            while (hookVec.x > 5.0 && hookVec.y > 5.0) {
                hookVec.x = hookVec.x / 2.0;
                hookVec.y = hookVec.y / 2.0;
            }
        } if (hookVec.x < 0 && hookVec.y < 0) {
            while (hookVec.x < -5.0 && hookVec.y < -5.0) {
                hookVec.x = hookVec.x / 2.0;
                hookVec.y = hookVec.y / 2.0;
            }
        } if (hookVec.x < 0 && hookVec.y > 0) {
            while (hookVec.x < -5.0 && hookVec.y > 5.0) {
                hookVec.x = hookVec.x / 2.0;
                hookVec.y = hookVec.y / 2.0;
            }
        } if (hookVec.x > 0 && hookVec.y < 0) {
            while (hookVec.x > 5.0 && hookVec.y < -5.0) {
                hookVec.x = hookVec.x / 2.0;
                hookVec.y = hookVec.y / 2.0;
            }
        }
        hookEnd = hookBeg;
    }
}

void Character::jump() {
    if (!is_jumping && !is_falling) {
        is_jumping = true;
        jump_sound->start();
        sprite.setTextureRect(sf::IntRect(65, 79, 21, 31));
        move = sf::Vector2f(0, -20);
    } else if (_comptree->getDoubleJump() && !is_falling && is_jumping && !isDoubleJump && move.y > -7) {
        isDoubleJump = true;
        jump_sound->start();
        sprite.setTextureRect(sf::IntRect(65, 79, 21, 31));
        move = sf::Vector2f(0, -20);
    }
}

void Character::fall() {
    if (!is_falling) {
        is_falling = true;
        sprite.setTextureRect(sf::IntRect(17, 52, 17, 22));
        move = sf::Vector2f(0, 0);
    }
}

void Character::shoot() {
    sf::IntRect rect = sprite.getTextureRect();
    int toTurn = 0;

    switch (getWeapon()) {
        case 1: shot_sound1->start(); break;
        case 2: shot_sound2->start(); break;
        case 3: shot_sound3->start(); break;
    } if (!is_shooting && !is_jumping && !is_falling) {
        is_shooting = true;
        if (sprite.getScale().x < 0)
            toTurn = 1;
        sprite.setTexture(*textureFight);
        if (toTurn == 0)
            sprite.setScale(sf::Vector2f(3, 3));
        else
            sprite.setScale(sf::Vector2f(-3, 3));
        sprite.setTextureRect(shootRect[shootRectPos]);
    }
}

void Character::channeling() {
    if (!is_jumping && !is_falling && !is_shooting && !is_channeling) {
        shot_sound4->start();
        is_channeling = true;
        oldPose = sprite.getPosition();
        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 30);
        sprite.setTextureRect(channelingRect[channelRectPos]);
    }
}

void Character::cacAttack() {
    if (!is_shooting && !is_channeling && !is_cac) {
        cac_clock.restartClock();
        is_cac = true;
        if (!is_jumping && !is_falling) {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 30);
            sprite.setTextureRect(cacAttackRect[cacRectPos]);
        } else
            sprite.setTextureRect(jumpCacAttackRect[jumpCacRectPos]);
    }
}

void Character::incWeapon() {
    int toTurn = 0;

    if (!is_switching && !is_jumping && !is_falling && !is_channeling && !is_shooting) {
        is_switching = true;
        hud->incWeaponType();
        weapon_type ++;
        if (weapon_type > 4)
            weapon_type = 1;
        if (sprite.getScale().x < 0)
            toTurn = 1;
        sprite.setTexture(*textureFight);
        if (toTurn == 0)
            sprite.setScale(sf::Vector2f(3, 3));
        else
            sprite.setScale(sf::Vector2f(-3, 3));
        switch_clock.restartClock();
        sprite.setTextureRect(sf::IntRect(10, 8, 40, 29));
    }
}

void Character::changeSprite(string path) {
    if (path == "")
        throw(Exception("Wrong Path."));
    if (!texture->loadFromFile(path))
        throw(Exception("resources load failed."));
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(65, 5, 19, 32));
    sprite.setScale(sf::Vector2f(3, 3));
    sprite.setPosition(sf::Vector2f(200, 1102 - (32 * 3)));
}

void Character::spriteAnimation() {
    float timeAnim;
    sf::IntRect rect = sprite.getTextureRect();

    is_sprinting ? timeAnim = 0.05 : timeAnim = 0.1;
    if (anim_clock.getTimeDiff(timeAnim) == 1) {
        if (rect.left >= 265)
            rect.left = 65;
        else
            rect.left += 50;
        sprite.setTextureRect(rect);
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

void Character::unblockCharacter(vector<shared_ptr<Block>> mapSFML) {
    sf::Vector2f leftPoint;
    sf::Vector2f rightPoint;

    if (sprite.getScale().x > 0) {
        leftPoint = {sprite.getPosition().x, sprite.getPosition().y + (sprite.getTextureRect().height / 2)};
        rightPoint = {sprite.getPosition().x + sprite.getTextureRect().width, sprite.getPosition().y + (sprite.getTextureRect().height / 2)};
    } else {
        rightPoint = {sprite.getPosition().x, sprite.getPosition().y + (sprite.getTextureRect().height / 2)};
        leftPoint = {sprite.getPosition().x - sprite.getTextureRect().width, sprite.getPosition().y + (sprite.getTextureRect().height / 2)};
    }
    for (size_t i = 0; i < mapSFML.size(); i++) {
        if (mapSFML[i]->getSprite().getGlobalBounds().contains(leftPoint))
            sprite.move(sf::Vector2f(15, 0));
        else if (mapSFML[i]->getSprite().getGlobalBounds().contains(rightPoint))
            sprite.move(sf::Vector2f(-15, 0));
    }
}

int Character::not_colision(vector<shared_ptr<Block>> mapSFML) {
    sf::FloatRect g;
    sf::FloatRect charact = sprite.getGlobalBounds();

    for (size_t i = 0; i < mapSFML.size() - 1; i ++) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if (charact.intersects(g)) {
            coli_sound->start();
            return 0;
        }
    }
    return 1;
}

int Character::collisionFall(vector<shared_ptr<Block>> mapSFML) {
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
    for (size_t i = 0; i < mapSFML.size() - 1; i ++) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if ((charact.intersects(g) && sprite.getPosition().y < mapSFML[i]->getSprite().getPosition().y &&
            sp.x > mapSFML[i]->getSprite().getPosition().x &&
            sp.x < mapSFML[i]->getSprite().getPosition().x + (mapSFML[i]->getSprite().getTextureRect().width * 0.5)) ||
            g.contains(charact_mx)  || g.contains(charact_xm)) {
            y = mapSFML[i]->getSprite().getPosition().y - (30 * 3) - 3;
            sprite.setPosition(sprite.getPosition().x, y);
            if (not_colision(mapSFML) == 0)
                unblockCharacter(mapSFML);
            return 0;
        }
    }
    return 1;
}

int Character::checkFall(vector<shared_ptr<Block>> mapSFML) {
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
    } for (size_t i = 0; i < mapSFML.size(); i ++) {
        g = mapSFML[i]->getSprite().getGlobalBounds();
        if (g.contains(charact) || g.contains(charact_xm) || g.contains(charact_mx))
            return 0;
    }
    fall();
    return 1;
}

void Character::checkCollMunPlus(vector<shared_ptr<MunPlus>> &PlusList) {
    sf::FloatRect rect;

    for (size_t i = 0; i < PlusList.size(); i ++) {
        rect = PlusList[i]->getMunShape();
        if (rect.intersects(sprite.getGlobalBounds())) {
            hud->incMun(PlusList[i]->getType() - 1);
            PlusList.erase(PlusList.begin() + i);
        }
    }
}

bool Character::isActionPossible() {
    if (!is_jumping && !is_falling && !is_channeling && !is_switching && !is_shooting && !is_cac && !is_hooking && !is_sprinting)
        return true;
    return false;
}

int Character::channelBat() {
    hud->batteryChanneling();
    return 0;
}

bool Character::isCac() {return (is_cac);}
bool Character::getMoving() {return (is_moving);}
bool Character::isJumping() {return (is_jumping);}
bool Character::isFalling() {return (is_falling);}
int Character::getWeapon() {return (weapon_type);}
void Character::stopSprint() {is_sprinting = false;}
bool Character::isShooting() {return (is_shooting);}
sf::Sprite Character::getSprite() {return (sprite);}
bool Character::isSwitching() {return (is_switching);}
bool Character::isChanneling() {return (is_channeling);}
int Character::getMun() {return (hud->getMunBattery());}
void Character::setMoving(bool status) {is_moving = status;}
int Character::getMunBattery() {return (hud->decBatteryMun());}
void Character::sprint() {is_sprinting = sprintBar > 0 ? true : false;}
void Character::setSpritePosition(int x, int y) {sprite.setPosition(x, y);}
vector<shared_ptr<Objet>> Character::getItems(void) const {return _objects;}
void Character::restartPos() {sprite.setTextureRect(sf::IntRect(65, 6, 18, 30));}
void Character::addValue(shared_ptr<Objet> newobject) {this->_objects.push_back(newobject);}
