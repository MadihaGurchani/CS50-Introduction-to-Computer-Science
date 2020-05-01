// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

typedef struct node *node_make;
node_make node_producer(const char *key);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
     //check if dictionary file opened successfully
     FILE *file = fopen(dictionary,"r");
     if (file == NULL)
     {
        return false;
     }
    //
    char term[length + 1];
    while(fscanf(file, %s, term) != EOF)
    {
        node_make node = node_producer(term);
        hash(word)


    word++
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
//Node making machine
node_make node_producer
{
    node_make node = malloc(sizeof(struct(node)));
    strcpy(node->word, key);
    node->next = NULL;
    return node;
}




