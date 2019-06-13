#include "../includes/option.h"

namespace music
{
    Option::Option(Rectangle rect, std::string text, int size_text, int index)
    {
        // this->rect = rect;
        value = 50.0f;
        rect_num = (Rectangle) {rect.x, rect.y, value, rect.height};
        this->rect = (Rectangle) {rect.x + value, rect.y, rect.width-value, rect.height};
        this->text = text;
        if (text.length() > 50)
        {
            text_incom = text.substr(0, 50);
            text_incom += "...";
        }
        else
        {
            text_incom = text;
        }

        this->size_text = size_text;
        this->index = index;
        
        global = Global::NewGlobal();

        color_default = global->color_4;
        color_select = global->color_3;
        font_color_default = global->color_1; //5
        font_color_select = global->color_8; //9

        pos_font = (Vector2) {rect.x + 5, rect.y + 2};
        pos_default_font = pos_font;
        font_text = LoadFont("resources/fonts/04B_03__.TTF");
        seconds_cont = 0;
        visible = false;
        diff = 6;

        velocity = 4.0f;
    }

    Option::~Option()
    {
        UnloadFont(font_text);
    }

    void Option::EventString()
    {
        if ((int) global->list_option.size() > 0)
        {
            if (index != global->index_selected_option && pos_font.x != pos_default_font.x)
            {
                pos_font.x = pos_default_font.x;
                seconds_cont = 0;
            }
            else
            {
                if (seconds_cont > (global->fps/9))
                {   
                    if (pos_font.x - (((text.length()-2) * (size_text - diff))) > (rect.x + rect.width)) pos_font.x = pos_default_font.x;
                    else pos_font.x += velocity;
                    seconds_cont = 0;
                }
                seconds_cont += 1;
            }
        }
    }

    void Option::EventNode()
    {
        if (global->screen_width != GetScreenWidth())
        {
            rect.x = (rect.x * GetScreenWidth()) / global->screen_width;
            rect.width = (rect.width * GetScreenWidth()) / global->screen_width;
        }

        if (global->screen_height != GetScreenHeight())
        {
            rect.y = (rect.y * GetScreenHeight()) / global->screen_height;
            rect.height = (rect.height * GetScreenHeight()) / global->screen_height;
        }

        EventString();
    }

    void Option::DrawString()
    {
        if ((int) global->list_option.size() > 0)
        {
            float pos = pos_font.x;
            for (int i=text.length(); i >= 0; i--)
            {
                if (pos > (rect.x) && pos+(size_text-diff) < (rect.x + rect.width))
                {
                    // DrawTextEx(font_text, FormatText("%c", text[i]), (Vector2){pos, rect.y + 2}, size_text, 1, font_color_select);
                    DrawTextEx(font_text, FormatText("%c", text[i]), (Vector2){pos, rect.y + 2}, size_text, 2, global->color_5);
                }
                pos -= (size_text - diff);
            }
        }
    }

    void Option::DrawNode()
    {
        if (visible)
        {
            
            if (global->current_index == index)
            {
                // DrawRectangleRec(rect, global->color_8); //3 -8
                // DrawTextEx(font_text, text_incom.c_str(), (Vector2) {rect.x + 5, rect.y + 2}, size_text, 1, global->color_5); 
                DrawRectangleRec(rect, color_select); //3 -8
                DrawTextEx(font_text, text_incom.c_str(), (Vector2) {rect.x + 5, rect.y + 2}, size_text, 1, font_color_select); 
            }
            else if (global->index_selected_option == index) 
            {
                // DrawRectangleRec(rect, color_select);
                DrawRectangleRec(rect, global->color_8);
                if (global->is_playing) DrawString();
                // else DrawTextEx(font_text, text_incom.c_str(), (Vector2) {rect.x + 5, rect.y + 2}, size_text, 1, font_color_select);
                else DrawTextEx(font_text, text_incom.c_str(), (Vector2) {rect.x + 5, rect.y + 2}, size_text, 1, global->color_5);
            }
            else
            {   
                DrawRectangleRec(rect, color_default);
                DrawTextEx(font_text, text_incom.c_str(), (Vector2) {rect.x + 5, rect.y + 2}, size_text, 1, font_color_default);
            }
            
            DrawRectangleRec((Rectangle) {rect.x-value, rect.y, value, rect.height}, global->color_5);
            
            if (global->current_index == index || global->index_selected_option == index)
                DrawTextEx(font_text, FormatText("%d", index+1), (Vector2) {(rect.x-value)+5, rect.y + 2}, size_text, 1, global->color_8);
            else 
                DrawTextEx(font_text, FormatText("%d", index+1), (Vector2) {(rect.x-value)+5, rect.y + 2}, size_text, 1, color_default);

        }
    }
}