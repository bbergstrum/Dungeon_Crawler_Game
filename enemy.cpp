#include "splashkit.h"
#include "level_data.h"
#include "player.h"
#include "enemy.h"

using namespace std;

// TODO: Make create_animations more dynamic for both enemys and enemies
// load all requires enemy animations and the respective drawing options
enemy_data create_animations(enemy_data &enemy)
{
    // load animations for idling
    enemy.enemy_animations.idle_left      = create_animation(enemy.animation_script, "IdleLeft");
    enemy.enemy_animations.idle_up        = create_animation(enemy.animation_script, "IdleUp");
    enemy.enemy_animations.idle_down      = create_animation(enemy.animation_script, "IdleDown");
    enemy.enemy_animations.idle_right     = create_animation(enemy.animation_script, "IdleRight");
    // load animations for walking
    enemy.enemy_animations.walk_up        = create_animation(enemy.animation_script, "WalkUp");
    enemy.enemy_animations.walk_left      = create_animation(enemy.animation_script, "WalkLeft");
    enemy.enemy_animations.walk_down      = create_animation(enemy.animation_script, "WalkDown");
    enemy.enemy_animations.walk_right     = create_animation(enemy.animation_script, "WalkRight");

    // load animations for attacking
    enemy.enemy_animations.attack_up      = create_animation(enemy.animation_script, "AttkUp");
    enemy.enemy_animations.attack_left    = create_animation(enemy.animation_script, "AttkLeft");
    enemy.enemy_animations.attack_down    = create_animation(enemy.animation_script, "AttkDown");
    enemy.enemy_animations.attack_right   = create_animation(enemy.animation_script, "AttkRight");

    // load animation for dying
    enemy.enemy_animations.death          = create_animation(enemy.animation_script, "Death");

    // create drawing options for idling animations
    enemy.draw_options.idle_left      = option_with_animation(enemy.enemy_animations.idle_up);
    enemy.draw_options.idle_up        = option_with_animation(enemy.enemy_animations.idle_left);
    enemy.draw_options.idle_down      = option_with_animation(enemy.enemy_animations.idle_down);
    enemy.draw_options.idle_right     = option_with_animation(enemy.enemy_animations.idle_right);

    // create drawing options for walking animations
    enemy.draw_options.walk_up        = option_with_animation(enemy.enemy_animations.walk_up);
    enemy.draw_options.walk_left      = option_with_animation(enemy.enemy_animations.walk_left);
    enemy.draw_options.walk_down      = option_with_animation(enemy.enemy_animations.walk_down);
    enemy.draw_options.walk_right     = option_with_animation(enemy.enemy_animations.walk_right);

    // create drawing options for attacking animations
    enemy.draw_options.attack_up      = option_with_animation(enemy.enemy_animations.attack_up);
    enemy.draw_options.attack_left    = option_with_animation(enemy.enemy_animations.attack_left);
    enemy.draw_options.attack_down    = option_with_animation(enemy.enemy_animations.attack_down);
    enemy.draw_options.attack_right   = option_with_animation(enemy.enemy_animations.attack_right);

    // create drawing options for death animation
    enemy.draw_options.death = option_with_animation(enemy.enemy_animations.death);

    return enemy;
}

// create the enemy sprite 
enemy_data create_enemy_sprite(enemy_data &enemy, const enemy_type &enemy_type)
{
    //load enemy bitmap 
    bitmap enemy_bitmap;

    switch (enemy.enemy_type)
    {
    case SKELETON:
        enemy_bitmap = load_bitmap("skeleton_bmp", "skeleton_enemy_sprite_sheet.png");
        break;
    case ORC:
        enemy_bitmap = load_bitmap("orc_bmp", "orc_enemy_sprite_sheet.png");
        break;
    case LIZARD_BOSS:
        enemy_bitmap = load_bitmap("lizard_bmp", "boss_enemy_sprite_sheet.png");
        break;
    }

    // set bitmap cell details
    bitmap_set_cell_details(enemy_bitmap, 64, 64, 13, 21, 273); // cell width, height, cols, rows, count

    // load animation script 
    enemy.animation_script = load_animation_script("enemy_animation_script", "enemy_animations.txt");

    // create animations for the enemy from the animation script
    create_animations(enemy);
    
    // create the sprite
    enemy.enemy_sprite = create_sprite("enemy", enemy_bitmap, enemy.animation_script);

    // begin with a default animation
    sprite_start_animation(enemy.enemy_sprite, "IdleDown");

    return enemy;
}

// spawn the enemys in their respective locations
enemy_data set_enemy_position(enemy_data &enemy, const int &pos_x, const int &pos_y)
{
    // set velocity x and y
    sprite_set_dx(enemy.enemy_sprite, 0);
    sprite_set_dy(enemy.enemy_sprite, 0);    

    // set position of enemy
    sprite_set_x(enemy.enemy_sprite, pos_x);
    sprite_set_y(enemy.enemy_sprite, pos_y);

    return enemy;
}

