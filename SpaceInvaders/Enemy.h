//
//  Enemy.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/25/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#ifndef SpaceInvaders_Enemy_h
#define SpaceInvaders_Enemy_h

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TimeManager.h"
#include "Console.h"
#include "Utils.h"

class Enemy {
private:
    sf::Texture enemyTexture1;
    sf::Sprite enemySprite1;

    sf::Texture enemyTexture2;
    sf::Sprite enemySprite2;

    float secsToChangeSprite = 1;
    float currentTime = 0;
    bool flag = true; //used to change between sprites for the enemy
public:
    Enemy() {}
    ~Enemy() {}
    void Initialize(std::string path, float x, float y);
    const sf::Sprite& GetEnemySprite();
    void Move(float, float);
    void SetPosition(float, float);
};

#endif
