// andrew's cool game! :)

// library stuff
#include "raylib.h"
#include <string>
#include <chrono>
#include <iostream>

// my stuff
#include "Player.h"
#include "Bullet.h"
#include "ObjectPool.h"
#include "ChargeZone.h"
#include "GameManager.h"
#include "SoundManager.h"

int main(void)
{

    srand(static_cast<int>(time(NULL)));

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int tickRate = 60;

    InitWindow(screenWidth, screenHeight, "Andrew's Cool Game");
    InitAudioDevice();

    std::cout << "Audio ready? " << IsAudioDeviceReady() << std::endl;

    SetTargetFPS(tickRate);               // Set our game to run at 60 frames-per-second
    
    // beast boy
    GameManager gm;

    // these static methods exist because we don't want to duplicate the sounds/textures that enemies use
    // BUT raylib's LoadTexture() and LoadSound() methods only work after some runtime init stuff has happened
    // so we use these to initialize them slightly later in runtime and it seems to work
    SoundManager::InitializeSounds();
    Enemy::InitializeSprite();
    ChargeBar::InitializeChargeBarSize();

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        switch (gm.GetCurrentGameState()) {
            
            case GameManager::GameState::Setup:

                if (!IsGamepadAvailable(0) && GetGamepadAxisCount(0) < 2) {
                    BeginDrawing();

                    ClearBackground(gm.GetBackgroundColour());
                    DrawText("Please connect a gamepad with two joysticks!", 190, 50, 20, BLACK);

                    EndDrawing();
                }
                else {
                    gm.StartGame();
                }

                break;

            case GameManager::GameState::Playing:

                // Update
                //----------------------------------------------------------------------------------

                gm.Tick();

                // Draw
                //----------------------------------------------------------------------------------
                BeginDrawing();

                ClearBackground(gm.GetBackgroundColour());

                gm.Draw();

                EndDrawing();

                break;
            case GameManager::GameState::PostGame:

                BeginDrawing();

                ClearBackground(gm.GetBackgroundColour());
                DrawText("You died! :(", 50, 50, 100, WHITE);
                std::string scoreString = "Final Score: " + std::to_string(gm.GetScore());
                DrawText(scoreString.c_str(), 50, 200, 100, WHITE);

                DrawText("Press any button to play again!", 50, GetScreenHeight() - 100, 50, WHITE);

                // checks for any button
                if (GetGamepadButtonPressed() != -1) {
                    
                    gm.Reset();

                }

                EndDrawing();

                break;
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}