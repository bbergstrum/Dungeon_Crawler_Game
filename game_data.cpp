#include "splashkit.h"
#include "game_data.h"
#include "player.h"
#include "level_data.h"
// #include "enemy.h"

using namespace std;

game_data new_game()
{
    game_data game;

    game.level = new_level();

    game.player = new_player();
     
    //timer
    game.game_timer = create_timer("game_time");

    start_timer("game_time");

    return game;
}

//============================================================================================================

// check sprite collisions - should look something like this eventually
void check_collisions(vector<object_data> &objects, player_data &player)
{
    // create a collisoin vector of all active objects 
    for(int i = 0; i < objects.size(); i++)
    {
        if( sprite_rectangle_collision(player.player_sprite, objects[i].object_rectangle) )
        {
            // reverse movement.
            switch(player.player_direction)
            {
                case UP:
                    sprite_set_dy(player.player_sprite, 0);
                    sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) + 3));
                    break;
                case LEFT:
                    sprite_set_dx(player.player_sprite, 0);
                    sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) + 3));
                    break;
                case DOWN:
                    sprite_set_dy(player.player_sprite, 0);
                    sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) - 3));
                    break;
                case RIGHT:
                    sprite_set_dx(player.player_sprite, 0);
                    sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) - 3));
                    break;
            }
        }
    }
}

void update_game(game_data &game)
{
    // update player movement
    update_player(game.player);

    // update enemies 

    // check collisions between sprites and objects
    check_collisions(game.level.objects, game.player);
}

void draw_game(const game_data &game)
{
    // Redraw everything
    clear_screen(COLOR_BLACK);

    draw_level(game.level);

    // redraw the player
    draw_player(game.player);

    // redraw enemies

    // refresh the screen
    refresh_screen(60);
}