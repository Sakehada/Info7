#include "game.hpp"
#include "world.hpp"
#include "window.hpp"
#include "window_audio.hpp"
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
    Block* detect_x = &game->world->grid[getId(game->ball_x + game->direction[0], game->ball_y, game->world->width)];
    Block* detect_y = &game->world->grid[getId(game->ball_x, game->ball_y + game->direction[1], game->world->width)];
    switch(*detect_y){
        case Empty:
            return;
            break;
        case Lose:
            game->statut = GameOver;
            return;
            break;
        case Type1:         
        case Type2:
            game->direction[1] = -game->direction[1];
            *detect_y = Empty;
            if(game->direction[0] != 0 && (*detect_x == Type1 || *detect_y == Type2)){game->direction[0] = -game->direction[0]; *detect_x = Empty;}
            return;
            break;
        case Border:
            game->direction[1] = -game->direction[1];
            if(game->direction[0] != 0 && *detect_x == Border){game->direction[0] = -game->direction[0]; *detect_x = Empty;}
            return;
            break;
    }

    game->direction[1] = 1;

    if(*detect_x == game->racket_x - 1){
        game->direction[0] = -1;
        return;
    }
    if(*detect_x == game->racket_x + 1){
        game->direction[0] = 1;
        return;
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
        set_color(&window->foreground, &game->colors[game->world->grid[i]]);
        draw_fill_rectangle(window, i % game->world->width * case_sizeX, i / game->world->width * case_sizeY, case_sizeX, case_sizeY);
    }

    refresh_window(window);
    SDL_Delay(5000);
}

void move_racket(Game* game, int d){
    if(game->racket_x + 2 * d == Empty && game->statut == Play){
        game->racket_x += d;
    }
}