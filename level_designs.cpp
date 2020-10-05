#include "level_data.h"
#include "level_designs.h"
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

// data for demo level objects TO-DO: Separate out data into .dat file and load in file to game.

// general
double level_height = 1200;
double level_width = 1200;
double min_x = 0;
double min_y = 0;

// boundary walls
double top_boundary_wall_height = 156;
double side_boundary_wall_width = 26;
double right_boundary_wall_x = 1174;
double bottom_boundary_wall_y = 1172;
double bottom_boundary_wall_height = 28;

// center walls
double center_edge_wall_width = 156;
double center_wall_height = 102;
double center_wall_x = 276;
double center_wall_y = 478;
double center_wall_width = 646;
double center_right_wall_x = 1044;

// pillars
double south_west_pillar_x = 136;
double south_west_pillar_y = 744;
double south_west_pillar_width = 158;
double south_west_pillar_height = 188;
double south_east_pillar_x = 858;
double south_east_pillar_y = 888;
double south_east_pillar_width = 202;
double south_east_pillar_height = 216;
double south_east_pillar_bot_x = 926;
double south_east_pillar_bot_y = 1070;
double south_east_pillar_bot_width = 68;
double south_east_pillar_bot_height = 112;
double south_east_pillar_rock_x = 1058;
double south_east_pillar_rock_y = 1054;
double south_east_pillar_rock_width = 45;
double south_east_pillar_rock_height = 45;

// river
double river_x = 525;
double river_width = 150;
double river_height = 96;
double top_river_y = 196;
double bottom_river_y = 380;
double center_drain_x = 576;
double center_drain_y = 540;
double center_drain_width = 48;
double center_drain_height = 134; 

// lava pools
double lava_pool_top_x = 342;
double lava_pool_top_y = 866;
double lava_pool_top_width = 182;
double lava_pool_top_height = 252;
double lava_pool_bottom_x = 142;
double lava_pool_bottom_y = 1110;
double lava_pool_bottom_width = 525;
double lava_pool_bottom_height = 65;
double lava_pool_left_x = 26;
double lava_pool_left_y = 1008;
double lava_pool_left_width = 115;
double lava_pool_left_height = 165;
double south_west_lava_pool_sml_x = 26;
double south_west_lava_pool_sml_y = 962;
double south_west_lava_pool_sml_width = 24;
double south_west_lava_pool_sml_height = 46;
double stalagmite_center_right_x = 526;
double stalagmite_center_right_y = 864;
double stalagmite_center_right_width = 45;
double stalagmite_center_right_height = 30;
double stalagmite_center_left_x = 434;
double stalagmite_center_left_y = 814;
double stalagmite_center_left_width = 45;
double stalagmite_center_left_height = 48;
double stalagmite_south_west_x = 144;
double stalagmite_south_west_y = 1060;
double stalagmite_south_west_width = 46;
double stalagmite_south_west_height = 46;

// torches barrels & chests
double south_pillar_torch_x = 230;
double south_pillar_torch_y = 868;
double south_pillar_torch_width = 20;
double south_pillar_torch_height = 94;
double top_right_barrels_x = 1034;
double top_right_barrels_y = 158;
double top_right_barrels_width = 154;
double top_right_barrels_height = 90;
double top_right_barrels_mid_x = 1142;
double top_right_barrels_mid_y = 252;
double top_right_barrels_mid_width = 46;
double top_right_barrels_mid_height = 230;
double top_right_barrels_bot_x = 1058;
double top_right_barrels_bot_y = 436;
double top_right_barrels_bot_width = 134;
double top_right_barrels_bot_height = 42;
double top_barrel_and_torch_x = 672;
double top_barrel_and_torch_y = 150;
double top_barrel_and_torch_width = 54;
double top_barrel_and_torch_height = 84;
double top_chests_and_torch_x = 285;
double top_chests_and_torch_y = 154;
double top_chests_and_torch_width = 152;
double top_chests_and_torch_height = 70;
double top_left_barrels_x = 26;
double top_left_barrels_y = 190;
double top_left_barrels_width = 92;
double top_left_barrels_height = 62;
double top_left_torch_x = 86;
double top_left_torch_y = 212;
double top_left_torch_width = 18;
double top_left_torch_height = 72;
double top_left_barrels_bot_x = 26;
double top_left_barrels_bot_y = 396;
double top_left_barrels_bot_width = 20;
double top_left_barrels_bot_height = 20;
double top_center_bottom_barrels_x = 456;
double top_center_bottom_barrels_y = 436;
double top_center_bottom_barrels_width = 68;
double top_center_bottom_barrels_height = 48;
double top_left_center_barrel_x = 338;
double top_left_center_barrel_y = 444;
double top_left_center_barrel_width = 42;
double top_left_center_barrel_height = 38;
double top_center_torch_x = 422;
double top_center_torch_y = 402;
double top_center_torch_width = 20;
double top_center_torch_height = 80;
double south_chest_lava_x = 288;
double south_chest_lava_y = 1056;
double south_chest_lava_width = 50;
double south_chest_lava_height = 50;



