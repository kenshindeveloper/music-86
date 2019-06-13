#include "../includes/move.h"
#include "../includes/div.h"

namespace music
{
    Move::Move(Rectangle rect)
    {
        global = Global::NewGlobal();
        this->rect = rect;

        background = new Div{rect, global->color_3};
    
        rect_up = (Rectangle) {rect.x, rect.y, rect.width, 30.0f};
        rect_down = (Rectangle) {rect.x, (rect.y+rect.height)-25.0f, rect.width, 30.0f};

        btn_up = new Div{rect_up, global->color_8};
        btn_down = new Div{rect_down, global->color_8};
    }

    Move::~Move()
    {
        delete background;
        delete btn_up;
        delete btn_down;
    }

    void Move::EventButton()
    {
        bool is_coll_up = CheckCollisionPointRec(GetMousePosition(), rect_up);
        bool is_coll_down = CheckCollisionPointRec(GetMousePosition(), rect_down);

        if (is_coll_up && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            global->PrevMusic();
        }
        else if (is_coll_down && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            global->ProxMusic();
        }
    }

    void Move::EventNode()
    {
        EventButton();
        background->EventNode();
        btn_up->EventNode();
        btn_down->EventNode();
    }

    void Move::DrawNode()
    {
        background->DrawNode();
        btn_up->DrawNode();
        btn_down->DrawNode();
    }
}