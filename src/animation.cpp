#include "../includes/animation.h"
#include "../includes/global.h"

namespace music {
    Animation::Animation(std::string name, std::vector<Rectangle> vec) {
        this->name = name;
        this->vec = vec;
        currentFrame = 0;
        cont = 0;

        global = Global::NewGlobal();
    }

    void Animation::play(const Texture2D& texture, const Vector2& position) {
        if (cont > (global->fps/6)) {
            currentFrame += 1;
            if (currentFrame >= (int)vec.size()) currentFrame = 0;
            cont = 0;
        }

        DrawTextureRec(texture, vec[currentFrame], position, WHITE);
        cont += 1;
    }
}