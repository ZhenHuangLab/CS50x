#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check_digits(string s);
char rotate_letter(char s, int key);

int main(int argc, string argv[])
{
    // make sure that the program only take one argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // make sure argv[1] is a digit
    if (check_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // convert argv[1] into an integer
    int key = atoi(argv[1]);

    // prompt the user for plaintext
    string plain_text = get_string("plaintext: ");

    // rotate every letter in plaintext
    int plain_text_len = strlen(plain_text);
    printf("ciphertext: ");
    for (int i = 0; i < plain_text_len; i++)
    {
        printf("%c", rotate_letter(plain_text[i], key));
    }
    printf("\n");
}

bool check_digits(string s)
{
    // check if argument contains only digit characters
    int s_len = strlen(s);
    bool flag = true;
    for (int i = 0; i < s_len; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            flag = false;
        }
    }
    return flag;
}

char rotate_letter(char s, int key)
{
    // Rotate the character if it's a letter
    if (isupper(s))
    {
        return (((s - 'A') + key) % 26 + 'A');
    }
    else if (islower(s))
    {
        return (((s - 'a') + key) % 26 + 'a');
    }
    else
    {
        return s;
    }
}
