#ifndef BOX_H
#define BOX_H

#include <vector>
#include "raylib.h"
#include "node.h"
#include "div.h"
#include "global.h"
#include "string"

namespace music
{
    class Box: public Node {
        private:
            Global* global;
            Div* background_div;
            
            std::string selected_option;
            int selected_size;
            Vector2 selected_position;
            std::string selected_msg;

            std::vector<Node*> vect_icons;

        public:
            Box();
            ~Box();

            void EventNode();
            void DrawNode();
    };
}

#endif //BOX_H