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
    int winner; // id of the winner
    int loser; // id of the loser
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count = 0;
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
        // each candidate has a specific id
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
    // printf("Pair: %i\n", preferences[pairs[0].winner][pairs[0].loser]);
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // loop through each vote
    for (int id = 0; id < candidate_count; id ++)
    {
        if (strcmp(name, candidates[id]) == 0)
        {
            ranks[rank] = id;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // ranks i'th
    for (int i = 0; i < candidate_count; i ++)
    {
        // ranks j'th
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
            preferences[ranks[i]][ranks[j]] += 0;
        }
    }
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // candidate's i'th
    for (int i = 0; i < candidate_count; i++)
    {
        // candidate's j'th
        for (int j = 0; j < candidate_count; j++)
        {
            // prevent count 2 times
            if (i < j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count += 1;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count += 1;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int glory[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        glory[i] = preferences[winner][loser] - preferences[loser][winner];
        // loop through pairs have been looped before
        for (int j = 0; j < i; j++)
        {
            if (glory[j+1] > glory[j])
            {
                // pairs[pair_count] is a non used pair in loop, used in assigning pair between 3 pairs
                pairs[pair_count] = pairs[j+1]; //
                pairs[j+1] = pairs[j]; // push number bigger in front
                pairs[j] = pairs[pair_count]; // smaller number behind
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int source = pairs[0].winner;
    for (int i = 0; i < pair_count; i++)
    {
        int candidates_win = pairs[i].winner;
        int candidates_los = pairs[i].loser;
        locked[candidates_win][candidates_los] = true;
        // prevent cycle
        if (candidates_los == source)
        {
            int maybe_source = candidates_win;
            for (int j = 0; j < i; j++)
            {
                if (candidates_win == pairs[j].loser)
                {
                    locked[candidates_win][candidates_los] = false;
                    break;
                }
            }
            if (locked[candidates_win][candidates_los] == true)
            {
                source = maybe_source;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}
