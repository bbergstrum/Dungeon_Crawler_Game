#ifndef DUNGEON_CRAWLER_ENEMY
#define DUNGEON_CRAWLER_ENEMY

#include "splashkit.h"
#include "level_data.h"
#include "player.h"

#include <vector>

using namespace std;

#define ENEMY_MOVEMENT_SPEED 2
#define PLAYER_BOUNDARY 64
enum enemy_type
{
    SKELETON = 1,
    ORC,
    LIZARD_BOSS
};

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
    enemy_type enemy_type;
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
 * 
 * @param enemy_type    The type of enemy to create
 * @param pos_x         The spawn position x
 * @param pos_y         The spawn position y
 */
enemy_data new_enemy(const enemy_type, const int &pos_x, const int &pos_y);

/**
* Draws the enemy to the screen. 
* 
* @param enemies_to_draw     The enemy to draw to the screen
* @param debug_mode         if debug mode enabled or not
*/
void draw_enemies(const vector<enemy_data> &enemies_to_draw, bool &debug_mode);

/**
 * Actions a step update of the enemy - moving them and adjusting the camera.
 * 
 * @param level_enemies      The vector of enemies to update
 */
void update_enemies(vector<enemy_data> &level_enemies);

/**
 * Read user input and update the enemy based on this interaction.
 * 
 * @param enemy         The enemy to update
 * @param player        The player to detect
 * @param enemy_timer_ticks timer to ensure enemy can only attack every 4 seconds
 */
void handle_enemy_behaviour(enemy_data &enemy, player_data &player);

#endif 