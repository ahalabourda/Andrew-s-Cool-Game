// andrew's cool game! :)
#include "raylib.h"
#include <string>
#include "Player.h"
#include "Bullet.h"
#include "ObjectPool.h"
#include "ObjectPool.cpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Andrew's Cool Game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Player player(250, 350);

    auto bullets = new ObjectPool<Bullet>(10000);

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        if (IsGamepadAvailable(0) && GetGamepadAxisCount(0) >= 2) {

            // movement
            player.Move(GetGamepadAxisMovement(0, 0), GetGamepadAxisMovement(0, 1));

            // shooting
            if (GetGamepadAxisMovement(0, 2) || GetGamepadAxisMovement(0, 3)) {
                bullets->GetNextAvailable()->Activate(player.GetPosition(), atan2(GetGamepadAxisMovement(0, 3), GetGamepadAxisMovement(0, 2)));

                DrawText(std::to_string(atan2(GetGamepadAxisMovement(0, 3), GetGamepadAxisMovement(0, 2))).c_str(), 10, 50, 20, BLACK);
            }

        }

        bullets->Tick();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(Color{ 25, 115, 175, 255 });

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

        
        bullets->Draw();

        // draw player
        DrawCircleV(player.GetPosition(), player.GetSize(), player.GetColour());

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}