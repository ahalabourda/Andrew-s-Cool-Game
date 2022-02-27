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
#include "LeaderboardManager.h"

void DrawTextCentered(std::string pText, int pPositionY, int pFontSize = 24, Color pColour = BLACK);

int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int tickRate = 60;

    InitWindow(screenWidth, screenHeight, "Andrew's Cool Game");
    InitAudioDevice();

    SetTargetFPS(tickRate);               // Set our game to run at 60 frames-per-second
    
    // beast boy
    GameManager gm;

    // http testing stuff
    LeaderboardManager lm;

    gm.InitLeaderboardManager(lm);

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
            {


                // Update

                if (GetGamepadButtonPressed() != -1 && gm.GetUserInfo().GetName().length() > 0) {
                    gm.StartGame();
                }


                // Set the window's cursor to the I-Beam
                SetMouseCursor(MOUSE_CURSOR_IBEAM);

                // Get char pressed (unicode character) on the queue
                int key = GetCharPressed();

                // Check if more characters have been pressed on the same frame
                while (key > 0)
                {
                    // only allows A-Za-z
                    if (((key >= 65) && (key <= 90) || (key >= 97 && key <= 122)) && (gm.GetUserInfo().GetName().length() < gm.GetUserInfo().GetMaxNameLength()))
                    {
                        gm.GetUserInfo().AddLetter(static_cast<char>(key));
                    }

                    key = GetCharPressed();  // Check next character in the queue
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    gm.GetUserInfo().RemoveLetter();

                }


                gm.GetUserInfo().Tick();

                // Draw

                BeginDrawing();

                ClearBackground(gm.GetBackgroundColour());

                // my unbelievably janky method for getting a new random colour every 1 second
                // lol
                // would NOT do this in a real project. but it's the last weekend before i start on my new team so it's staying because it works
                srand(static_cast<int>(GetTime() + 333));

                Color randomColor{  static_cast<unsigned char>(rand() % 255),
                                    static_cast<unsigned char>(rand() % 255),
                                    static_cast<unsigned char>(rand() % 255),
                                    255};

                DrawTextCentered("Space Tank: 3030", GetScreenHeight() / 12, 100, randomColor);
                DrawTextCentered("Enter a name, then press any gamepad button to begin!", GetScreenHeight() / 2, 42, BLACK);
                //DrawText("Welcome to Andrew's Cool Game!", GetScreenWidth() )

                //DrawTextCentered("Input your name for the high score leaderboards!", 340, gm.GetUserInfo().GetFontSize(), BLACK);

                DrawText("Name: ", static_cast<int>( GetScreenWidth() / 2.0f - gm.GetUserInfo().GetTextBox().width ), static_cast<int>(gm.GetUserInfo().GetTextBox().y), gm.GetUserInfo().GetFontSize(), BLACK);

                DrawRectangleRec(gm.GetUserInfo().GetTextBox(), LIGHTGRAY);

                DrawRectangleLines(static_cast<int>(gm.GetUserInfo().GetTextBox().x), static_cast<int>(gm.GetUserInfo().GetTextBox().y), static_cast<int>(gm.GetUserInfo().GetTextBox().width), static_cast<int>(gm.GetUserInfo().GetTextBox().height), BLACK);

                DrawText(gm.GetUserInfo().GetName().c_str(), static_cast<int>(gm.GetUserInfo().GetTextBox().x) + 5, static_cast<int>(gm.GetUserInfo().GetTextBox().y) + 8, 40, BLACK);
                
                if (gm.GetUserInfo().GetName().length() < gm.GetUserInfo().GetMaxNameLength())
                {
                    // Draw blinking underscore char
                    //if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
                    if (gm.GetGameDurationInSeconds() % 2 == 0) {
                        DrawText("_", static_cast<int>(gm.GetUserInfo().GetTextBox().x + 8) + MeasureText(gm.GetUserInfo().GetName().c_str(), gm.GetUserInfo().GetFontSize()), static_cast<int>(gm.GetUserInfo().GetTextBox().y + 12), gm.GetUserInfo().GetFontSize(), BLACK);
                    }
                }


                EndDrawing();

                break;
            }

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

                // old Update
                if (GetGamepadButtonPressed() != -1) {

                    gm.Reset();

                }

                // Update
                // Update
                //----------------------------------------------------------------------------------



                

                // Draw

                ClearBackground(gm.GetBackgroundColour());
                DrawText("You died! :(", 50, 50, 100, WHITE);
                std::string scoreString = "Score: " + std::to_string(gm.GetScore());
                DrawText(scoreString.c_str(), 50, 200, 100, WHITE);

                DrawText("Press any button to play again!", 50, GetScreenHeight() - 100, 50, WHITE);

                DrawText(lm.GetLeaderboardData().c_str(), GetScreenWidth() - (MeasureText(lm.GetLeaderboardData().c_str(), lm.GetFontSize()) + lm.GetFontSize() * 2.0f ), GetScreenHeight() / 12, lm.GetFontSize(), BLACK);

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

void DrawTextCentered(std::string pText, int pPositionY, int pFontSize, Color pColour) {
    
    DrawText(pText.c_str(), (GetScreenWidth() / 2) - (MeasureText(pText.c_str(), pFontSize) / 2), pPositionY, pFontSize, pColour);

}