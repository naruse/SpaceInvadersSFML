//
//  EnemyManager.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/25/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#ifndef SpaceInvaders_EnemyManager_h
#define SpaceInvaders_EnemyManager_h

#include "ResourcePath.hpp"
#include <iostream>
#include "TimeManager.h"
#include "BulletManager.h"
#include "Enemy.h"
#include "Defines.h"

class EnemyManager {
private:
    Enemy*** enemies;
    Enemy* enemyUFO = NULL;
    float timeToMoveEnemies = ENEMIESMOVINGRATIO;//each ENEMIESMOVINGRATION seconds enemies get moved
    float currentTime = 0;//time counter to move the enemies matrix
    
    float timeToCreateUFO = UFOSPAWNINGRATIO;//each UFOSPAWNINGRATIO seconds create an UFO
    float currentTimeUFO = 0;
    
    float timeToShootEnemies = 3;//each 3 seconds an enemy randomly shoots a bullet
    float currentTimeForShooting = 0;
    void MoveAllEnemies(float, float);
    void CreateEnemyUFO();
    void EnemiesShoot();//make enemies shoot randomly
public:
    EnemyManager();
    ~EnemyManager();
    void MoveEnemiesLogic();
    Enemy*** GetEnemies();
    Enemy* GetEnemyUFO();
    void InitializeEnemies();
    void ResetEnemyUFOPosition();
    void RestartEnemies();
};

#endif
