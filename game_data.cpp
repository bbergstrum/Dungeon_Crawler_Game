#include "splashkit.h"
#include "game_data.h"
// #include "level_data.h"
#include "player.h"
// #include "enemy.h"

using namespace std;

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

game_data new_game()
{
    game_data game;

    game.player = new_player();
     
    //timer
    game.game_timer = create_timer("game_time");

    start_timer("game_time");

    return game;
}

//============================================================================================================

// check sprite collisions - should look something like this eventually
// void check_collisions(vector<enemy_data> enemies, player_data &player)
// {
        // create a collisoin vector of all active objects 
        // rectangle r = rectangle_from(50, 50, 50, 50);

        // sprite_rectangle_collision(player.player_sprite, r);

        // sprite_collision_circle - maybe, circle collisions are taxing
        
        // add a rectangle for attacking collisions 

// }

void update_game(game_data &game)
{
    // update player movement
    update_player(game.player);

    // update enemies 

    // check collisions between sprites and rectangles
}

void draw_game(const game_data &game)
{
    // Redraw everything
    clear_screen(COLOR_BLACK);

    // redraw the player
    draw_player(game.player);

    // redraw enemies

    // refresh the screen
    refresh_screen(60);
}