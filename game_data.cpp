#include "splashkit.h"
#include "game_data.h"
#include "level_data.h"
#include "player.h"
#include "enemy.h"

using namespace std;

void setup_attack_timers(game_data &game)
{
    // create attack timers for both players
    game.player_one_attack_timer = create_timer("player_one");
    game.player_two_attack_timer = create_timer("player_one");

    // start player timers
    start_timer("player_one");
    start_timer("player_two");

    // create attack timers for every enemy in the level
    for(int i = 0; i < game.level.level_enemies.size(); i++)
    {
        timer new_enemy_timer;
        string enemy_timer_name = "enemy_" + to_string(i + 1); 
        new_enemy_timer = create_timer(enemy_timer_name);

        game.enemy_attack_timers.push_back(new_enemy_timer);
    }

    // start attack timers for every enemy in the level
    for(int i = 0; i < game.enemy_attack_timers.size(); i++)
    {
        string enemy_timer_name = "enemy_" + to_string(i + 1); 
        start_timer(enemy_timer_name);
    }
}

// create a new game to start 
game_data new_game()
{
    // initialize a new game
    game_data game;

    // set game debug mode to false intially
    game.debug_mode = false;

    // game.level = load_level(DEMO);
    game.level = load_level(START);

    game.player_one = new_player(ONE, 540, 1130);
    game.player_two = new_player(TWO, 600, 1130);

    // setup game attack timers for each sprite
    setup_attack_timers(game);

    return game;
}

// apply damage to a defending player 
void apply_damage(player_data &defending_sprite)
{
    // pop off one of the hearts
    if(defending_sprite.hearts.size() != 0) // remove 1 heart if there are hearts to remove
    {
        defending_sprite.hearts.pop_back();
    }
}

// apply damage from an attacking players attack to
void apply_damage(player_data &attacking_player, enemy_data &enemy)
{
    // remove 1 health from the enemy
    enemy.health = enemy.health - 1;

    // log some more stuff to the console later eg. combat text
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
                    apply_damage(defending_player);
                };
                break;
            case PLAYER_LEFT:
                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_left))
                {
                    apply_damage(defending_player);
                };
                break;
            case PLAYER_DOWN:
                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_down))
                {
                    apply_damage(defending_player);
                };
                break;
            case PLAYER_RIGHT:
                if(sprite_rectangle_collision(defending_player.player_sprite, attacking_player.atk_hit_box_right))
                {
                    apply_damage(defending_player);
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

// confirm that an attacking players attack hit an enemy
void hit_collision(player_data &attacking_player, vector<enemy_data> &level_enemies)
{
    for(int i = 0; i < level_enemies.size(); i++)
    {
        // check if the attacking player is making an attack
        if(attacking_player.is_attacking)
        {
            // check the attacking players direction to determine where to hit check
            switch(attacking_player.player_direction)
            {
                case PLAYER_UP:
                    if(sprite_rectangle_collision(level_enemies[i].enemy_sprite, attacking_player.atk_hit_box_up))
                    {
                        apply_damage(attacking_player, level_enemies[i]);
                    };
                    break;
                case PLAYER_LEFT:
                    if(sprite_rectangle_collision(level_enemies[i].enemy_sprite, attacking_player.atk_hit_box_left))
                    {
                        apply_damage(attacking_player, level_enemies[i]);
                    };
                    break;
                case PLAYER_DOWN:
                    if(sprite_rectangle_collision(level_enemies[i].enemy_sprite, attacking_player.atk_hit_box_down))
                    {
                        apply_damage(attacking_player, level_enemies[i]);
                    };
                    break;
                case PLAYER_RIGHT:
                    if(sprite_rectangle_collision(level_enemies[i].enemy_sprite, attacking_player.atk_hit_box_right))
                    {
                        apply_damage(attacking_player, level_enemies[i]);
                    };
                    break;
            }
        }

        //check if an attack hit kills the enemy
        if(level_enemies[i].health == 0)
        {
            // stop all movement
            sprite_set_dx(level_enemies[i].enemy_sprite, 0);
            sprite_set_dy(level_enemies[i].enemy_sprite, 0);

            if(level_enemies[i].current_animation != level_enemies[i].enemy_animations.death)
            {

                level_enemies[i].current_animation = level_enemies[i].enemy_animations.death;
                sprite_start_animation(level_enemies[i].enemy_sprite, "death");
            }
        }
    }
};

// check player collisions - TODO: fix known bug with collision logic switch statement
void check_player_collisions(const vector<object_data> &objects, player_data &player)
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
                    sprite_set_dy(player.player_sprite, 0);
                    sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) + 2));
                    break;
                case PLAYER_LEFT:
                    sprite_set_dx(player.player_sprite, 0);
                    sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) + 2));
                    break;
                case PLAYER_DOWN:
                    sprite_set_dy(player.player_sprite,  0);
                    sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) - 2));
                    break;
                case PLAYER_RIGHT:
                    sprite_set_dx(player.player_sprite, 0);
                    sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) - 2));
                    break;
            }
        }
    }
}

