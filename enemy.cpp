// #include "enemy.h"
// #include "game_data.h"
// #include "splashkit.h"

// using namespace std;

// // TODO: Make create_animations more dynamic for both enemys and enemies
// // load all requires enemy animations and the respective drawing options
// enemy_data create_animations(enemy_data &enemy)
// {
//     // load animations for idling
//     enemy.enemy_animations.idle_left      = create_animation(enemy.animation_script, "IdleLeft");
//     enemy.enemy_animations.idle_up        = create_animation(enemy.animation_script, "IdleUp");
//     enemy.enemy_animations.idle_down      = create_animation(enemy.animation_script, "IdleDown");
//     enemy.enemy_animations.idle_right     = create_animation(enemy.animation_script, "IdleRight");
//     // load animations for walking
//     enemy.enemy_animations.walk_up        = create_animation(enemy.animation_script, "WalkUp");
//     enemy.enemy_animations.walk_left      = create_animation(enemy.animation_script, "WalkLeft");
//     enemy.enemy_animations.walk_down      = create_animation(enemy.animation_script, "WalkDown");
//     enemy.enemy_animations.walk_right     = create_animation(enemy.animation_script, "WalkRight");

//     // load animations for attacking
//     enemy.enemy_animations.attack_up      = create_animation(enemy.animation_script, "AttkUp");
//     enemy.enemy_animations.attack_left    = create_animation(enemy.animation_script, "AttkLeft");
//     enemy.enemy_animations.attack_down    = create_animation(enemy.animation_script, "AttkDown");
//     enemy.enemy_animations.attack_right   = create_animation(enemy.animation_script, "AttkRight");

//     // load animation for dying
//     enemy.enemy_animations.death          = create_animation(enemy.animation_script, "Death");

//     // create drawing options for idling animations
//     enemy.draw_options.idle_left      = option_with_animation(enemy.enemy_animations.idle_up);
//     enemy.draw_options.idle_up        = option_with_animation(enemy.enemy_animations.idle_left);
//     enemy.draw_options.idle_down      = option_with_animation(enemy.enemy_animations.idle_down);
//     enemy.draw_options.idle_right     = option_with_animation(enemy.enemy_animations.idle_right);

//     // create drawing options for walking animations
//     enemy.draw_options.walk_up        = option_with_animation(enemy.enemy_animations.walk_up);
//     enemy.draw_options.walk_left      = option_with_animation(enemy.enemy_animations.walk_left);
//     enemy.draw_options.walk_down      = option_with_animation(enemy.enemy_animations.walk_down);
//     enemy.draw_options.walk_right     = option_with_animation(enemy.enemy_animations.walk_right);

//     // create drawing options for attacking animations
//     enemy.draw_options.attack_up      = option_with_animation(enemy.enemy_animations.attack_up);
//     enemy.draw_options.attack_left    = option_with_animation(enemy.enemy_animations.attack_left);
//     enemy.draw_options.attack_down    = option_with_animation(enemy.enemy_animations.attack_down);
//     enemy.draw_options.attack_right   = option_with_animation(enemy.enemy_animations.attack_right);

//     // create drawing options for death animation
//     enemy.draw_options.death = option_with_animation(enemy.enemy_animations.death);

//     return enemy;
// }

// // create the enemy sprite 
// enemy_data create_enemy_sprite(enemy_data &enemy)
// {
//     //load enemy bitmap and define cell details
//     bitmap default_bitmap = load_bitmap("enemyBmp", "skeleton_enemy_sprite_sheet.png");
//     bitmap_set_cell_details(default_bitmap, 64, 64, 13, 21, 273); // cell width, height, cols, rows, count

//     // load animation script 
//     enemy.animation_script = load_animation_script("enemy_animation_script", "enemy_animations.txt");

//     // create animations for the enemy from the animation script
//     create_animations(enemy);
    
//     // create the sprite
//     enemy.enemy_sprite = create_sprite("enemy", default_bitmap, enemy.animation_script);

//     // begin with a default animation
//     sprite_start_animation(enemy.enemy_sprite, "IdleDown");

//     return enemy;
// }

// // spawn the enemys in their respective locations
// enemy_data set_enemy_position(enemy_data &enemy)
// {
//     //set position x and y
//     sprite_set_dx(enemy.enemy_sprite, 0);
//     sprite_set_dy(enemy.enemy_sprite, 0);    

//     // position the enemys on either end of the level

//     return enemy;
// }

