#include "world.hpp"

void init_world(World *world, int w, int h)
{
    world->height = h;
    world->width = w;
    world->grid = new Block[w * h];
    for (int i = 0; i < h * w; i++)
    {
        world->grid[i] = Empty;
    }
}

void free_world(World *world)
{
    delete[] world->grid;
}

Block read(World *world, int x, int y)
{

    int i = y * world->width + x;
    if (i < 0 or i > world->height * world->width)
    {
        cout << "Erreur de coordonnee" << endl;
        return Empty;
    }
    else
    {
        return world->grid[i];
    }
}

void write(World *world, int x, int y, Block b)
{
    int i = y * world->width + x;
    if (i < 0 or i > world->height * world->width)
    {
        cout << "Erreur de coordonnee" << endl;
        return;
    }
    else
    {
        world->grid[i] = b;
    }
}

void display(World *world)
{
    for (int i = 0; i < world->height * world->width; i++)
    {
        if (i != 0 && i % (world->width) == 0)
        {
            cout << endl;
        }
        switch (world->grid[i])
        {
        case Empty:
            cout << '.';
            break;
        case Border:
            cout << '#';
            break;
        case Lose:
            cout << '$';
            break;
        case Type1:
            cout << '1';
            break;
        case Type2:
            cout << '2';
            break;

        default:
            break;
        }
    }
    cout << endl;
}

int getId(int x, int y, int w)
{
    return y * w + x;
}

void init_world_from_file(World *world, string filename)
{

    ifstream fic(filename.c_str());
    if (fic)
    {
        fic >> world->width;
        fic >> world->height;

        init_world(world, world->width, world->height);
        string line;
        for (int i = 0; i < world->height; i++)
        {
            fic >> line;
            Block b;
            for (int k = 0; k < world->width; k++)
            {

                switch (line[k])
                {
                case '.':
                    b = Empty;
                    break;
                case '#':
                    b = Border;
                    break;
                case '$':
                    b = Lose;
                    break;
                case '1':
                    b = Type1;
                    break;
                case '2':
                    b = Type2;
                    break;
                }
                write(world, k, i, b);
            }
        }
    }
}