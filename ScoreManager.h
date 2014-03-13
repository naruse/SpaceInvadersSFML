//
//  ScoreManager.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/29/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#ifndef __SpaceInvaders__ScoreManager__
#define __SpaceInvaders__ScoreManager__

#include <iostream>
#include "Utils.h"

class ScoreManager {
private:
    static int currentScore;
    
public:
    static std::string GetCurrentScore();
    static void AddScore(int);
    static void ClearScores();
};
#endif /* defined(__SpaceInvaders__ScoreManager__) */
