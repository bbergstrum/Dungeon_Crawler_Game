#include "level_data.h"
#include "game_data.h"
#include "splashkit.h"

void draw_objects(const vector<object_data> objects)
{
    for(int i = 0; i > objects.size(); i++)           // iterate over all objects in level_data object array
        {   
            // draw each rectangle in array 
            draw_rectangle(COLOR_BLUE, objects[i].object_rectangle); 
        }

    // draw_rectangle(COLOR_BLUE, min_x, min_y, level_width, top_boundary_wall_height);
    // draw_rectangle(COLOR_BLUE, min_x, min_y, side_boundary_wall_width, level_height);
    // draw_rectangle(COLOR_BLUE, min_x, boundary_y, level_width, side_boundary_wall_width);
    // draw_rectangle(COLOR_BLUE, boundary_x, min_y, side_boundary_wall_width, level_height);
    // draw_rectangle(COLOR_BLUE, min_x, stairs_wall_y, stairs_left_wall_width, stairs_wall_height);
    // draw_rectangle(COLOR_BLUE, west_stairs_right_wall_x, stairs_wall_y, stairs_right_wall_width, stairs_wall_height);
    // draw_rectangle(COLOR_BLUE, center_wall_x, center_wall_y, center_wall_width, center_wall_height);
    // draw_rectangle(COLOR_BLUE, east_stairs_left_wall_x, stairs_wall_y, stairs_right_wall_width, stairs_wall_height);
    // draw_rectangle(COLOR_BLUE, east_stairs_right_wall_x, stairs_wall_y, stairs_left_wall_width, stairs_wall_height);
    // draw_rectangle(COLOR_BLUE, west_torch_lg_x, torch_lg_y, torch_lg_width, torch_lg_height);
    // draw_rectangle(COLOR_BLUE, west_torch_sml_x, torch_sml_y, torch_sml_width, torch_sml_height);
    // draw_rectangle(COLOR_BLUE, east_torch_lg_x, torch_lg_y, torch_lg_width, torch_lg_height);
    // draw_rectangle(COLOR_BLUE, east_torch_sml_x, torch_sml_y, torch_sml_width, torch_sml_height);
};

level_data load_level(level_type level_type)
{
    level_data new_level;

    new_level.level_bitmap = load_bitmap("LevelBmp", "demo_level.png");

    new_level.objects = load_objects(new_level.objects, level_type);

    return new_level;
}

void draw_level(const level_data level_to_draw)
{
    draw_bitmap(level_to_draw.level_bitmap, 0, 0);                  // level bitmap should take up entire screen size

    if(DEBUG_MODE)                                                  // if debugging mode on, draw collision objects in blue
    {
        draw_objects(level_to_draw.objects);
    }
};
