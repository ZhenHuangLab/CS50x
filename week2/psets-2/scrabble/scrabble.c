#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string upper(string word, int word_len);
int calc_word_score(string word, int word_len);

// Initialize the list of points
const int points_list[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                           1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // Prompt for the user for two words
    string p1_word = get_string("Player 1: ");
    string p2_word = get_string("Player 2: ");
    int p1_word_len = strlen(p1_word);
    int p2_word_len = strlen(p2_word);

    // Convert both p1 and p2 words to uppercase
    string p1_word_upper = upper(p1_word, p1_word_len);
    string p2_word_upper = upper(p2_word, p2_word_len);

    // Compute the score of each word
    int p1_word_score = calc_word_score(p1_word, p1_word_len);
    int p2_word_score = calc_word_score(p2_word, p2_word_len);

    // Compare and print the winner
    if (p1_word_score == p2_word_score)
    {
        printf("Tie!\n");
    }
    else if (p1_word_score > p2_word_score)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

string upper(string word, int word_len)
{
    // Convert a word to uppercase
    for (int i = 0; i < word_len; i++)
    {
        word[i] = toupper(word[i]);
    }
    return word;
}

int calc_word_score(string word, int word_len)
{
    // Calculate the score of each word
    int score = 0;
    for (int i = 0; i < word_len; i++)
    {
        score += points_list[word[i] - 'A'];
    }
    return score;
}
