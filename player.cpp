#include "player.h"
#include "splashkit.h"

using namespace std;

player_data new_player()
{
    player_data player;

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

    player.player_direction = DOWN;
    player.is_moving = false;
    sprite_start_animation(player.player_sprite, "IdleDown");

    //set position x and y
    int x_coordinate = screen_width() / 2;
    int y_coordinate = screen_height() / 2;

    // Position in the centre of the initial screen
    sprite_set_x(player.player_sprite, x_coordinate);
    sprite_set_y(player.player_sprite, y_coordinate);

    // store the sprite x & y location
    player.x = sprite_x(player.player_sprite);
    player.y = sprite_y(player.player_sprite);

    return player;
}

void draw_player(const player_data &player_to_draw)
{
    draw_sprite(player_to_draw.player_sprite);
}

void update_player(player_data &player)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(player.player_sprite);
    update_animation(player.player_animation);
}


void handle_input(player_data &player)
{
    // // Get the center of the player - use later for drawing collison rectangles
    // point_2d sprite_center = center_point(player.player_sprite);

    //when each direction key is pressed, change is_moving and assign a direction 
    if(key_down(UP_KEY))
    {
        player.is_moving = true;
        player.player_direction = UP;
    }
    else if(key_down(LEFT_KEY))
    {
        player.is_moving = true;
        player.player_direction = LEFT;
    }
    else if(key_down(DOWN_KEY))
    {
        player.is_moving = true;
        player.player_direction = DOWN;
    }
    else if(key_down(RIGHT_KEY))
    {
        player.is_moving = true;
        player.player_direction = RIGHT;
    }

    // when the user releases the movement keys set is_moving to false again
    if (key_released(UP_KEY))
    {
        player.is_moving = false;
    }
    else if (key_released(LEFT_KEY))
    {
        player.is_moving = false;
    }
    else if (key_released(DOWN_KEY))
    {
        player.is_moving = false;
    }
    else if (key_released(RIGHT_KEY))
    {
        player.is_moving = false;
    }

    // check if the player is moving to assign animations and movement
    if(player.is_moving && player.current_animation.find("Attk"))
    {   
        // check the direction they are moving in and apply movement
        switch (player.player_direction)
        {
            case UP:
                sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) - 2));
                if(to_lowercase(player.current_animation) != to_lowercase("WalkUp"))
                {
                    sprite_start_animation(player.player_sprite, "WalkUp");
                    player.current_animation = "WalkUp";
                }
                break;
            case LEFT:
                sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) - 2));
                if(to_lowercase(player.current_animation) != to_lowercase("WalkLeft"))
                {
                    sprite_start_animation(player.player_sprite, "WalkLeft");
                    player.current_animation = "WalkLeft";
                }
                break;
            case DOWN:
                sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) + 2));
                if(to_lowercase(player.current_animation) != to_lowercase("WalkDown"))
                {
                    sprite_start_animation(player.player_sprite, "WalkDown");
                    player.current_animation = "WalkDown";
                }
                break;
            case RIGHT:
                sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) + 2));
                if(to_lowercase(player.current_animation) != to_lowercase("WalkRight"))
                {
                    sprite_start_animation(player.player_sprite, "WalkRight");
                    player.current_animation = "WalkRight";
                }
                break;    
        }
    }  
    else // if the player isn't moving animate idle
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
    if(key_down(SPACE_KEY))
    {
        switch (player.player_direction)      
        {
            case UP:
                if(to_lowercase(player.current_animation) != to_lowercase("AttkUp"))
                {
                    sprite_start_animation(player.player_sprite, "AttkUp");
                    player.current_animation = "AttkUp";
                }
                break;
            case LEFT:
                if(to_lowercase(player.current_animation) != to_lowercase("AttkLeft"))
                {
                    sprite_start_animation(player.player_sprite, "AttkLeft");
                    player.current_animation = "AttkLeft";
                }
                break;
            case DOWN:
                if(to_lowercase(player.current_animation) != to_lowercase("AttkDown"))
                {
                    sprite_start_animation(player.player_sprite, "AttkDown");
                    player.current_animation = "AttkDown";
                    write_line("DICKS");
                }
                break;
            case RIGHT:
                if(to_lowercase(player.current_animation) != to_lowercase("AttkRight"))
                {
                    sprite_start_animation(player.player_sprite, "AttkRight");
                    player.current_animation = "AttkRight";
                }
                break;    
        }
    }

    write_line(player.current_animation);

    write_line("Current Animation: " + animation_name(player.player_animation));
}