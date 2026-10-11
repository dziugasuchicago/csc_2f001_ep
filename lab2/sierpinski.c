#include <stdio.h>

int sort_get_index(float tab[], int top, float val)
{ for (int i = 0; i < top; i++) {
        if (tab[i] > val) {
            return i;
        }
    }
    return top;
}

void sort_insert_at(float tab[], int i, int top, float val)
{
    for (int j = top; j > i; j--) {
        tab[j] = tab[j - 1];
    }
    tab[i] = val;
}

void sort_insert(float tab[], int top, float val)
{
    int i = sort_get_index(tab, top, val);
    sort_insert_at(tab, i, top, val);
}

int nb_columns()
{
    return 32;
}

int nb_lines()
{
    return 16;
}

void grid_init(char grid[], char pixel)
{
    for (int i = 0; i < nb_lines() * nb_columns(); i++) {
        grid[i] = pixel;
    }
}

void grid_display(char grid[])
{
    for (int y = 0; y < nb_lines(); y++) {
        for (int x = 0; x < nb_columns(); x++) {
            printf("%c", grid[y * nb_columns() + x]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    char grid[nb_lines() * nb_columns()];
    grid_init(grid, '*');
    grid_display(grid);
}
