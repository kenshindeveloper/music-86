#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "../includes/global.h"
#include "../includes/option.h"

namespace music
{
    Global* Global::self = nullptr;

    Global::Global()
    {
        screen_width = 640;
        screen_height = 480;
        index_up = 0;
        max_num_opt = 14;
        pos_y_player = 40;
        save_volume = 0;
        current_volume = 30;
        level = 0;
        index_tag = 0;
        index_selected_option = -1;
        current_index = -1;

        line_time = 0.0f;
        info_music_width = 260.0;
        info_music_height = 40.0f;

        color_0 = (Color) { 255, 49, 247, 255 }; 
        color_1 = (Color) { 186, 55, 246, 255 }; 
        color_2 = (Color) { 146, 57, 246, 255 }; 
        color_3 = (Color) { 144, 52, 149, 255 }; 
        color_4 = (Color) { 111, 52, 96, 255 }; 
        color_5 = (Color) { 74, 53, 79, 255 };  
        color_6 = (Color) { 210, 0, 118, 255 };  
        color_7 = (Color) { 255, 0, 118, 255 };  
        color_8 = (Color) { 255, 107, 88, 255 };  
        color_9 = (Color) { 255, 67, 115, 255 };  
        color_10 = (Color) { 255, 0, 90, 255 };  
        
        list_option = std::vector<Option*>();

        fps = 60;

        is_playing = false;
        flag_prox = false;
        is_repeat = false;
        is_shuffle = false;
        is_mute = false;
        is_run = true;
        
        music = nullptr;

        size_img_icons = (Vector2) {4, 12};
    }

    Global::~Global()
    {
        if (music != nullptr) 
        {
            UnloadMusicStream(*music);
            free(music);
            music = nullptr;
        }
        for (Option*& option : list_option) delete option;
        list_option.clear();
    }

    Global* Global::NewGlobal() 
    {
        if (self == nullptr) self = new Global{};
        return self;
    }

    void Global::FreeGlobal() 
    {
        delete self;
    }

    bool Global::IsValidMusic(std::string name)
    {
        if (name.length() <= 4) return false;

        std::vector<std::string> vector_extends;
        vector_extends.push_back(".mp3");

        for (std::string& token : vector_extends)
        {
            if (token == name.substr(name.length()-4, 4)) return true;
        }

        return false;
    }

    void Global::ChangeMusic()
    {
        index_selected_prev = index_selected_option;
        std::string name_music = "music/"+list_option[index_selected_option]->GetText();
        if (music != nullptr)
        {
            UnloadMusicStream(*music);
            free(music);
            music = nullptr;
        }

        music = (Music*) malloc(sizeof(Music));
        (*music) = LoadMusicStream(name_music.c_str());
        SetVolume();
    }

    void Global::PlayMusic()
    {
        // index_selected_option = current_index;
        line_time = 0.0f;
        if (music != nullptr && index_selected_prev == index_selected_option)
        {
            PlayMusicStream(*music);
        } 
        else 
        {
            ChangeMusic();
            PlayMusicStream(*music);
        }
    }

    void Global::UpdateMusic()
    {
        UpdateMusicChange();
        if (music != nullptr && is_playing) UpdateMusicStream(*music);

        if (!is_mute && current_volume == 0) is_mute = true; 

        if (IsKeyPressed(KEY_PAGE_UP))
        {
            current_volume += 10;
            if (current_volume > 100) current_volume = 100;
            if (current_volume > 0 && is_mute) is_mute = false;
            SetVolume();
        } 
        else if (IsKeyPressed(KEY_PAGE_DOWN))
        {
            current_volume -= 10;
            if (current_volume < 0) current_volume = 0;
            SetVolume();
        }
    }

    void Global::PauseMusic()
    {
        if (music != nullptr) PauseMusicStream(*music);
    }

    float Global::GetMusicTime()
    {
        if (music != nullptr) return GetMusicTimePlayed(*music);
        return 0.0f;
    }

