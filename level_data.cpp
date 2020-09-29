#include "level_data.h"
#include "game_data.h"
#include "splashkit.h"

void draw_objects(const vector<object_data> objects)
{
    // iterate over all objects in level_data object array
    for(int i = 0; i < objects.size(); i++)           
        {   
            // draw each rectangle in array 
            draw_rectangle(COLOR_BLUE, objects[i].object_rectangle); 
        }
};

level_data load_level(level_type level_type)
{
    level_data new_level;

    // load level bitmap based on level type
    new_level.level_bitmap = load_level(new_level.level_bitmap, level_type); 

    // load all the corresponding objects for that level type
    new_level.objects = load_objects(new_level.objects, level_type); 

    return new_level;
}

void draw_level(const level_data level_to_draw, bool debug_mode)
{
    // draw the level bitmap
    draw_bitmap(level_to_draw.level_bitmap, 0, 0);                  // level bitmap should take up entire screen size

    // outline collisionable objects if debug mode on
    if(debug_mode)                                                  // if debugging mode on, draw collision objects in blue
    {
        draw_objects(level_to_draw.objects);
    }
};
