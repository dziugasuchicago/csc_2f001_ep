#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char* argv[]) 
{
    if (argc > 2)
    {
        printf("There should be only one argument\n");
        return 0;
    }

    else 
    {
        int read_sudoku(const char* path grids, grid01);
    }
}

int read_sudoku(const char* path, int grid[])
{
    int fd = open(path, O_RDONLY);
    ssize_t read(int fd, void* buf, size_t nbytes);
    read(fd, grid, 81 * sizeof(int));
    return 0;
}
