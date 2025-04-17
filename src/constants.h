#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Config {
    inline constexpr short window_width = 1200;
    inline constexpr short window_height = 800;
    inline constexpr double EPSILON = 0.0001;

    namespace Ant {
        inline constexpr int max_age = 13;
        inline constexpr int nanny_age = 2;
        inline constexpr int soldier_age = 5;
        inline constexpr int collector_age = 8;
        inline constexpr int cleaner_age = 10;
        inline constexpr int max_health = 100;
        inline constexpr int start_age = 0;

        inline constexpr float age_update_time_interval = 2.0f;
        inline constexpr float speed = 50;
    }

    namespace Anthill {
        inline constexpr int max_size = 20;
        inline constexpr int default_size = 10;
        inline constexpr float spawn_interval = 5.0f;
        inline constexpr int hunger_damage = 30;
        inline constexpr int spawners_count = 10;
    }

    namespace Food
    {
        inline constexpr float spawn_interval = 5.0f;
        inline constexpr int max_count_of_food = 10;

    }
}

#endif //CONSTANTS_H
