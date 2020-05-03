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
// Number of buckets in hash table 2^16
const unsigned int N = 40001;
typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
} node;
// Hash table
node *table[N] = {NULL};

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
//Djb2 Hash Function used
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