#include "../includes/button.h"

namespace music
{
    Button::Button(Vector2 position, std::string type)
    {
        global = Global::NewGlobal();
        is_collision = false;
        is_pressed = false;
        float diff = 32.0f;

        image = LoadImage("resources/sprites/icons.png");
        ImageResizeNN(&image, (int)global->size_img_icons.x * diff, (int)global->size_img_icons.y * diff);
        texture = LoadTextureFromImage(image);
        this->type = type;
        
        map_rect = std::map<std::string, Rectangle>();
        
        if (type == "update")
        {
            map_rect["update"] = (Rectangle) {diff * 1, diff * 8, diff, diff};
            map_rect["update_select"] = (Rectangle) {diff * 2, diff * 8, diff, diff};
        }
        else if (type == "sound")
        {
            map_rect["sound_0"] = (Rectangle) {diff * 3, diff * 9, diff, diff};
            map_rect["sound_1"] = (Rectangle) {diff * 2, diff * 9, diff, diff};
            map_rect["sound_2"] = (Rectangle) {diff * 1, diff * 9, diff, diff};
            map_rect["sound_3"] = (Rectangle) {diff * 0, diff * 9, diff, diff};
            map_rect["sound_4"] = (Rectangle) {diff * 3, diff * 8, diff, diff};
        }

        rect_collision = (Rectangle) {position.x, position.y, diff, diff};
        this->position = position;
    }

    Button::~Button()
    {
        UnloadImage(image);
    }

    void Button::UpdateEvent()
    {
        is_collision = CheckCollisionPointRec(GetMousePosition(), rect_collision);

        if (is_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !global->is_playing)
        {
            is_pressed = true;
            global->UpdateListMusic();
            global->SetRectOption();
        }
        else
        {
            is_pressed = false;
        }
    }

    void Button::SoundEvent()
    {
         is_collision = CheckCollisionPointRec(GetMousePosition(), rect_collision);

        if ((is_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_M))
        {
            if (!global->is_mute)
            {
                global->is_mute = true;
                global->save_volume = global->current_volume;
                global->current_volume = 0;
            }
            else
            {
               global->is_mute = false;
               global->current_volume = global->save_volume; 
            }
            global->SetVolume();
        }
        
    }

    void Button::EventNode()
    {
        if (type == "update") UpdateEvent();
        else if (type == "sound") SoundEvent();
    }

    void Button::UpdateDraw()
    {
        if (!is_pressed) DrawTextureRec(texture, map_rect["update"], position, WHITE);
        else DrawTextureRec(texture, map_rect["update_select"], position, WHITE);
    }

    void Button::SoundDraw()
    {
        // if (!global->is_mute) DrawTextureRec(texture, map_rect["sound"], position, WHITE);
        // else DrawTextureRec(texture, map_rect["sound_select"], position, WHITE);

        if (global->is_mute)
        {
            DrawTextureRec(texture, map_rect["sound_0"], position, WHITE);
        }
        else 
        {
            if (global->current_volume == 0) DrawTextureRec(texture, map_rect["sound_0"], position, WHITE);
            else if (global->current_volume > 0 && global->current_volume <= 20) DrawTextureRec(texture, map_rect["sound_1"], position, WHITE);
            else if (global->current_volume > 20 && global->current_volume <= 50) DrawTextureRec(texture, map_rect["sound_2"], position, WHITE);
            else if (global->current_volume > 50 && global->current_volume <= 75) DrawTextureRec(texture, map_rect["sound_3"], position, WHITE);
            else if (global->current_volume > 75) DrawTextureRec(texture, map_rect["sound_4"], position, WHITE);
        }
    
    }

    void Button::DrawNode()
    {
        if (type == "update") UpdateDraw();
        else if (type == "sound") SoundDraw();
    }
}