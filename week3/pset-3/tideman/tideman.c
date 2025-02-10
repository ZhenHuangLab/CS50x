#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Name is a match for the name of a valid candidate
        if (strcmp(candidates[i], name) == 0)
        {
            // Update the ranks array
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Record the number of voters who prefer candidate i over j
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Add each pair of candidates to pairs, if one candidate is preferred over the other
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                // Update the global variable pair_count after adding pair
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort
    for (int i = 0; i < pair_count; i++)
    {
        // A flag to detect whether every element is in order
        bool swapped = true;

        for (int j = 0; j < pair_count - 1; j++)
        {
            // Calculate the strength of victory of current pair
            int winner_current = pairs[j].winner;
            int loser_current = pairs[j].loser;
            int strength_of_victory_current = preferences[winner_current][loser_current] -
                                              preferences[loser_current][winner_current];

            // Calculate the strength of victory of next pair
            int winner_next = pairs[j + 1].winner;
            int loser_next = pairs[j + 1].loser;
            int strength_of_victory_next =
                preferences[winner_next][loser_next] - preferences[loser_next][winner_next];

            // If the current strength is less than the next's, do swapping
            if (strength_of_victory_current < strength_of_victory_next)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
                swapped = true;
            }
            // If more or equal, do not need swapping
            else
            {
                swapped = false;
            }
        }

        // If every element does not need swapping now, we can break the loop
        if (!swapped)
        {
            break;
        }
    }
}

// Check if there's a cycle right now in graph recursively
bool has_cycle(int winner, int loser)
{
    // If we have found a path from loser to winner, we have a cycle
    if (winner == loser)
    {
        return true;
    }

    // Check all potential paths from loser to other candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If there's an edge from loser to i-th candidate
        if (locked[loser][i])
        {
            // see if there's an edge from winner to that candidate
            if (has_cycle(winner, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Temporarily add the edge
        locked[pairs[i].winner][pairs[i].loser] = true;

        // Check if this creates a cycle
        if (has_cycle(pairs[i].winner, pairs[i].loser))
        {
            // If it creates a cycle, remove the edge
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Record how many times the candidate has been beaten
    int beated_sum[candidate_count];

    for (int p = 0; p < candidate_count; p++)
    {
        // Initialize the list
        beated_sum[p] = 0;

        // Calculate how many times this candidate has been beaten by others
        for (int q = 0; q < candidate_count; q++)
        {
            beated_sum[p] += locked[q][p];
        }
    }

    // loop through the list and figure out who haven't been beaten by others yet, and he/they
    // should be winner(s)
    for (int k = 0; k < candidate_count; k++)
    {
        if (beated_sum[k] == 0)
        {
            printf("%s\n", candidates[k]);
        }
    }
}
