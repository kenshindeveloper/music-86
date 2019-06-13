#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <map>
#include "string"
#include "raylib.h"
#include "node.h"
#include "global.h"

namespace music
{
    class Button: public Node
    {
        private:
            Global* global;
            bool is_collision;
            bool is_pressed;
            std::string type;

            Vector2 position;

            Image image;
            Texture texture;
            std::map<std::string, Rectangle> map_rect;

            Rectangle rect_collision;

        public:
            Button(Vector2, std::string);
            ~Button();

            void EventNode();
            void DrawNode();

        private:
            void UpdateEvent();
            void UpdateDraw();

            void SoundEvent();
            void SoundDraw();
    };
}

#endif //__BUTTON_H_