//
//  Player.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/27/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#include "PlayerManager.h"

void PlayerManager::Initialize(std::string texturePath) {
    if(!playerTexture.loadFromFile(texturePath))
        std::cerr << "Couldnt load " + texturePath + " texture." << std::endl;
    playerSprite.setTexture(playerTexture);
    ResetPosition();
}

void PlayerManager::ResetPosition() {
    playerSprite.setPosition(SCREENHORIZONTAL/2 - playerTexture.getSize().x/2,SCREENVERTICAL-32/*half height texture*/ - playerTexture.getSize().y/2);
}

const sf::Sprite& PlayerManager::GetPlayerSprite() {
    return playerSprite;
}

//Moves the player within the screen limits
void PlayerManager::MoveLogic() {
    float x = 0;
    //multiply times delta time to make the movement frame independent
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        x = PLAYERSPEED*TimeManager::GetDeltaTime();
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        x = -PLAYERSPEED*TimeManager::GetDeltaTime();
    }
    if((playerSprite.getPosition().x < 0 && x > 0) || //on the left and moving  right
       (playerSprite.getPosition().x+playerTexture.getSize().x > SCREENHORIZONTAL && x < 0) ||//on the right corner and moving left
       (playerSprite.getPosition().x > 0 && playerSprite.getPosition().x+playerTexture.getSize().x < SCREENHORIZONTAL))//within limits
        playerSprite.move(x,0/*no movement in y*/);
}

void PlayerManager::ShootLogic() {
    currentTime += TimeManager::GetDeltaTime();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if(!playerHasShoot) {
            Bullet b;
            b.Initialize(playerSprite.getPosition(), -1/*direction*/);
            BulletManager::CreatePlayerBullet(b);
            playerHasShoot = true;
        }
    }
    //wait PLAYERSHOOTRATIO in order to let the player shoot again.
    if(currentTime > PLAYERSHOOTRATIO) {
        playerHasShoot = false;
        currentTime = 0;
    }
}

