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
// Number of buckets in hash table 2^16
const unsigned int N = 65536;
typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
} node;
// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //lowercase word
    char lower_case[LENGTH + 1];
    //change word to all lower case letters
    for (int i = 0; i < strlen(word); i++)
    {
        lower_case[i] = tolower(word[i]);
    }
    //Find index of word
    int index = hash(lower_case);
    //Set pointer to the correct head in the hash table
    node *pointer = table[index];
    //Traverse the linked list
    while (pointer != NULL)
    {
        //Ignoring case, check if word matches
        if(strcasecmp(word, pointer->word) == 0)
        {
            return true;
        }
        pointer = pointer->next;
    }
    return false;
}
//* https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
// Hashes word to a number
unsigned int hash(const char *needs_hashing)
{
    // TODO
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % N;
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //OPEN Dictionary file successfully
    FILE *file_pointer =  fopen(dictionary, "r");
    if (file_pointer == NULL)
    {
        printf("Could not open file\n");
        return false;
    }
    //create an array to store words
    char word[LENGTH + 1];
    //Red through the file
    while (fscanf(file_pointer,"%s",word) != EOF)
    {
       fscanf(file_pointer,"%s",word);
       //allocate memory for node
       node *n = malloc(sizeof(node));
       if (n == NULL)
       {
          unload();
          return false;

       }
       //insert word in node
       strcpy(n->word,word);
       //get index for insertion
       int index = hash(n->word);
       //Insert in the correct linked list
       n->next = table[index];
       table[index] = n;
    }
    fclose(file_pointer);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //iterating over the heads in the hash table
    int total = 0;
    for (int i = 0; i < N; i++)
    {
     // set pointer to head of list
     node *pointer = table[i];
     // traverse list
     while (pointer != NULL)
     {
        total++;
        pointer = pointer->next;
     }
    }
    return total;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //iterate over the heads in the hash table
    for (int i = 0; i < N; i++)
    {
        node *pointer = table[i];
        //traverse the linked list
        while (pointer != NULL)
        {
           node *tmp = pointer;
           pointer = pointer->next;
           free(tmp);
        }
        free(pointer);
    }
    return false;
}