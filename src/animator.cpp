#include "../includes/animator.h"

namespace music {
    Animator::Animator() {

    }

    Animator::~Animator() {
        std::map<std::string, Animation*>::iterator itera = animations.begin();

        while (itera != animations.end()) {
            delete(itera->second);
            itera++;
        }
        animations.clear();
    }

    void Animator::add(std::string name, std::vector<Rectangle> vec) {
        animations[name] = new Animation{name, vec};
    }

    void Animator::play(std::string name, const Texture2D& texture, const Vector2& position) {
        animations[name]->play(texture, position);
    }

    void Animator::flipH(Image& image) {
        ImageFlipHorizontal(&image);
    }
}