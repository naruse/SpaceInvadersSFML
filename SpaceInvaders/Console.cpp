//
//  Console.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/26/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#include "Console.h"


void Console::Log(std::string s) {
    for(int i = 1; i < consoleSize; i++) {
        buffer[i-1] = buffer[i];
    }
    buffer[consoleSize-1] = s;
}


std::string Console::GetConsoleContents() {
    std::string result = "";
    for(int i = 0; i < consoleSize; i++) {
        result = result + buffer[i] + "\n";
    }
    return result;
}

void Console::Clear() {
    for(int i = 0; i < consoleSize; i++) {
        buffer[i] = "";
    }
}