#include "level_data.h"
#include "game_data.h"
#include "splashkit.h"

void draw_objects(const vector<object_data> objects)
{
    // for(int i = 0; i > objects.size(); i++)           // iterate over all objects in level_data object array
    //     {   
    //         // draw each rectangle in array 
    //         draw_rectangle(COLOR_BLUE, objects[i].object_rectangle); 
    //     }

    draw_rectangle(COLOR_BLUE, objects[0].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[1].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[2].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[3].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[4].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[5].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[6].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[7].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[8].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[9].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[10].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[11].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[12].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[13].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[14].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[15].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[16].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[17].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[18].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[19].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[20].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[21].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[22].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[23].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[24].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[25].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[26].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[27].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[28].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[29].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[30].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[31].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[32].object_rectangle);
    draw_rectangle(COLOR_BLUE, objects[33].object_rectangle);
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
