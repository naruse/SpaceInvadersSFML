//
//  ExplosionManager.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/30/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#ifndef __SpaceInvaders__ExplosionManager__
#define __SpaceInvaders__ExplosionManager__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "ResourcePath.hpp"
#include "Utils.h"
#include "Console.h"

class ExplosionManager {
private:
    sf::Texture* explosionTextures;//size numberOfFrames
    sf::Sprite* explosionSprites;//size numberOfFrames
    
    const int numberOfFrames = 5;
    
    static sf::Vector2f* explosionsPositions;//Size MAXEXPLOSIONSONSCREEN
    static int* frameAtExplosionsPositions;//size of MAXEPLOSIONSONSCREEN and represents for each explosion  the frame is being displayed
    
public:
    void Initialize();
    static void CreateExplosionAtPos(const sf::Vector2f &v);
    sf::Vector2f* GetExplosionsPositions() { return explosionsPositions; }
    int* GetFrameAtExplosionsPosition() { return frameAtExplosionsPositions; }
    int GetTotalFramesForExplosion() { return numberOfFrames; }
    void IncrementFrameAtPos(int pos) { frameAtExplosionsPositions[pos]++; }
    void FinalizeExplosionAtPos(int pos);
    sf::Sprite& GetSpriteAtFrame(int frame) { return explosionSprites[frame]; }
    ExplosionManager();
    ~ExplosionManager();
};

#endif /* defined(__SpaceInvaders__ExplosionManager__) */
