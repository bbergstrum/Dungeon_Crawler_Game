#include "splashkit.h"
#include "game_data.h"
#include "player.h"
#include "level_data.h"
#include "level_designs.h"

using namespace std;

game_data new_game()
{
    // initialize a new game
    game_data game;

    // set game debug mode to false intially
    game.debug_mode = false;

    game.level = load_level(DEMO);

    game.player_one = new_player(ONE);
    game.player_two = new_player(TWO);
     
    // set the game timer and start it
    game.game_timer = create_timer("game_time");
    start_timer("game_time");

    return game;
}

//============================================================================================================
void apply_damage(player_data &attacking_player, player_data &defending_player)
{
    // write to the console the attack hit
    write_line("Player " + std::to_string(attacking_player.player_number) + " hit Player " + std::to_string(defending_player.player_number) + "!");
    
    // pop off one of the hearts
    if(defending_player.hearts.size() != 0) // remove 1 heart if there are hearts to remove
    {
        defending_player.hearts.pop_back();
    }
    // write to the console the defending players remaining hearts
    write_line("Player " + std::to_string(attacking_player.player_number) + " remaining hearts: " + std::to_string(defending_player.hearts.size()));
}

void hit_collision(player_data &attacking_player, player_data &defending_player)
{
    // check if the attacking player is making an attack
    if(attacking_player.is_attacking)
    {
        // check the attacking players direction to determine where to hit check
        switch(attacking_player.player_direction)
        {
            case UP:
                // write to the console attacking player performed an attack up
                write_line("Player " + std::to_string(attacking_player.player_number) + " attacked up.");

                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_up))
                {
                    apply_damage(attacking_player, defending_player);
                };
                break;
            case LEFT:
                // write to the console attacking player performed an attack left
                write_line("Player " + std::to_string(attacking_player.player_number) + " attacked left.");

                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_left))
                {
                    apply_damage(attacking_player, defending_player);
                };
                break;
            case DOWN:
                // write to the console attacking player performed an attack down
                write_line("Player " + std::to_string(attacking_player.player_number) + " attacked down.");

                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_down))
                {
                    apply_damage(attacking_player, defending_player);
                };
                break;
            case RIGHT:
                // write to the console attacking player performed an attack right
                write_line("Player " + std::to_string(attacking_player.player_number) + " attacked right.");

                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_right))
                {
                    apply_damage(attacking_player, defending_player);
                };
                break;
        }
    }
};

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
                    sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) + 2));
                    break;
                case LEFT:
                    sprite_set_dx(player.player_sprite, 0);
                    sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) + 2));
                    break;
                case DOWN:
                    sprite_set_dy(player.player_sprite, 0);
                    sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) - 2));
                    break;
                case RIGHT:
                    sprite_set_dx(player.player_sprite, 0);
                    sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) - 2));
                    break;
            }
        }
    }
}

void update_game(game_data &game)
{
    // update player movement
    update_player(game.player_one);
    update_player(game.player_two);

    // check collisions between sprites and objects
    check_collisions(game.level.objects, game.player_one);
    check_collisions(game.level.objects, game.player_two);

    // check hit_collisions if a player performs an attack
    hit_collision(game.player_one, game.player_two);
    hit_collision(game.player_two, game.player_one);
}

void draw_player_hearts(player_data &player)
{
    // draw each player heart    
    int player_one_heart_x_location = 240; // initial x location for player one first heart      
    int player_two_heart_x_location = 840; // initial x location for player two first heart     

    if(player.hearts.size() != 0) // check if there are any hearts left to draw 
    {
        for(int i = 0; i < player.hearts.size(); i++)
        {
            if(player.player_number == ONE)
            {
                // concat string for bitmap name using player number and index
                string player_one_heart_name = "player_" + std::to_string(player.player_number) + "_heart_" + std::to_string(i + 1);

                // draw each heart with incremented x location
                draw_bitmap(player_one_heart_name, player_one_heart_x_location, 1288);

                player_one_heart_x_location += 42; // increment x location for next heart
            }
            else
            {
                // concat string for bitmap name using player number and index
                string player_two_heart_name = "player_" + std::to_string(player.player_number) + "_heart_" + std::to_string(i + 1);
                
                // draw each heart with incremented x location
                draw_bitmap(player_two_heart_name, player_two_heart_x_location, 1288);

                player_two_heart_x_location += 42; // increment x location for next heart
            }
        };
    }
}

void draw_hud(player_data &player)
{
    // draw player number
    if(player.player_number == ONE)
    {
        draw_text("PLAYER ONE", COLOR_WHITE, 150, 1300, option_to_screen());
    }
    else
    {
        draw_text("PLAYER TWO", COLOR_WHITE, 750, 1300, option_to_screen());
    }

    draw_player_hearts(player);
}

void draw_game(game_data &game)
{
    // clear screen 
    clear_screen(COLOR_BLACK);

    // redraw the level
    draw_level(game.level, game.debug_mode);

    // redraw both players
    draw_player(game.player_one, game.debug_mode);
    draw_player(game.player_two, game.debug_mode);

    // draw HUD
    draw_hud(game.player_one);
    draw_hud(game.player_two);

    // refresh the screen
    refresh_screen(60);
}