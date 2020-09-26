#ifndef DUNGEON_CRAWLER_PLAYER
#define DUNGEON_CRAWLER_PLAYER

#include "splashkit.h"
#include <vector>

using namespace std;

#define MOVEMENT_SPEED 2


enum direction
{
    UP,
    LEFT,
    DOWN,
    RIGHT
};

struct player_data
{
    sprite player_sprite;
    animation_script animation_script;
    animation player_animation;
    drawing_options draw_options;
    direction player_direction;
    bool is_moving;
    bool is_attacking;
    string current_animation;
    rectangle player_hit_box;
    rectangle atk_hit_box_up;
    rectangle atk_hit_box_left;
    rectangle atk_hit_box_down;
    rectangle atk_hit_box_right;
    int health;
    int attack_power;
};

/**
 * Creates a new player in the centre of the screen.
 * 
 * @returns     The new player data
 */
player_data new_player();

/**
* Draws the player to the screen. 
* 
* @param player_to_draw    The player to draw to the screen
*/
void draw_player(const player_data &player_to_draw);

/**
 * Actions a step update of the player - moving them and adjusting the camera.
 * 
 * @param player      The player being updated
 */
void update_player(player_data &player);

/**
 * Read user input and update the player based on this interaction.
 * 
 * @param player    The player to update
 */
void handle_input(player_data &player);

#endif 