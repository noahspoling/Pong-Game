#include "raylib.h"

#include "Util/SceneManager.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/Header/Pong.hpp"

const int screenWidth = 1280;
const int screenHeight = 720;

int main()
{
    InitWindow(screenWidth, screenHeight, "Game Title");
    InitAudioDevice();
    SetTargetFPS(30);

    Pong *pong = new Pong();
    SceneManager::LoadScene(pong);



    while (!WindowShouldClose())
    {
        #ifdef NDEBUG
            TraceLog(LOG_INFO, "New Frame");
        #endif

        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        if(SceneManager::SceneLoaded())
        {
            SceneManager::Update();
        }
        else
        {
            #ifdef DEBUG
                TraceLog(LOG_INFO, "Scene not loaded");
            #endif
            SceneManager::LoadScene(pong);
        }

        //DrawText("Congrats! You created your first window!", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}