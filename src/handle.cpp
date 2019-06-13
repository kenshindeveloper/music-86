#include "../includes/handle.h"
#include "../includes/canvas.h"
#include "../includes/init.h"
#include "../includes/close.h"

namespace music
{
    Handle::Handle()
    {
        global = Global::NewGlobal();
        canvas = new Canvas{};
        init = new Init{};
        close = new Close{};
    }

    Handle::~Handle()
    {
        if (init != nullptr) delete init;
        delete canvas;
        delete close;
    }

    void Handle::EventNode()
    {
        switch (global->level)
        {
            case 0:
                init->EventNode();
                break;

            case 1:
                if (init != nullptr)
                {
                    delete init;
                    init = nullptr;
                }
                canvas->EventNode();
                break;

            case 2:
                close->EventNode();
                break; 
        }
    }

    void Handle::DrawNode()
    {
        if (global->level == 0 && init != nullptr) init->DrawNode();
        else if (global->level == 1) canvas->DrawNode();
        else if (global->level == 2) close->DrawNode();
    }
}