vector<object_data> demo_level_objects = 
{
    // boundary walls
    {
        object_data {
            rectangle { rectangle_from(min_x, min_y, level_width, top_boundary_wall_height) },
            string { "top_boundary_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(min_x, min_y, side_boundary_wall_width, level_height) },
            string { "left_boundary_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(right_boundary_wall_x, min_y, side_boundary_wall_width, level_height) },
            string { "right_boundary_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(min_x, bottom_boundary_wall_y, level_width, bottom_boundary_wall_height) },
            string { "bottom_boundary_wall" }
        }
    },
    // center walls
    {
        object_data {
            rectangle { rectangle_from(min_x, center_wall_y, center_edge_wall_width, center_wall_height) },
            string { "left_center_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(center_wall_x, center_wall_y, center_wall_width, center_wall_height) },
            string { "center_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(center_right_wall_x, center_wall_y, center_edge_wall_width, center_wall_height) },
            string { "right_center_wall" }
        }
    },

    // pillars
    {
        object_data {
            rectangle { rectangle_from(south_west_pillar_x, south_west_pillar_y, south_west_pillar_width, south_west_pillar_height) },
            string { "south_west_pillar" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(south_east_pillar_x, south_east_pillar_y, south_east_pillar_width, south_east_pillar_height) },
            string { "south_east_pillar" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(south_east_pillar_bot_x, south_east_pillar_bot_y, south_east_pillar_bot_width, south_east_pillar_bot_height) },
            string { "south_east_pillar_bottom" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(south_east_pillar_rock_x, south_east_pillar_rock_y, south_east_pillar_rock_width, south_east_pillar_rock_height) },
            string { "south_east_pillar_rock" }
        }
    },

    // river
    {
        object_data {
            rectangle { rectangle_from(river_x, top_river_y, river_width, river_height) },
            string { "top_river" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(river_x, bottom_river_y, river_width, river_height) },
            string { "bottom_river" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(center_drain_x, center_drain_y, center_drain_width, center_drain_height) },
            string { "center_drain" }
        }
    },

    // lava pools & stalagmites
    {
        object_data {
            rectangle { rectangle_from(lava_pool_top_x, lava_pool_top_y, lava_pool_top_width, lava_pool_top_height) },
            string { "lava_pool_top" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(lava_pool_bottom_x, lava_pool_bottom_y, lava_pool_bottom_width, lava_pool_bottom_height) },
            string { "lava_pool_bottom" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(lava_pool_left_x, lava_pool_left_y, lava_pool_left_width, lava_pool_left_height) },
            string { "lava_pool_left" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(south_west_lava_pool_sml_x, south_west_lava_pool_sml_y, south_west_lava_pool_sml_width, south_west_lava_pool_sml_height) },
            string { "south_west_lava_pool_small" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(stalagmite_center_right_x, stalagmite_center_right_y, stalagmite_center_right_width, stalagmite_center_right_height) },
            string { "stalagmite_center_right" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(stalagmite_center_left_x, stalagmite_center_left_y, stalagmite_center_left_width, stalagmite_center_left_height) },
            string { "stalagmite_center_left" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(stalagmite_south_west_x, stalagmite_south_west_y, stalagmite_south_west_width, stalagmite_south_west_height) },
            string { "stalagmite_south_west" }
        }
    },

    // torches barrels chests
    {
        object_data {
            rectangle { rectangle_from(south_pillar_torch_x, south_pillar_torch_y, south_pillar_torch_width, south_pillar_torch_height) },
            string { "south_pillar_torch" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_right_barrels_x, top_right_barrels_y, top_right_barrels_width, top_right_barrels_height) },
            string { "top_right_barrels" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_right_barrels_mid_x, top_right_barrels_mid_y, top_right_barrels_mid_width, top_right_barrels_mid_height) },
            string { "top_right_barrels_mid" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_right_barrels_bot_x, top_right_barrels_bot_y, top_right_barrels_bot_width, top_right_barrels_bot_height) },
            string { "top_right_barrels_bot" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_barrel_and_torch_x, top_barrel_and_torch_y, top_barrel_and_torch_width, top_barrel_and_torch_height) },
            string { "top_barrel_and_torch" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_chests_and_torch_x, top_chests_and_torch_y, top_chests_and_torch_width, top_chests_and_torch_height) },
            string { "top_chests_and_torch" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_left_barrels_x, top_left_barrels_y, top_left_barrels_width, top_left_barrels_height) },
            string { "top_left_barrels" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_left_torch_x, top_left_torch_y, top_left_torch_width, top_left_torch_height) },
            string { "top_left_torch" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_left_barrels_bot_x, top_left_barrels_bot_y, top_left_barrels_bot_width, top_left_barrels_bot_height) },
            string { "top_left_barrels_bottom" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_center_bottom_barrels_x, top_center_bottom_barrels_y, top_center_bottom_barrels_width, top_center_bottom_barrels_height) },
            string { "top_center_bottom_barrels" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_left_center_barrel_x, top_left_center_barrel_y, top_left_center_barrel_width, top_left_center_barrel_height) },
            string { "top_left_center_barrel" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(top_center_torch_x, top_center_torch_y, top_center_torch_width, top_center_torch_height) },
            string { "top_center_torch" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(south_chest_lava_x, south_chest_lava_y, south_chest_lava_width, south_chest_lava_height) },
            string { "south_chest_lava" }
        }
    }
};

