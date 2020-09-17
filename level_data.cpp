#include "level_data.h"
#include "splashkit.h"

level_data new_level()
{
    level_data new_level;

    new_level.level_id = 1;

    new_level.level_bitmap = load_bitmap("LevelBmp", "demo_level.png");

    return new_level;
}

void draw_level(level_data level_to_draw)
{
    draw_bitmap(level_to_draw.level_bitmap, 0, 0); // level bitmap should take up entire screen size
};
