#ifndef __TIME_H__
#define __TIME_H__

#include "raylib.h"
#include "div.h"
#include "node.h"
#include "global.h"

namespace music
{
    class Time: public Node
    {
        private:
            Global* global;
            
            Div* background;
            Div* line_time;
            Div* cursor;

            Vector2 pos_line_time;
            Vector2 pos_cursor;
            Vector2 default_pos_cursor;
            Vector2 pos_info_music;
            
            float length_line;

            Font* font;

        public:
            Time();
            ~Time();

            void EventNode();
            void DrawNode();   
            void DrawInfoMusic();

    };
}

#endif //__TIME_H__