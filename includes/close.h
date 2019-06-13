#ifndef __CLOSE_H__
#define __CLOSE_H__

#include "raylib.h"
#include "global.h"
#include "node.h"

namespace music
{
    class Close: public Node {
        private:
            Global* global;
            Node* background;

            Font font;

            bool is_yes = false;

            Vector2 pos_label;
            Vector2 pos_yes;
            Vector2 pos_no;

        public:
            Close();
            ~Close();

            void EventNode();
            void DrawNode();  
            void KeyboardEvent();    
    };
}

#endif //__CLOSE_H__