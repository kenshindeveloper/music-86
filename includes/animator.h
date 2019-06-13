#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include <map>
#include <vector>
#include "raylib.h"
#include "animation.h"

namespace music {
    class Animator {
        private:
            std::map<std::string, Animation*> animations;

        public:
            Animator();
            ~Animator();
            void add(std::string, std::vector<Rectangle>);
            void play(std::string, const Texture2D&, const Vector2&);
            void flipH(Image&);
    };
}

#endif //ANIMATOR_HPP