#include "level_data.h"
#include "game_data.h"
#include "splashkit.h"

double level_height = 1210;
double level_width = 1210;
double min_x = 0;
double min_y = 0;

double boundary_x = 1185;
double boundary_y = 1185;
double side_boundary_wall_width = 25;
double top_boundary_wall_height = 50;

double west_stairs_left_wall_y = 458;
double west_stairs_left_wall_width = 122;
double west_stairs_left_wall_height = 136;

vector<object_data> demo_level_objects = 
{
    {
        object_data {
            rectangle { rectangle_from(min_x, min_y, level_width, top_boundary_wall_height) },
            string { "top_boundary_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(min_x, min_y, side_boundary_wall_width, level_height) },
            string { "left_boundary_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(min_x, boundary_y, level_width, side_boundary_wall_width) },
            string { "bottom_boundary_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(boundary_x, min_y, side_boundary_wall_width, level_height) },
            string { "right_boundary_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(min_x, west_stairs_left_wall_y, west_stairs_left_wall_width, west_stairs_left_wall_height) },
            string { "west_stairs_left_wall" }
        }
    }
};

void draw_objects(const vector<object_data> objects)
{
    // for(int i = 0; i > objects.size(); i++)           // iterate over all objects in level_data object array
    //     {   
    //         // draw each rectangle in array 
    //         draw_rectangle(
    //             COLOR_BLUE,
    //             objects[i].object_rectangle.x,        // x location of the rectangle
    //             objects[i].object_rectangle.y,        // y location of the rectangle
    //             objects[i].object_rectangle.width,    // width of the rectangle
    //             objects[i].object_rectangle.height    // height of the rectangle
    //         ); 
    //     }

    draw_rectangle(COLOR_BLUE, min_x, min_y, level_width, top_boundary_wall_height);
    draw_rectangle(COLOR_BLUE, min_x, min_y, side_boundary_wall_width, level_height);
    draw_rectangle(COLOR_BLUE, min_x, boundary_y, level_width, side_boundary_wall_width);
    draw_rectangle(COLOR_BLUE, boundary_x, min_y, side_boundary_wall_width, level_height);
    draw_rectangle(COLOR_BLUE, min_x, west_stairs_left_wall_y, west_stairs_left_wall_width, west_stairs_left_wall_height);
};

vector<object_data> load_objects(const vector<object_data> level_objects)
{
    return level_objects;
}

level_data new_level()
{
    level_data new_level;

    new_level.level_bitmap = load_bitmap("LevelBmp", "demo_level.png");

    new_level.objects = load_objects(demo_level_objects);

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
