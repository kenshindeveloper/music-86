#include "../includes/grid.h"
#include "../includes/div.h"
#include "../includes/music_fill.h"

namespace music
{
    Grid::Grid(Rectangle rect)
    {
        global = Global::NewGlobal();
        this->rect = rect;
        info_music = new MusicFill{(Rectangle) {rect.x + (rect.width - global->info_music_width), rect.y, global->info_music_width, global->info_music_height}};

        row = 14;
        column = 30;
        diff = 10;

        position = (Vector2) {rect.x, rect.y};
        position_default = position;

        background = new Div{rect, global->color_0};

        bars = std::vector<Bar*>();
    
        for (int j = 0; j <= column; j++) 
        {
            // if (j == 15) bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 10.0f, 19.0f, rect.height - 10.0f}, 200}); 
            // if (j == column) bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 150.0f, 20.0f, rect.height -150.0f}});
            // else bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 150.0f, 19.0f, rect.height -150.0f}});
            
            if (j < 4 || j > 26)
            {
                if (j != 0 && j != column)
                    bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 250.0f, 19.0f, rect.height - 250.0f}, 20});  
                // bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 270.0f, 19.0f, rect.height - 270.0f}, 10});  
            }
            else if ((j >= 4 && j < 8) || (j > 21 && j <= 26))
                bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 200.0f, 19.0f, rect.height - 200.0f}, 70});  
            else if ((j >= 8 && j < 14) || (j > 15 && j <= 21))
            {
                if ((j >= 8 && j < 10) || (j > 19 && j <= 21))
                    bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 170.0f, 19.0f, rect.height - 170.0f}, 100});
                else if ((j >= 10 && j < 13) || (j > 17 && j <= 19))
                    bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 150.0f, 19.0f, rect.height - 150.0f}, 120});
                else
                    bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 90.0f, 19.0f, rect.height - 90.0f}, 180});
            }  
            else
            {
                if (j == 15) bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 20.0f, 19.0f, rect.height - 20.0f}, 220});  
                else bars.push_back(new Bar {(Rectangle) {position.x  , position.y + 40.0f, 19.0f, rect.height - 40.0f}, 200});  
            }

            position.x += 20.0f;
        }
        position = position_default;
    }

    Grid::~Grid()
    {
        delete background;
        background = nullptr;
        for (Bar*& bar : bars) delete bar;
        bars.clear();

        delete info_music;
        info_music = nullptr;
    }

    void Grid::EventNode()
    {
        background->EventNode();
        info_music->EventNode();
    }

    void Grid::DrawNode()
    {
        background->DrawNode();
        for (Bar*& bar : bars) bar->EventNode();

        DrawGrid();

        info_music->DrawNode();
    }

    void Grid::DrawGrid()
    {
        float pos_x = rect.x + 20.0f;
        float pos_y = rect.y + 20.0f;

        for (int j = 0; j < 30; j++)
        {
            // DrawLine(pos_x, pos_y, pos_x, rect.height+ rect.y, WHITE);
            DrawRectangleRec((Rectangle) {pos_x, rect.y, 1.0f, rect.height}, global->color_1);
            if (j < 14) DrawRectangleRec((Rectangle) {rect.x, pos_y, rect.width, 1.0f}, global->color_1);
            pos_x += 20.0f;
            pos_y += 20.0f;
        }

        for (Bar*& bar : bars) bar->DrawNode();
    }
}