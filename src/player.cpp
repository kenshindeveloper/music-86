#include <string>
#include "../includes/player.h"
#include "../includes/icon.h"
#include "../includes/option.h"
#include "../includes/move.h"

namespace music
{
    Player::Player()
    { 
        global = Global::NewGlobal();
        float pos_x = 10.0f;
        float pos_y = (float) global->pos_y_player;

        float option_height = 20.0f;
        int default_width = (float) GetScreenWidth() - 20;
        int default_height = option_height * (global->max_num_opt+1);

        background_div = new Div{(Rectangle) {pos_x, pos_y, (float)default_width, (float)default_height}, global->color_3};
        padding = (Vector2) { 10.0f + background_div->GetRectangle().x, 10.0f + background_div->GetRectangle().y };
        grid = new Grid{(Rectangle) {pos_x, pos_y, (float)default_width, (float)default_height}};

        move = new Move{(Rectangle) {(pos_x + default_width) - 15.0f, pos_y, 15.0f, (float) default_height}};

        global->UpdateListMusic();
        global->SetRectOption();
    }

    Player::~Player()
    {
        delete background_div;
        delete grid;
        delete move;
    }

    void Player::EventNode()
    {
        switch (global->index_tag)
        {
            case 0:
                for (Option*& opt : global->list_option) opt->EventNode();
                background_div->EventNode();
                move->EventNode();
                break;

            case 1:
                grid->EventNode();
                break;
        }
    }

    void Player::DrawNode() 
    {
        switch (global->index_tag)
        {
            case 0:
                background_div->DrawNode();

                for (Option*& opt : global->list_option) 
                {
                    if (opt->GetVisible()) opt->DrawNode();
                }

                move->DrawNode();
                break;

            case 1:
                grid->DrawNode();
                break;
        }
    }
}