#include "GameManager.h"
#include <iostream>
#include <string>

void GameManager::Tick()
{

    // find active charge zone
    for (int i = 0; i < ARRAY_LENGTH(mZones); i++) {
        
        if (CheckCollisionPointRec(mPlayer.GetPosition(), mZones[i].GetTriggerRect())) {
            mZones[i].SetIsActive(true);
        }
        else {
            // we are just spamming this to false every tick... hmm. maybe an event based system is in order
            mZones[i].SetIsActive(false);
        }

        // TODO: discuss how to do this properly
        if (mZones[i].Tick() == true) {
            
            std::cout << "we are upgarding " << i << std::endl;
            mPlayer.IncrementUpgradeLevel(mZones[i].GetUpgradeType());

        }

    }
    
    // UPGRADE ZONE STUFF
    

    
    mPlayer.Tick();


    // GAME OBJECT STUFF

    // tick da bullets
    for (int i = 0; i < mPlayer.GetBullets().GetSize(); i++) {
        (mPlayer.GetBullets().GetItems() + i)->Tick();
    }
    
    

    AttemptEnemySpawn();

    ProcessEnemies();

}

void GameManager::Draw() const
{

    // charge zones
    for (int i = 0; i < ARRAY_LENGTH(mZones); i++) {
        mZones[i].Draw();
    }

    // bullets
    mPlayer.GetBullets().Draw();

    mPlayer.Draw();

    mEnemies.Draw();

    DrawText(std::to_string(mScore).c_str(), 25, 25, mFontSize, mHudColour);

}

void GameManager::StartGame()
{
    mCurrentGameState = GameState::Playing;
}

void GameManager::EndGame()
{
    mCurrentGameState = GameState::PostGame;
}

void GameManager::Reset()
{

    mCurrentGameState = GameState::Playing;
    mTimerBegin = std::chrono::steady_clock::now();
    mScore = 0;

    mEnemies.Reset();

    mPlayer.Reset();

    for (int i = 0; i < ARRAY_LENGTH(mZones); i++) {
        mZones[i].Reset();
    }

}

void GameManager::AttemptEnemySpawn()
{
    // try to spawn an enemy
    if (rand() % 100 <= mEnemySpawnFrequency) {

        try {
            mEnemies.GetNextAvailable()->Activate();
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
    for (int i = 0; i < mEnemies.GetSize(); i++) {

        // we only care about checking active enemies
        if ((mEnemies.GetItems() + i)->GetIsActive()) {

            // tick the enemy
            (mEnemies.GetItems() + i)->Tick(mPlayer.GetPosition());

            if (CheckCollisionCircleRec(mPlayer.GetPosition(), mPlayer.GetSize(), (mEnemies.GetItems() + i)->GetRectangle())) {

                EndGame();

            }

            for (int j = 0; j < mPlayer.GetBullets().GetSize(); j++) {

                // we only care about active bullets
                if ((mPlayer.GetBullets().GetItems() + j)->GetIsActive()) {

                    if (CheckCollisionCircleRec((mPlayer.GetBullets().GetItems() + j)->GetPosition(), (mPlayer.GetBullets().GetItems() + j)->GetSize(), (mEnemies.GetItems() + i)->GetRectangle())) {
                        
                        // TakeDamage() returns TRUE if the enemy died from this damage, so we add some score
                        if ((mEnemies.GetItems() + i)->TakeDamage(mPlayer.GetActualDamage()) == true) {
                            mScore += mPlayer.GetUpgradeLevel(Upgrade::UpgradeType::ScoreMultiplier);
                        }

                        (mPlayer.GetBullets().GetItems() + j)->Deactivate();
                    }

                }

            }

        }

    }

}