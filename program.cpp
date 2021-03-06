#include "splashkit.h"
#include "game_data.h"

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "dungeon_crawler.txt");
}

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Dungeon Crawler", 1200, 1392);
    
    load_resources();

    game_data game = new_game();

    while (not quit_requested())
    {
        // Handle input to adjust player movement
        process_events();

        handle_input(game.player_one, game.debug_mode);
        handle_input(game.player_two, game.debug_mode);

        for(int i = 0; i < game.level.level_enemies.size(); i++)
        {
            handle_enemy_behaviour(game.level.level_enemies[i], game.player_one);
        }

        update_game(game);

        draw_game(game);
    }

    return 0;
}
