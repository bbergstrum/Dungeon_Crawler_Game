#ifndef DUNGEON_CRAWLER_LEVEL_DATA
#define DUNGEON_CRAWLER_LEVEL_DATA

#include "splashkit.h"

using namespace std;

// structured something like this eventually
struct level_data
{
    double level_id;

    bitmap level_bitmap;
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