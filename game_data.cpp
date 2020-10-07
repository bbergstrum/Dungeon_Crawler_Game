#include "splashkit.h"
#include "game_data.h"
#include "level_data.h"
#include "player.h"
#include "enemy.h"

using namespace std;

// create a new game to start 
game_data new_game()
{
    // initialize a new game
    game_data game;

    // set game debug mode to false intially
    game.debug_mode = false;

    // game.level = load_level(DEMO);
    game.level = load_level(START);

    game.player_one = new_player(ONE, 575, 1130);
    game.player_two = new_player(TWO, 575, 1130);

    game.enemy = new_enemy();

    // set the game timer and start it
    game.game_timer = create_timer("game_time");
    start_timer("game_time");

    return game;
}

// check an attacking players attack against a defending player if in range
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

// confirm that an attacking players attack hit another player
void hit_collision(player_data &attacking_player, player_data &defending_player)
{
    // check if the attacking player is making an attack
    if(attacking_player.is_attacking)
    {
        // check the attacking players direction to determine where to hit check
        switch(attacking_player.player_direction)
        {
            case PLAYER_UP:
                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_up))
                {
                    apply_damage(attacking_player, defending_player);
                };
                break;
            case PLAYER_LEFT:
                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_left))
                {
                    apply_damage(attacking_player, defending_player);
                };
                break;
            case PLAYER_DOWN:
                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_down))
                {
                    apply_damage(attacking_player, defending_player);
                };
                break;
            case PLAYER_RIGHT:
                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_right))
                {
                    apply_damage(attacking_player, defending_player);
                };
                break;
        }
    }

    //check if an attack hit kills the defending player
    if(defending_player.hearts.size() ==0)
    {
        if(defending_player.current_animation != defending_player.player_animations.death)
        {
            defending_player.current_animation = defending_player.player_animations.death;
            sprite_start_animation(defending_player.player_sprite, "death");
        }
    }
};

// check sprite collisions - TODO: fix known bug with collision logic switch statement
void check_collisions(vector<object_data> &objects, player_data &player)
{
    // create a collisoin vector of all active objects 
    for(int i = 0; i < objects.size() - 2; i++) // we do not count the last two objects as they are event triggers
    {
        if( sprite_rectangle_collision(player.player_sprite, objects[i].object_rectangle) )
        {
            // reverse movement.
            switch(player.player_direction)
            {
                case PLAYER_UP:
                    sprite_set_dy(player.player_sprite, - 2);
                    sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) + 2));
                    break;
                case PLAYER_LEFT:
                    sprite_set_dx(player.player_sprite, - 2);
                    sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) + 2));
                    break;
                case PLAYER_DOWN:
                    sprite_set_dy(player.player_sprite,  - 2);
                    sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) - 2));
                    break;
                case PLAYER_RIGHT:
                    sprite_set_dx(player.player_sprite, - 2);
                    sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) - 2));
                    break;
            }
        }
    }
}

void change_level(game_data &game, trigger_type trigger_type)
{
    // check the level type of the current level
    switch (game.level.type)
    {
        case START:
            // load the next level - dungeon level one
            if(trigger_type == NEXT)
            {
                game.level = load_level(DUNGEON_ONE);
                set_player_position(game.player_one, 550, 1070);
            }
            // start level has no previous level
            break;
        case DUNGEON_ONE:
            // load the next level - dungeon level two
            if(trigger_type == NEXT)
            {
                game.level = load_level(DUNGEON_TWO);
                set_player_position(game.player_one, 550, 1070);
            }
            else 
            // load the previous level - starter level
            {
                game.level = load_level(START);
                // set the player at the entrance of the cave
                set_player_position(game.player_one, 546, 218);
            }         
            break;
        case DUNGEON_TWO:

            break;
        case DUNGEON_THREE:

            break;
        case DEMO: // demo has no triggers
            break;
    };
}

void check_event_triggers(game_data &game)
{
    // check if event triggered by player collision
    for(int i = 0; i < game.level.event_triggers.size(); i++)
    {
        // check for player one collisions 
        if(sprite_rectangle_collision(game.player_one.player_sprite, game.level.event_triggers[i].location))
        {  
            // check the trigger type of the event trigger to determine which level to load
            if(game.level.event_triggers[i].type == 1)
            {   
                // change level to the next level in the sequence
                change_level(game, NEXT);
            }
            else if(game.level.event_triggers[i].type == 2)
            {
                // change back to the previous level in the sequence
                change_level(game, PREV);
            }
        }
    }
}

// update all aspects of the game: the players, any colisions, any hit checks
void update_game(game_data &game)
{
    // update player movement
    update_player(game.player_one);
    update_player(game.player_two);

    // update the enemy
    update_enemy(game.enemy);

    // check collisions between sprites and objects
    check_collisions(game.level.objects, game.player_one);
    check_collisions(game.level.objects, game.player_two);

    // check hit_collisions if a player performs an attack
    hit_collision(game.player_one, game.player_two);
    hit_collision(game.player_two, game.player_one);

    // check if any events were triggered by the player
    check_event_triggers(game);
}

// draw each of the players hearts from their respective array of hearts
void draw_player_hearts(player_data &player)
{
    // draw each player heart    
    int player_one_heart_x_location = 190; // initial x location for player one first heart      
    int player_two_heart_x_location = 940; // initial x location for player two first heart     

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

// draw basic HUD information regarding both players and state of the game
void draw_hud(player_data &player)
{
    // draw player number
    if(player.player_number == ONE)
    {
        draw_text("PLAYER ONE", COLOR_WHITE, 100, 1300, option_to_screen());
    }
    else
    {
        draw_text("PLAYER TWO", COLOR_WHITE, 850, 1300, option_to_screen());
    }

    draw_player_hearts(player);

    if(player.player_number == ONE && player.hearts.size() == 0) draw_text("PLAYER TWO WINS!", COLOR_WHITE, 500, 1300, option_to_screen());
    if(player.player_number == TWO && player.hearts.size() == 0) draw_text("PLAYER ONE WINS!", COLOR_WHITE, 500, 1300, option_to_screen());
}

// draw the game to the screen with all relevent entities
void draw_game(game_data &game)
{
    // clear screen 
    clear_screen(COLOR_BLACK);

    // redraw the level
    draw_level(game.level, game.debug_mode);

    // redraw both players
    draw_player(game.player_one, game.debug_mode);
    draw_player(game.player_two, game.debug_mode);

    // draw enemy
    draw_enemy(game.enemy, game.debug_mode);

    // draw HUD
    draw_hud(game.player_one);
    draw_hud(game.player_two);

    // refresh the screen
    refresh_screen(60);
}