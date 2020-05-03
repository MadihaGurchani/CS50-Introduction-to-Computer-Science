/**
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 40001

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Djb2 function used -Source: http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *str)
{
    unsigned int hash = 5381;
    int c;

    // Iterate through the characters of string
    while ((c = *str++))
    {
        // Calculate (hash * 33) + c
        hash = ((hash << 5) + hash) + tolower(c);
    }

    return hash % N;
}

// Represents a hash table
node *table[N] = {NULL};

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open File successfully
    FILE *file_pointer = fopen(dictionary, "r");
    if (file_pointer == NULL)
    {
        unload();
        return false;
    }

    // Create character array for words
    char word[LENGTH + 1];

    // Insert the word in the hash table
    while (fscanf(file_pointer, "%s", word) != EOF)
    {
        // Get index
        unsigned int index = hash(word);

        // Allocate memory for a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            printf("No more memory\n");
            return false;
        }

        //Copy word to node
        strcpy(n -> word, word);

        // Point towards next node
        n -> next = table[index];
        table[index] = n;

    }
    fclose(file_pointer);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Total words
    int Total = 0;

    // Iterate over all the heads in hash table
    for (int i = 0; i < N; ++i)
    {
        node *temp = table[i];

        // Traverse the linked list
        while (temp != NULL)
        {
            Total++;
            temp = temp -> next;
        }
    }

    return Total;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Find index pointer of head in hash table
    unsigned int Index = hash(word);
    //Set pointer to index
    node *temp = table[Index];

    // Traverse the linked list
    while (temp != NULL)
    {
        // if words are similar ignoring case
        if (strcasecmp(temp -> word, word) == 0)
        {
            return true;
        }
        //else check next node
        temp = temp -> next;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Counter for checking if all buckets are checked
    int Total = 0;

    // Iterate over all the heads in hash table
    for (int i = 0; i < N; ++i)
    {
        node *temp = table[i];

        // Traverse over linked list
        while (table[i] != NULL)
        {
            temp = temp -> next;
            free(table[i]);
            table[i] = temp;
        }

        // Case when bucket is empty
        if (table[i] == NULL)
        {
            Total++;
        }
    }
    // Returns true if all buckets are NULL or free
    if (Total == N)
    {
        return true;
    }
    return false;
}