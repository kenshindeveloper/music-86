#include "../includes/div.h"
#include "../includes/global.h"
#include "raylib.h"

namespace music
{
    Div::Div(Rectangle rect, Color color)
    {
        this->rect = rect;
        this->color = color;
    }

    Div::~Div()
    {
        
    }

    void Div::EventNode()
    {
        Global* global = Global::NewGlobal();
        
        if (global->screen_width != GetScreenWidth()) 
        {
            rect.width = (rect.width * GetScreenWidth()) / global->screen_width;
            rect.x = (rect.x * GetScreenWidth()) / global->screen_width;
        }

        if (global->screen_height != GetScreenHeight())
        {
            rect.height = (rect.height * GetScreenHeight()) / global->screen_height;
            rect.y = (rect.y * GetScreenHeight()) / global->screen_height;
        }
    }

    void Div::DrawNode()
    {
        DrawRectangleRec(rect, color);
    }

    void Div::SetPosition(Vector2 position)
    {
        rect.x = position.x;
        rect.y = position.y;
    }
}