/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

#define SIZE 10000

// Global variable to count size of dictionary
int word_count = 0;

// create node for a linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// create hashtable
node* hashtable[SIZE] = {NULL};

// create hash function 
// Credit for Hash function = Found a pdf on hash functions for strings on the Bourns College of engineering website computer science dept.
int hash(const char* word)
{
    int hash = 0;
    int n;
    for(int i = 0; word[i] != '\0'; i++)
    {
        // alphabet case
        if(isalpha(word[i]))
            n = word[i] - 'a' + 1;
        // comma case
        else
            n = 27;
        hash = ((hash << 3) + n) % SIZE;
    }

    return hash;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // creates a temp variable that stores a lower case version of the word
    char temp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
        temp[i] = tolower(word[i]);
    
    // add the null character
    temp[len] = '\0';
    
    // find what index of the arry the word should be in
    int index = hash(temp);
    
    // if hashtable is empty at index, return false
    if(hashtable[index] == NULL) 
    {
        return false;
    } 
    
    // create cursor to compare to word 
    node* cursor = hashtable[index];  
    
    // if hashtable is not empty at index, iterate though words and compare
    while(cursor != NULL)
    {
        if(strcmp(temp, cursor->word)== 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    // if you do not find a word, return false
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // opens dictionary
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
        return false;
    
    // create an array fro word to be stored in
    char word[LENGTH + 1];
    
    // scan through the file, loading each word into the hash table
    while(fscanf(file, "%s\n",word) != EOF)
    {
        // increment dictionary size
        word_count++;
        // allocate memory for new word
        node* newword = malloc(sizeof(node));
        // put wor in the new node
        strcpy(newword->word, word);
        
        // find what index of the array the word should go in
        int index = hash(word);
        
        // if hashtable is empty at index, insert
        if(hashtable[index] == NULL)
        {
            // insert as head of list
            hashtable[index] = newword;
            newword->next = NULL;
        }
        // if hashtable is not empty at index, append
        else
        {
            // insert node at head of list
            newword->next = hashtable[index];
            hashtable[index] = newword;
        }
    }
    // close file
    fclose(file);
    // return true if successful
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{ 
    // if dictionary is loaded, return number of words 
    if(word_count > 0)
    {
        return word_count;
    }
    // if dictionary has not been loaded, return 0
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // create a variable to go through index
    int index = 0;
    
    // iterate through entire hashtable array
    while(index < SIZE)
    {
        // if hashtable is empty at index, go to the next index
        if(hashtable[index] == NULL)
        {
            index++;
        }
        // if hashtable is not empty, iterate through nodes and start freeing
        else
        {
            while(hashtable[index] != NULL)
            {
                node* cursor = hashtable[index];
                hashtable[index] = cursor->next;
                free(cursor);
            }
            // once hashtable is empty at index, go to next index
            index++;
        }
    }
    // return true if successful
    return true;
}
