#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Get key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];

    // Validate key
    // Check key length
    int key_len = strlen(key);

    if (key_len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int dist_alphabet_to_key[26];

    // Convert key to distance
    for (int i = 0; i < key_len; i++)
    {
        if (isupper(key[i]))
        {
            dist_alphabet_to_key[i] = key[i] - ('A' + i);
        }
        else if (islower(key[i]))
        {
            dist_alphabet_to_key[i] = key[i] - ('a' + i);
        }
        else
        {
            // Check for non-alphabetic characters
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // Check for repeated characters (case-insensitive)
    char key_upper[26];
    for (int i = 0; i < key_len; i++)
    {
        key_upper[i] = toupper(key[i]);
    }

    for (int i = 0; i < key_len; i++)
    {
        char current_char = key_upper[i];
        for (int j = i + 1; j < key_len; j++)
        {
            if (current_char == key_upper[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // Get plain text
    string plain_text = get_string("plaintext: ");
    int plain_text_len = strlen(plain_text);

    // Encipher
    printf("ciphertext: ");
    for (int i = 0; i < plain_text_len; i++)
    {
        // Print cipher text
        if (isupper(plain_text[i]))
        {
            printf("%c", plain_text[i] + dist_alphabet_to_key[plain_text[i] - 'A']);
        }
        else if (islower(plain_text[i]))
        {
            printf("%c", plain_text[i] + dist_alphabet_to_key[plain_text[i] - 'a']);
        }
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
}
