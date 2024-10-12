#include <cs50.h>
#include <stdio.h>

void print_rows_oneside(int bricks, int spaces);
void print_rows_otherside(int bricks, int spaces);

int main(void)
{
    // prompt the user for the height of the pyramid
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // print the pyramid
    for (int i = 0; i < n; i++)
    {
        // print rows and spaces
        print_rows_oneside(i + 1, n - i - 1);
        printf("  ");
        print_rows_otherside(i + 1, n - i - 1);
        printf("\n");
    }
}

void print_rows_oneside(int bricks, int spaces)
{
    // print spaces (one side)
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    // print bricks (one side)
    for (int j = 0; j < bricks; j++)
    {
        printf("#");
    }
}

void print_rows_otherside(int bricks, int spaces)
{
    // print bricks (otherside)
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}
