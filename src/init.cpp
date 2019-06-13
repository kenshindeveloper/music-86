#include <vector>
#include "../includes/init.h"

namespace music
{
    Init::Init()
    {
        global = Global::NewGlobal();
        background = new Div{(Rectangle) {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()}, global->color_4};

        font = LoadFont("resources/fonts/04B_03__.TTF");
        float diff = 128.0f;

        animator = new Animator{};

        std::vector<Rectangle> vect = std::vector<Rectangle>();

        vect.push_back((Rectangle) {diff * 1, diff * 2, diff, diff});
        vect.push_back((Rectangle) {diff * 2, diff * 2, diff, diff});
        vect.push_back((Rectangle) {diff * 3, diff * 2, diff, diff});
        vect.push_back((Rectangle) {diff * 2, diff * 2, diff, diff});

        animator->add("loading", vect);
        image = LoadImage("resources/sprites/icons.png");
        ImageResizeNN(&image, (int) ((int)global->size_img_icons.x * diff), (int) ((int)global->size_img_icons.y * diff));
        texture = LoadTextureFromImage(image);

        pos_x = (GetScreenWidth()/2.0f);
        pos_y = (GetScreenHeight()/2.0f);

        pos_font = (Vector2){ pos_x - 80.0f, pos_y + 80.0f};
        pos_img = (Vector2){ pos_x - 64.0f, pos_y - 54.0f };
    }

    Init::~Init()
    {
        UnloadFont(font);
        delete background;
        delete animator;
        UnloadImage(image);
    }

    void Init::EventNode()
    {
        background->EventNode();
        if (IsKeyPressed(KEY_ENTER)) global->level = 1;
    }

    void Init::DrawNode()
    {
        background->DrawNode();
        animator->play("loading", texture, pos_img);
        DrawTextEx(font, "Press enter...", (Vector2) {pos_font.x-2.0f, pos_font.y}, 26, 1, global->color_5);
        DrawTextEx(font, "Press enter...", pos_font, 24, 1, WHITE);
        DrawTextEx(font, "Develop for Kenshin Urashima", (Vector2) {pos_x - 125.0f, pos_y + 210.0f}, 16, 1, global->color_8);
    }
}