bitmap load_level(bitmap level_bitmap, level_type level_type)
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
        // source_file = "resources/levels/starter_level.dat";
        break;
    case DUNGEON_ONE:
        // source_file = "resources/levels/dungeon_level_one.dat";
        break;
    case DUNGEON_TWO:
        // source_file = "resources/levels/dungeon_level_two.dat";
        break;
    case DUNGEON_THREE:
        // source_file = "resources/levels/dungeon_level_three.dat";
        break;
    case DEMO:
        source_file = "resources/levels/demo_level.dat";
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
        write_line(" x: " + to_string(new_level_objects[i].object_rectangle.x) + " y: " + to_string(new_level_objects[i].object_rectangle.y) + " w: " + to_string(new_level_objects[i].object_rectangle.width) + " h: " + to_string(new_level_objects[i].object_rectangle.height));
    }

    // close the data file when finished
    data_file.close();

    // return the level objects array
    return new_level_objects;
}

vector<object_data> configure_level_objects(vector<object_data> &level_objects, level_type level_type)
{
    // load level bitmap based on level type
    switch (level_type)
    {
    case START:
        // load_level_objects(level_type);
        break;
    case DUNGEON_ONE:
        // load_level_objects(level_type);
        break;
    case DUNGEON_TWO:
        // load_level_objects(level_type);
        break;
    case DUNGEON_THREE:
        // load_level_objects(level_type);
        break;
    case DEMO:
        level_objects = demo_level_objects;
        load_level_objects(level_type);
        break;
    }

    return level_objects;
}