// #include "enemy.h"
// #include "player.h"
// #include "splashkit.h"

// enemy_data new_enemy()
// {
//     // power_up_data result;
//     // power_up_kind kind = static_cast<power_up_kind>(rnd(0, 6));
//     // write_line("Power Up Kind: " + std::to_string(result.kind));

//     // // Create the sprite with 5 layers - we can turn on and off based
//     // // on the power up kind selected
//     // result.power_up_sprite = create_sprite(power_up_bitmap(kind));

//     // sprite_add_layer(result.power_up_sprite, power_up_bitmap(SHIELD), "SHIELD");
//     // sprite_add_layer(result.power_up_sprite, power_up_bitmap(BULLET), "BULLET");
//     // sprite_add_layer(result.power_up_sprite, power_up_bitmap(HEART), "HEART");
//     // sprite_add_layer(result.power_up_sprite, power_up_bitmap(MUSCLE), "MUSCLE");
//     // sprite_add_layer(result.power_up_sprite, power_up_bitmap(DIAMOND), "DIAMOND");

//     // // Default to layer 0 = Fuel so hide others
//     // sprite_hide_layer(result.power_up_sprite, 1);
//     // sprite_hide_layer(result.power_up_sprite, 2);
//     // sprite_hide_layer(result.power_up_sprite, 3);
//     // sprite_hide_layer(result.power_up_sprite, 4);
//     // sprite_hide_layer(result.power_up_sprite, 5);

//     // // Position in the centre of the initial screen
//     // sprite_set_x(result.power_up_sprite, x);
//     // sprite_set_y(result.power_up_sprite, y);
//     // //random velocity
//     // sprite_set_dx(result.power_up_sprite, rnd() * 4 - 2);

//     // return result;
// }

// void add_enemy(vector<enemy_data> &enemies)
// {
//     enemy_data enemy = new_enemy();

//     enemies.push_back(enemy);
// }

// void update_enemies(vector<enemy_data> &enemies_to_update)
// {
//     for(int i = 0; i < enemies_to_update.size(); i++)
//     {
//         update_sprite(enemies_to_update[i].enemy_sprite);
//     }
// }

// void draw_enemies(const vector<enemy_data> &enemies_to_draw)
// {
//     for(int i = 0; i < enemies_to_draw.size(); i++)
//     {
//         draw_sprite(enemies_to_draw[i].enemy_sprite);
//     }
// }