    float Global::GetMusicTimeLen()
    {
        if (music != nullptr) return GetMusicTimeLength(*music);
        return 0.0f;
    }

    void Global::ProxMusic()
    {
        if ((current_index + 1) >= (int) (list_option.size() - 1))
        {
            current_index = (int) (list_option.size() - 1);
        }
        else
        {
            if (current_index >= (index_up + (max_num_opt - 2))) 
            {
                index_up += 1;
                SetRectOption();
            }
            current_index += 1;
        }
    }

    void Global::PrevMusic()
    {
        if ((current_index - 1) < 0) 
        {
            current_index = 0;
            index_up = 0;
        }    
        else 
        {
            if ((current_index - 1) == index_up) 
            {
                index_up = ((index_up - 1) >= 0)?(index_up-1):(0);
                SetRectOption();
            }
            current_index -= 1;
        }
    }

    void Global::StopMusic()
    {
        StopMusicStream(*music);
    }

    void Global::Shuffle()
    {
        int size = (int) (list_option.size() - 1);
        int max_num = (max_num_opt-1);
        int rand_index = GetRandomValue(0, size);
        index_selected_option = rand_index;
        ChangeMusic();
        PlayMusicStream(*music);
        if (index_up > rand_index)
        {
            int cont = 0;
            while ((index_up-cont) >= rand_index) cont += 1;
            index_up -= cont;
            if (index_up < 0) index_up = 0;
        }
        else if (index_up < rand_index)
        {
            int cont = 0;
            while (((index_up+cont)+max_num) < rand_index) cont += 1;
            index_up += cont;
        }
    }

    void Global::UpdateMusicChange()
    {
        if (flag_prox && !is_shuffle)
        {
            flag_prox = false;
            if (!is_repeat)
            {
                if ((index_selected_option+1) < (int)(list_option.size()-1)) index_selected_option += 1;
                else index_selected_option = 0;

                PlayMusic();
            }
            else
            {
                ChangeMusic();
                PlayMusicStream(*music);
            }
        } 
        else if (flag_prox && is_shuffle)
        {   
            flag_prox = false;
            Shuffle();
            SetRectOption();
        }
    }

    void Global::SetRectOption()
    {
        int pos_y = pos_y_player;
        for (int i=0; i < (int) list_option.size(); i++)
        {
            if (list_option[i]->GetIndex() >= index_up && list_option[i]->GetIndex() < (index_up + max_num_opt))
            {
                list_option[i]->SetVisible(true);
                list_option[i]->GetRectangle().y = pos_y;
                pos_y += 22;
            }
            else
            {
                list_option[i]->SetVisible(false);
            }
        }
    }

    void Global::UpdateListMusic()
    {
        for (Option*& option : list_option) delete option;
        list_option.clear();

        DIR* dir = opendir("music/");
        if (dir == NULL)
        {
            exit(1); //evaluar este error
        }  

        int default_width = (float) GetScreenWidth() - 20;
        int pos_x = 10;
        float option_height = 20.0f;
        int pos_y = pos_y_player;
        int size_text = 16;
        int cont = 0;
        int index = 0;

        struct dirent* ent = readdir(dir);
        while (ent != NULL)
        {
            if (cont > 1)
            {
                std::string sound = (std::string) ent->d_name;
                if (IsValidMusic(sound))
                {
                    list_option.push_back(new Option{ (Rectangle) {(float)pos_x, (float)pos_y, (float)default_width, option_height }, sound, size_text, index});
                    pos_y += option_height + 1;
                    index += 1;
                }
            } 
            cont += 1;
            ent = readdir(dir);
        }

        closedir(dir);

        if ((int) list_option.size() > 0)
        {
            index_selected_option = 0;
            current_index = 0;
        }
    }

    void Global::SetVolume()
    {
        if (music != nullptr) SetMusicVolume(*music, (current_volume/100.0f));
    }
}