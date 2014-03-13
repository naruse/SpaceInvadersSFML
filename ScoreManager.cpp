//
//  ScoreManager.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/29/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#include "ScoreManager.h"

void ScoreManager::AddScore(int sc) {
     currentScore += sc;
}

void ScoreManager::ClearScores() {
    currentScore = 0;
}

std::string ScoreManager::GetCurrentScore() {
    return Utils::ToStr(currentScore);
}