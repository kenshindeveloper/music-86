#include "../includes/canvas.h"
#include "../includes/player.h"
#include "../includes/box.h"
#include "../includes/time.h"
#include "../includes/button.h"
#include "../includes/volume.h"
#include "../includes/tag.h"

namespace music
{
    Canvas::Canvas() 
    {
        global = Global::NewGlobal();
        rects = std::vector<Node*>();
        rects.push_back(new Volume{});
        rects.push_back(new Button{(Vector2){GetScreenWidth() - 40.0f, 5.0f}, "update"});
        rects.push_back(new Player{});
        rects.push_back(new Time{});        
        rects.push_back(new Box{});  
        rects.push_back(new Tag{(Vector2) {10.0f, 10.0f}, 0});      
        rects.push_back(new Tag{(Vector2) {50.0f, 10.0f}, 1});      
    }

    Canvas::~Canvas() 
    {
        for (Node*& node : rects) delete node;
    }

    void Canvas::EventNode()
    {
        for (Node*& node : rects) node->EventNode();
        
        if (IsKeyPressed(KEY_ESCAPE)) global->level = 2;
    }

    void Canvas::DrawNode() 
    {
        for (Node*& node : rects) node->DrawNode();
    }
}