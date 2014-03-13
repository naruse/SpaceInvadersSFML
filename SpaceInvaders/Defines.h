//
//  Defines.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/26/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//
#include <SFML/Graphics.hpp>

#ifndef SpaceInvaders_Defines_h
#define SpaceInvaders_Defines_h
/*** DONT TOUCH ***/
#define NULLV2 sf::Vector2f(-999,-999)
/** ** **  ** ** **/

#define CONSOLEBUFFERSIZE 25

#define ENEMIESHORIZONTAL 11
#define ENEMIESVERTICAL 5

#define SCREENHORIZONTAL 1024
#define SCREENVERTICAL 768

#define STARTINGDISTANCEHORIZONTAL 60
#define STARTINGDISTANCEVERTICAL 90

#define DISTANCEBETWEENENEMIESHORIZONTAL 80
#define DISTANCEBETWEENENEMIESVERTICAL 65

#define ENEMIESMOVINGDISTANCEHORIZONTAL 10.0
#define ENEMIESMOVINGDISTANCEVERTICAL 25.0

#define MAXBULLETSONSCREEN 32 //maximum amount of bullets renderable to the screen
#define MAXEXPLOSIONSONSCREEN 32//maximum amount of explosions at the same time on the screen
#define BULLETSSPEED 300.0

#define ENEMYUFOSPEED 400.0
#define ENEMYUFOSCORE 300 //scoring points when you kill an UFO
#define ENEMYSCORE 50 //scoring points when you kill a normal enemy

#define ENEMIESMOVINGRATIO 0.5 //ratio of movement of the enemies
#define UFOSPAWNINGRATIO 13 //secs to spawn an UFO 

#define PLAYERSPEED 150.0
#define PLAYERSHOOTRATIO 0.5 //one bullet per second
#define PLAYERLIVES 3

#define EXPLOSIONSRATIO 0.05

#endif
