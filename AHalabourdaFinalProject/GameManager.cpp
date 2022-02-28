#include "GameManager.h"
#include <sstream>
#include <string>

void GameManager::Tick()
{

    // UPGRADE ZONE STUFF
    ProcessZones();
    
    // PLAYER STUFF
    mPlayer.Tick();

    // GAME OBJECT STUFF
    ProcessSpawning();
    ProcessBullets();
    ProcessEnemies();

    // increment the difficulty level every 30 seconds
    if (GetGameDurationInSeconds() > mLevelDurationInSeconds * mCurrentDifficultyLevel) {
        mCurrentDifficultyLevel++;
    }

    // this is required to actually play a music stream with raylib. hmm
    UpdateMusicStream(*SoundManager::GetMusic());

}

void GameManager::Draw() const
{

    // space!
    float offsetX = -((GetScreenWidth() / 2.0f) - mPlayer.GetSmoothedPosition(mPlayer.GetRecentPositions()).x) * .1f;
    float offsetY = -((GetScreenHeight() / 2.0f) - mPlayer.GetSmoothedPosition(mPlayer.GetRecentPositions()).y) * .1f;

    DrawTextureTiled(   mBackground,
                        Rectangle{ 0.0f, 0.0f, static_cast<float>(mBackground.width), static_cast<float>(mBackground.height) }, // source rectangle (same shape as the bg file)
                        Rectangle{ -150.0f, -150.0f, GetScreenWidth() * 1.5f, GetScreenHeight() * 1.5f }, // destination rectangle (bigger than the screen so we can wobble)
                        Vector2{ offsetX, offsetY }, // origin
                        0.0f, // rotation
                        1.0f, // scale
                        WHITE
    );

    // charge zones
    for (int i = 0; i < ARRAY_LENGTH(mZones); i++) {
        mZones[i].Draw();
    }

    // bullets
    mPlayer.GetBullets().Draw();

    // player
    mPlayer.Draw();

    // enemy
    mEnemies.Draw();

    // hud zone!

    // score
    std::stringstream ss;
    ss << "Score: " << mScore;
    std::string tmp = ss.str();
    DrawText(tmp.c_str(), GetScreenWidth() / 100, GetScreenHeight() - mFontSize, mFontSize, mHudColour);

    // current level
    ss.str(""); // reusing the stringstream. so sick..
    ss << "Level: " << mCurrentDifficultyLevel;
    tmp = ss.str();
    DrawText(tmp.c_str(), GetScreenWidth() - (GetScreenWidth() / 100) - (MeasureText(tmp.c_str(), mFontSize)), GetScreenHeight() - mFontSize, mFontSize, mHudColour);

}

void GameManager::StartGame()
{
    srand(static_cast<int>(time(NULL)));
    mCurrentGameState = GameState::Playing;
    mActiveZone->SetIsActive(true);
    SoundManager::StartMusic();
}

void GameManager::EndGame()
{

    // score submission!
    mLeaderboardManager.SubmitScore(mUserInfo.GetName(), mScore);
    mLeaderboardManager.FetchLeaderboardData();

    SoundManager::TriggerSound(SoundManager::SoundKey::PlayerDeath);
    SoundManager::StopMusic();

    mCurrentGameState = GameState::PostGame;
}

void GameManager::Reset()
{

    mCurrentGameState = GameState::Playing;
    mTimerBegin = std::chrono::steady_clock::now();
    mScore = 0;

    mEnemies.Reset();

    mPlayer.Reset();

    mCurrentDifficultyLevel = 1;

    for (int i = 0; i < ARRAY_LENGTH(mZones); i++) {
        mZones[i].Reset();
    }

    SoundManager::StartMusic();

}

void GameManager::ProcessSpawning()
{

    mTicksSinceLastEnemySpawn++;

    if (mTicksSinceLastEnemySpawn >= GetActualTicksPerEnemySpawn()) {

        mTicksSinceLastEnemySpawn = 0;

        try {
            mEnemies.GetNextAvailable()->Activate();
        }
        catch (std::exception e) {
            // Failed to spawn an enemy, but not crashing :)
            // this used to have a std::cerr but i'm building for release so no error messages..
            // if i'm not doing anything on the catch then maybe this exception throw is useless. hmm
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

            if ((mEnemies.GetItems() + i)->IsCollidingWithPlayer(mPlayer.GetPosition())) {

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

void GameManager::ProcessBullets()
{
    // tick da bullets
    for (int i = 0; i < mPlayer.GetBullets().GetSize(); i++) {
        (mPlayer.GetBullets().GetItems() + i)->Tick();
    }
}

void GameManager::ProcessZones()
{
    // first we check the currently active zone to see if they are gone
    if (!CheckCollisionPointRec(mPlayer.GetPosition(), mActiveZone->GetTriggerRect())) {

        // if the player is NOT in the "active" zone, this means they just moved to another zone! so we find which one they moved to and then update the "active" tracking accordingly
        mActiveZone->SetIsActive(false);

        for (int i = 0; i < ARRAY_LENGTH(mZones); i++) {
            if (CheckCollisionPointRec(mPlayer.GetPosition(), mZones[i].GetTriggerRect())) {
                mActiveZone = &mZones[i];
                mActiveZone->SetIsActive(true);
            }
        }

    }

    // only tick the active zone
    if (mActiveZone->Tick() == true) {
        mPlayer.IncrementUpgradeLevel(mActiveZone->GetUpgradeType());
    }
}

// multiplies the spawn rate by .8 each time we move up a level
int GameManager::GetActualTicksPerEnemySpawn() const
{
    return mTicksPerEnemySpawnBase * std::powf(mEnemySpawnAccelerationRate, static_cast<float>(mCurrentDifficultyLevel) - 1.0f);
}