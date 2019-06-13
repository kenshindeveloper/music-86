#ifndef __TAG_H__
#define __TAG_H__

#include "raylib.h"
#include "global.h"
#include "node.h"

namespace music
{
    class Tag: public Node
    {
        private:
            Global* global;

            Rectangle rect;
            Rectangle rect_img;

            Vector2 position;
            Vector2 position_img;
            
            int index;
            bool is_collision;
            Color color_default;
            Color color_selected;

            Image image;
            Texture texture;
        
        public:
            Tag(Vector2, int);
            ~Tag();

            void EventNode();
            void DrawNode();
    };
}

#endif //__TAG_H__