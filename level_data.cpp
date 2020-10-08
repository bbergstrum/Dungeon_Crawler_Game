#include "splashkit.h"
#include "level_data.h"
#include "enemy.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

bitmap load_level_bitmap(bitmap &level_bitmap, const level_type &level_type)
{
    switch (level_type)
    {
    case START:
        level_bitmap = load_bitmap("start", "starting_level.png");
        break;
    case DUNGEON_ONE:
        level_bitmap = load_bitmap("level_one", "dungeon_level_one.png");
        break;
    case DUNGEON_TWO:
        level_bitmap = load_bitmap("level_two", "dungeon_level_two.png");   
        break;
    case FINAL:
        level_bitmap = load_bitmap("final_boss", "final_boss_level.png");
        break;
    case DEMO:
        level_bitmap = load_bitmap("demo_level", "demo_level_with_hud.png");
        break;
    }
    
    return level_bitmap;
}

vector<string> split_string(const string &object_data, const string &delimiter)
{
    // initialize a temp string
    string values;

    // intialise an array of strings as the output
    vector<string> output;

    // open a string stream from the input string
    stringstream data_stream(object_data);

    // read each line of the string with the delimiter
    while(getline(data_stream,values,',')) {
        // push the separeted characters into the array of strings
        output.push_back(values);
    }

    // return the array of strings
    return output;
}

string select_objects_input_file(const level_type &level_type)
{
    string source_file;
   
    switch (level_type)
    {
        case START:
            source_file = "Resources/levels/starter_level.dat";
            break;
        case DUNGEON_ONE:
            source_file = "Resources/levels/dungeon_level_one.dat";
            break;
        case DUNGEON_TWO:
            source_file = "Resources/levels/dungeon_level_two.dat";
            break;
        case FINAL:
            source_file = "Resources/levels/final_boss_level.dat";
            break;
        case DEMO:
            source_file = "Resources/levels/demo_level.dat";
            break;
    };

    return source_file;
}

string select_enemies_input_file(const level_type &level_type)
{
    string source_file;
   
    switch (level_type)
    {
        case START:
            source_file = "Resources/enemies/starter_level_enemies.dat";
            break;
        case DUNGEON_ONE:
            source_file = "Resources/enemies/d_lvl_one_enemies.dat";
            break;
        case DUNGEON_TWO:
            source_file = "Resources/enemies/d_lvl_two_enemies.dat";
            break;
        case FINAL:
            source_file = "Resources/enemies/final_lvl_enemies.dat";
            break;
        case DEMO:
            // demo has no enemies
            break;
    };

    return source_file;
}

vector<object_data> load_level_objects(const level_type &level_type)
{
    // initialize a vector of object data
    vector<object_data> new_level_objects;

    // initialize a new object
    object_data new_object = {};
    
    // initialize a string to store rectangle data
    string object_data;

    // store delimiter character to split string
    string delimiter = ",";
    
    // load input file depending on level type
    ifstream data_file(select_objects_input_file(level_type));
    
    // read each line of the .dat file - a buffer to store data, and an input stream 
    while (getline(data_file, object_data)) 
    {
        //separte each value on each line into an array of strings
        vector<string> values = split_string(object_data, delimiter);

        // cast each value to an int
        int x_loc = convert_to_integer(values[0]);
        int y_loc = convert_to_integer(values[1]);
        int width = convert_to_integer(values[2]);
        int height = convert_to_integer(values[3]);

        // create the rectangle for the object with the values from each line
        new_object.object_rectangle = rectangle_from(x_loc, y_loc, width, height);

        // push the object onto the level objects array
        new_level_objects.push_back(new_object);
    }

    // close the data file when finished
    data_file.close();

    // return the level objects array
    return new_level_objects;
}

