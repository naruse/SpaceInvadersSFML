//
//  Console.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/26/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#ifndef SpaceInvaders_Console_h
#define SpaceInvaders_Console_h

#include <iostream>

class Console {
private:
    static int consoleSize;
    static std::string buffer[];
    
public:
    static std::string GetConsoleContents();
    static int GetBufferSize() { return consoleSize; }
    static void Log(std::string);
    static void Clear();
};

#endif
