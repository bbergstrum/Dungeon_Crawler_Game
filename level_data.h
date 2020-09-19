#ifndef DUNGEON_CRAWLER_LEVEL_DATA
#define DUNGEON_CRAWLER_LEVEL_DATA

#include "splashkit.h"
#include "level_designs.h"

using namespace std;

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
level_data load_level(level_type level_type);

/**
* Draws the level to the screen. 
* 
* @param level_to_draw    The level to draw to the screen
*/
void draw_level(level_data level_to_draw);

#endif