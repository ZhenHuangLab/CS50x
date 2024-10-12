#include <cs50.h>
#include <stdio.h>

// declare the function
void print_rows(int bricks, int spaces);

int main(void)
{
    // prompt the user for the height of the pyramid
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // print the pyramid
    for (int i = 0; i < n; i++)
    {
        // print rows and spaces
        print_rows(i + 1, n - i - 1);
    }
}

void print_rows(int bricks, int spaces)
{
    // print spaces
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    // print bricks
    for (int j = 0; j < bricks; j++)
    {
        printf("#");
    }
    printf("\n");
}
