#ifndef __SOUNDC_H__
#define __SOUNDC_H__

#include "raylib.h"
#include "node.h"
#include "div.h"
#include "global.h"

namespace music
{
    class SoundC: public Node
    {
        private:
            Global* global;
            Div* line;
            Div* dial;
            
            Vector2 position;
            
        public:
            SoundC(Vector2);
            ~SoundC();
            void EventNode();
            void DrawNode();
    };
}

#endif //__SOUNDC_H__