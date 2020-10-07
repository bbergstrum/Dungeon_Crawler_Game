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

    enemy_data enemy;

    vector<event_trigger> event_triggers;

    timer game_timer;

    bool debug_mode;

    level_data level;
};

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
void update_game(game_data &game_to_update);

/**
 * Creates a new game with game data.
 * 
 * @param game_to_draw    The game to draw to the screen 
 */
void draw_game(game_data &game_to_draw);

#endif