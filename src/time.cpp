#include "../includes/time.h"

namespace music
{
    bool operator!= (Vector2& obj_0, Vector2& obj_1)
    {
        return (obj_0.x == obj_1.x && obj_0.y == obj_1.y)?(true):(false);
    }

    Time::Time()
    {
        global = Global::NewGlobal();
        
        int default_height = (float)GetScreenHeight() - 125;
        length_line = 500.0f;
        
        pos_line_time = (Vector2) {60.0f, (float)(default_height - 3)};
        pos_cursor = (Vector2) {60.0f, (float)(default_height - 8)};
        default_pos_cursor = pos_cursor;
        pos_info_music = (Vector2) {default_pos_cursor.x + length_line + 18, default_pos_cursor.y};

        line_time = new Div{(Rectangle) { pos_line_time.x, pos_line_time.y, length_line, 5.0f }, global->color_8};
        cursor = new Div{(Rectangle) {pos_cursor.x, pos_cursor.y, 8.0f, 15.0f }, global->color_9};

        background = new Div{(Rectangle) {10.0f, default_height - 10.0f, (float) (GetScreenWidth()-20), 20.0f}, global->color_4};

        font = new Font{};
        (*font) = LoadFont("resources/fonts/04B_03__.TTF");
    }

    Time::~Time()
    {
        delete line_time;
        delete cursor;
        delete background;

        UnloadFont(*font);
        delete font;
        font = nullptr;
    }

    void Time::EventNode()
    {
        if (global->screen_width != GetScreenWidth()) 
        {
            default_pos_cursor.x = (default_pos_cursor.x * GetScreenWidth()) / global->screen_width;
            pos_info_music.x = (pos_info_music.x * GetScreenWidth()) / global->screen_width;
        }

        if (global->screen_height != GetScreenHeight()) 
        {
            default_pos_cursor.y = (default_pos_cursor.y * GetScreenHeight()) / global->screen_height;
            pos_info_music.y = (pos_info_music.y * GetScreenHeight()) / global->screen_height;
        }

        // if (global->is_playing && (cursor->GetRectangle().x + 10) < (pos_line_time.x + length_line))
        if (global->is_playing && (global->GetMusicTime()/global->GetMusicTimeLen() < 0.99f))
        {
            global->line_time = (global->GetMusicTime()/global->GetMusicTimeLen())*(length_line - 8);
            pos_cursor.x = (global->line_time) + default_pos_cursor.x;
            cursor->SetPosition(pos_cursor);
            
		} 
        // else if (global->is_playing && (cursor->GetRectangle().x + 10) >= (pos_line_time.x + length_line))
        else if (global->is_playing && (global->GetMusicTime()/global->GetMusicTimeLen() >= 0.99f))
        {
            global->flag_prox = true;
            cursor->SetPosition(default_pos_cursor);
        }

        background->EventNode();
        line_time->EventNode();
        cursor->EventNode();
    }

    void Time::DrawInfoMusic()
    {
        int t = (int) (global->GetMusicTimeLen() - global->GetMusicTime());
        int minute = 0;
        if (t >= 100) minute = (t / 100);
        int second = (t % 100);
        DrawTextEx(*font, FormatText("%d:%s%d", minute, ((second<10)?("0"):("")), second), pos_info_music, 18, 1, global->color_8);
    }

    void Time::DrawNode()
    {
        background->DrawNode();
        line_time->DrawNode();
        cursor->DrawNode();
        
        DrawTextEx(*font, "time", (Vector2) {14.0f, pos_info_music.y}, 18, 1, global->color_8);

        DrawInfoMusic();
    }
}
