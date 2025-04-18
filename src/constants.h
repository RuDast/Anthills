#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Config {
    inline constexpr short window_width = 1200;
    inline constexpr short window_height = 800;
    inline constexpr double EPSILON = 0.0001;

    namespace Ant {
        inline constexpr int max_age = 13;
        inline constexpr int nanny_age = 1; // TODO 2
        inline constexpr int soldier_age = 2; // TODO 5
        inline constexpr int collector_age = 5; // TODO 8
        inline constexpr int cleaner_age = 8;
        inline constexpr int max_health = 100;
        inline constexpr int start_age = 0;

        inline constexpr float age_update_time_interval = 4.0f;
        inline constexpr float speed = 100;
    }
    namespace Enemy {
        inline constexpr float enemy_speed = 100.0f;
        inline constexpr float min_y = 0.0f;
        inline constexpr float max_y= 800.0f;
        inline constexpr float size = 20.0f;
    }

    namespace Anthill {
        inline constexpr int max_size = 20;
        inline constexpr int default_size = 10;
        inline constexpr float spawn_interval = 5.0f;
        inline constexpr int hunger_damage = 30;
        inline constexpr int spawners_count = 10;
        inline constexpr float sklad_x = 500;
        inline constexpr float sklad_y = 120;
        inline constexpr float trash_x = 500;
        inline constexpr float trash_y = 700;
    }

    namespace Food
    {
        inline constexpr float spawn_interval = 3.0f;
        inline constexpr int max_count_of_food = 30;

    }
}
#endif //CONSTANTS_H
