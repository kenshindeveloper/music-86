#ifndef MUSIC_FILL_H
#define MUSIC_FILL_H

#include <string>
#include "raylib.h"
#include "global.h"
#include "node.h"

namespace music
{
    class MusicFill: public Node
    {
        private:
            Global* global;
            Node* background;

            Rectangle rect;
            Color color;
            Font font;
            Vector2 pos_font;
            Vector2 pos_default_font;

            std::string info;
            
            int font_size;
            int seconds_cont;
            int current_index_music;
            int diff;

            float velocity;

        public:
            MusicFill(Rectangle);
            ~MusicFill();
            void EventNode();
            void DrawNode();

        private:
            void EventString();
            void DrawString();
    };
}


#endif //MUSIC_FILL_H