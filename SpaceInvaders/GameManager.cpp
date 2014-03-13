//
//  GameManager.cpp
//  SpaceInvaders
//
//  Created by Juan Sebastian Muñoz on 6/25/13.
//  Copyright (c) 2013 Juan Sebastian Muñoz. All rights reserved.
//

#include "GameManager.h"


sf::RenderWindow& GameManager::GetWindow() {
    return gameWindow;
}

//Initialize everything
GameManager::GameManager(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    livesLeft = PLAYERLIVES;
    
    if(!playerLivesTexture.loadFromFile(ResourcePath() + "Player.png"))
        std::cerr << "Couldnt load Player.png for lives icon." << std::endl;
    playerLivesSprite.setTexture(playerLivesTexture);
    playerLivesSprite.setScale(0.5, 0.5);
    playerLivesSprite.setPosition(SCREENHORIZONTAL-playerLivesTexture.getSize().x/2, 0);
    
    // Create a graphical text to display
    if(!sansationFont.loadFromFile(ResourcePath() + "sansation.ttf"))
        std::cerr << "Couldnt load sansation.ttf font." << std::endl;
    consoleText.setFont(sansationFont);
    consoleText.setCharacterSize(consoleSize);
    consoleText.setColor(sf::Color::Red);
    
    gameOverText.setFont(sansationFont);
    gameOverText.setCharacterSize(gameOverSize);
    gameOverText.setColor(sf::Color::White);
    gameOverText.setPosition(SCREENHORIZONTAL/2 - SCREENHORIZONTAL/5, SCREENVERTICAL/2);
    
    //Load score font
    scoreText.setFont(sansationFont);
    scoreText.setCharacterSize(scoreTextSize);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(SCREENHORIZONTAL/2, 0);
    Console::Clear();
    
    gameWindow.create(sf::VideoMode(windowWidth, windowHeight), "Space Invaders Juan Sebastian Munoz");

    if (!appIcon.loadFromFile(ResourcePath() + "Icon.png"))
        std::cerr << "Couldnt load Icon.png from Resources." << std::endl;
    gameWindow.setIcon(appIcon.getSize().x, appIcon.getSize().y, appIcon.getPixelsPtr());

    // Load a sprite to display
    if (!backgroundTexture.loadFromFile(ResourcePath() + "Background.png"))
        std::cerr << "Couldnt load Background.png from Resources." << std::endl;
    background.setTexture(backgroundTexture);
    background.setScale((float)gameWindow.getSize().x/(float)backgroundTexture.getSize().x,
                        (float)gameWindow.getSize().y/(float)backgroundTexture.getSize().y);
    
    player.Initialize(ResourcePath() + "Player.png");
    bulletManager.Initialize();
    enemyManager.InitializeEnemies();
    explosionManager.Initialize();
}

GameManager::~GameManager() {
    enemyManager.~EnemyManager();
    player.~PlayerManager();
    bulletManager.~BulletManager();
}

//Called frame by frame
void GameManager::ProcessInput() {
    player.MoveLogic();
    player.ShootLogic();
}


//Called frame by frame RENDER LOOP
void GameManager::Render() {
    gameWindow.draw(background);
    
    if(!gameFinished) {
        DrawBullets();
        enemyManager.MoveEnemiesLogic();
        DrawEnemies();
        DrawPlayer();
        
        DrawExplosions();
        DrawGUI();
    } else {
        std::string gameOverStr =  "     Game Over\n";
                    gameOverStr += " Final Score: " + ScoreManager::GetCurrentScore() + "\n";
                    gameOverStr += "press 'R' to restart";
        gameOverText.setString(gameOverStr);
        gameWindow.draw(gameOverText);        
    }

    consoleText.setString(Console::GetConsoleContents());
    gameWindow.draw(consoleText);
}

