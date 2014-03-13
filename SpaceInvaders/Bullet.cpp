//
//  Bullet.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/28/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#include "Bullet.h"
#include "Utils.h"

void Bullet::Initialize(const sf::Vector2f& initialPos, float direction) {
    bulletDirection = (direction > 0)? 1 : -1;
    bulletPos = initialPos;
}

//when called, called frame by frame.
void Bullet::Move() {
    //bulletPos.x += 0; //always is 0 but left in case we want to move a bullet on the x axis..
    bulletPos.y += bulletDirection * BULLETSSPEED * TimeManager::GetDeltaTime();
}

bool Bullet::CanBulletBeDisposed() {
    return bulletPos.y > SCREENVERTICAL || bulletPos.y < 0;
}