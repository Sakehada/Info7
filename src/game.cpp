#include "game.hpp"
#include "world.hpp"
#include "window.hpp"
#include "window_audio.hpp"
struct Game;

void init_game(Window* window, Game *game, string filename)
{
    game->world = new World;
    init_world_from_file(game->world, filename);
    game->racket_y = window->height / (game->world->height - 2);
    game->racket_x = window->width / 2;
    game->racket_half_width = 3;
    game->ball_x = game->racket_x;
    game->ball_y = game->racket_y - 1;
    game->ball_speed = 1;
    game->ball_dx = 0;
    game->ball_dy = -1;
    game->statut = Play;
}

void move_ball(Game* game){
    Block* detect_y = &game->world->grid[getId(game->ball_x, game->ball_y + game->ball_dy, game->world->width)];
    Block* detect_x = &game->world->grid[getId(game->ball_x + game->ball_dx, game->ball_y, game->world->width)];
    switch(*detect_y){
        case Empty:
            break;
        case Lose:
            game->statut = GameOver;
            return;
            break;
        case Type1:         
        case Type2:
            game->ball_dy = -game->ball_dy;
            *detect_y = Empty;         
            if(game->ball_dx != 0 && (*detect_x == Type1 || *detect_y == Type2)){game->ball_dx = -game->ball_dx; *detect_x = Empty;}
            return;
            break;
        case Border:
            game->ball_dy = -game->ball_dy;
            if(game->ball_dx != 0 && *detect_x != Empty){game->ball_dx = -game->ball_dx;}
            return;
            break;
    }
    
    if(game->racket_y == game->ball_y + game->ball_dy){
        if(game->racket_x == game->ball_x){game->ball_dy = -1;}
        else if(game->racket_x == game->ball_x - 1){game->ball_dy = -1;game->ball_dx = -1;}
        else if(game->racket_x == game->ball_x + 1){game->ball_dy = -1;game->ball_dx = 1;}
    }

    game->ball_x += game->ball_dx;
    game->ball_y += game->ball_dy;
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

    set_color(&window->foreground, 0, 0, 200, 255);

    for(int i = -1; i < 2; i++){
        draw_fill_rectangle(window, (i + game->racket_x) * case_sizeX, game->racket_y * case_sizeY, case_sizeX, case_sizeY);
    }

    set_color(&window->foreground, 200, 200, 200, 255);
    draw_fill_rectangle(window, game->ball_x * case_sizeX, game->ball_y * case_sizeY, case_sizeX, case_sizeY);

    refresh_window(window);
}

void move_racket(Game* game, int d){
    if(game->racket_x + 2 * d == Empty && game->statut == Play){
        game->racket_x += d;
    }
}

bool keyboard_event(Game *game)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_KEYDOWN)
        {
            SDL_KeyboardEvent key_event = event.key;
            switch (key_event.keysym.sym)
            {
            case SDLK_q:
                cout << "q" << endl;
                return true;
            case SDLK_r:
                cout << "r" << endl;
                return false;
            case SDLK_SPACE:
                cout << "Espace" << endl;
                return false;
            case SDLK_RIGHT:
                cout << "Right" << endl;
                return false;
            case SDLK_LEFT:
                cout << "Left" << endl;
                return false;
            default:
                return false;
                break;
            }
        }
    }
    return false;
}