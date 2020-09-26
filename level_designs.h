#ifndef DUNGEON_CRAWLER_LEVEL_DESIGNS
#define DUNGEON_CRAWLER_LEVEL_DESIGNS

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
    rectangle object_rectangle; // rectangle which represents collision boundaries
    string name; // name of the object to identify the object among the array of objects
};

/**
* returns the level bitmap to be loaded
* 
* @param level_bitmap    the level variable which stores the level bitmap
* @param level_type    the level type which determines which level to load
*/
bitmap load_level(bitmap level_bitmap, level_type level_type);

/**
* returns the level objects to be loaded into the level objects array
* 
* @param level_objects    array of objects for the respective level
* @param level_type    the level type which determines which level to load
*/
vector<object_data> load_objects(vector<object_data> &level_objects, level_type level_type);

#endif