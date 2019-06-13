#include "../includes/music_fill.h"
#include "../includes/div.h"
#include "../includes/option.h"

namespace music
{
    MusicFill::MusicFill(Rectangle rect)
    {
        global = Global::NewGlobal();
        this->rect = (Rectangle) {rect.x-5, rect.y+5, rect.width, rect.height};
        color = (Color) {global->color_4.r, global->color_4.g, global->color_4.b, 240};
        background = new Div{this->rect, color};

        font = LoadFont("resources/fonts/04B_03__.TTF");
        pos_font = (Vector2) {this->rect.x + 10, this->rect.y +10};
        pos_default_font = pos_font;
        font_size = 16;
        diff = 6;
        info = "hello, word!";
        velocity = 3.0f;

        current_index_music = -1;
    }

    MusicFill::~MusicFill()
    {
        delete background;
        background = nullptr;
        UnloadFont(font);
    }

    void MusicFill::EventString()
    {
        if ((int) global->list_option.size() > 0)
        {
            if (current_index_music != global->index_selected_option)
            {
                info = global->list_option[global->index_selected_option]->GetText();
                current_index_music = global->index_selected_option;
                pos_font.x = pos_default_font.x;
            }

            if (seconds_cont > (global->fps/9))
            {   
                if (pos_font.x - (((info.length()-2) * (font_size - diff))) > (rect.x + rect.width)) pos_font.x = pos_default_font.x;
                else pos_font.x += velocity;
                seconds_cont = 0;
            }
            seconds_cont += 1;
        }
    }

    void MusicFill::EventNode()
    {
        background->EventNode();
        EventString();
    }

    void MusicFill::DrawString()
    {
        if ((int) global->list_option.size() > 0)
        {
            float pos = pos_font.x;
            info = global->list_option[global->index_selected_option]->GetText();
            for (int i=info.length(); i >= 0; i--)
            {
                if (pos > (rect.x) && pos+(font_size-diff) < (rect.x + rect.width))
                {
                    DrawTextEx(font, FormatText("%c", info[i]), (Vector2){pos, pos_font.y}, font_size, 1, global->color_8);
                }
                pos -= (font_size - diff);
            }
        }
    }

    void MusicFill::DrawNode()
    {
        background->DrawNode();
        DrawString();
    }
}