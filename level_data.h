#ifndef DUNGEON_CRAWLER_LEVEL_DATA
#define DUNGEON_CRAWLER_LEVEL_DATA

#include "splashkit.h"
#include "level_designs.h"

using namespace std;

// level data broken up into a level bitmap with a vector of collidable objects
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
* @param level_to_draw      The level to draw to the screen
* @param debug_mode         If debug mode is turned on or off
*/
void draw_level(const level_data level_to_draw, bool debug_mode);

#endif