#ifndef __VOLUME_H__
#define __VOLUME_H__

#include "raylib.h"
#include "node.h"
#include "global.h"
#include "div.h"
#include "button.h"

namespace music
{
    class Volume: public Node
    {
        private:
            Global* global;
            Button* button;
            Div* line_time;
            Div* cursor;
            
            bool is_push;

            Rectangle rect_line;
            Rectangle rect_cursor;

            Vector2 ini_pos_cursor;
            Vector2 pos_volume;

            Font font;

            int font_size;
        
        public:
            Volume();
            ~Volume();

            void EventNode();
            void DrawNode();        

        private:
            void EventCursor();
            void UpdateVolumeCursor();
            void UpdateCursorVolume();
    };
}

#endif //__VOLUME_H__