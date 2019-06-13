#ifndef ICON_H
#define ICON_H

#include <map>
#include <string>
#include "raylib.h"
#include "node.h"
#include "animator.h"
#include "global.h"

namespace music
{
    class Icon: public Node
    {
        private:
            Image image;
            Texture2D texture;
            std::map<std::string, Rectangle> map_rect;
            std::string type;
            Rectangle rect;
            Vector2 position;
            std::string type_name;
            Rectangle rect_collision;
            Animator* animator;
            Global* global;

            bool is_collision;
            int index_play;

        public:
            Icon(std::string, Vector2);
            ~Icon();
            void EventNode();
            void DrawNode();

        private:
            void IsPlayButton();
            void IsLeftButton();
            void IsRightButton();
            void IsRepeatButton();
            void IsShuffleButton();

            void ChangeSize();
            void DrawRepeat();
            void DrawShuffle();
    };
}

#endif //ICON_H