// create a new enemy 
enemy_data new_enemy(const enemy_type enemy_type, const int &pos_x, const int &pos_y)
{
    // initialize the enemy
    enemy_data enemy;

    enemy.enemy_type = enemy_type;

    // load sprite related data
    create_enemy_sprite(enemy, enemy.enemy_type);

    // set the spawning position of the palyer
    set_enemy_position(enemy, pos_x, pos_y);

    // set enemy states
    enemy.enemy_direction = ENEMY_DOWN;
    enemy.is_moving = false;
    enemy.is_attacking = false;

    // set enemy vision
    enemy.enemy_sight = rectangle_from((center_point(enemy.enemy_sprite).x - 128), (center_point(enemy.enemy_sprite).y - 128) , 256, 256);
    
    // set enemy health
    enemy.health = 4;

    return enemy;
}

// draw a enemy to the screen
void draw_enemies(const vector<enemy_data> &enemies_to_draw, bool &debug_mode)
{
    // draw every enemy's sprite to the screen
    for(int i = 0; i < enemies_to_draw.size(); i++)
    {
        draw_sprite(enemies_to_draw[i].enemy_sprite);
        
        // draw visible hitboxes if debug mode enabled
        if(debug_mode)
        {
            draw_rectangle(COLOR_RED, enemies_to_draw[i].enemy_sight);
            draw_rectangle(COLOR_GREEN, enemies_to_draw[i].enemy_hit_box);
            draw_rectangle(COLOR_RED, enemies_to_draw[i].atk_hit_box_up);
            draw_rectangle(COLOR_RED, enemies_to_draw[i].atk_hit_box_left);
            draw_rectangle(COLOR_RED, enemies_to_draw[i].atk_hit_box_down);
            draw_rectangle(COLOR_RED, enemies_to_draw[i].atk_hit_box_right);
        };
    }
}

// move hitboxes as the enemy moves
void update_hit_boxes(enemy_data &enemy)
{
    // update and move the enemy sight as the enemy moves
    enemy.enemy_sight = rectangle_from((center_point(enemy.enemy_sprite).x - 128), (center_point(enemy.enemy_sprite).y - 128) , 256, 256);

    // update and move the hit boxes of the enemy as the enemy moves
    enemy.enemy_hit_box = rectangle_from((sprite_x(enemy.enemy_sprite) + 8), (sprite_y(enemy.enemy_sprite) + 8), 48, 64);
    enemy.atk_hit_box_up = rectangle_from((center_point(enemy.enemy_sprite).x - 16), (center_point(enemy.enemy_sprite).y - 64), 32, 32);
    enemy.atk_hit_box_left = rectangle_from((center_point(enemy.enemy_sprite).x - 80), center_point(enemy.enemy_sprite).y, 32, 32);
    enemy.atk_hit_box_down = rectangle_from((center_point(enemy.enemy_sprite).x - 16), (center_point(enemy.enemy_sprite).y + 64), 32, 32);
    enemy.atk_hit_box_right = rectangle_from((center_point(enemy.enemy_sprite).x + 48), center_point(enemy.enemy_sprite).y, 32, 32);
}

// update the enemys movement, their animations and their hitboxes
void update_enemy(enemy_data &enemy)
{
    // Apply movement based on rotation and velocity in the sprite
    // only update if the update wouldn't cause a collisison...
    update_sprite(enemy.enemy_sprite);
    update_animation(enemy.current_animation);
    
    // update the enemy hit boxes as the enemy moves around
    update_hit_boxes(enemy);
}

void update_enemies(vector<enemy_data> level_enemies)
{
    // iterate over all the levels enemies and update them
    for(int i = 0; i < level_enemies.size(); i++)
    {
        update_enemy(level_enemies[i]);
    }
}

