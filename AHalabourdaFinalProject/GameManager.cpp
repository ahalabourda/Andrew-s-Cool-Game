#include "GameManager.h"

GameManager::GameManager()
{

    

}

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

    bullets.Tick();

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

}
