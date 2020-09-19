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
    rectangle object_rectangle;
    string name;
};

/**
* returns the level objects into the level_objects array 
* 
* @param level_objects    array of objects for the respective level
*/
vector<object_data> load_objects(vector<object_data> &level_objects, level_type level_type);

#endif