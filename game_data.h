#ifndef DUNGEON_CRAWLER_GAME_DATA
#define DUNGEON_CRAWLER_GAME_DATA

#include "splashkit.h"
#include "level_data.h"
#include "player.h"
#include "enemy.h"

using namespace std;

struct game_data 
{
    player_data player_one;
    player_data player_two;

    timer game_timer;

    bool debug_mode;

    level_data level;
};

// /**
//  * Checks if a player collides with an object
//  * 
//  * @param objects the vector of objects to check rectangle collisions on
//  * @param player  the sprite to check rectangle collisons on
//  */
// void check_player_collisions(const vector<object_data> &objects, player_data &player);

// /**
//  * Checks if a enemy collides with an object
//  * 
//  * @param objects the vector of objects to check rectangle collisions on
//  * @param level_enemies  the vector of enemies to check rectangle collisons on
//  */
// void check_enemy_collisions(const vector<object_data> &objects, vector<enemy_data> &level_enemies);

/**
 * Checks if a players attack hits another sprite
 * 
 * @param attacking_player the player performing the attack
 * @param defending_player the player defending the attack
 */
void hit_collision(player_data &attacking_player, player_data &defending_player);
   
/**
 * Creates a new game with game data.
 * 
 * @returns     The new game to play
 */
game_data new_game();

/**
 * Creates a new game with game data.
 * 
 * @param game_to_update    The game to update 
 */
void update_game(game_data &game);

/**
 * Creates a new game with game data.
 * 
 * @param game_to_draw    The game to draw to the screen 
 */
void draw_game(game_data &game_to_draw);

#endif