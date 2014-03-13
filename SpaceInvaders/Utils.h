//
//  Utils.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/25/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//
// Utility class for testing and checking values.

#ifndef __SpaceInvaders__Utils__
#define __SpaceInvaders__Utils__

#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>


class Utils {
    
public:
    static std::string ToStr(const float&);
    static std::string ToStr(const int&);
    static std::string ToStr(const bool&);
};
#endif /* defined(__SpaceInvaders__Utils__) */
