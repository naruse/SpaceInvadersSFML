
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Defines.h"
#include "ResourcePath.hpp"
#include "TimeManager.h"
#include "GameManager.h"
#include "Utils.h"

//initialization of the static console logger.
int Console::consoleSize = CONSOLEBUFFERSIZE;
std::string Console::buffer[CONSOLEBUFFERSIZE];
/* * * * * * * * * * * * * * * * * * * * * * */
int ScoreManager::currentScore = 0;
float TimeManager::deltaTime = 0;

//initialization of the static bullet array for rendering bullets on the screen.
Bullet* BulletManager::enemyBullets;
Bullet* BulletManager::playerBullets;

//offsets for making the bullet sprite match the bullet position for when colliding
sf::Vector2f BulletManager::offsetEnemyBullet;
sf::Vector2f BulletManager::offsetPlayerBullet;

//initialization of the static arrays for rendering explosions on the screen.
sf::Vector2f* ExplosionManager::explosionsPositions;
int* ExplosionManager::frameAtExplosionsPositions;

GameManager gameManager(SCREENHORIZONTAL,SCREENVERTICAL);//initialize the main window
TimeManager timeManager;

//Prototypes:
void RenderingLoop();
void GameLogicLoop();

int main(int, char const**) {
    // Start the game loop
    while (gameManager.GetWindow().isOpen()) {
        sf::Event event;
        while(gameManager.GetWindow().pollEvent(event)) {
            if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) ||
                event.type == sf::Event::Closed) {
                gameManager.GetWindow().close();
            }
            if(gameManager.GameHasFinished()) {
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    gameManager.RestartGameAndClearScoresAndLives();
                }
            }
        }
        gameManager.ProcessInput();
        RenderingLoop();
        GameLogicLoop();
    }
    return EXIT_SUCCESS;
}


void RenderingLoop() {
    // Clear screen
    gameManager.GetWindow().clear();
    gameManager.Render();
    // Update the window
    gameManager.GetWindow().display();
    timeManager.UpdateDelta();//calculate time to complete the last frame.
}

void GameLogicLoop() {
    gameManager.GameLogic();
}
