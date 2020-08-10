#include "splashkit.h"

struct player_data
{
    int health;
    bool is_alive;
    int x_coordinate;
    int y_coordinate;
    bitmap bmp;
    animation_script animation_script;
    animation walk;
    drawing_options draw_options;
};

player_data new_player()
{
    player_data player;

    player.health = 100;
    player.is_alive = true;
    player.x_coordinate = screen_width() / 2;
    player.y_coordinate = screen_height() / 2;
    player.bmp = load_bitmap("PlayerBmp", "player_sprite_sheet.png");
    player.animation_script = load_animation_script("PlayerAnimations", "player_animations.txt");
    player.walk = create_animation(player.animation_script, "WalkDown");
    player.draw_options = option_with_animation(player.walk);

    return player;
}

void handle_input(player_data &player)
{
    if (key_typed(UP_KEY))
    {
        // move_sprite(player, move_up);
        assign_animation(player.walk, "WalkUp");
    }
    else if (key_typed(LEFT_KEY))
    {
        // move_sprite(player, move_left);
        assign_animation(player.walk, "WalkLeft");
    }
    else if (key_typed(DOWN_KEY))
    {
        // move_sprite(player, move_down);
        assign_animation(player.walk, "WalkDown");
    }
    else if (key_typed(RIGHT_KEY))
    {
        // move_sprite(player, move_right);
        assign_animation(player.walk, "WalkRight");
    }
}

int main()
{
    window w = open_window("Animation Test", 500, 500);
    player_data player = new_player();
    bitmap_set_cell_details(player.bmp, 64, 64, 13, 21, 273); // cell width, height, cols, rows, count

    // Basic event loop
    while (!quit_requested())
    {
        clear_screen(COLOR_WHITE);

        // Draw the bitmap - using opt to link to animation
        draw_bitmap(player.bmp, player.x_coordinate, player.y_coordinate, player.draw_options);

        refresh_screen(60);

        // Update the animation
        update_animation(player.walk);

        process_events();

        // Switch animations
        handle_input(player);
    }
}
