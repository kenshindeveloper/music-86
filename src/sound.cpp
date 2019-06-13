#include "../includes/sound.h"

namespace music
{
    SoundC::SoundC(Vector2 position)
    {
        global = Global::NewGlobal();
        this->position = position;

        line = new Div{(Rectangle) {position.x, position.y, 220, 5}, global->color_0};
        dial = new Div{(Rectangle) {position.x, position.y - 4, 8, 15}, RED};
    }

    SoundC::~SoundC()
    {
        delete line;
        delete dial;
    }

    void SoundC::EventNode()
    {
        line->EventNode();
        dial->EventNode();
    }

    void SoundC::DrawNode()
    {
        line->DrawNode();
        dial->DrawNode();
    }
}