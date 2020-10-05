#include "level_data.h"
#include "game_data.h"
#include "splashkit.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

bitmap load_level_bitmap(bitmap level_bitmap, level_type level_type)
{
    switch (level_type)
    {
    case START:
        // level_bitmap = load_bitmap("LevelBmp", "start_level.png");
        break;
    case DUNGEON_ONE:
        // level_bitmap = load_bitmap("LevelBmp", "dungeon_level_one.png");
        break;
    case DUNGEON_TWO:
        // level_bitmap = load_bitmap("LevelBmp", "dungeon_level_two.png");   
        break;
    case DUNGEON_THREE:
        // level_bitmap = load_bitmap("LevelBmp", "dungeon_level_three.png");
        break;
    case DEMO:
        level_bitmap = load_bitmap("LevelBmp", "demo_level_with_hud.png");
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

string select_input_file(level_type level_type)
{
    string source_file;
   
    switch (level_type)
    {
    case START:
        // source_file = "Resources/levels/starter_level.dat";
        break;
    case DUNGEON_ONE:
        // source_file = "Resources/levels/dungeon_level_one.dat";
        break;
    case DUNGEON_TWO:
        // source_file = "Resources/levels/dungeon_level_two.dat";
        break;
    case DUNGEON_THREE:
        // source_file = "Resources/levels/dungeon_level_three.dat";
        break;
    case DEMO:
        source_file = "Resources/levels/demo_level.dat";
        break;
    };

    return source_file;
}
vector<object_data> load_level_objects(level_type level_type)
{
    // initialize a vector of object data
    vector<object_data> new_level_objects;

    // initialize a new object
    object_data new_object = {};
    
    // initialize a string to store rectangle data
    string object_details;

    vector<string> rectangle_data;

    // store delimiter character to split string
    string delimiter = ",";
    
    // load input file depending on level type
    ifstream data_file(select_input_file(level_type));
    
    // read each line of the .dat file - a buffer to store data, and an input stream 
    while (getline(data_file, object_details)) 
    {
        //separte each value on each line into an array of strings
        vector<string> values = split_string(object_details, delimiter);

        write_line("x: " + values[0] + " y: " + values[1] + " w: " + values[2] + " h: " + values[3]);

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

    for(int i = 0; i < new_level_objects.size(); i++)
    {
        write_line( " x: " + to_string(new_level_objects[i].object_rectangle.x) + 
                    " y: " + to_string(new_level_objects[i].object_rectangle.y) + 
                    " w: " + to_string(new_level_objects[i].object_rectangle.width) + 
                    " h: " + to_string(new_level_objects[i].object_rectangle.height)
        );
    }

    // close the data file when finished
    data_file.close();

    // return the level objects array
    return new_level_objects;
}

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
    new_level.level_bitmap = load_level_bitmap(new_level.level_bitmap, level_type); 

    // load all the corresponding objects for that level type
    new_level.objects = load_level_objects(level_type);

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
}