// // create a new enemy 
// enemy_data new_enemy()
// {
//     // initialize the enemy
//     enemy_data enemy;

//     // load sprite related data
//     create_enemy_sprite(enemy);

//     // set the spawning position of the palyer
//     set_enemy_position(enemy);

//     // set enemy states
//     enemy.enemy_direction = DOWN;
//     enemy.is_moving = false;
//     enemy.is_attacking = false;

//     // set enemy health

//     return enemy;
// }

// // draw a enemy to the screen
// void draw_enemy(const enemy_data &enemy_to_draw, bool &debug_mode)
// {
//     draw_sprite(enemy_to_draw.enemy_sprite);

//     // draw visible hitboxes if debug mode enabled
//     if(debug_mode)
//     {
//         draw_rectangle(COLOR_GREEN, enemy_to_draw.enemy_hit_box);
//         draw_rectangle(COLOR_RED, enemy_to_draw.atk_hit_box_up);
//         draw_rectangle(COLOR_RED, enemy_to_draw.atk_hit_box_left);
//         draw_rectangle(COLOR_RED, enemy_to_draw.atk_hit_box_down);
//         draw_rectangle(COLOR_RED, enemy_to_draw.atk_hit_box_right);
//     };
// }

// // move hitboxes as the enemy moves
// void update_hit_boxes(enemy_data &enemy)
// {
//     enemy.enemy_hit_box = rectangle_from((sprite_x(enemy.enemy_sprite) + 8), (sprite_y(enemy.enemy_sprite) + 8), 48, 64);
//     enemy.atk_hit_box_up = rectangle_from((center_point(enemy.enemy_sprite).x - 16), (center_point(enemy.enemy_sprite).y - 64), 32, 32);
//     enemy.atk_hit_box_left = rectangle_from((center_point(enemy.enemy_sprite).x - 80), center_point(enemy.enemy_sprite).y, 32, 32);
//     enemy.atk_hit_box_down = rectangle_from((center_point(enemy.enemy_sprite).x - 16), (center_point(enemy.enemy_sprite).y + 64), 32, 32);
//     enemy.atk_hit_box_right = rectangle_from((center_point(enemy.enemy_sprite).x + 48), center_point(enemy.enemy_sprite).y, 32, 32);
// }

// // update the enemys movement, their animations and their hitboxes
// void update_enemy(enemy_data &enemy)
// {
//     // Apply movement based on rotation and velocity in the sprite
//     // only update if the update wouldn't cause a collisison...
//     update_sprite(enemy.enemy_sprite);
//     update_animation(enemy.current_animation);
    
//     // update the enemy hit boxes as the enemy moves around
//     update_hit_boxes(enemy);
// }

// // handle enemy input based on enemy actions
// void handle_enemy_animations(enemy_data &enemy, bool &debug_mode)
// {
//     // disable input if enemy is dead
//     if(enemy.hearts.size() != 0)
//     {
//             //when each direction key is pressed, change is_moving and assign a direction 
//         if(!enemy.is_attacking)
//         {
//             if(key_down(enemy.enemy_key_map.up))
//             {
//                 // 
//                 enemy.is_moving = true;
//                 enemy.enemy_direction = UP;
//                 sprite_set_dy(enemy.enemy_sprite, -MOVEMENT_SPEED);
//             }
//             else if(key_down(enemy.enemy_key_map.left))
//             {
//                 enemy.is_moving = true;
//                 enemy.enemy_direction = LEFT;
//                 sprite_set_dx(enemy.enemy_sprite, -MOVEMENT_SPEED);
//             }
//             else if(key_down(enemy.enemy_key_map.down))
//             {
//                 enemy.is_moving = true;
//                 enemy.enemy_direction = DOWN;
//                 sprite_set_dy(enemy.enemy_sprite, MOVEMENT_SPEED);
//             }
//             else if(key_down(enemy.enemy_key_map.right))
//             {
//                 enemy.is_moving = true;
//                 enemy.enemy_direction = RIGHT;
//                 sprite_set_dx(enemy.enemy_sprite, MOVEMENT_SPEED);
//             }
//         }

