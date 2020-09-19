#ifndef DUNGEON_CRAWLER_LEVEL_DATA
#define DUNGEON_CRAWLER_LEVEL_DATA

#include "splashkit.h"

using namespace std;

// enumeration for dynamic level loading
enum level_type
{
    START,
    DUNGEON_ONE,
    DUNGEON_TWO,
    DUNGEON_THREE,
    DEMO
};

struct object_data
{
    rectangle object_rectangle;
    string name;
};

// structured something like this eventually
struct level_data
{
    level_type type;
    
    bitmap level_bitmap;

    vector<object_data> objects;
};

/**
 * loads a new level bitmap
 * 
 * @returns     The new level data
 */
level_data new_level();

/**
* Draws the level to the screen. 
* 
* @param level_to_draw    The level to draw to the screen
*/
void draw_level(level_data level_to_draw);

#endif