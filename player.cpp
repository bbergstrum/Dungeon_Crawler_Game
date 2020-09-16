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
    if(player.is_moving)
    {   
        // check the direction they are moving in and apply movement
        switch (player.player_direction)
        {
            case UP:
                sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) - 2));
                assign_animation(player.player_animation, "WalkUp");
                // sprite_start_animation(player.player_sprite, "WalkUp");
                break;
            case LEFT:
                sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) - 2));
                assign_animation(player.player_animation, "WalkLeft");
                // sprite_start_animation(player.player_sprite, "WalkLeft");
                break;
            case DOWN:
                sprite_set_y(player.player_sprite, (sprite_y(player.player_sprite) + 2));
                assign_animation(player.player_animation, "WalkDown");
                // sprite_start_animation(player.player_sprite, "WalkDown");
                break;
            case RIGHT:
                sprite_set_x(player.player_sprite, (sprite_x(player.player_sprite) + 2));
                assign_animation(player.player_animation, "WalkRight");
                // sprite_start_animation(player.player_sprite, "WalkRight");
                break;    
        }
    } 
    else // if the player isn't moving animate idle
    {
        // check the players direction and update the idle animation
        switch (player.player_direction)
        {
            case UP:
                assign_animation(player.player_animation, "IdleUp");
                // sprite_start_animation(player.player_sprite, "IdleUp");
                break;
            case LEFT:
                assign_animation(player.player_animation, "IdleLeft");
                // sprite_start_animation(player.player_sprite, "IdleLeft");
                break;
            case DOWN:
                assign_animation(player.player_animation, "IdleDown");
                // sprite_start_animation(player.player_sprite, "IdleDown");
                break;
            case RIGHT:
                assign_animation(player.player_animation, "IdleRight");
                // sprite_start_animation(player.player_sprite, "IdleRight");
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
                assign_animation(player.player_animation, "AttkUp");
                // sprite_start_animation(player.player_sprite, "AttkUp");
                break;
            case LEFT:
                assign_animation(player.player_animation, "AttkLeft");
                // sprite_start_animation(player.player_sprite, "AttkLeft");
                break;
            case DOWN:
                assign_animation(player.player_animation, "AttkDown");
                // sprite_start_animation(player.player_sprite, "AttkDown");
                break;
            case RIGHT:
                assign_animation(player.player_animation, "AttkRight");
                // sprite_start_animation(player.player_sprite, "AttkRight");
                break;    
        }
    }
}