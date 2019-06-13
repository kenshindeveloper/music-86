#include <vector>
#include "../includes/icon.h"
#include "../includes/global.h"

namespace music
{
    Icon::Icon(std::string type, Vector2 position) 
    {   
        global = Global::NewGlobal();
        this->type = type;
        float diff = 128.0f;
        animator = nullptr;

        map_rect = std::map<std::string, Rectangle>();
        if (type == "play")
        {
            map_rect["play"] = (Rectangle) {diff * 1, 0, diff, diff};
            map_rect["play_select"] = (Rectangle) {diff * 2, 0, diff, diff};

            animator = new Animator{};
            std::vector<Rectangle> vect = std::vector<Rectangle>();

            vect.push_back((Rectangle) {diff * 1, diff * 2, diff, diff});
            vect.push_back((Rectangle) {diff * 2, diff * 2, diff, diff});
            vect.push_back((Rectangle) {diff * 3, diff * 2, diff, diff});
            vect.push_back((Rectangle) {diff * 2, diff * 2, diff, diff});

            animator->add("pause", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 0, diff * 11, diff, diff});
            vect.push_back((Rectangle) {diff * 1, diff * 11, diff, diff});
            vect.push_back((Rectangle) {diff * 2, diff * 11, diff, diff});
            vect.push_back((Rectangle) {diff * 1, diff * 11, diff, diff});

            animator->add("play_no_select", vect);
        }
        else if (type == "left")
        {
            map_rect["left"] = (Rectangle) {diff * 3, 0, diff, diff};
            map_rect["left_select"] = (Rectangle) {diff * 0, diff * 1, diff, diff};
            map_rect["left_pause"] = (Rectangle) {diff * 1, diff * 1, diff, diff};
        }
        else if (type == "right")
        {
            map_rect["right"] = (Rectangle) {diff * 2, diff, diff, diff};
            map_rect["right_select"] = (Rectangle) {diff * 3, diff, diff, diff};
            map_rect["right_pause"] = (Rectangle) {diff * 0, diff * 2, diff, diff};
        }
        else if (type == "repeat")
        {
            animator = new Animator{};
            std::vector<Rectangle> vect = std::vector<Rectangle>();

            vect.push_back((Rectangle) {diff * 3, diff * 4, diff, diff});
            vect.push_back((Rectangle) {diff * 0, diff * 5, diff, diff});
            vect.push_back((Rectangle) {diff * 1, diff * 5, diff, diff});
            vect.push_back((Rectangle) {diff * 0, diff * 5, diff, diff});
            animator->add("playing_not_repeat", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 0, diff * 4, diff, diff});
            vect.push_back((Rectangle) {diff * 1, diff * 4, diff, diff});
            vect.push_back((Rectangle) {diff * 2, diff * 4, diff, diff});
            vect.push_back((Rectangle) {diff * 1, diff * 4, diff, diff});
            animator->add("playing_repeat", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 2, diff * 3, diff, diff});
            animator->add("not_playing_repeat_open", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 1, diff * 3, diff, diff});
            animator->add("not_playing_not_repeat_open", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 3, diff * 3, diff, diff});
            animator->add("not_playing_repeat_close", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 0, diff * 3, diff, diff});
            animator->add("not_playing_not_repeat_close", vect);
            vect.clear();
        }
        else if (type == "shuffle")
        {
            animator = new Animator{};
            std::vector<Rectangle> vect = std::vector<Rectangle>();

            vect.push_back((Rectangle) {diff * 3, diff * 6, diff, diff});
            vect.push_back((Rectangle) {diff * 0, diff * 7, diff, diff});
            vect.push_back((Rectangle) {diff * 1, diff * 7, diff, diff});
            vect.push_back((Rectangle) {diff * 0, diff * 7, diff, diff});
            animator->add("playing_not_shuffle", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 2, diff * 7, diff, diff});
            vect.push_back((Rectangle) {diff * 3, diff * 7, diff, diff});
            vect.push_back((Rectangle) {diff * 0, diff * 8, diff, diff});
            vect.push_back((Rectangle) {diff * 7, diff * 7, diff, diff});
            animator->add("playing_shuffle", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 1, diff * 6, diff, diff});
            animator->add("not_playing_shuffle_open", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 0, diff * 6, diff, diff});
            animator->add("not_playing_not_shuffle_open", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 2, diff * 6, diff, diff});
            animator->add("not_playing_shuffle_close", vect);
            vect.clear();

            vect.push_back((Rectangle) {diff * 3, diff * 5, diff, diff});
            animator->add("not_playing_not_shuffle_close", vect);
            vect.clear();
        }

        rect = map_rect[type];
        type_name = type;
        image = LoadImage("resources/sprites/icons.png");
        ImageResizeNN(&image, (int) ((int)global->size_img_icons.x * diff), (int) ((int)global->size_img_icons.y * diff));
        texture = LoadTextureFromImage(image);

        this->position = position;
        rect_collision = Rectangle {position.x + 28, position.y + 10, 75, 98};

        is_collision = false;
        index_play = -1;
    }

    Icon::~Icon()
    {
        if (animator != nullptr) delete animator;
        UnloadImage(image);
    }

    void Icon::ChangeSize()
    {
        if (global->screen_width != GetScreenWidth())
        {
            position.x = (position.x * GetScreenWidth()) / global->screen_width;
            rect_collision.x = (rect_collision.x * GetScreenWidth()) / global->screen_width;
            rect_collision.width = (rect_collision.width * GetScreenWidth()) / global->screen_width;
        }

        if (global->screen_height != GetScreenHeight())
        {
            position.y = (position.y * GetScreenHeight()) / global->screen_height;
            rect_collision.y = (rect_collision.y * GetScreenHeight()) / global->screen_height;
            rect_collision.height = (rect_collision.height * GetScreenHeight()) / global->screen_height;
        }

        if ((global->screen_width != GetScreenWidth()) &&  (global->screen_height != GetScreenHeight()))
        {
            float diff = (image.width / 4);
            diff = (diff * GetScreenWidth()) / global->screen_width;
            if (diff < 258)
            {
                ImageResizeNN(&image, (int) (4 * diff), (int) (3 * diff));
                texture = LoadTextureFromImage(image);

                map_rect["play"] = (Rectangle) {diff * 1, 0, diff, diff};
                map_rect["play_select"] = (Rectangle) {diff * 2, 0, diff, diff};
                map_rect["left"] = (Rectangle) {diff * 3, 0, diff, diff};
                map_rect["left_select"] = (Rectangle) {diff * 0, diff * 1, diff, diff};
                map_rect["left_pause"] = (Rectangle) {diff * 1, diff * 1, diff, diff};
                map_rect["right"] = (Rectangle) {diff * 2, diff, diff, diff};
                map_rect["right_select"] = (Rectangle) {diff * 3, diff, diff, diff};
                map_rect["right_pause"] = (Rectangle) {diff * 0, diff * 2, diff, diff};

                if (type_name == "play")
                {
                    animator = new Animator{};
                    std::vector<Rectangle> vect = std::vector<Rectangle>();

                    vect.push_back((Rectangle) {diff * 1, diff * 2, diff, diff});
                    vect.push_back((Rectangle) {diff * 2, diff * 2, diff, diff});
                    vect.push_back((Rectangle) {diff * 3, diff * 2, diff, diff});
                    vect.push_back((Rectangle) {diff * 2, diff * 2, diff, diff});
                    animator->add("pause", vect);
                }
            }
        }
    }

    void Icon::IsPlayButton()
    {
        if ((int) global->list_option.size() > 0)
        {
            bool is_collision = CheckCollisionPointRec(GetMousePosition(), rect_collision);
            rect = (is_collision)?(map_rect["play_select"]):(map_rect["play"]);

            switch (global->is_playing)
            {
                case true:
                    if ((is_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_ENTER))
                    {
                        if (global->current_index == global->index_selected_option)
                        {
                            global->is_playing = false;
                            global->PauseMusic();
                        }
                        else
                        {
                            global->index_selected_option = global->current_index;
                            index_play = global->index_selected_option;
                            global->PlayMusic();
                        }
                    }
                    break;

                case false:
                    if ((is_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_ENTER))
                    {
                        global->index_selected_option = global->current_index;
                        index_play = global->index_selected_option;
                        global->is_playing = true;
                        global->PlayMusic();
                    }
                    break;
            }
        }
    }

    void Icon::IsLeftButton()
    {
        if ((int) global->list_option.size() > 0)
        {
            bool is_collision = CheckCollisionPointRec(GetMousePosition(), rect_collision);
            rect = (is_collision)?(map_rect["left_select"]):(map_rect["left"]);

            //--------------------------------------------------------
            if (global->is_playing ) rect = map_rect["left_pause"];

            if ((is_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_UP))
            {

                global->PrevMusic();
            }
        }
    }

    void Icon::IsRightButton()
    {
        if ((int) global->list_option.size() > 0)
        {
            bool is_collision = CheckCollisionPointRec(GetMousePosition(), rect_collision);
            rect = (is_collision)?(map_rect["right_select"]):(map_rect["right"]);

            if (global->is_playing ) rect = map_rect["right_pause"];

            if ((is_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_DOWN))
            {
                global->ProxMusic();
            }
        }
    }

    void Icon::IsRepeatButton()
    {
        if ((int) global->list_option.size() > 0)
        {
            is_collision = CheckCollisionPointRec(GetMousePosition(), rect_collision);
            if ((global->list_option.size() > 0) && ((is_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_R)))
            {
                global->is_repeat = !global->is_repeat;
                global->is_shuffle = false;
            }
        }
    }

    void Icon::IsShuffleButton()
    {
        if (global->list_option.size() > 0)
        {
            is_collision = CheckCollisionPointRec(GetMousePosition(), rect_collision);
            if ((global->list_option.size() > 0) && ((is_collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_S)))
            {
                global->is_shuffle = !global->is_shuffle;
                global->is_repeat = false;
            }
        }
    }

    void Icon::EventNode()
    {
        ChangeSize();
        
        if (type == "play") IsPlayButton();
        else if (type == "left") IsLeftButton();
        else if (type == "right") IsRightButton();
        else if (type == "repeat") IsRepeatButton();
        else if (type == "shuffle") IsShuffleButton();
    }

    void Icon::DrawRepeat()
    {
        if (is_collision)
        {
            if (!global->is_playing && !global->is_repeat) 
                animator->play("not_playing_not_repeat_open", texture, position);
            else if (!global->is_playing && global->is_repeat)
                animator->play("not_playing_repeat_open", texture, position);
            else if (global->is_playing && !global->is_repeat)
                animator->play("playing_not_repeat", texture, position);
            else if (global->is_playing && global->is_repeat)
                animator->play("playing_repeat", texture, position);
        }
        else
        {
            if (global->is_playing && !global->is_repeat) 
                animator->play("playing_not_repeat", texture, position);
            else if (global->is_playing && global->is_repeat) 
                animator->play("playing_repeat", texture, position);
            else if (!global->is_playing && global->is_repeat)
                animator->play("not_playing_repeat_close", texture, position);
            else if (!global->is_playing && !global->is_repeat)
                animator->play("not_playing_not_repeat_close", texture, position);
            else DrawTextureRec(texture, rect, position, WHITE);
        }
    }

    void Icon::DrawShuffle()
    {
        if (is_collision)
        {
            if (!global->is_playing && !global->is_shuffle) 
                animator->play("not_playing_not_shuffle_open", texture, position);
            else if (!global->is_playing && global->is_shuffle)
                animator->play("not_playing_shuffle_open", texture, position);
            else if (global->is_playing && !global->is_shuffle)
                animator->play("playing_not_shuffle", texture, position);
            else if (global->is_playing && global->is_shuffle)
                animator->play("playing_shuffle", texture, position);
        }
        else
        {
            if (global->is_playing && !global->is_shuffle) 
                animator->play("playing_not_shuffle", texture, position);
            else if (global->is_playing && global->is_shuffle) 
                animator->play("playing_shuffle", texture, position);
            else if (!global->is_playing && global->is_shuffle)
                animator->play("not_playing_shuffle_close", texture, position);
            else if (!global->is_playing && !global->is_shuffle)
                animator->play("not_playing_not_shuffle_close", texture, position);
            else DrawTextureRec(texture, rect, position, WHITE);
        }
    }

    void Icon::DrawNode()
    {
        if (type == "play" && global->is_playing && animator != nullptr)
        {
            if (global->current_index == index_play)
                animator->play("pause", texture, position);
            else
                animator->play("play_no_select", texture, position);
        }
        else if (type == "repeat")
            DrawRepeat();
        else if (type == "shuffle")
            DrawShuffle();
        else
            DrawTextureRec(texture, rect, position, WHITE);
    }
}