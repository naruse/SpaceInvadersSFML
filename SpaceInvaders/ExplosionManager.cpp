//
//  ExplosionManager.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/30/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#include "ExplosionManager.h"

void ExplosionManager::Initialize() {
    explosionSprites = new sf::Sprite[numberOfFrames];
    explosionTextures = new sf::Texture[numberOfFrames];

    for(int i = 0; i < numberOfFrames; i++) {
        if(!explosionTextures[i].loadFromFile(ResourcePath() + "Boom" + Utils::ToStr(i+1) + ".png")) {
            std::cerr << "Couldnt load " + ResourcePath() + "Boom" << (i+1) << ".png" << std::endl;
        }
        explosionSprites[i].setTexture(explosionTextures[i]);
    }
    explosionsPositions = new sf::Vector2f[MAXEXPLOSIONSONSCREEN];
    frameAtExplosionsPositions = new int[MAXEXPLOSIONSONSCREEN];
    for(int i = 0; i < MAXEXPLOSIONSONSCREEN; i++) {
        explosionsPositions[i] = NULLV2;
        frameAtExplosionsPositions[i] = 0;
    }
}

//marks the explosion for not being rendered anymore
void ExplosionManager::FinalizeExplosionAtPos(int pos) {
    explosionsPositions[pos] = NULLV2;
    frameAtExplosionsPositions[pos] = 0;
}

void ExplosionManager::CreateExplosionAtPos(const sf::Vector2f& pos) {

    for(int i = 0; i < MAXEXPLOSIONSONSCREEN; i++) {
        if(explosionsPositions[i] == NULLV2) {
            //Console::Log("Created Explosion at: " + Utils::ToStr(pos.x) + "," + Utils::ToStr(pos.y));
            explosionsPositions[i] = pos;
            frameAtExplosionsPositions[i] = 0;
            break;
        }
    }
}

ExplosionManager::ExplosionManager() {
    
}

ExplosionManager::~ExplosionManager() {
    delete[] explosionSprites;
    delete[] explosionTextures;
    //delete[] explosionsPositions;//static vars.
    //delete[] frameAtExplosionsPositions;
}

