//
//  Player.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/27/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#ifndef __SpaceInvaders__PlayerManager__
#define __SpaceInvaders__PlayerManager__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TimeManager.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Defines.h"
#include "Console.h"
#include "Utils.h"

class PlayerManager {
private:
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    float currentTime = 0;
    bool playerHasShoot = false;

public:
    void Initialize(std::string);
    const sf::Sprite& GetPlayerSprite();
    void MoveLogic();
    void ShootLogic();
    void ResetPosition();
    PlayerManager() {}
    ~PlayerManager() {}
};

#endif /* defined(__SpaceInvaders__Player__) */
