#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <string>
#include "raylib.h"
#include "global.h"

namespace music {
    class Animation {
        private: 
            std::string  name;
            int currentFrame;
            int cont;
            
            std::vector<Rectangle> vec;

            Global* global;

        public:
            Animation(std::string, std::vector<Rectangle>);
            void play(const Texture2D&, const Vector2&);
    };
}

#endif //ANIMATION_HPP