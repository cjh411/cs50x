#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]){
    
    if (argc == 1 || argc>2){
        return 1;
    }else{
        string keywrd = argv[1];
        printf("Plaintext: ");
        string inst = get_string();
        printf("Cipher Text: ");
        int n = 0;
        int keywrdlen = strlen(keywrd);
        int k = 0;
        int kwindex;
        while(inst[n] != '\0'){
            if (inst[n] >= 65 && inst[n] <=90){
                if(keywrdlen == 1){
                    kwindex = 0;
                }else{
                    kwindex = k%keywrdlen;  
                }
                printf("%c", 65+(((inst[n]+(toupper(keywrd[kwindex])%65))%65)%26));
                k++;
            }else if (inst[n] >= 97 && inst[n] <=122){
                if(keywrdlen == 1){
                    kwindex = 0;
                }else{
                    kwindex = k%keywrdlen;  
                }
                printf("%c", 97+(((inst[n]+(toupper(keywrd[kwindex])%65))%97)%26));
                k++;
            }else{
               printf("%c",inst[n]);
            }
            n++;
        }
        
    }
    printf("%s","\n");
    return 0;
}