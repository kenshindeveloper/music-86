#ifndef DIV_H
#define DIV_H

#include "raylib.h"
#include "node.h"

namespace music
{
    class Div: public Node
    {
        private:
            Rectangle rect;
            Color color;
        
        public:
            Div(Rectangle, Color);
            ~Div();
            void EventNode();
            void DrawNode();
            Rectangle& GetRectangle() { return rect; }

            void SetPosition(Vector2);
    };
}

#endif //DIV_H