#ifndef __MOVE_H__
#define __MOVE_H__

#include "raylib.h"
#include "global.h"
#include "node.h"

namespace music 
{
    class Move: public Node
    {
        private:
            Global* global;
            
            Node* background;
            Node* btn_up;
            Node* btn_down;

            Rectangle rect;
            Rectangle rect_up;
            Rectangle rect_down;

        public:
            Move(Rectangle);
            ~Move();

            void EventNode();
            void DrawNode();
        
        private:
            void EventButton();
    };
}

#endif //__MOVE_H__