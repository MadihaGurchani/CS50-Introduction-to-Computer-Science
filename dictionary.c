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

// Djb2 hash function
// Modified to be case insensitive
// Source: http://www.cse.yorku.ca/~oz/hash.html
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
node *hashTable[N] = {NULL};

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1] = {0};

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Hash the word
        unsigned int hashValue = hash(word);

        // Allocate memory for a new node
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            unload();
            printf("\n\nLOG: messed up while mallocing newNode.\n\n");
            return false;
        }

        // Insert word to the newly created node
        strcpy(newNode -> word, word);

        // Prepend the node
        newNode -> next = hashTable[hashValue];
        hashTable[hashValue] = newNode;

    }

    // Close dictionary and success
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Word counter
    int wordCount = 0;

    // Iterate over all the buckets
    for (int i = 0; i < N; ++i)
    {
        node *temp = hashTable[i];

        // Iterate over each word in a bucket
        while (temp != NULL)
        {
            ++wordCount;
            temp = temp -> next;
        }
    }

    return wordCount;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash the word and store a pointer to the bucket
    unsigned int hashValue = hash(word);
    node *temp = hashTable[hashValue];

    // Compare each word in dictionary with the input word
    while (temp != NULL)
    {
        // If words are same (ignoring case) return true
        if (strcasecmp(temp -> word, word) == 0)
        {
            return true;
        }

        temp = temp -> next;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Counter for checking if all buckets are NULL or not
    int countBuckets = 0;

    // Iterate over all the buckets
    for (int i = 0; i < N; ++i)
    {
        node *temp = hashTable[i];

        // Free all the nodes in a bucket
        while (hashTable[i] != NULL)
        {
            temp = temp -> next;
            free(hashTable[i]);
            hashTable[i] = temp;
        }

        // if bucket is NULL then increment the counter
        if (hashTable[i] == NULL)
        {
            ++countBuckets;
        }
    }

    // return true if all buckets are NULL (or free)
    if (countBuckets == N)
    {
        return true;
    }

    return false;
}