// handle enemy input based on enemy actions
void handle_enemy_behaviour(enemy_data &enemy, player_data &player)
{
    // disable input if enemy is dead
    if(enemy.health > 1)
    {
        // check for sprite_collision with a player - sight
        if(sprite_rectangle_collision(player.player_sprite, enemy.enemy_sight) && !enemy.is_attacking)
        {
            // movement logic
            // move towards player and animate
            enemy.is_moving = true; // this is sense - you could record as "can see player"
            
            // retrieve the x and y of the enemy
            point_2d enemy_location = sprite_position(enemy.enemy_sprite);
 
            // retrieve the x and y of the player
            point_2d player_location = sprite_position(player.player_sprite);
 
            // if enemy is located further east of the player
            if(enemy_location.x > player_location.x + PLAYER_BOUNDARY)
            {
                sprite_set_dx(enemy.enemy_sprite, -ENEMY_MOVEMENT_SPEED);
                enemy.enemy_direction = ENEMY_LEFT;
            }
            // if enemy is located further west of the player
              else if (enemy_location.x < player_location.x - PLAYER_BOUNDARY)
            {
                sprite_set_dx(enemy.enemy_sprite, ENEMY_MOVEMENT_SPEED);
                enemy.enemy_direction = ENEMY_RIGHT;
            }
          
            // if enemy is located further south of the player
            if(enemy_location.y > player_location.y + PLAYER_BOUNDARY)
            {
                sprite_set_dy(enemy.enemy_sprite, -ENEMY_MOVEMENT_SPEED);
                enemy.enemy_direction = ENEMY_UP;
            }
            // if enemy is located further north of the player
              else if (enemy_location.y < player_location.y - PLAYER_BOUNDARY)
            {
                sprite_set_dy(enemy.enemy_sprite, ENEMY_MOVEMENT_SPEED);
                enemy.enemy_direction = ENEMY_DOWN;
            }
        }
        else 
        {
            enemy.is_moving = false;
            sprite_set_dx(enemy.enemy_sprite, 0);
            sprite_set_dy(enemy.enemy_sprite, 0);
        }    
        
        // walking animations
        if(!enemy.is_attacking && enemy.is_moving )
        {
            switch (enemy.enemy_direction)
            {
                case ENEMY_UP:
                    // check if walking up animation is not already being animated
                    if(enemy.current_animation !=  enemy.enemy_animations.walk_up)
                    {
                        enemy.current_animation = enemy.enemy_animations.walk_up;
                        sprite_start_animation(enemy.enemy_sprite, "WalkUp");
                    }
                    break;
                case ENEMY_LEFT:
                    // check if walking left animation is not already being animated
                    if(enemy.current_animation != enemy.enemy_animations.walk_left)
                    {
                        enemy.current_animation = enemy.enemy_animations.walk_left;
                        sprite_start_animation(enemy.enemy_sprite, "WalkLeft");
                    }
                    break;
                case ENEMY_DOWN:
                    // check if walking down animation is not already being animated
                    if(enemy.current_animation != enemy.enemy_animations.walk_down)
                    {
                        enemy.current_animation = enemy.enemy_animations.walk_down;
                        sprite_start_animation(enemy.enemy_sprite, "WalkDown");
                        
                    }
                    break;
                case ENEMY_RIGHT:
                    // check if walking right animation is not already being animated
                    if(enemy.current_animation != enemy.enemy_animations.walk_right)
                    {
                        enemy.current_animation = enemy.enemy_animations.walk_right;
                        sprite_start_animation(enemy.enemy_sprite, "WalkRight");
                    }
                    break; 
            }
        }
        
        // idle animations
        if(!enemy.is_attacking && !enemy.is_moving)  // if the enemy isn't moving animate idle
        {
            // check the enemys direction and update the idle animation
            switch (enemy.enemy_direction)
            {
                case ENEMY_UP:
                    // check if idle up animation is not already being animated
                    if(enemy.current_animation != enemy.enemy_animations.idle_up)
                    {
                        enemy.current_animation = enemy.enemy_animations.idle_up;
                        sprite_start_animation(enemy.enemy_sprite, "IdleUp");
                    }
                    break;
                case ENEMY_LEFT:
                    // check if idle left animation is not already being animated
                    if(enemy.current_animation != enemy.enemy_animations.idle_left)
                    {
                        enemy.current_animation = enemy.enemy_animations.idle_left;
                        sprite_start_animation(enemy.enemy_sprite, "IdleLeft");
                    }
                    break;
                case ENEMY_DOWN:
                    // check if idle down animation is not already being animated
                    if(enemy.current_animation != enemy.enemy_animations.idle_down)
                    {
                        enemy.current_animation = enemy.enemy_animations.idle_down;
                        sprite_start_animation(enemy.enemy_sprite, "IdleDown");
                    }
                    break;
                case ENEMY_RIGHT:
                    // check if idle right animation is not already being animated
                    if(enemy.current_animation != enemy.enemy_animations.idle_right)
                    {
                        enemy.current_animation = enemy.enemy_animations.idle_right;
                        sprite_start_animation(enemy.enemy_sprite, "IdleRight");
                    }
                    break;    
            }
        }

        // attacking logic
        // if(sprite_position(enemy.enemy_sprite).x == sprite_position(enemy.enemy_sprite).x + PLAYER_BOUNDARY);
        // if(sprite_position(enemy.enemy_sprite).x == sprite_position(enemy.enemy_sprite).x - PLAYER_BOUNDARY);
        // if(sprite_position(enemy.enemy_sprite).y == sprite_position(enemy.enemy_sprite).y + PLAYER_BOUNDARY);
        // if(sprite_position(enemy.enemy_sprite).y == sprite_position(enemy.enemy_sprite).y - PLAYER_BOUNDARY);

        // if(sprite_position(enemy.enemy_sprite).x - (sprite_position(player.player_sprite).x + PLAYER_BOUNDARY) == 0);
        // if(sprite_position(enemy.enemy_sprite).y - (sprite_position(player.player_sprite).y + PLAYER_BOUNDARY) == 0);

    }
}