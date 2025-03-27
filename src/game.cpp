#include "game.hpp"
struct Game;

void init_game(Game *game, string filename)
{
    game->world = new World;
    init_world_from_file(game->world, filename);
    game->racket_y = game->world->height - 2;
    game->racket_x = game->world->width / 2;
    game->racket_half_width = 3;
}

void move_ball(Game* game){
    int detect_x = game->ball_x + game->direction[0];
    int detect_y = game->ball_y + game->direction[1];
    if(game->direction[0] == 0){
        if(game->world->grid[getId(game->ball_x, detect_y, game->world->width)] == Border){
            game->direction[1] = - game->direction[1];
            return;
        }
        return;
    }
    if(game->world->grid[getId(game->ball_x, detect_y, game->world->width)] == Border){
        if(game->world->grid[getId(detect_x, game->ball_y, game->world->width)] == Border){
            game->direction[1] = -game->direction[1];
        }
        game->direction[0] = -game->direction[0];
    }
}

void change_statut(Statut* statut){
    switch(*statut){
        case Begin:
            *statut = Play;
            break;
        case Play:
            *statut = Pause;
            break;
        case Pause:
            *statut = Play;
            break;
        case Win:
        case GameOver:
            *statut = Begin;
            break;
    }
}

void display_game(Window *window, Game *game)
{
    clear_window(window);
    int case_sizeX = window->width / game->world->width;
    int case_sizeY = window->height / game->world->height;
    for (int i = 0; i < game->world->width * game->world->height; i++)
    {
        switch (game->world->grid[i])
        {
        case Empty:
            set_color(&window->foreground, &game->Empty);
            break;
        case Border:
            set_color(&window->foreground, &game->Border);
            break;
        case Type1:
            set_color(&window->foreground, &game->Type1);
            break;
        case Type2:
            set_color(&window->foreground, &game->Type2);
            break;
        case Lose:
            set_color(&window->foreground, &game->Lose);
            break;
        }
        draw_fill_rectangle(window, i % game->world->width * case_sizeX, i / game->world->width * case_sizeY, case_sizeX, case_sizeY);
    }
    set_color(&window->foreground, &game->racket_color);
    draw_fill_rectangle(window, case_sizeX * (game->racket_x - game->racket_half_width - 1), case_sizeY * (game->racket_y), case_sizeX * (game->racket_half_width * 2 + 1), 1 * case_sizeY);
    refresh_window(window);
    SDL_Delay(5000);
}
