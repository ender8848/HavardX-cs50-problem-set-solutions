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
}
pair;

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
bool check_cycle(bool c[MAX][MAX]);
int find_source(int ln, bool locked[MAX][MAX]);

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
        printf("vote%i\n", i + 1);

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

// Update ranks given a new vote, ci represents candidate index in array candidates
bool vote(int rank, string name, int ranks[])
{
    for (int ci = 0; ci < candidate_count; ci++)
    {
        if (strcmp(name, candidates[ci]) == 0)
        {
            ranks[rank] = ci;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
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
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
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
    int max = 0;
    int p = 0; // stand for position of max victory in pairs
    pair temp; //used to temporarily store position when swapping

    for (int i = 0; i < candidate_count - 1; i++)
    {
        p = i;
        max = preferences[pairs[p].winner][pairs[p].loser];
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > max)
            {
                max = preferences[pairs[j].winner][pairs[j].loser];
                p = j;
            }
        }

        // Swap
        temp.winner = pairs[p].winner;
        temp.loser = pairs[p].loser;
        pairs[p].winner = pairs[i].winner;
        pairs[p].loser = pairs[i].loser;
        pairs[i].winner = temp.winner;
        pairs[i].loser = temp.loser;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (check_cycle(locked))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

// check if there is a cycle in the lock_pairs
bool check_cycle(bool b[][MAX]) // retreieved from https://www.cnblogs.com/goodswarm/p/9799162.html
{
    bool c[candidate_count][candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            c[i][j] = b[i][j];
        }
    }

    for (int k = 0; k < candidate_count; k++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                c[i][j] = c[i][j] || (c[i][k] && c[k][j]);
            }
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (c[i][i] == 1)
        {
            return true;
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // find the source of locked
    // firstly, find any true point, and then trace back until there is no starting point
    int ln = pairs[0].winner;
    int col = pairs[0].loser;
    printf("Winner: %s\n", candidates[find_source(ln, locked)]);
}

int find_source(int ln, bool c[MAX][MAX])
{
    for (int k = 0; k < candidate_count; k++)
    {
        if (c[k][ln] == true)
        {
            return find_source(k, c);
        }
    }
    return ln;
}