float currentTime = 0;
void GameManager::DrawExplosions() {
    currentTime += TimeManager::GetDeltaTime();
    for(int i = 0; i < MAXEXPLOSIONSONSCREEN; i++) {
        if(explosionManager.GetExplosionsPositions()[i] != NULLV2) {//we found an explosion lets check if its time for loading the explosion
            if(currentTime > EXPLOSIONSRATIO) {//each EXPLOSIONSRATIO enters here.
                //Set the position of the explosion depending on the frame that has to be loaded
                explosionManager.IncrementFrameAtPos(i);
                if(explosionManager.GetTotalFramesForExplosion() == explosionManager.GetFrameAtExplosionsPosition()[i]) {//if the explosion has finished reproducing
                    explosionManager.FinalizeExplosionAtPos(i);//remove the explosion
                }
                currentTime = 0;
            }
            //Console::Log(Utils::ToStr(explosionManager.GetExplosionsPositions()[i].x) + "," + Utils::ToStr(explosionManager.GetExplosionsPositions()[i].y));
            explosionManager.GetSpriteAtFrame(explosionManager.GetFrameAtExplosionsPosition()[i]).setPosition(explosionManager.GetExplosionsPositions()[i]);
            gameWindow.draw(explosionManager.GetSpriteAtFrame(explosionManager.GetFrameAtExplosionsPosition()[i]));
        }
    }
}

//checks for player dying / destroying enemies
void GameManager::GameLogic() {
    bool allEnemiesDead = true;
    //check for player hitting the enemy.
    for(int i = 0; i < ENEMIESHORIZONTAL; i++) {
        for(int j = 0; j < ENEMIESVERTICAL; j++) {
            if(enemyManager.GetEnemies()[i][j] != NULL)
                allEnemiesDead = false;
            for(int k = 0; k < MAXBULLETSONSCREEN; k++) {
                if(BulletManager::GetPlayerBullets()[k].GetBulletPosition() != NULLV2 && //Check a valid bullet
                    enemyManager.GetEnemies()[i][j] != NULL) {//check that the enemy position is valid
                    //if the bullet [k]  hit enemy[i][j]
                    if(enemyManager.GetEnemies()[i][j]->GetEnemySprite().getGlobalBounds().contains(BulletManager::GetPlayerBullets()[k].GetBulletPosition() + BulletManager::GetPlayerBullets()[k].GetBulletOffset())) {
                        //Console::Log("Bullet " + Utils::ToStr(k) + " Touched enemy " + Utils::ToStr(i) + "," + Utils::ToStr(j));
                        ScoreManager::AddScore(ENEMYSCORE);
                        //Console::Log("Bullet Pos: " + Utils::ToStr(BulletManager::GetPlayerBullets()[k].GetBulletPosition().x)+ "," +Utils::ToStr(BulletManager::GetPlayerBullets()[k].GetBulletPosition().y));
                        ExplosionManager::CreateExplosionAtPos(enemyManager.GetEnemies()[i][j]->GetEnemySprite().getPosition());
                        bulletManager.DestroyPlayerBulletAtPos(k);//destroy bullet [k]
                        delete enemyManager.GetEnemies()[i][j];// free enemy memory
                        enemyManager.GetEnemies()[i][j] = NULL;//make the pointer point to NULL
                    }
                }
            }
            //check if an enemy touches the bottom side of the screen
            if(enemyManager.GetEnemies()[i][j] != NULL) {
                sf::FloatRect enemyRect = enemyManager.GetEnemies()[i][j]->GetEnemySprite().getGlobalBounds();
                if(enemyRect.top + enemyRect.height > SCREENVERTICAL - player.GetPlayerSprite().getGlobalBounds().height) {
                    RestartGame();
                    livesLeft--;
                }
            }
        }
    }
    //Check for player hitting the UFO
    if(enemyManager.GetEnemyUFO() != NULL) {
        for(int k = 0; k < MAXBULLETSONSCREEN; k++) {
            //A bullet has hit the UFO.
            if(enemyManager.GetEnemyUFO()->GetEnemySprite().getGlobalBounds().contains(BulletManager::GetPlayerBullets()[k].GetBulletPosition() + BulletManager::GetPlayerBullets()[k].GetBulletOffset())) {
                bulletManager.DestroyPlayerBulletAtPos(k);
                ScoreManager::AddScore(ENEMYUFOSCORE);
                ExplosionManager::CreateExplosionAtPos(enemyManager.GetEnemyUFO()->GetEnemySprite().getPosition());
                enemyManager.ResetEnemyUFOPosition();
                break;
            }
        }
    }
    //check for enemy bullets hitting the player.
    for(int k = 0; k < MAXBULLETSONSCREEN; k++) {
        if(player.GetPlayerSprite().getGlobalBounds().contains(BulletManager::GetEnemyBullets()[k].GetBulletPosition() +
                                                               BulletManager::GetEnemyBullets()[k].GetBulletOffset())) {
            bulletManager.DestroyEnemyBulletAtPos(k);
            //Console::Log("enemy bullet hit player");
            ExplosionManager::CreateExplosionAtPos(player.GetPlayerSprite().getPosition());
            RestartGame();
            livesLeft--;
            break;
        }
    }
    
    if(livesLeft == 0) {
        gameFinished = true;
        //Console::Log("GAME OVER");
    }
    if(allEnemiesDead)
        RestartGame();
}

