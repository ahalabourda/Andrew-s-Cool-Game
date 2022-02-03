// andrew's cool game! :)
#include "raylib.h"
#include <string>
#include <chrono>
#include "Player.h"
#include "Bullet.h"
#include "ObjectPool.h"
#include "EnemyManager.h"
#include "ChargeZone.h"
#include <GameManager.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int tickRate = 60;

    InitWindow(screenWidth, screenHeight, "Andrew's Cool Game");

    SetTargetFPS(tickRate);               // Set our game to run at 60 frames-per-second
    
    // beast boy
    GameManager gm;

    
    
    //EnemyManager enemyManager(player);


    // timer required to control game's tickrate
    auto begin = std::chrono::steady_clock::now();


    // wait for controller availability
    while (!IsGamepadAvailable(0) && GetGamepadAxisCount(0) < 2) {

        BeginDrawing();

        ClearBackground(Color{ 25, 115, 175, 255 });
        DrawText("Please connect a gamepad with two joysticks!", 190, 50, 20, BLACK);
        
        EndDrawing();
    }


    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        
        gm.Tick();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(Color{ 0, 0, 0, 255 });

        gm.Draw();

        DrawText("Welcome to Andrew's Cool Game", 190, 50, 20, BLACK);

        if (IsGamepadAvailable(0)) {

            DrawText("Check out these cool joystick values:", 190, 200, 20, BLACK);

            DrawText(std::to_string(GetGamepadAxisMovement(0, 0)).c_str(), 50, 250, 20, BLACK);
            DrawText(std::to_string(GetGamepadAxisMovement(0, 1)).c_str(), 50, 275, 20, BLACK);
            DrawText(std::to_string(GetGamepadAxisMovement(0, 2)).c_str(), 50, 300, 20, BLACK);
            DrawText(std::to_string(GetGamepadAxisMovement(0, 3)).c_str(), 50, 325, 20, BLACK);

            

        }
        else {
            DrawText("There are no gamepads :(", 190, 300, 20, BLACK);
        }

        

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}