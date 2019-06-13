#include "../includes/bar.h"

namespace music
{
    Bar::Bar(Rectangle rect, int diff)
    {
        global = Global::NewGlobal();
        this->rect = rect;

        limite_up = rect.y;
        limite_down = (rect.y + rect.height) - diff;
        mov_y = rect.y+rect.height;
        velocity_y = 2;
        this->diff = diff;

        is_mov_up = false;

        col_default = global->color_9;
        col_mute = global->color_8;
    }

    Bar::~Bar()
    {
        
    }

    void Bar::MovBar()
    {
        if (!is_mov_up && ((rect.y+mov_y) < limite_down))
        {
             mov_y += velocity_y;
        }
        else if (!is_mov_up && ((rect.y+mov_y) >= limite_down))
        {
            is_mov_up = true;
            limite_up = GetRandomValue(limite_down, rect.y);
        }

        if (is_mov_up && ((rect.y+mov_y) > limite_up))
        {
            mov_y -= velocity_y;
        }
        else if (is_mov_up && ((rect.y+mov_y) <= limite_up))
        {
            is_mov_up = false;
        }

    }

    void Bar::EventNode()
    {
        if (global->is_playing)
        {
            MovBar();
        }
        else if(!global->is_playing && ((rect.y+mov_y) < (rect.y+rect.height)))
        {
            mov_y += velocity_y;
        }
    }

    void Bar::DrawNode()
    {
        if (!global->is_mute) DrawRectangleRec((Rectangle) {rect.x, rect.y + mov_y, rect.width, rect.height - mov_y}, col_default);
        else DrawRectangleRec((Rectangle) {rect.x, rect.y + mov_y, rect.width, rect.height - mov_y}, col_mute);
    }
}