//
//  BulletManager.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/28/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#ifndef __SpaceInvaders__BulletManager__
#define __SpaceInvaders__BulletManager__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Console.h"
#include "Bullet.h"
#include "Utils.h"

class BulletManager {
private:
    sf::Texture playerBulletTexture;
    sf::Sprite playerBulletSprite;
    
    sf::Texture enemyBulletTexture;
    sf::Sprite enemyBulletSprite;
    
    //offsets for centering bullets.
    static sf::Vector2f offsetEnemyBullet;
    static sf::Vector2f offsetPlayerBullet;
    
    static Bullet* playerBullets;
    static Bullet* enemyBullets;
    
    
public:
    static void CreateEnemyBullet(const Bullet& b);
    static void CreatePlayerBullet(const Bullet& b);

    static Bullet* GetPlayerBullets(){ return playerBullets; }
    static Bullet* GetEnemyBullets() { return enemyBullets; }
    void Initialize();
    ~BulletManager();
    BulletManager(){}
    sf::Sprite& GetEnemyBulletSprite() { return enemyBulletSprite; }
    sf::Sprite& GetPlayerBulletSprite() { return playerBulletSprite; }
    void DestroyPlayerBulletAtPos(int p);
    void DestroyEnemyBulletAtPos(int p);
};

#endif /* defined(__SpaceInvaders__BulletManager__) */
