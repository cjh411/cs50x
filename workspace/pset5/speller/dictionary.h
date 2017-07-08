/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <string.h>
// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define DICTLEN 144000

typedef struct hash
{
    char value[LENGTH+2];
    struct hash *next;
}
hash;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

// int checkdict(void);
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

int hashfunc(const char* word);
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
