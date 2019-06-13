#ifndef GLOBAL_H
#define GLOBAL_H

#include <vector>
#include <string>
#include "raylib.h"

namespace music 
{
    class Option;

    class Global
    {
        private:
            static Global* self;

        public:
            int index_selected_option;
            int index_selected_prev;
            int current_index;
            int screen_height;
            int screen_width;
            int fps;
            int font_info_size;
            int index_up;
            int max_num_opt;
            int pos_y_player;
            int save_volume;
            int current_volume;
            int level;
            int index_tag;

			bool is_playing;
            bool flag_prox;
            bool is_repeat;
            bool is_shuffle;
            bool is_mute;
            bool is_run;

            float line_time;
            float time_music;
            float info_music_width;
            float info_music_height;

            Color color_0;
            Color color_1;
            Color color_2;
            Color color_3;
            Color color_4;
            Color color_5;
            Color color_6;
            Color color_7;
            Color color_8;
            Color color_9;
            Color color_10;

            std::vector<Option*> list_option;

            Music* music;

            Vector2 size_img_icons;

        private:
            Global();
            void ChangeMusic();
            void Shuffle();

        public:
            ~Global();
            static Global* NewGlobal();
            static void FreeGlobal();

            bool IsValidMusic(std::string);
            void PlayMusic();
            void UpdateMusic();
            void PauseMusic();
            float GetMusicTime();
            float GetMusicTimeLen();
            void ProxMusic();
            void PrevMusic();
            void StopMusic();
            void UpdateMusicChange();
            void SetRectOption();

            void UpdateListMusic();
            void SetVolume();
    };
}

#endif //GLOBAL_H
