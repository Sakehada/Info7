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
    game->ball_x = game->racket_x;
    game->ball_y = game->racket_y - 1;
    game->ball_speed = 80;
    game->ball_dx = 0;
    game->ball_dy = -1;
    game->statut = Begin;
    game->score = 0;
    game->scrWin = 0;
    for (int i = 0; i < game->world->height * game->world->width; i++)
    {
        switch (game->world->grid[i])
        {
        case Type1:
            game->scrWin = game->scrWin + 1;
            break;
        case Type2:
            game->scrWin = game->scrWin + 2;
            break;
        default:
            break;
        }
    }
}

void move_ball(Window *window, Game *game)
{
    Block *detect_y = &game->world->grid[getId(game->ball_x, game->ball_y + game->ball_dy, game->world->width)];
    Block *detect_x = &game->world->grid[getId(game->ball_x + game->ball_dx, game->ball_y, game->world->width)];
    switch (*detect_y)
    {
    case Empty:
        break;
    case Lose:
        game->statut = GameOver;
        break;
    case Type1:
        game->ball_dy = -game->ball_dy;
        *detect_y = Empty;
        play(window->mixer, Break, 1500);
        game->score = game->score + 1;
        break;
    case Type2:
        game->ball_dy = -game->ball_dy;
        *detect_y = Type1;
        play(window->mixer, Break, 1500);
        game->score = game->score + 1;
        break;
    case Border:
        play(window->mixer, Bong, 500);
        game->ball_dy = -game->ball_dy;
        break;
    }

    switch (*detect_x)
    {
    case Empty:
        break;
    case Lose:
        game->statut = GameOver;
        return;
        break;
    case Type1:
    case Type2:
        play(window->mixer, Break, 500);
        game->ball_dx = -game->ball_dx;
        return;
        break;
    case Border:
        play(window->mixer, Bong, 500);
        game->ball_dx = -game->ball_dx;
        return;
        break;
    }

    if (game->racket_y == game->ball_y + game->ball_dy)
    {
        if (game->racket_x == game->ball_x)
        {
            game->ball_dy = -1;
        }
        else if (game->racket_x == game->ball_x - 1)
        {
            game->ball_dy = -1;
            game->ball_dx = 1;
        }
        else if (game->racket_x == game->ball_x + 1)
        {
            game->ball_dy = -1;
            game->ball_dx = -1;
        }
    }

    game->ball_x += game->ball_dx;
    game->ball_y += game->ball_dy;
}

void change_statut(Statut *statut)
{
    switch (*statut)
    {
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
        *statut = Begin;
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
        set_color(&window->foreground, 0, 0, 0, 250);
        draw_fill_rectangle(window, (i % game->world->width * case_sizeX), (i / game->world->width * case_sizeY), case_sizeX, case_sizeY);
        set_color(&window->foreground, &game->colors[game->world->grid[i]]);
        draw_fill_rectangle(window, (i % game->world->width * case_sizeX) - 1, (i / game->world->width * case_sizeY) - 1, case_sizeX - 1, case_sizeY - 1);
    }

    set_color(&window->foreground, 0, 0, 200, 255);

    for (int i = -1; i < 2; i++)
    {
        draw_fill_rectangle(window, (i + game->racket_x) * case_sizeX, game->racket_y * case_sizeY, case_sizeX, case_sizeY);
    }

    set_color(&window->foreground, 200, 200, 200, 255);
    draw_fill_rectangle(window, game->ball_x * case_sizeX, game->ball_y * case_sizeY, case_sizeX, case_sizeY);

    set_color(&window->foreground, 0, 0, 0, 255);
    set_color(&window->background, 255, 255, 255, 255);
    string scr = "Score:" + to_string(game->score);
    draw_text(window, scr, 0, 0);
    refresh_window(window);
}

void move_racket(Game *game, int d) // Mouvement de la raquette
{

    if (game->statut == Play || game->statut == Begin)
    {
        if (d > 0 && game->world->width > game->racket_x + d + game->racket_half_width - 1) // Si on veux aller a droite
        {
            game->racket_x += d;
        }
        else if (d < 0 && 0 < game->racket_x - d - game->racket_half_width) // Aller a gauche

        {
            game->racket_x += d;
        }

        if (game->statut == Begin)
        {
            game->ball_x = game->racket_x;
        }
    }
}

bool keyboard_event(Game *game, string pathMap) // regarde les actions du clavier
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_KEYDOWN)
        {
            SDL_KeyboardEvent key_event = event.key;
            switch (key_event.keysym.sym)
            {
            case SDLK_q: // pour quitter
                cout << "q" << endl;
                return true;
            case SDLK_r: // reset
                cout << "Reset" << endl;
                game->statut = Pause;
                init_game(game, pathMap);
                return false;
            case SDLK_SPACE: // Pause
                change_statut(&(game->statut));
                return false;
            case SDLK_RIGHT: // Deplacer la raquette
                move_racket(game, 1);
                return false;
            case SDLK_LEFT:
                move_racket(game, -1);
                return false;
            default:
                return false;
                break;
            }
        }
    }
    return false;
}