#ifndef __INIT_H__
#define __INIT_H__

#include "raylib.h"
#include "global.h"
#include "node.h"
#include "div.h"
#include "animator.h"

namespace music
{
    class Init: public Node
    {
        private:
            Global* global;
            Div* background;

            Font font;

            Animator* animator;
            Image image;
            Texture texture;

            Vector2 pos_img;
            Vector2 pos_font;

            float pos_x;
            float pos_y;

        public:
            Init();
            ~Init();

            void EventNode();
            void DrawNode();
    };
}

#endif //__INIT_H__