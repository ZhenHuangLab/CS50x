#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Loop through all candidates to find matching name
    for (int i = 0; i < candidate_count; i++)
    {
        // Found matching candidate name if the existing name equals to the given candidate's name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // update their index as this voter's preference at given rank
            preferences[voter][rank] = i;
            return true;
        }
    }

    // No matching candidate was found if we get here, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        // Initialize voted_rank with 0, the first rank this voter choose
        int voted_rank = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                // If corresponding candidate has not been eliminated,
                // set voted_rank to current rank and stop looping through ranks right away
                voted_rank = j;
                break;
            }
        }
        // count one ballot
        candidates[preferences[i][voted_rank]].votes++;
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Calculate how many votes one need to win the election
    int votes_thr = voter_count / 2;
    for (int i = 0; i < candidate_count; i++)
    {
        // If any candidate has more than half of the vote,
        // their name should be printed and the function should return true
        if (candidates[i].votes > votes_thr)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // Nobody has won the election yet
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialize minimum number of votes with the number of voters
    int min_votes = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop through the candidates who is still in the election
        if (!candidates[i].eliminated)
        {
            // Keep track of the minimum number of votes
            if (candidates[i].votes < min_votes)
            {
                min_votes = candidates[i].votes;
            }
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // As for candidates remaining in the election
        if (!candidates[i].eliminated)
        {
            // If there is any candidate whose number of votes is not equal to the minimum, the
            // election is not tied
            if (candidates[i].votes != min)
            {
                return false;
            }
        }
    }
    // If we get here, all candidates has the same number of votes.
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // For all candidates still in the election
        if (!candidates[i].eliminated)
        {
            // If one's votes number is equal to minimum, he should be eliminated from the election
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
}
