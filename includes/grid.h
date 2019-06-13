#ifndef __GRID_H__
#define __GRID_H__

#include <vector>
#include "raylib.h"
#include "global.h"
#include "node.h"
#include "bar.h"

namespace music
{
    class Grid: public Node
    {
        private:
            Global* global;
            Node* background;
            Node* info_music;
            
            int row;
            int column;
            int diff;
            
            Vector2 position;
            Vector2 position_default;

            Rectangle rect;
            std::vector<Bar*> bars;

        public:
            Grid(Rectangle);
            ~Grid();

            void EventNode();
            void DrawNode();
        
        private:
            void DrawGrid();
    };
}

#endif //__GRID_H__