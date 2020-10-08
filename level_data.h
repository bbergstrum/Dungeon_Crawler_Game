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
    FINAL,
    DEMO
};

enum trigger_type
{
    NEXT = 1,
    PREV
};

struct event_trigger
{
    trigger_type type;
    rectangle location;
};

struct object_data
{
    rectangle object_rectangle; // rectangle which represents collision boundaries
    string name; // name of the object to identify the object among the array of objects
};

// level data broken up into a level bitmap with a vector of collidable objects
struct level_data
{
    level_type type;

    bitmap level_bitmap;

    vector<object_data> objects;

    vector<event_trigger> event_triggers;
};

/**
 * loads a new level bitmap
 * 
 * @returns     The new level data
 */
level_data load_level(const level_type &level_type);

/**
* Draws the level to the screen. 
* 
* @param level_to_draw      The level to draw to the screen
* @param debug_mode         If debug mode is turned on or off
*/
void draw_level(const level_data &level_to_draw, bool &debug_mode);

#endif