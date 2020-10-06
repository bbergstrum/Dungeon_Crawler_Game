#ifndef DUNGEON_CRAWLER_ENEMY
#define DUNGEON_CRAWLER_ENEMY

#include "splashkit.h"
#include "game_data.h"
#include <vector>

using namespace std;

#define MOVEMENT_SPEED 2

enum enemy_direction
{
    ENEMY_UP,
    ENEMY_LEFT,
    ENEMY_DOWN,
    ENEMY_RIGHT
};

struct enemy_animations 
{
    animation idle_up;
    animation idle_left;
    animation idle_down;
    animation idle_right;
    animation walk_up;
    animation walk_left;
    animation walk_down;
    animation walk_right;
    animation attack_up;
    animation attack_left;
    animation attack_down;
    animation attack_right;
    animation death;
};

struct enemy_drawing_options 
{
    drawing_options idle_up;
    drawing_options idle_left;
    drawing_options idle_down;
    drawing_options idle_right;
    drawing_options walk_up;
    drawing_options walk_left;
    drawing_options walk_down;
    drawing_options walk_right;
    drawing_options attack_up;
    drawing_options attack_left;
    drawing_options attack_down;
    drawing_options attack_right;
    drawing_options death;
};

struct enemy_data
{
    sprite enemy_sprite;
    animation_script animation_script;
    enemy_animations enemy_animations;
    enemy_drawing_options draw_options;
    enemy_direction enemy_direction;
    bool is_moving;
    bool is_attacking;
    animation current_animation;
    rectangle enemy_sight;
    rectangle enemy_hit_box;
    rectangle atk_hit_box_up;
    rectangle atk_hit_box_left;
    rectangle atk_hit_box_down;
    rectangle atk_hit_box_right;
    double health;
};

/**
 * Returns a new enemy
 */
enemy_data new_enemy();

/**
* Draws the enemy to the screen. 
* 
* @param enemy_to_draw     The enemy to draw to the screen
* @param debug_mode         if debug mode enabled or not
*/
void draw_enemy(const enemy_data &enemy_to_draw, bool &debug_mode);

/**
 * Actions a step update of the enemy - moving them and adjusting the camera.
 * 
 * @param enemy      The enemy being updated
 */
void update_enemy(enemy_data &enemy);

/**
 * Read user input and update the enemy based on this interaction.
 * 
 * @param enemy         The enemy to update
 * @param player        The player to detect
 */
void handle_enemy_behaviour(enemy_data &enemy, player_data &player);

#endif 