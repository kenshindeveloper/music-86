#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include "raylib.h"
#include "node.h"
#include "global.h"

namespace music 
{
    class Canvas:public Node {
        private:
            Global* global;
            std::vector<Node*> rects;

        public:
            Canvas();
            ~Canvas();
            void EventNode();
            void DrawNode();
    };
}

#endif //CANVAS_H