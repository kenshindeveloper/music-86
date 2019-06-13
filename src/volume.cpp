#include "../includes/volume.h"

namespace music
{
    Volume::Volume()
    {
        global = Global::NewGlobal();
        float diff_x = 290.0;

        rect_line = (Rectangle){GetScreenWidth() - diff_x, 20.0f, 200.0f, 4.0f};
        rect_cursor = (Rectangle){GetScreenWidth() - diff_x, 15.0f, 8.0f, 12.0f};
        
        ini_pos_cursor = (Vector2) {rect_cursor.x, rect_cursor.y};
        pos_volume = (Vector2) {(rect_line.x + rect_line.width) + 10.0f, rect_cursor.y};
        
        line_time = new Div{rect_line, global->color_8};
        cursor = new Div{rect_cursor, global->color_9};
        button = new Button{(Vector2) {rect_line.x - 40, 5.0f}, "sound"};

        is_push = false;

        font = LoadFont("resources/fonts/04B_03__.TTF");

        font_size = 16;
    }

    Volume::~Volume()
    {
        UnloadFont(font);
        delete line_time;
        delete cursor;
        delete button;
    }

    void Volume::EventCursor()
    {
        bool is_collision = CheckCollisionPointRec(GetMousePosition(), cursor->GetRectangle());

        if (is_collision && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) is_push = true;
        else if (is_push && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) is_push = false;

        if (is_push)
        {
            float pos_x = GetMousePosition().x;
            if (pos_x < ini_pos_cursor.x) pos_x = ini_pos_cursor.x;
            else if (pos_x > ((rect_line.x + rect_line.width) - rect_cursor.width)) pos_x = ((rect_line.x + rect_line.width) - rect_cursor.width);
            cursor->SetPosition((Vector2){pos_x, ini_pos_cursor.y});
            UpdateVolumeCursor();

            if (global->current_volume > 0 && global->is_mute) global->is_mute = false;

            global->SetVolume();
        }
        else
        {
            UpdateCursorVolume();
        }
    }

    void Volume::UpdateCursorVolume()
    {
        cursor->GetRectangle().x = ini_pos_cursor.x + ((rect_line.width - rect_cursor.width) * global->current_volume / 100);
    }

    void Volume::UpdateVolumeCursor()
    {
        global->current_volume = (100 * abs(ini_pos_cursor.x - cursor->GetRectangle().x)) / (rect_line.width - rect_cursor.width);
    }

    void Volume::EventNode()
    {      
        line_time->EventNode();
        EventCursor();

        cursor->EventNode();
        button->EventNode();
    }

    void Volume::DrawNode()
    {
        line_time->DrawNode();
        cursor->DrawNode();
        DrawTextEx(font, FormatText("%d", global->current_volume), pos_volume, font_size, 1, global->color_8);
        // DrawTextEx(font, FormatText("volume", global->current_volume), (Vector2) {ini_pos_cursor.x - 90, pos_volume.y}, font_size, 1, global->color_8);
        button->DrawNode();
    }
}