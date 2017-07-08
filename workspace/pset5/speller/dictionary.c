/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <cs50.h>
#include <ctype.h>
/**
 * Returns true if word is in dictionary else false.
 */

hash* hashtable[DICTLEN];
int dictcnt = 0;
bool loaded =  false;

bool check(const char *word)
{
    int len = strlen(word);
    char copy[len+1];
    for(int i = 0; i < len; i++){
        copy[i] = tolower(word[i]);
    }
    copy[len] = '\0';
    
    int hashkey = hashfunc(copy);
    hash* search  = hashtable[hashkey];
    if(search!=NULL){
        if (strcmp(search->value,copy)==0){
            return true;
        }else{
            while(search->next != NULL){
                if (strcmp(search->value,copy)==0){
                    return true;
                }
                search = search->next;
            
            }
        }
    }
    return false;
}


int hashfunc(const char* word)
{
    long hashkey = 0;
    int len = strlen(word);
    hashkey = toupper(word[0])-'A' ;
    for(int s = 1; s<len; s++){
        if(isalpha(word[s])){
        hashkey = ((tolower(word[s])-'a') + hashkey)*3 ;
        }else if(word[s]==96){
            hashkey = ((27) + hashkey)*3 ;
        }
    }
    return (int)(hashkey%DICTLEN);
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL){
        return false;
    }
    loaded = true;
    
    
    char* word;
    int* hashval;
    word = (char *)malloc(LENGTH+2);
    hashval = malloc(sizeof(int));

    while(fgets(word,LENGTH+2,(FILE*)dict)!=NULL){
        strtok(word, "\n");
        *hashval =  hashfunc(word);
        // *hashval = dictcnt;
        
        hash* word_input = malloc(sizeof(hash));

        if(word_input == NULL){
            printf("Out of Memory to allocate input word");
            return false;
        }
        strcpy(word_input->value,word);
        word_input->next = NULL;
        
        if(hashtable[*hashval] == NULL){
            hashtable[*hashval] = word_input;
        }
        else{
            hash* node  = hashtable[*hashval];
            while(node->next != NULL){
                node = node->next;
                //add code to check for same value
            }
            node->next = word_input;
        }
        dictcnt++;
    }
    free(word);
    free(hashval);
    return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{

    if (loaded == true){
        return dictcnt;
    }else{
        return 0;
    }
// return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    if(loaded == true){
        for(int i = 0; i <DICTLEN; i++){
            hash* temp = hashtable[i];
            
            while(temp!=NULL){
                hash* temp_follow = temp;
                temp = temp->next;
                free(temp_follow);
            }
        }
        return true;
    }
    
    return false;
}


