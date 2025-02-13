// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Count words when loading dictionary
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain a hash value
    int hash_value = hash(word);

    // Access linked list at that index in the hash table
    node *list = table[hash_value];

    // Traverse linked list, looking for the word (strcasecmp)
    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        // If the word is found
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    // If no word is found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    // Check whether the file opened correctly
    if (source == NULL)
    {
        return false;
    }

    // Initialize the hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Buffer for reading words
    char word[LENGTH + 1];

    // Read each word from the file
    while (fscanf(source, "%s", word) != EOF)
    {
        // Create space for a new hash table node
        node *new_node = malloc(sizeof(node));

        // Check if memory is enough
        if (new_node == NULL)
        {
            fclose(source);
            return false;
        }

        new_node->next = NULL;

        // Copy the word into the new node using strcpy
        strcpy(new_node->word, word);

        // Hash the word to obtain its hash value
        int hash_value = hash(new_node->word);

        // Insert the new node into the hash table (using the index specified by its hash value)
        new_node->next = table[hash_value];
        table[hash_value] = new_node;

        // Update word count
        word_count++;

    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    else
    {
        return 0;
    }

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through the whole table
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *ptr = table[i];
            while (ptr != NULL)
            {
                node *tmp = ptr->next;
                free(ptr);
                ptr = tmp;
            }
        }
    }

    return true;
}