vector<enemy_data> load_level_enemies(const level_type &level_type)
{
    // initialize a vector of object data
    vector<enemy_data> new_enemies;

    enemy_data enemy;
    
    // initialize a string to store rectangle data
    string enemy_params;

    // store delimiter character to split string
    string delimiter = ",";
    
    // load input file depending on level type
    ifstream data_file(select_enemies_input_file(level_type));
    
    // read each line of the .dat file - a buffer to store data, and an input stream 
    while (getline(data_file, enemy_params)) 
    {
        //separte each value on each line into an array of strings
        vector<string> values = split_string(enemy_params, delimiter);

        // cast each value to an int
        int type = convert_to_integer(values[0]);
        int pos_x = convert_to_integer(values[1]);
        int pos_y = convert_to_integer(values[2]);

        // initialize a new enemy and push enemy details
        enemy = new_enemy(static_cast<enemy_type>(type), pos_x, pos_y);
        // create the rectangle for the object with the values from each line

        // push the object onto the level objects array
        new_enemies.push_back(enemy);
    }

    // close the data file when finished
    data_file.close();

    // return the level objects array
    return new_enemies;
}
vector<event_trigger> load_event_triggers(const level_type &level_type, vector<event_trigger> &event_triggers, const vector<object_data> &objects)
{
    event_trigger new_event_trigger;

    switch (level_type)
    {
        // event trigger locations and size always at end of .dat file for that level
        case START:
            new_event_trigger.type = NEXT;
            new_event_trigger.location = objects[objects.size() - 1].object_rectangle;
            event_triggers.push_back(new_event_trigger);
            new_event_trigger.type = PREV;
            new_event_trigger.location = objects[objects.size() - 2].object_rectangle;
            event_triggers.push_back(new_event_trigger);
            break;
        case DUNGEON_ONE:
            new_event_trigger.type = NEXT;
            new_event_trigger.location = objects[objects.size() - 1].object_rectangle;
            event_triggers.push_back(new_event_trigger);
            new_event_trigger.type = PREV;
            new_event_trigger.location = objects[objects.size() - 2].object_rectangle;
            event_triggers.push_back(new_event_trigger);
            break;
        case DUNGEON_TWO:
            new_event_trigger.type = NEXT;
            new_event_trigger.location = objects[objects.size() - 1].object_rectangle;
            event_triggers.push_back(new_event_trigger);
            new_event_trigger.type = PREV;
            new_event_trigger.location = objects[objects.size() - 2].object_rectangle;
            event_triggers.push_back(new_event_trigger);
            break;
        case FINAL:
            new_event_trigger.type = NEXT;
            new_event_trigger.location = objects[objects.size() - 1].object_rectangle;
            event_triggers.push_back(new_event_trigger);
            new_event_trigger.type = PREV;
            new_event_trigger.location = objects[objects.size() - 2].object_rectangle;
            event_triggers.push_back(new_event_trigger);
            break;
        case DEMO:
            break;
    };

    return event_triggers;
}

void draw_objects(const vector<object_data> &objects, const level_type &level_type)
{
    // iterate over all objects in level_data object array
    for(int i = 0; i < objects.size() - 2; i++) // last two objects are always event triggers          
        {   
            // draw each rectangle in array 
            draw_rectangle(COLOR_BLUE, objects[i].object_rectangle); 
        }

    switch (level_type)
    {
        // draw event triggers yellow
        case START:
            draw_rectangle(COLOR_YELLOW, objects[objects.size() - 1].object_rectangle); 
            break;
        case DUNGEON_ONE:
            draw_rectangle(COLOR_YELLOW, objects[objects.size() - 1].object_rectangle);
            draw_rectangle(COLOR_YELLOW, objects[objects.size() - 2].object_rectangle);
            break;
        case DUNGEON_TWO:
            break;
        case FINAL:
            break;
        case DEMO:
            break;
    };

};

level_data load_level(const level_type &level_type)
{
    level_data new_level;

    new_level.type = level_type;

    // load level bitmap based on level type
    new_level.level_bitmap = load_level_bitmap(new_level.level_bitmap, level_type); 

    // load all the corresponding objects for that level type
    new_level.objects = load_level_objects(level_type);

    new_level.level_enemies = load_level_enemies(level_type);

    new_level.event_triggers = load_event_triggers(new_level.type, new_level.event_triggers, new_level.objects);

    write_line("EVENT TRIGGERS: ");
    for(int i = 0; i < new_level.event_triggers.size(); i++)
    {
        
        write_line( " x: " + to_string(new_level.event_triggers[i].location.x) + 
                    " y: " + to_string(new_level.event_triggers[i].location.y) + 
                    " w: " + to_string(new_level.event_triggers[i].location.width) + 
                    " h: " + to_string(new_level.event_triggers[i].location.height)
                    );
    }

    return new_level;
}

void draw_level(const level_data &level_to_draw, bool &debug_mode)
{
    // draw the level bitmap
    draw_bitmap(level_to_draw.level_bitmap, 0, 0);                  // level bitmap should take up entire screen size

    // outline collisionable objects if debug mode on
    if(debug_mode)                                                  // if debugging mode on, draw collision objects in blue
    {
        draw_objects(level_to_draw.objects, level_to_draw.type);
    }
}
