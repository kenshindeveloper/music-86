#ifndef __BAR_H__
#define __BAR_H__

#include "raylib.h"
#include "node.h"
#include "global.h"

namespace music
{
    class Bar: public Node
    {
        private:
            Global* global;
            Rectangle rect;

            int limite_up;
            int limite_down;
            int mov_y;
            int velocity_y;
            int diff;

            bool is_mov_up;

            Color col_default;
            Color col_mute;

        public:
            Bar(Rectangle, int);
            ~Bar();

            void EventNode();
            void DrawNode();

        private:
            void MovBar();
    };
}

#endif //__BAR_H__
