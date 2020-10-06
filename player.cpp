#include "player.h"
#include "game_data.h"
#include "splashkit.h"

using namespace std;

// load all requires player animations and the respective drawing options
player_data create_animations(player_data &player)
{
    // load animations for idling
    player.player_animations.idle_left      = create_animation(player.animation_script, "IdleLeft");
    player.player_animations.idle_up        = create_animation(player.animation_script, "IdleUp");
    player.player_animations.idle_down      = create_animation(player.animation_script, "IdleDown");
    player.player_animations.idle_right     = create_animation(player.animation_script, "IdleRight");
    // load animations for walking
    player.player_animations.walk_up        = create_animation(player.animation_script, "WalkUp");
    player.player_animations.walk_left      = create_animation(player.animation_script, "WalkLeft");
    player.player_animations.walk_down      = create_animation(player.animation_script, "WalkDown");
    player.player_animations.walk_right     = create_animation(player.animation_script, "WalkRight");

    // load animations for attacking
    player.player_animations.attack_up      = create_animation(player.animation_script, "AttkUp");
    player.player_animations.attack_left    = create_animation(player.animation_script, "AttkLeft");
    player.player_animations.attack_down    = create_animation(player.animation_script, "AttkDown");
    player.player_animations.attack_right   = create_animation(player.animation_script, "AttkRight");

    // load animation for dying
    player.player_animations.death          = create_animation(player.animation_script, "Death");

    // create drawing options for idling animations
    player.draw_options.idle_left      = option_with_animation(player.player_animations.idle_up);
    player.draw_options.idle_up        = option_with_animation(player.player_animations.idle_left);
    player.draw_options.idle_down      = option_with_animation(player.player_animations.idle_down);
    player.draw_options.idle_right     = option_with_animation(player.player_animations.idle_right);

    // create drawing options for walking animations
    player.draw_options.walk_up        = option_with_animation(player.player_animations.walk_up);
    player.draw_options.walk_left      = option_with_animation(player.player_animations.walk_left);
    player.draw_options.walk_down      = option_with_animation(player.player_animations.walk_down);
    player.draw_options.walk_right     = option_with_animation(player.player_animations.walk_right);

    // create drawing options for attacking animations
    player.draw_options.attack_up      = option_with_animation(player.player_animations.attack_up);
    player.draw_options.attack_left    = option_with_animation(player.player_animations.attack_left);
    player.draw_options.attack_down    = option_with_animation(player.player_animations.attack_down);
    player.draw_options.attack_right   = option_with_animation(player.player_animations.attack_right);

    // create drawing options for death animation
    player.draw_options.death = option_with_animation(player.player_animations.death);

    return player;
}

// create the player sprite 
player_data create_player_sprite(player_data &player)
{
    //load player bitmap and define cell details

    bitmap player_one_bitmap = load_bitmap("player_one_bitmap", "player_one_sprite_sheet.png");
    bitmap_set_cell_details(player_one_bitmap, 64, 64, 13, 21, 273); // cell width, height, cols, rows, count

    bitmap player_two_bitmap = load_bitmap("player_two_bitmap", "player_two_sprite_sheet.png");
    bitmap_set_cell_details(player_two_bitmap, 64, 64, 13, 21, 273); // cell width, height, cols, rows, count

    // load animation script 
    player.animation_script = load_animation_script("player_animation_script", "player_animations.txt");

    // create animations for the player from the animation script
    create_animations(player);
    
    // create the sprite
    if(player.player_number == ONE)
    {
        player.player_sprite = create_sprite("player_one", player_one_bitmap, player.animation_script);
    }
    else 
    {
        player.player_sprite = create_sprite("player_two", player_two_bitmap, player.animation_script);
    }

    // begin with a default animation
    sprite_start_animation(player.player_sprite, "IdleDown");

    return player;
}

// load a set of key maps based on player number
player_data load_key_maps(player_data &player)
{
    // set different keybinds for player one and player two
    if(player.player_number == ONE)
    {
        player.player_key_map.up = UP_KEY;
        player.player_key_map.left = LEFT_KEY;
        player.player_key_map.down = DOWN_KEY;
        player.player_key_map.right = RIGHT_KEY;
        player.player_key_map.attack = RIGHT_CTRL_KEY;
    }
    else
    {
        player.player_key_map.up = W_KEY;
        player.player_key_map.left = A_KEY;
        player.player_key_map.down = S_KEY;
        player.player_key_map.right = D_KEY;
        player.player_key_map.attack = SPACE_KEY;
    }

    return player;
};

// spawn the players in their respective locations
player_data set_player_position(player_data &player)
{
    //set position x and y
    sprite_set_dx(player.player_sprite, 0);
    sprite_set_dy(player.player_sprite, 0);    

    // position the players on either end of the level
    if(player.player_number == ONE)
    {
        sprite_set_x(player.player_sprite, 190);
        sprite_set_y(player.player_sprite, 285);
    }
    else 
    {
        sprite_set_x(player.player_sprite, 960);
        sprite_set_y(player.player_sprite, 285);
    }

    return player;
}

