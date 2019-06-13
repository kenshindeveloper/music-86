#include "../includes/tag.h"

namespace music
{
    Tag::Tag(Vector2 position, int index)
    {
        global = Global::NewGlobal();
        this->position = position;
        this->index = index;

        float diff = 24.0f;
        rect = (Rectangle) {position.x, position.y, 40.0f, 30.0f};
        position_img = (Vector2) {position.x + 7.0f, position.y + 2.0f};

        color_default = global->color_4;
        color_selected = global->color_3;

        image = LoadImage("resources/sprites/icons.png");
        ImageResizeNN(&image, (int)global->size_img_icons.x * diff, (int)global->size_img_icons.y * diff);
        texture = LoadTextureFromImage(image);
        
        if (index == 0) rect_img = (Rectangle) {diff * 0, diff * 10, diff, diff};
        else rect_img = (Rectangle) {diff * 1, diff * 10, diff, diff};
    }
    
    Tag::~Tag()
    {
        UnloadImage(image);
    }

    void Tag::EventNode()
    {
        is_collision = CheckCollisionPointRec(GetMousePosition(), rect);

        if (is_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) global->index_tag = index;

        if (IsKeyPressed(KEY_LEFT) && index == 0) global->index_tag = index;
        if (IsKeyPressed(KEY_RIGHT) && index == 1) global->index_tag = index;
    }

    void Tag::DrawNode()
    {
        if (global->index_tag == index) DrawRectangleRec(rect, color_selected);
        else DrawRectangleRec(rect, color_default);

        DrawTextureRec(texture, rect_img, position_img, RAYWHITE);
    }
}