// check enemy collisions - TODO: fix known bug with collision logic switch statement
void check_enemy_collisions(const vector<object_data> &objects, vector<enemy_data> &level_enemies)
{
    for(int j = 0; j < level_enemies.size(); j++)
    {
        // create a collisoin vector of all active objects 
        for(int i = 0; i < objects.size() - 2; i++) // we do not count the last two objects as they are event triggers
        {
            if( sprite_rectangle_collision(level_enemies[j].enemy_sprite, objects[i].object_rectangle) )
            {
                // reverse movement.
                switch(level_enemies[j].enemy_direction)
                {
                    case ENEMY_UP:
                        sprite_set_dy(level_enemies[j].enemy_sprite, 0);
                        sprite_set_y(level_enemies[j].enemy_sprite, (sprite_y(level_enemies[j].enemy_sprite) + 2));
                        break;
                    case ENEMY_LEFT:
                        sprite_set_dx(level_enemies[j].enemy_sprite, 0);
                        sprite_set_x(level_enemies[j].enemy_sprite, (sprite_x(level_enemies[j].enemy_sprite) + 2));
                        break;
                    case ENEMY_DOWN:
                        sprite_set_dy(level_enemies[j].enemy_sprite,  0);
                        sprite_set_y(level_enemies[j].enemy_sprite, (sprite_y(level_enemies[j].enemy_sprite) - 2));
                        break;
                    case ENEMY_RIGHT:
                        sprite_set_dx(level_enemies[j].enemy_sprite, 0);
                        sprite_set_x(level_enemies[j].enemy_sprite, (sprite_x(level_enemies[j].enemy_sprite) - 2));
                        break;
                }
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
                set_player_position(game.player_one, 114, 124);
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
            // load the next level - dungeon level two
            if(trigger_type == NEXT)
            {
                game.level = load_level(FINAL);
                set_player_position(game.player_one, 600, 1116);
            }
            else 
            // load the previous level - starter level
            {
                game.level = load_level(DUNGEON_ONE);
                set_player_position(game.player_one, 992, 114);
            }  
            break;
        case FINAL:
            if(trigger_type == PREV)
            {
                game.level = load_level(DUNGEON_TWO);
                set_player_position(game.player_one, 606, 698);
            }
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
    update_enemies(game.level.level_enemies);

    // check collisions between sprites and objects
    check_player_collisions(game.level.objects, game.player_one);
    check_player_collisions(game.level.objects, game.player_two);
    check_enemy_collisions(game.level.objects, game.level.level_enemies);

    // check hit_collisions if a player performs an attack
    hit_collision(game.player_one, game.player_two);
    hit_collision(game.player_two, game.player_one);
    hit_collision(game.player_one, game.level.level_enemies);

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
    draw_enemies(game.level.level_enemies, game.debug_mode);

    // draw HUD
    draw_hud(game.player_one);
    draw_hud(game.player_two);

    // refresh the screen
    refresh_screen(60);
}