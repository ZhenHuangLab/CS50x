#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get user's name
    string name = get_string("What's your name? ");
    // show your name on the screen
    printf("hello, %s\n", name);
}
