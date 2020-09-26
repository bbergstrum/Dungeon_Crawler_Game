#ifndef DUNGEON_CRAWLER_GAME_DATA
#define DUNGEON_CRAWLER_GAME_DATA

#include "player.h"
// #include "enemy.h"
#include "level_data.h"
#include "splashkit.h"

#define DEBUG_MODE true

using namespace std;

struct game_data 
{
    player_data player_one;
    player_data player_two;

    timer game_timer;

    level_data level;
};

/**
 * Checks if a players attack hits another sprite
 * 
 * @param player the player performing the attack
 */
void hit_collision(const player_data &player);

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
void draw_game(const game_data &game_to_draw);

#endif