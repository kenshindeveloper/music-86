#ifndef __HANDLE_H__
#define __HANDLE_H__

#include "raylib.h"
#include "global.h"
#include "node.h"

namespace music
{
    class Handle: public Node
    {
        private:
            Global* global;
            Node* canvas;
            Node* init;
            Node* close;

        public:
            Handle();
            ~Handle();

            void EventNode();
            void DrawNode();           
    };
}

#endif //__HANDLE_H__