#include "../includes/box.h"
#include "../includes/option.h"
#include "../includes/icon.h"

namespace music
{
    Box::Box()
    {
        global = Global::NewGlobal();
        float default_height = GetScreenHeight() - 108.0f;
        float default_width = (GetScreenWidth() / 2) - 60.0f;
        // color_4 // 8 //9
        background_div = new Div{(Rectangle) { 10.0f , default_height, (float) (GetScreenWidth()-20), 100.0f }, global->color_9};
        selected_position = (Vector2) {10.0f + 10, (float)(30 + (GetScreenHeight() - 85.0f))};
        
        vect_icons = std::vector<Node*>();
        vect_icons.push_back(new Icon{"shuffle", (Vector2){5.0f, (float) (selected_position.y-64) }});
        vect_icons.push_back(new Div{(Rectangle){135.0f, (selected_position.y - 53.0f), 4.0f, 100.0f}, global->color_5});
        vect_icons.push_back(new Icon{"left", (Vector2){default_width - 100.0f, (float) (selected_position.y-64) }});
        vect_icons.push_back(new Icon{"play", (Vector2){default_width, (float) (selected_position.y-64) }});
        vect_icons.push_back(new Icon{"right", (Vector2){default_width + 100.0f, (float) (selected_position.y-64) }});
        vect_icons.push_back(new Div{(Rectangle){default_width + 250.0f, (selected_position.y - 53.0f), 4.0f, 100.0f}, global->color_5});
        vect_icons.push_back(new Icon{"repeat", (Vector2){(float) GetScreenWidth() - 130, (float) (selected_position.y-64) }});

    }

    Box::~Box()
    {
        delete background_div;

        for (Node*& icon : vect_icons) delete icon;
        vect_icons.clear();
    }

    void Box::EventNode()
    {
        background_div->EventNode();
        
        if (global->screen_width != GetScreenWidth())
        {
            selected_position.x = (selected_position.x * GetScreenWidth()) / global->screen_width;
        }

        if (global->screen_height != GetScreenHeight())
        {
            selected_position.y = (selected_position.y * GetScreenHeight()) / global->screen_height;
        }

        for (Node*& icon : vect_icons) icon->EventNode();
    }

    void Box::DrawNode()
    {
        background_div->DrawNode();
        for (Node*& icon : vect_icons) icon->DrawNode();
    }
}