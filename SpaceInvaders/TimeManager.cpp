//
//  TimeManager.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/25/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#include "TimeManager.h"

float TimeManager::GetDeltaTime() {
    return deltaTime;
}

void TimeManager::UpdateDelta() {
    deltaTime = clock.restart().asSeconds();
}

TimeManager::TimeManager() {
    deltaTime = 0;
}