void GameManager::RestartGame() {
    //Console::Log("Restarting Game");
    //destroy all the bullets.
    for(int i = 0; i < MAXBULLETSONSCREEN; i++) {
        bulletManager.DestroyEnemyBulletAtPos(i);
        bulletManager.DestroyEnemyBulletAtPos(i);
    }
    player.ResetPosition();
    enemyManager.RestartEnemies();
}

void GameManager::RestartGameAndClearScoresAndLives() {
    RestartGame();
    livesLeft = PLAYERLIVES;
    ScoreManager::ClearScores();
    gameFinished = false;
}

void GameManager::DrawPlayer() {
    gameWindow.draw(player.GetPlayerSprite());
}

void GameManager::DrawBullets() {
    for(int i = 0; i < MAXBULLETSONSCREEN; i++) {
        //Player bullets
        if(bulletManager.GetPlayerBullets()[i].GetBulletPosition() != NULLV2) {
            
            bulletManager.GetPlayerBulletSprite().setPosition(bulletManager.GetPlayerBullets()[i].GetBulletPosition());
            gameWindow.draw(bulletManager.GetPlayerBulletSprite());
            
            bulletManager.GetPlayerBullets()[i].Move();//move the just drawn bullet
            if(bulletManager.GetPlayerBullets()[i].CanBulletBeDisposed()) {
                //anulate the bullet and dont draw it anymore
                //Console::Log("Disposing player bullet: " + Utils::ToStr(i));
                bulletManager.GetPlayerBullets()[i].SetBulletPosition(NULLV2);
            }
        }
        //Enemy Bullets
        if(bulletManager.GetEnemyBullets()[i].GetBulletPosition() != NULLV2) {
            
            bulletManager.GetEnemyBulletSprite().setPosition(bulletManager.GetEnemyBullets()[i].GetBulletPosition());
            gameWindow.draw(bulletManager.GetEnemyBulletSprite());
            
            bulletManager.GetEnemyBullets()[i].Move();//move the just drawn bullet
            if(bulletManager.GetEnemyBullets()[i].CanBulletBeDisposed()) {
                //anulate the bullet and dont draw it anymore
                //Console::Log("Disposing enemy bullet: " + Utils::ToStr(i));
                bulletManager.GetEnemyBullets()[i].SetBulletPosition(NULLV2);
            }
        }
    }
    bulletManager.GetPlayerBulletSprite().setPosition(NULLV2);
    bulletManager.GetEnemyBulletSprite().setPosition(NULLV2);
}

void GameManager::DrawEnemies() {
    for(int i = 0; i < ENEMIESHORIZONTAL; i++) {
        for(int j = 0; j < ENEMIESVERTICAL; j++) {
            if(enemyManager.GetEnemies()[i][j] != NULL)
                gameWindow.draw(enemyManager.GetEnemies()[i][j]->GetEnemySprite());
        }
    }
    if(enemyManager.GetEnemyUFO() != NULL) {
        gameWindow.draw(enemyManager.GetEnemyUFO()->GetEnemySprite());
    }
    
}

void GameManager::DrawGUI() {
    //lives.
    for(int i = 1; i < livesLeft+1; i++) {
        playerLivesSprite.setPosition(SCREENHORIZONTAL-(playerLivesTexture.getSize().x/2*i), 0);
        gameWindow.draw(playerLivesSprite);
    }
    //Scores
    scoreText.setString("SCORE: " + ScoreManager::GetCurrentScore());
    gameWindow.draw(scoreText);
}














