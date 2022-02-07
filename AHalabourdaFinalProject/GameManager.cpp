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

    player.Move(GetGamepadAxisMovement(0, 0), GetGamepadAxisMovement(0, 1));

    // shooting
    if (GetGamepadAxisMovement(0, 2) || GetGamepadAxisMovement(0, 3)) {
        bullets.GetNextAvailable()->Activate(player.GetPosition(), atan2(GetGamepadAxisMovement(0, 3), GetGamepadAxisMovement(0, 2)));
    }

    // tick da bullets
    for (int i = 0; i < bullets.GetSize(); i++) {
        (bullets.GetItems() + i)->Tick();
    }
    

    // try to spawn an enemy
    if (rand() % 30 == 1) {

        try {
            enemies.GetNextAvailable()->Activate();
        }
        catch(std::exception e) {
            std::cerr << "Failed to spawn an enemy, but not crashing :)" << std::endl;
        }
        
        //std::cout << "activating an enemy!" << std::endl;
    }

    // tick all enemies
    for (int i = 0; i < enemies.GetSize(); i++) {
        (enemies.GetItems() + i)->Tick(player.GetPosition());
    }

    // check collisions for all bullets, all enemies, and player
    for (int i = 0; i < enemies.GetSize(); i++) {

        for (int j = 0; j < bullets.GetSize(); j++) {

            // only check if both are active
            if ((enemies.GetItems() + i)->GetIsActive() && (bullets.GetItems() + j)->GetIsActive()) {
                
                if (CheckCollisionCircleRec((bullets.GetItems() + j)->GetPosition(), (bullets.GetItems() + j)->GetSize(), (enemies.GetItems() + i)->GetRectangle())) {
                    (enemies.GetItems() + i)->Deactivate();
                    (bullets.GetItems() + j)->Deactivate();
                    score++;
                }

            }

        }

    }

    // check for player collision!
    for (int i = 0; i < enemies.GetSize(); i++) {

        if ((enemies.GetItems() + i)->GetIsActive()) {

            if (CheckCollisionCircleRec(player.GetPosition(), player.GetSize(), (enemies.GetItems() + i)->GetRectangle())) {

                std::cout << " wow a collide with player" << std::endl;

                EndGame();

            }

        }

    }

}

void GameManager::Draw() const
{

    // charge zones
    for (int i = 0; i < ARRAY_LENGTH(zones); i++) {
        zones[i].Draw();
    }

    // bullets
    bullets.Draw();

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
}