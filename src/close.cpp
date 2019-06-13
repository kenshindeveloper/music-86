#include "../includes/close.h"
#include "../includes/div.h"

namespace music
{
    Close::Close()
    {
        global = Global::NewGlobal();
        background = new Div{(Rectangle) {0.0f, 0.0f, (float) global->screen_width, (float) global->screen_height}, global->color_5};

        font = LoadFont("resources/fonts/04B_03__.TTF");

        pos_label = (Vector2) { 90.0f, 150.0f };
        pos_yes = (Vector2) {150.0f, pos_label.y + 50.0f};
        pos_no = (Vector2) {460.0f, pos_label.y + 50.0f};
    }

    Close::~Close()
    {
        UnloadFont(font);
        delete background;
    }

    void Close::KeyboardEvent()
    {
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) is_yes = !is_yes;

        if (IsKeyPressed(KEY_ENTER))
        {
            if (is_yes) global->is_run = false;
            else global->level = 1;
        }
    }

    void Close::EventNode()
    {
        KeyboardEvent();
        background->EventNode();
    }

    void Close::DrawNode()
    {
        background->DrawNode();
        DrawTextEx(font, "Do you want to close music player?", pos_label, 24, 1, global->color_9);
        
        if (is_yes) 
        {
            DrawTextEx(font, "yes", pos_yes, 24, 1, global->color_8);
            DrawTextEx(font, "no", pos_no, 24, 1, global->color_3);
        }
        else 
        {
            DrawTextEx(font, "no", pos_no, 24, 1, global->color_8);
            DrawTextEx(font, "yes", pos_yes, 24, 1, global->color_3);
        }

        DrawTextEx(font, "Develop for Kenshin Urashima", (Vector2) {(GetScreenWidth()/2.0f) - 125.0f, (GetScreenHeight()/2.0f) + 210.0f}, 16, 1, global->color_8);
    }
}