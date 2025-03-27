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
            }
        }
    }
}

void move_racket(Game *game, int d)
{
    if (d > 0)
        if (game->racket_x + d >= game.)
        {
        }
}

/*
void run(Window *window, Game *game)
{
    int case_sizeX = window->width / game->world->width;
    int case_sizeY = window->height / game->world->height;
    SDL_Event event;
    bool quit = 0; // variable pour quitter
    while (quit == 0)
    {
        while (SDL_PollEvent(&event) != 0) // Temps qa il y a un evenement
    }
}
*/