// create a new player 
player_data new_player(player_number player_number)
{
    // initialize the player
    player_data player;

    // assign a player number
    player.player_number = player_number;

    // load input keybindings
    load_key_maps(player);

    // load sprite related data
    create_player_sprite(player);

    // set the spawning position of the palyer
    set_player_position(player);

    // set player states
    player.player_direction = PLAYER_DOWN;
    player.is_moving = false;
    player.is_attacking = false;

    // set player health
    for(int i = 0; i < 4; i++)
    {
        // concat string for bitmap name using player number and index
        string player_heart_name = "player_" + std::to_string(player.player_number) + "_heart_" + std::to_string(i + 1);
        // bitmap file
        player.hearts.push_back(load_bitmap(player_heart_name, "heart_small.png"));
    }

    return player;
}

// draw a player to the screen
void draw_player(const player_data &player_to_draw, bool &debug_mode)
{
    draw_sprite(player_to_draw.player_sprite);

    // draw visible hitboxes if debug mode enabled
    if(debug_mode)
    {
        draw_rectangle(COLOR_GREEN, player_to_draw.player_hit_box);
        draw_rectangle(COLOR_RED, player_to_draw.atk_hit_box_up);
        draw_rectangle(COLOR_RED, player_to_draw.atk_hit_box_left);
        draw_rectangle(COLOR_RED, player_to_draw.atk_hit_box_down);
        draw_rectangle(COLOR_RED, player_to_draw.atk_hit_box_right);
    };
}

// move hitboxes as the player moves
void update_hit_boxes(player_data &player)
{
    player.player_hit_box = rectangle_from((sprite_x(player.player_sprite) + 8), (sprite_y(player.player_sprite) + 8), 48, 64);
    player.atk_hit_box_up = rectangle_from((center_point(player.player_sprite).x - 16), (center_point(player.player_sprite).y - 64), 32, 32);
    player.atk_hit_box_left = rectangle_from((center_point(player.player_sprite).x - 80), center_point(player.player_sprite).y, 32, 32);
    player.atk_hit_box_down = rectangle_from((center_point(player.player_sprite).x - 16), (center_point(player.player_sprite).y + 64), 32, 32);
    player.atk_hit_box_right = rectangle_from((center_point(player.player_sprite).x + 48), center_point(player.player_sprite).y, 32, 32);
}

// update the players movement, their animations and their hitboxes
void update_player(player_data &player)
{
    // Apply movement based on rotation and velocity in the sprite
    // only update if the update wouldn't cause a collisison...
    update_sprite(player.player_sprite);
    update_animation(player.current_animation);
    
    // update the player hit boxes as the player moves around
    update_hit_boxes(player);
}

