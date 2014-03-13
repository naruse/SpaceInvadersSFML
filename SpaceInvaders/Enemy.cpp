//
//  Enemy.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/25/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//
//
// Each enemy should have 2 textures A and B to fill in the textures array.
#include "Enemy.h"

void Enemy::Initialize(std::string texturePath, float x, float y) {
    if(!enemyTexture1.loadFromFile(texturePath + "A.png"))
        std::cerr << "Couldnt load " + texturePath + "A texture." << std::endl;
    enemySprite1.setTexture(enemyTexture1);
    
    if(!enemyTexture2.loadFromFile(texturePath + "B.png"))
        std::cerr << "Couldnt load " + texturePath + "B texture." << std::endl;
    enemySprite2.setTexture(enemyTexture2);

    enemySprite1.setPosition(x,y);
    enemySprite2.setPosition(x,y);
}

void Enemy::Move(float x, float y) {
    enemySprite1.move(x,y);
    enemySprite2.move(x,y);
}

void Enemy::SetPosition(float x, float y) {
    enemySprite1.setPosition(x, y);
    enemySprite2.setPosition(x, y);
}


const sf::Sprite& Enemy::GetEnemySprite() {
    currentTime = currentTime + TimeManager::GetDeltaTime();
    if(currentTime > secsToChangeSprite) {
        flag = !flag;
        currentTime = 0;
    }
    if(flag)
        return enemySprite1;
    else
        return enemySprite2;
}