//         // when the user releases the movement keys set is_moving to false again
//         if (key_released(enemy.enemy_key_map.up))
//         {
//             enemy.is_moving = false;
//             sprite_set_dx(enemy.enemy_sprite, 0);
//             sprite_set_dy(enemy.enemy_sprite, 0);
//         }
//         else if (key_released(enemy.enemy_key_map.left))
//         {
//             enemy.is_moving = false;
//             sprite_set_dx(enemy.enemy_sprite, 0);
//             sprite_set_dy(enemy.enemy_sprite, 0);
//         }
//         else if (key_released(enemy.enemy_key_map.down))
//         {
//             enemy.is_moving = false;
//             sprite_set_dx(enemy.enemy_sprite, 0);
//             sprite_set_dy(enemy.enemy_sprite, 0);
//         }
//         else if (key_released(enemy.enemy_key_map.right))
//         {
//             enemy.is_moving = false;
//             sprite_set_dx(enemy.enemy_sprite, 0);
//             sprite_set_dy(enemy.enemy_sprite, 0);
//         }
        
//         // check if the enemy is moving to assign animations and movement
//         if(!enemy.is_attacking && enemy.is_moving ) // npos maximum possible length of string
//         {   
//             // check the direction they are moving in and apply movement
//             switch (enemy.enemy_direction)
//             {
//                 case UP:
//                     // check if walking up animation is not already being animated
//                     if(enemy.current_animation !=  enemy.enemy_animations.walk_up)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.walk_up;
//                         sprite_start_animation(enemy.enemy_sprite, "WalkUp");
//                     }
//                     break;
//                 case LEFT:
//                     // check if walking left animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.walk_left)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.walk_left;
//                         sprite_start_animation(enemy.enemy_sprite, "WalkLeft");
//                     }
//                     break;
//                 case DOWN:
//                     // check if walking down animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.walk_down)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.walk_down;
//                         sprite_start_animation(enemy.enemy_sprite, "WalkDown");
                        
//                     }
//                     break;
//                 case RIGHT:
//                     // check if walking right animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.walk_right)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.walk_right;
//                         sprite_start_animation(enemy.enemy_sprite, "WalkRight");
//                     }
//                     break;    
//             }
//         }  
        
//         if(!enemy.is_attacking && !enemy.is_moving)  // if the enemy isn't moving animate idle
//         {
//             // check the enemys direction and update the idle animation
//             switch (enemy.enemy_direction)
//             {
//                 case UP:
//                     // check if idle up animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.idle_up)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.idle_up;
//                         sprite_start_animation(enemy.enemy_sprite, "IdleUp");
//                     }
//                     break;
//                 case LEFT:
//                     // check if idle left animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.idle_left)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.idle_left;
//                         sprite_start_animation(enemy.enemy_sprite, "IdleLeft");
//                     }
//                     break;
//                 case DOWN:
//                     // check if idle down animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.idle_down)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.idle_down;
//                         sprite_start_animation(enemy.enemy_sprite, "IdleDown");
//                     }
//                     break;
//                 case RIGHT:
//                     // check if idle right animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.idle_right)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.idle_right;
//                         sprite_start_animation(enemy.enemy_sprite, "IdleRight");
//                     }
//                     break;    
//             }
//         }    

//         // when the enemy attacks, check the direction, animate the attack in that direction
//         if(key_typed(enemy.enemy_key_map.attack))
//         {
//             enemy.is_attacking = true;

//             switch (enemy.enemy_direction)      
//             {
//                 case UP:
//                     // check if attack up animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.attack_up)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.attack_up;
//                         sprite_start_animation(enemy.enemy_sprite, "AttkUp");
//                         enemy.is_attacking = true;
//                     }
//                     break;
//                 case LEFT:
//                     // check if attack left animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.attack_left)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.attack_left;
//                         sprite_start_animation(enemy.enemy_sprite, "AttkLeft");
//                         enemy.is_attacking = true;
//                     }
//                     break;
//                 case DOWN:
//                     // check if attack down animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.attack_down)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.attack_down;
//                         sprite_start_animation(enemy.enemy_sprite, "AttkDown");
//                         enemy.is_attacking = true;
//                     }
//                     break;
//                 case RIGHT:
//                     // check if attack right animation is not already being animated
//                     if(enemy.current_animation != enemy.enemy_animations.attack_right)
//                     {
//                         enemy.current_animation = enemy.enemy_animations.attack_right;
//                         sprite_start_animation(enemy.enemy_sprite, "AttkRight");
//                         enemy.is_attacking = true;                        
//                     }
//                     break;    
//             }
//         } else 
//         {
//             if (animation_ended(enemy.current_animation))
//             {
//                 write_line("Animation Ended");
//                 enemy.is_attacking = false;
//             }
//         }