//
//  Utils.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/25/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#include "Utils.h"

std::string Utils::ToStr(const float& f) {
    std::stringstream stream;
    stream << f;
    return stream.str();
}
std::string Utils::ToStr(const int& i) {
    std::stringstream stream;
    stream << i;
    return stream.str();
}

std::string Utils::ToStr(const bool& b) {
    return (b? "True" : "False");
}

