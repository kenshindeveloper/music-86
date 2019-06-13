#include <stdlib.h>
#include "raylib.h"
#include "includes/handle.h"
#include "includes/global.h"

int main()
{
    music::Global* global = music::Global::NewGlobal();

    // SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(global->screen_width, global->screen_height, "music-86");
    InitAudioDevice();
    SetExitKey(-1);

    Image image = LoadImage("resources/sprites/icon.png");
    ImageResizeNN(&image, 16, 16);
    SetWindowIcon(image);

    music::Handle* handle = new music::Handle{};
    Shader shader = LoadShader(NULL, "resources/shaders/base.fs");

    int i_time = GetShaderLocation(shader, "u_time");

    float time_fps[1] = { 0.0f };
    int cont_fps = 0;

    bool fps_up = true;

    SetTargetFPS(global->fps);
    while (global->is_run)
    {
        //mientras no se implementa la validacion de salida final.
        // if (IsKeyPressed(KEY_F9)) global->is_run = false;

        global->UpdateMusic();
        handle->EventNode();
        global->screen_width = GetScreenWidth();
        global->screen_height = GetScreenHeight();

        if (cont_fps > global->fps)
        {
            if (fps_up) 
            {
                time_fps[0] += 0.1f;
                if (time_fps[0] > 1.0f) 
                {
                    fps_up = false;
                    time_fps[0] = 1.0f;
                }
            }
            else
            {
                time_fps[0] -= 0.1f;
                if (time_fps[0] < 0.0f) 
                {
                    fps_up = true;
                    time_fps[0] = 0.0f;
                }
            }

            SetShaderValue(shader, i_time, time_fps, 1);
            cont_fps = 0;
        }
        else
        {
            cont_fps += 1; 
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginShaderMode(shader);
                DrawRectangleRec((Rectangle) {0.0f, 0.0f, (float) global->screen_width, (float) global->screen_height}, global->color_5);
                handle->DrawNode();
            EndShaderMode();
        EndDrawing();
    }

    UnloadImage(image);
    UnloadShader(shader);
    delete handle;
    music::Global::FreeGlobal();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
