#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "raylib.h"
#include "global.h"
#include "div.h"
#include "grid.h"

namespace music
{
    class Player: public Node
    {
        private:
            Global* global;
            Div* background_div;
            Vector2 padding;
            Grid* grid;

            Node* move;

        public:
            Player();
            ~Player();
            void EventNode();
            void DrawNode();
    };
}

#endif //PLAYER_H