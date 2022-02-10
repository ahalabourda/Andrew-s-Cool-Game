#include "GameManager.h"
#include <iostream>
#include <string>

void GameManager::Tick()
{

    // find active charge zone
    for (int i = 0; i < ARRAY_LENGTH(zones); i++) {
        
        if (CheckCollisionPointRec(player.GetPosition(), zones[i].GetTriggerRect())) {
            zones[i].SetIsActive(true);
        }
        else {
            // we are just spamming this to false every tick that we aren't in... hmm. maybe an event based system is in order
            zones[i].SetIsActive(false);
        }

    }

    
    
    // UPGRADE ZONE STUFF
    

    
    player.Tick();


    // GAME OBJECT STUFF

    // tick da bullets
    for (int i = 0; i < player.GetBullets().GetSize(); i++) {
        (player.GetBullets().GetItems() + i)->Tick();
    }
    
    

    AttemptEnemySpawn();

    ProcessEnemies();

}

void GameManager::Draw() const
{

    // charge zones
    for (int i = 0; i < ARRAY_LENGTH(zones); i++) {
        zones[i].Draw();
    }

    // bullets
    player.GetBullets().Draw();

    player.Draw();

    enemies.Draw();

    DrawText(std::to_string(score).c_str(), 25, 25, fontSize, hudColour);

}

void GameManager::StartGame()
{
    currentGameState = GameState::Playing;
}

void GameManager::EndGame()
{

    currentGameState = GameState::PostGame;

}

void GameManager::Reset()
{

    currentGameState = GameState::Playing;
    begin = std::chrono::steady_clock::now();
    score = 0;

    enemies.Reset();

    player.Reset();

}

void GameManager::AttemptEnemySpawn()
{
    // try to spawn an enemy
    if (rand() % 100 <= enemySpawnFrequency) {

        try {
            enemies.GetNextAvailable()->Activate();
        }
        catch (std::exception e) {
            std::cerr << "Failed to spawn an enemy, but not crashing :)" << std::endl;
        }

        //std::cout << "activating an enemy!" << std::endl;
    }
}

void GameManager::ProcessEnemies()
{

    // big loop for all enemies! ticks them forward, and checks collision with bullets and the player
    for (int i = 0; i < enemies.GetSize(); i++) {

        // we only care about checking active enemies
        if ((enemies.GetItems() + i)->GetIsActive()) {

            // tick the enemy
            (enemies.GetItems() + i)->Tick(player.GetPosition());

            if (CheckCollisionCircleRec(player.GetPosition(), player.GetSize(), (enemies.GetItems() + i)->GetRectangle())) {

                EndGame();

            }

            for (int j = 0; j < player.GetBullets().GetSize(); j++) {

                // we only care about active bullets
                if ((player.GetBullets().GetItems() + j)->GetIsActive()) {

                    if (CheckCollisionCircleRec((player.GetBullets().GetItems() + j)->GetPosition(), (player.GetBullets().GetItems() + j)->GetSize(), (enemies.GetItems() + i)->GetRectangle())) {
                        (enemies.GetItems() + i)->Deactivate();
                        (player.GetBullets().GetItems() + j)->Deactivate();
                        score++;
                    }

                }

            }

        }

    }

}