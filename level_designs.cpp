#include "level_data.h"
#include "level_designs.h"
#include "game_data.h"
#include "splashkit.h"

// ====================================== DEMO LEVEL =============================================

double level_height = 1210;
double level_width = 1210;
double min_x = 0;
double min_y = 0;

double boundary_x = 1185;
double boundary_y = 1185;
double side_boundary_wall_width = 25;
double top_boundary_wall_height = 50;

double stairs_wall_y = 458;
double stairs_left_wall_width = 122;
double stairs_right_wall_width = 52;
double stairs_wall_height = 136;
double west_stairs_right_wall_x = 266;
double center_wall_x = 266;
double center_wall_y = 532;
double center_wall_width = 678;
double center_wall_height = 62;
double east_stairs_left_wall_x = 892;
double east_stairs_right_wall_x = 1088;

double west_torch_lg_x = 326;
double west_torch_sml_x = 396;
double east_torch_lg_x = 860;
double east_torch_sml_x = 784;
double torch_lg_y = 402;
double torch_sml_y = 578;
double torch_sml_width = 30;
double torch_sml_height = 80;
double torch_lg_width = 25;
double torch_lg_height = 125;

double north_lava_lg_x = 740;
double north_lava_lg_y = 50;
double north_lava_lg_width = 172;
double north_lava_lg_height = 182;
double north_east_lava_sml_x = 1065;
double north_east_lava_sml_y = 50;
double lava_sml_width = 52;
double lava_sml_height = 45;
double north_west_lava_sml_x = 246;
double north_west_lava_sml_y = 196;
double lava_xsml_width = 38;
double lava_xsml_height = 44;

double south_east_lava_sml_x = 1062;
double south_east_lava_sml_y = 1020;
double south_center_lava_sml_x = 580;
double south_center_lava_sml_y = 628;
double south_center_lava_sml_width = 50;
double south_center_lava_sml_height = 50;
double south_west_lava_lg_x = 348;
double south_west_lava_lg_y = 876;
double south_west_lava_lg_width = 174;
double south_west_lava_lg_height = 128;
double south_west_lava_vertical_x = 395;
double south_west_lava_vertical_y = 1000;
double south_west_lava_vetical_width = 80;
double south_west_lava_vetical_height = 186;
double south_west_lava_horizontal_x = 25;
double south_west_lava_horizontal_y = 1074;
double south_west_lava_horizontal_width = 110;
double south_west_lava_horizontal_height = 115;

vector<object_data> demo_level_objects = 
{
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
            rectangle { rectangle_from(min_x, boundary_y, level_width, side_boundary_wall_width) },
            string { "bottom_boundary_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(boundary_x, min_y, side_boundary_wall_width, level_height) },
            string { "right_boundary_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(min_x, stairs_wall_y, stairs_left_wall_width, stairs_wall_height) },
            string { "west_stairs_left_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(west_stairs_right_wall_x, stairs_wall_y, stairs_right_wall_width, stairs_wall_height) },
            string { "west_stairs_right_wall" }
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
            rectangle { rectangle_from(east_stairs_left_wall_x, stairs_wall_y, stairs_right_wall_width, stairs_wall_height) },
            string { "east_stairs_left_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(east_stairs_right_wall_x, stairs_wall_y, stairs_left_wall_width, stairs_wall_height) },
            string { "east_stairs_right_wall" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(west_torch_lg_x, torch_lg_y, torch_lg_width, torch_lg_height) },
            string { "west_torch_large" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(west_torch_sml_x, torch_sml_y, torch_sml_width, torch_sml_height) },
            string { "west_torch_small" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(east_torch_lg_x, torch_lg_y, torch_lg_width, torch_lg_height) },
            string { "east_torch_large" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(east_torch_sml_x, torch_sml_y, torch_sml_width, torch_sml_height) },
            string { "east_torch_small" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(north_lava_lg_x, north_lava_lg_y, north_lava_lg_width, north_lava_lg_height) },
            string { "north_laval_large" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(north_east_lava_sml_x, north_east_lava_sml_y, lava_sml_width, lava_sml_height) },
            string { "north_east_lava_sml" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(north_west_lava_sml_x, north_west_lava_sml_y, lava_xsml_width, lava_xsml_height) },
            string { "north_west_lava_sml" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(south_west_lava_lg_x, south_west_lava_lg_y, south_west_lava_lg_width, south_west_lava_lg_height) },
            string { "south_west_lava_large" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(south_west_lava_vertical_x, south_west_lava_vertical_y, south_west_lava_vetical_width, south_west_lava_vetical_height) },
            string { "south_west_lava_vertical" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(south_west_lava_horizontal_x, south_west_lava_horizontal_y, south_west_lava_horizontal_width, south_west_lava_horizontal_height) },
            string { "south_west_lava_horizontal" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(south_center_lava_sml_x, south_center_lava_sml_y, south_center_lava_sml_width, south_center_lava_sml_height) },
            string { "south_center_lava_sml" }
        }
    },
    {
        object_data {
            rectangle { rectangle_from(south_east_lava_sml_x, south_east_lava_sml_y, lava_sml_width, lava_sml_height) },
            string { "south_west_lava_small" }
        }
    },

};

// ====================================== DEMO LEVEL END =========================================

// ====================================== STARTER LEVEL ==========================================

// ====================================== STARTER LEVEL END ======================================

vector<object_data> load_objects(vector<object_data> &level_objects, level_type level_type)
{
    switch (level_type)
    {
    case START:
        break;
    case DUNGEON_ONE:
        break;
    case DUNGEON_TWO:
        break;
    case DUNGEON_THREE:
        break;
    case DEMO:
        level_objects = demo_level_objects;
        break;
    }

    return level_objects;
}