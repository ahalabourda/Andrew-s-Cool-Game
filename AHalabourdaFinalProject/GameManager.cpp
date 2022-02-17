#include "GameManager.h"
#include <iostream>
#include <sstream>
#include <string>

void GameManager::Tick()
{

    // UPGRADE ZONE STUFF

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
            mPlayer.IncrementUpgradeLevel(mZones[i].GetUpgradeType());
        }

    }
    
    // PLAYER STUFF
    mPlayer.Tick();


    // GAME OBJECT STUFF

    // tick da bullets
    for (int i = 0; i < mPlayer.GetBullets().GetSize(); i++) {
        (mPlayer.GetBullets().GetItems() + i)->Tick();
    }
    
    // increment the difficulty level every 30 seconds
    if (GetGameDurationInSeconds() > mLevelDurationInSeconds * mCurrentDifficultyLevel) {
        mCurrentDifficultyLevel++;
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

    // score!
    // current level stuff
    std::stringstream ss;
    ss << "Score: " << mScore;
    std::string tmp = ss.str();

    //DrawText(std::to_string(mScore).c_str(), 25, 25, mFontSize, mHudColour);
    DrawText(tmp.c_str(), GetScreenWidth() / 100, GetScreenHeight() - mFontSize, mFontSize, BLACK);

    // current level stuff
    ss.str("");
    ss << "Level: " << mCurrentDifficultyLevel;
    tmp = ss.str();

    // using font size for positioning here!
    DrawText(tmp.c_str(), GetScreenWidth() - (GetScreenWidth() / 100) - (MeasureText(tmp.c_str(), mFontSize)), GetScreenHeight() - mFontSize, mFontSize, BLACK);

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

    mEnemySpawnFrequency = 1;
    mCurrentDifficultyLevel = 1;

    for (int i = 0; i < ARRAY_LENGTH(mZones); i++) {
        mZones[i].Reset();
    }

}

void GameManager::AttemptEnemySpawn()
{
    // try to spawn an enemy
    if (rand() % 100 <= mEnemySpawnFrequency * (mEnemySpawnAccelerationRate * mCurrentDifficultyLevel)) {

        try {
            mEnemies.GetNextAvailable()->Activate();
        }
        catch (std::exception e) {
            std::cerr << "Failed to spawn an enemy, but not crashing :)" << std::endl;
        }

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