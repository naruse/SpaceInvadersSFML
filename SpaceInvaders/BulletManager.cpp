//
//  BulletManager.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/28/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#include "BulletManager.h"

void BulletManager::CreateEnemyBullet(const Bullet& b) {
    for(int i = 0; i < MAXBULLETSONSCREEN; i++) {
        if(enemyBullets[i].GetBulletPosition() == NULLV2) {//found an empty position
            enemyBullets[i] = b;
            enemyBullets[i].SetBulletCenterOffset(offsetEnemyBullet);
            return;
        }
    }
    Console::Log("No spaces for enemy bullets");
}
void BulletManager::CreatePlayerBullet(const Bullet& b) {
    for(int i = 0; i < MAXBULLETSONSCREEN; i++) {
        if(playerBullets[i].GetBulletPosition() == NULLV2) {//found an empty position
            playerBullets[i] = b;
            playerBullets[i].SetBulletCenterOffset(offsetPlayerBullet);
            return;
        }
    }
    Console::Log("No spaces for player bullets");
}

void BulletManager::DestroyPlayerBulletAtPos(int p) {
    playerBullets[p].SetBulletPosition(NULLV2);
}

void BulletManager::DestroyEnemyBulletAtPos(int p) {
    enemyBullets[p].SetBulletPosition(NULLV2);
}

void BulletManager::Initialize(){
    //Console::Log("Initializing Bullet Manager");
    
    if(!enemyBulletTexture.loadFromFile(ResourcePath() + "EnemyBomb.png"))
        std::cerr << "Couldnt load EnemyBomb.png texture" << std::endl;
    enemyBulletSprite.setTexture(enemyBulletTexture);
    enemyBulletSprite.setPosition(NULLV2);
    offsetEnemyBullet.x = (float)enemyBulletTexture.getSize().x/2;
    offsetEnemyBullet.y = (float)enemyBulletTexture.getSize().y/2;
    
    if(!playerBulletTexture.loadFromFile(ResourcePath() + "Laser.png"))
        std::cerr << "Couldnt load Laser.png texture" << std::endl;
    playerBulletSprite.setTexture(playerBulletTexture);
    playerBulletSprite.setPosition(NULLV2);
    offsetPlayerBullet.x = (float)playerBulletTexture.getSize().x/2;
    offsetPlayerBullet.y = 0;//we only need the top of the texture centered
    
    
    enemyBullets = new Bullet[MAXBULLETSONSCREEN];
    playerBullets = new Bullet[MAXBULLETSONSCREEN];
    
    for(int i = 0; i < MAXBULLETSONSCREEN; i++) {
        enemyBullets[i].SetBulletPosition(NULLV2);
        playerBullets[i].SetBulletPosition(NULLV2);
    }
}

BulletManager::~BulletManager() {
//    delete[] enemyBullets;//gets destroyed at the end of the program
//    delete[] playerBullets;//gets destroyed at the end of the program as they are static
}
