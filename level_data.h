#ifndef DUNGEON_CRAWLER_LEVEL_DATA
#define DUNGEON_CRAWLER_LEVEL_DATA

#include "player.h"
#include "enemy.h"
#include "game_data.h"
#include "splashkit.h"

using namespace std;

// structured something like this eventually
struct level_data
{
    int level_id;
    string level_name;
    bitmap level_bitmap;
    // vector<enemy_data> enemies;
    vector<player_data> players;
    vector<vector<int>> collisions;
};

level_data create_level(game_data game);


#endif