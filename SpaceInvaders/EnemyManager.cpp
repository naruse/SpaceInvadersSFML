//
//  EnemyManager.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/25/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#include "EnemyManager.h"
#include <ostream>
#include <stdlib.h>

EnemyManager::EnemyManager() {
    InitializeEnemies();    
}

//called frame by frame
int timesMovedHorizontal = 0;
int maxMovesHorizontal = 6;//moves maxMovesHorizontal-1 times.
float direction = 1;
bool movingUFO = false;
void EnemyManager::MoveEnemiesLogic() {
    currentTime += TimeManager::GetDeltaTime();
    currentTimeUFO += TimeManager::GetDeltaTime();
    if(currentTime > timeToMoveEnemies) {
        timesMovedHorizontal++;
        if(timesMovedHorizontal < maxMovesHorizontal) {
            MoveAllEnemies(direction * ENEMIESMOVINGDISTANCEHORIZONTAL, 0);
        } else {
            MoveAllEnemies(0, ENEMIESMOVINGDISTANCEVERTICAL);
            direction *= -1;
            timesMovedHorizontal = 0;
        }
        currentTime = 0;
    }
    
    if(currentTimeUFO > timeToCreateUFO) {
        if(enemyUFO == NULL) {
            CreateEnemyUFO();
        }
        movingUFO = true;
        currentTimeUFO = 0;
    }
    if(movingUFO) {
        enemyUFO->Move(-ENEMYUFOSPEED * TimeManager::GetDeltaTime(), 0);
        //ufo gone of screen
        if(enemyUFO->GetEnemySprite().getPosition().x < -((float)enemyUFO->GetEnemySprite().getTexture()->getSize().x)){
            ResetEnemyUFOPosition();
        }
    }
    EnemiesShoot();
}

void EnemyManager::RestartEnemies() {
    //Delete All The Enemies memory
    for(int i = 0; i < ENEMIESHORIZONTAL; i++) {
        for(int j = 0; j < ENEMIESVERTICAL; j++) {
            if(enemies[i][j] != NULL) {
                delete enemies[i][j];
                enemies[i][j] = NULL;
            }
        }
    }
    for (int i = 0; i < ENEMIESHORIZONTAL; i++) {
        delete[] enemies[i];
        enemies[i] = NULL;
    }
    delete enemies;
    enemies = NULL;
    //initialize enemies
    InitializeEnemies();
    ResetEnemyUFOPosition();
}

void EnemyManager::ResetEnemyUFOPosition() {
    enemyUFO->SetPosition(SCREENHORIZONTAL + 10, 10);
    movingUFO = false;
    currentTimeUFO = 0;
}

//called frame by frame
void EnemyManager::EnemiesShoot() {
    currentTimeForShooting += TimeManager::GetDeltaTime();
    if(currentTimeForShooting > timeToShootEnemies) {
        //Console::Log("Should Shoot");
        int randIPos = rand()%ENEMIESHORIZONTAL;
        int randJPos = rand()%ENEMIESVERTICAL;
        Bullet b;
        if(enemies[randIPos][randJPos] != NULL) {
            //Console::Log("Enemy[" + Utils::ToStr(randIPos) + "][" + Utils::ToStr(randJPos) + "] Shot.");
            b.Initialize(enemies[randIPos][randJPos]->GetEnemySprite().getPosition(), 1/*direction*/);
            BulletManager::CreateEnemyBullet(b);
        } else {//random failed, then just search for the first available enemy and shoot.
            bool foundEnemy = false;
            for(int i = 0; i < ENEMIESHORIZONTAL; i++) {
                for(int j = 0; j < ENEMIESVERTICAL; j++) {
                    if(enemies[i][j] != NULL) {
                        //Console::Log("Rand Fail; enemy[" + Utils::ToStr(i) + "][" + Utils::ToStr(j) + "] shot.");
                        b.Initialize(enemies[i][j]->GetEnemySprite().getPosition(), 1/*direction*/);
                        BulletManager::CreateEnemyBullet(b);
                        foundEnemy = true;
                        break;
                    }
                }
                if(foundEnemy)
                    break;
            }
        }
        currentTimeForShooting = 0;
    }
}

void EnemyManager::MoveAllEnemies(float x, float y) {
    for(int i = 0; i < ENEMIESHORIZONTAL; i++) {
        for(int j = 0; j < ENEMIESVERTICAL; j++) {
            if(enemies[i][j] != NULL)
                enemies[i][j]->Move(x, y);
        }
    }
}

//called frame by frame
Enemy*** EnemyManager::GetEnemies() {
    return enemies;
}
//called frame by frame
Enemy* EnemyManager::GetEnemyUFO() {
    return enemyUFO;
}

void EnemyManager::CreateEnemyUFO() {
    if(enemyUFO != NULL) {
        //Console::Log("Releasing EnemyUFO memory");
        delete enemyUFO;
        enemyUFO = NULL;
    }
    enemyUFO = new Enemy();
    enemyUFO->Initialize(ResourcePath() + "Ufo", SCREENHORIZONTAL + 10, 10);
}

void EnemyManager::InitializeEnemies() {
    //Console::Log("Initializing enemy Manager");
    CreateEnemyUFO();
    // Allocate enemies matrix
    enemies = new Enemy**[ENEMIESHORIZONTAL];
    // Allocate each member of the enemies matrix
    for (int i = 0; i < ENEMIESHORIZONTAL; i++) {
        enemies[i] = new Enemy*[ENEMIESVERTICAL];
    }
    
    //initialize enemies
    for(int i = 0; i < ENEMIESHORIZONTAL; i++) {
        for(int j = 0; j < ENEMIESVERTICAL; j++) {
            enemies[i][j] = new Enemy();
            enemies[i][j]->Initialize(ResourcePath() + "Enemy" + ((j < 2) ? "1" : ((j < 4) ? "2" : "3")),
                                      STARTINGDISTANCEHORIZONTAL + (i * DISTANCEBETWEENENEMIESHORIZONTAL),
                                      STARTINGDISTANCEVERTICAL + (j * DISTANCEBETWEENENEMIESVERTICAL));
        }
    }
}

EnemyManager::~EnemyManager() {
    //Delete All The Enemies memory
   for(int i = 0; i < ENEMIESHORIZONTAL; i++) {
        for(int j = 0; j < ENEMIESVERTICAL; j++) {
//            if(enemies[i][j] != NULL) {
//                delete enemies[i][j];
                enemies[i][j] = NULL;
  //          }
        }
    }
  /*  for (int i = 0; i < ENEMIESHORIZONTAL; i++) {
        if(enemies[i] != NULL) {
            delete[] enemies[i];
            enemies[i] = NULL;
        }
    }
    if(enemies != NULL) {
        delete[] enemies;
        enemies = NULL;
    }*/
    if(enemyUFO != NULL) {
        delete enemyUFO;
        enemyUFO = NULL;
    }
}