// handle player input based on player actions
void handle_input(player_data &player, bool &debug_mode)
{
    // disable input if player is dead
    if(player.hearts.size() != 0)
    {
            //when each direction key is pressed, change is_moving and assign a direction 
        if(!player.is_attacking)
        {
            if(key_down(player.player_key_map.up))
            {
                // 
                player.is_moving = true;
                player.player_direction = PLAYER_UP;
                sprite_set_dy(player.player_sprite, -MOVEMENT_SPEED);
            }
            else if(key_down(player.player_key_map.left))
            {
                player.is_moving = true;
                player.player_direction = PLAYER_LEFT;
                sprite_set_dx(player.player_sprite, -MOVEMENT_SPEED);
            }
            else if(key_down(player.player_key_map.down))
            {
                player.is_moving = true;
                player.player_direction = PLAYER_DOWN;
                sprite_set_dy(player.player_sprite, MOVEMENT_SPEED);
            }
            else if(key_down(player.player_key_map.right))
            {
                player.is_moving = true;
                player.player_direction = PLAYER_RIGHT;
                sprite_set_dx(player.player_sprite, MOVEMENT_SPEED);
            }
        }

        // when the user releases the movement keys set is_moving to false again
        if (key_released(player.player_key_map.up))
        {
            player.is_moving = false;
            sprite_set_dx(player.player_sprite, 0);
            sprite_set_dy(player.player_sprite, 0);
        }
        else if (key_released(player.player_key_map.left))
        {
            player.is_moving = false;
            sprite_set_dx(player.player_sprite, 0);
            sprite_set_dy(player.player_sprite, 0);
        }
        else if (key_released(player.player_key_map.down))
        {
            player.is_moving = false;
            sprite_set_dx(player.player_sprite, 0);
            sprite_set_dy(player.player_sprite, 0);
        }
        else if (key_released(player.player_key_map.right))
        {
            player.is_moving = false;
            sprite_set_dx(player.player_sprite, 0);
            sprite_set_dy(player.player_sprite, 0);
        }
        
        // check if the player is moving to assign animations and movement
        if(!player.is_attacking && player.is_moving ) 
        {   
            // check the direction they are moving in and apply movement
            switch (player.player_direction)
            {
                case PLAYER_UP:
                    // check if walking up animation is not already being animated
                    if(player.current_animation !=  player.player_animations.walk_up)
                    {
                        player.current_animation = player.player_animations.walk_up;
                        sprite_start_animation(player.player_sprite, "WalkUp");
                    }
                    break;
                case PLAYER_LEFT:
                    // check if walking left animation is not already being animated
                    if(player.current_animation != player.player_animations.walk_left)
                    {
                        player.current_animation = player.player_animations.walk_left;
                        sprite_start_animation(player.player_sprite, "WalkLeft");
                    }
                    break;
                case PLAYER_DOWN:
                    // check if walking down animation is not already being animated
                    if(player.current_animation != player.player_animations.walk_down)
                    {
                        player.current_animation = player.player_animations.walk_down;
                        sprite_start_animation(player.player_sprite, "WalkDown");
                        
                    }
                    break;
                case PLAYER_RIGHT:
                    // check if walking right animation is not already being animated
                    if(player.current_animation != player.player_animations.walk_right)
                    {
                        player.current_animation = player.player_animations.walk_right;
                        sprite_start_animation(player.player_sprite, "WalkRight");
                    }
                    break;    
            }
        }  
        
        if(!player.is_attacking && !player.is_moving)  // if the player isn't moving animate idle
        {
            // check the players direction and update the idle animation
            switch (player.player_direction)
            {
                case PLAYER_UP:
                    // check if idle up animation is not already being animated
                    if(player.current_animation != player.player_animations.idle_up)
                    {
                        player.current_animation = player.player_animations.idle_up;
                        sprite_start_animation(player.player_sprite, "IdleUp");
                    }
                    break;
                case PLAYER_LEFT:
                    // check if idle left animation is not already being animated
                    if(player.current_animation != player.player_animations.idle_left)
                    {
                        player.current_animation = player.player_animations.idle_left;
                        sprite_start_animation(player.player_sprite, "IdleLeft");
                    }
                    break;
                case PLAYER_DOWN:
                    // check if idle down animation is not already being animated
                    if(player.current_animation != player.player_animations.idle_down)
                    {
                        player.current_animation = player.player_animations.idle_down;
                        sprite_start_animation(player.player_sprite, "IdleDown");
                    }
                    break;
                case PLAYER_RIGHT:
                    // check if idle right animation is not already being animated
                    if(player.current_animation != player.player_animations.idle_right)
                    {
                        player.current_animation = player.player_animations.idle_right;
                        sprite_start_animation(player.player_sprite, "IdleRight");
                    }
                    break;    
            }
        }    

        // when the player attacks, check the direction, animate the attack in that direction
        if(key_typed(player.player_key_map.attack))
        {
            player.is_attacking = true;

            switch (player.player_direction)      
            {
                case PLAYER_UP:
                    // check if attack up animation is not already being animated
                    if(player.current_animation != player.player_animations.attack_up)
                    {
                        player.current_animation = player.player_animations.attack_up;
                        sprite_start_animation(player.player_sprite, "AttkUp");
                        player.is_attacking = true;
                    }
                    break;
                case PLAYER_LEFT:
                    // check if attack left animation is not already being animated
                    if(player.current_animation != player.player_animations.attack_left)
                    {
                        player.current_animation = player.player_animations.attack_left;
                        sprite_start_animation(player.player_sprite, "AttkLeft");
                        player.is_attacking = true;
                    }
                    break;
                case PLAYER_DOWN:
                    // check if attack down animation is not already being animated
                    if(player.current_animation != player.player_animations.attack_down)
                    {
                        player.current_animation = player.player_animations.attack_down;
                        sprite_start_animation(player.player_sprite, "AttkDown");
                        player.is_attacking = true;
                    }
                    break;
                case PLAYER_RIGHT:
                    // check if attack right animation is not already being animated
                    if(player.current_animation != player.player_animations.attack_right)
                    {
                        player.current_animation = player.player_animations.attack_right;
                        sprite_start_animation(player.player_sprite, "AttkRight");
                        player.is_attacking = true;                        
                    }
                    break;    
            }
        } else 
        {
            if (animation_ended(player.current_animation))
            {
                write_line("Animation Ended");
                player.is_attacking = false;
            }
        }

        // if(debug_mode)
        // {
        //     write_line(animation_current_cell(player.current_animation));
        //     write_line(animation_name(player.current_animation));
        // }
    }
    
    // debug mode key bind
    if(key_typed(F1_KEY)) debug_mode = false;
    if(key_typed(F2_KEY)) debug_mode = true;
}