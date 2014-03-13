//
//  Bullet.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/28/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#ifndef __SpaceInvaders__Bullet__
#define __SpaceInvaders__Bullet__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "TimeManager.h"
#include "Defines.h"
#include "Console.h"

class Bullet {
private:
    sf::Vector2f bulletPos;
    sf::Vector2f bulletOffset;//done to center the texture acording to the point
    float bulletDirection = 0;
public:
    void Initialize(const sf::Vector2f& initialPos, float);
    void Move();
    bool CanBulletBeDisposed();
    const sf::Vector2f& GetBulletPosition() { return bulletPos; }
    const sf::Vector2f& GetBulletOffset() { return bulletOffset; }
    void SetBulletPosition(const sf::Vector2f& pos) { bulletPos = pos; }
    void SetBulletCenterOffset(const sf::Vector2f& offset) { bulletOffset = offset; }
};

#endif /* defined(__SpaceInvaders__Bullet__) */
