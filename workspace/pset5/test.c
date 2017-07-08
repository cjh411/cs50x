


#include <stdbool.h>
#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>
// #include "dictionary.h"
#include <string.h>
#include <cs50.h>
#include <ctype.h>

#define DICTLEN 150000
// default dictionary
#define DICTIONARY "dictionaries/large"

int hashfunc(const char* word)
{
    long hashkey = 0;
    int len = strlen(word);
    hashkey = toupper(word[0])-'A' ;
    for(int s = 1; s<len; s++){
        if(isalpha(word[s])){
        hashkey = ((toupper(word[s])-'A') + hashkey)*3 ;
        }else if(word[s]==96){
            hashkey = ((27) + hashkey)*3 ;
        }
    }
    return (int)(hashkey%DICTLEN);
}

bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL){
        return false;
    }
    
    
    char* word;
    int* hashval;
    word = (char *)malloc(LENGTH+2);
    hashval = malloc(sizeof(int));
    fgets(word,LENGTH,(FILE*)dict);
    printf("initialized");
    while(fgets(word,LENGTH,(FILE*)dict)!=NULL){
        
        *hashval =  hashfunc(word);
        // *hashval = dictcnt;
        if(hashtable[*hashval] == NULL){
            hashtable[*hashval] = malloc(sizeof(hash));
            hashtable[*hashval]->value = malloc(LENGTH+2);
            strcpy(hashtable[*hashval]->value,word);
            printf("%i, %s",*hashval,word);
        }
        else{
            hash* node = malloc(sizeof(hash));
            if(node == NULL){
                printf("Out of Memory");
                return false;
            }else{
                hash* search = hashtable[*hashval];
                while(search->next != NULL){
                    search = search->next;
                }
                search->next = node;
                
            }
        }
        dictcnt++;
    }
    free(word);
    free(hashval);
    return true;
}

int main(void){
    printf("String input: \n");
    string tmp = get_string();
    
    printf("HashOut %i",hashfunc(tmp));
    
}