//
//  GameManager.h
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/25/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#ifndef __SpaceInvaders__GameManager__
#define __SpaceInvaders__GameManager__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ResourcePath.hpp"
#include "TimeManager.h"
#include "BulletManager.h"
#include "ScoreManager.h"
#include "ExplosionManager.h"
#include "Bullet.h"
#include "Console.h"

class GameManager {
private:
    sf::Image appIcon;
    sf::Font sansationFont;
    int windowWidth;
    int windowHeight;
    sf::RenderWindow gameWindow;
    
    sf::Sprite background;
    sf::Texture backgroundTexture;

    int livesLeft;//initialized with defines.h
    sf::Texture playerLivesTexture;
    sf::Sprite playerLivesSprite;

    sf::Text consoleText;
    int consoleSize = 13;
    
    sf::Text scoreText;
    int scoreTextSize = 22;
    
    sf::Text gameOverText;
    int gameOverSize = 48;
    
    EnemyManager enemyManager;
    PlayerManager player;
    BulletManager bulletManager;
    ExplosionManager explosionManager;
    bool gameFinished = false;
    
    
    void DrawBullets();
    void DrawEnemies();
    void DrawPlayer();
    void DrawExplosions();
    void DrawGUI();
    
    void RestartGame();//restarts the game, lives arent touched and scores arent touched

public:
    static void CreateBullet(Bullet* b);
    GameManager(int, int);
    ~GameManager();
    sf::RenderWindow& GetWindow();
    void Render();
    void ProcessInput();
    void GameLogic();
    bool GameHasFinished() { return gameFinished; }
    void RestartGameAndClearScoresAndLives();//this is called when we get a Game Over.
};
#endif /* defined(__SpaceInvaders__GameManager__) */
