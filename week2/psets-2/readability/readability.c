#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void counter(int counter_array[], string text, int text_len);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Calculate the text length
    int text_len = strlen(text);

    // Initialize the array of letters' number, words' number and sentences' number
    int counter_array[] = {0, 1, 0};

    // Count the number of letters, words, and sentences in the text
    counter(counter_array, text, text_len);

    int letter_num = counter_array[0];
    int word_num = counter_array[1];
    int sentence_num = counter_array[2];

    // Compute the Coleman-Liau index
    float L = letter_num / (float) word_num * 100.0;
    float S = sentence_num / (float) word_num * 100.0;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Print the grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        int grade = (int) round(index);
        printf("Grade %i\n", grade);
    }
}

void counter(int counter_array[], string text, int text_len)
{
    // Go through all char in the text
    for (int i = 0; i < text_len; i++)
    {
        char j = text[i];
        if (isalpha(j))
        {
            // Letter number added by 1 if this char is in alphabet
            counter_array[0]++;
        }
        else if (isblank(j))
        {
            // Word number added by 1 if this char is space
            counter_array[1]++;
        }
        else if (j == '?' || j == '!' || j == '.')
        {
            // Sentence number added by 1 if this char is "?", "!", or "."
            counter_array[2]++;
        }
    }
}
