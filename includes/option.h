#ifndef OPTION_H
#define OPTION_H

#include "node.h"
#include "raylib.h"
#include "string"
#include "global.h"

namespace music
{
    class Option: public Node {
        private:
            Global* global;
            std::string text;
            std::string text_incom;
            Rectangle rect;
            Rectangle rect_num;
            Color color_default;
            Color color_select;   
            Color font_color_default;
            Color font_color_select;
            
            Font font_text;
            
            int size_text;
            int index;
            int seconds_cont;
            int diff;

            float value;
            float velocity;

            Vector2 pos_font;
            Vector2 pos_default_font;

            bool visible;

        public:
            Option(Rectangle, std::string, int, int);
            ~Option();
            void EventNode();
            void DrawNode();
    
            std::string GetText() { return text; }
            Rectangle& GetRectangle() { return rect; }
            int GetIndex() { return index; }
            void SetVisible(bool value) { visible = value; }
            bool GetVisible() { return visible; }
        
        private:
            void EventString();
            void DrawString();
    };
}

#endif //OPTION_H