#include "player.h"
#include "game_data.h"
#include "splashkit.h"

using namespace std;

player_data load_sprite_data(player_data &player)
{
    //load player bitmap and define cell details
    bitmap default_bitmap = load_bitmap("PlayerBmp", "player_sprite_sheet.png");
    bitmap_set_cell_details(default_bitmap, 64, 64, 13, 21, 273); // cell width, height, cols, rows, count

    //load animations
    player.animation_script = load_animation_script("player_animation_script", "player_animations.txt");
    player.player_animation = create_animation(player.animation_script, "IdleDown");
    
    //load the player sprite sheet
    player.player_sprite = create_sprite("player", default_bitmap, player.animation_script);

    //load drawing options
    player.draw_options = option_with_animation(player.player_animation);

    sprite_start_animation(player.player_sprite, "IdleDown");

    return player;
}

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

player_data new_player(player_number player_number)
{
    // initialize the player
    player_data player;

    // assign a player number
    player.player_number = player_number;

    // load input keybindings
    load_key_maps(player);

    // load sprite related data
    load_sprite_data(player);

    // set the spawning position of the palyer
    set_player_position(player);

    // set player states
    player.player_direction = DOWN;
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

void update_player(player_data &player)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(player.player_sprite);
    update_animation(player.player_animation);

    // update the player hit boxes as the player moves around
    player.player_hit_box = rectangle_from((sprite_x(player.player_sprite) + 8), (sprite_y(player.player_sprite) + 8), 48, 64);
    player.atk_hit_box_up = rectangle_from((center_point(player.player_sprite).x - 16), (center_point(player.player_sprite).y - 64), 32, 32);
    player.atk_hit_box_left = rectangle_from((center_point(player.player_sprite).x - 80), center_point(player.player_sprite).y, 32, 32);
    player.atk_hit_box_down = rectangle_from((center_point(player.player_sprite).x - 16), (center_point(player.player_sprite).y + 64), 32, 32);
    player.atk_hit_box_right = rectangle_from((center_point(player.player_sprite).x + 48), center_point(player.player_sprite).y, 32, 32);
}

void handle_input(player_data &player, bool &debug_mode)
{
    //when each direction key is pressed, change is_moving and assign a direction 
    if(!player.is_attacking)
    {
        if(key_down(player.player_key_map.up))
        {
            player.is_moving = true;
            player.player_direction = UP;
            sprite_set_dy(player.player_sprite, -MOVEMENT_SPEED);
        }
        else if(key_down(player.player_key_map.left))
        {
            player.is_moving = true;
            player.player_direction = LEFT;
            sprite_set_dx(player.player_sprite, -MOVEMENT_SPEED);
        }
        else if(key_down(player.player_key_map.down))
        {
            player.is_moving = true;
            player.player_direction = DOWN;
            sprite_set_dy(player.player_sprite, MOVEMENT_SPEED);
        }
        else if(key_down(player.player_key_map.right))
        {
            player.is_moving = true;
            player.player_direction = RIGHT;
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
    if(!player.is_attacking && player.is_moving) // npos maximum possible length of string
    {   
        // check the direction they are moving in and apply movement
        switch (player.player_direction)
        {
            case UP:
                if(to_lowercase(player.current_animation) != to_lowercase("WalkUp"))
                {
                    sprite_start_animation(player.player_sprite, "WalkUp");
                    player.current_animation = "WalkUp";
                }
                break;
            case LEFT:
                if(to_lowercase(player.current_animation) != to_lowercase("WalkLeft"))
                {
                    sprite_start_animation(player.player_sprite, "WalkLeft");
                    player.current_animation = "WalkLeft";
                }
                break;
            case DOWN:
                if(to_lowercase(player.current_animation) != to_lowercase("WalkDown"))
                {
                    sprite_start_animation(player.player_sprite, "WalkDown");
                    player.current_animation = "WalkDown";
                }
                break;
            case RIGHT:
                if(to_lowercase(player.current_animation) != to_lowercase("WalkRight"))
                {
                    sprite_start_animation(player.player_sprite, "WalkRight");
                    player.current_animation = "WalkRight";
                }
                break;    
        }
    }  
    
    if(!player.is_attacking && !player.is_moving)  // if the player isn't moving animate idle
    {
        // check the players direction and update the idle animation
        switch (player.player_direction)
        {
            case UP:
                if(to_lowercase(player.current_animation) != to_lowercase("IdleUp"))
                {
                    sprite_start_animation(player.player_sprite, "IdleUp");
                    player.current_animation = "IdleUp";
                }
                break;
            case LEFT:
                if(to_lowercase(player.current_animation) != to_lowercase("IdleLeft"))
                {
                    sprite_start_animation(player.player_sprite, "IdleLeft");
                    player.current_animation = "IdleLeft";
                }
                break;
            case DOWN:
                if(to_lowercase(player.current_animation) != to_lowercase("IdleDown"))
                {
                    sprite_start_animation(player.player_sprite, "IdleDown");
                    player.current_animation = "IdleDown";
                }
                break;
            case RIGHT:
                if(to_lowercase(player.current_animation) != to_lowercase("IdleRight"))
                {
                    sprite_start_animation(player.player_sprite, "IdleRight");
                    player.current_animation = "IdleRight";
                }
                break;    
        }
    }
   
    // when the player attacks, check the direction, animate the attack in that direction
    // drawing rectangles for attack collisions?
    if(key_down(player.player_key_map.attack))
    {
        switch (player.player_direction)      
        {
            case UP:
                if(to_lowercase(player.current_animation) != to_lowercase("AttkUp"))
                {
                    sprite_start_animation(player.player_sprite, "AttkUp");
                    player.current_animation = "AttkUp";
                    player.is_attacking = true;
                }
                break;
            case LEFT:
                if(to_lowercase(player.current_animation) != to_lowercase("AttkLeft"))
                {
                    sprite_start_animation(player.player_sprite, "AttkLeft");
                    player.current_animation = "AttkLeft";
                    player.is_attacking = true;
                }
                break;
            case DOWN:
                if(to_lowercase(player.current_animation) != to_lowercase("AttkDown"))
                {
                    sprite_start_animation(player.player_sprite, "AttkDown");
                    player.current_animation = "AttkDown";
                    player.is_attacking = true;
                }
                break;
            case RIGHT:
                if(to_lowercase(player.current_animation) != to_lowercase("AttkRight"))
                {
                    sprite_start_animation(player.player_sprite, "AttkRight");
                    player.current_animation = "AttkRight";
                    player.is_attacking = true;
                }
                break;    
        }
    }
    else
    {
        player.is_attacking = false;
    }

    // if(key_typed(F1_KEY))
    // {
    //     if(debug_mode)
    //     {
    //         debug_mode = false;
    //         write_line("DEBUG MODE OFF");
    //     }
    //     else
    //     {
    //         debug_mode = true;
    //         write_line("DEBUG MODE ON");
    //     }
    // }

    if(key_typed(F1_KEY)) debug_mode = false;
    if(key_typed(F2_KEY)) debug_mode = true;
}