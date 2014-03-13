//
//  TimeManager.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/25/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#ifndef __SpaceInvaders__TimeManager__
#define __SpaceInvaders__TimeManager__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class TimeManager {
private:
    static float deltaTime;
    sf::Clock clock;
public:
    TimeManager();
    ~TimeManager(){};
    static float GetDeltaTime();
    void UpdateDelta();
};

#endif /* defined(__SpaceInvaders__TimeManager__) */
